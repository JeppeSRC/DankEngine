#include "nativeapp.h"

#include <unistd.h>

namespace dank {

	PFNGLGENVERTEXARRAYSOESPROC NativeApp::glGenVertexArraysOES;
	PFNGLBINDVERTEXARRAYOESPROC NativeApp::glBindVertexArrayOES;
	PFNGLDELETEVERTEXARRAYSOESPROC NativeApp::glDeleteVertexArraysOES;

	void process_command();
	void process_input();

	NativeApp* NativeApp::app = nullptr;

	bool NativeApp::Initialise(ANativeActivity* activity) {
		LOGD("[NativeApp] Creating NativeApp");
		NativeApp::app = denew NativeApp(activity);
		return true;
	}

	void NativeApp::Destroy() {
		LOGD("[NativeApp] Destroying NativeApp");
		delete NativeApp::app;
	}

	NativeApp::NativeApp(ANativeActivity* activity) {
		this->activity = activity;

		window = nullptr;

		surface_width = 0;
		surface_height = 0;

		display = nullptr;
		surface = nullptr;
		context = nullptr;

		activity->instance = this;

		pthread_mutex_init(&mutex, nullptr);
		pthread_cond_init(&cond, nullptr);

		if (pipe(&msgRead) != 0) {
			LOGF("[NativeApp] Failed to get pipes!");
			_exit(1);
		}

		cmd = process_command;
		input = process_input;
		OnInput = nullptr;
		
	}

	NativeApp::~NativeApp() {
		activity->instance = nullptr;

		pthread_join(thread, nullptr);
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);
	}

	void NativeApp::Lock() {
		pthread_mutex_lock(&mutex);
	}

	void NativeApp::Unlock() {
		pthread_mutex_unlock(&mutex);
	}

	void NativeApp::Start(void*(*startRoutine)(void*)) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		status = APP_STATUS_TERMINATE;
		pthread_create(&thread, &attr, startRoutine, nullptr);

		pthread_mutex_lock(&mutex);
		while (status != APP_STATUS_RUNNING)
			pthread_cond_wait(&cond, &mutex);
		pthread_mutex_unlock(&mutex);
	}

	void InitializeDisplay() {
		NativeApp* app = NativeApp::app;

		int num_configs;
		EGLConfig config;

		int attrib[]{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 0,
			EGL_NONE
		};

		if (app->display && app->context) {
			EGL(eglChooseConfig(app->display, attrib, &config, 1, &num_configs));

			app->surface = EGL(eglCreateWindowSurface(app->display, config, app->window, nullptr));
			if (eglMakeCurrent(app->display, app->surface, app->surface, app->context) == 0) {
				EGL((void)app->surface);
				LOGF("[NativeApp] Failed to make context current!");
				_exit(3);
			}

			return;
		}


		app->display = EGL(eglGetDisplay(EGL_DEFAULT_DISPLAY));

		if (eglInitialize(app->display, 0, 0) == 0) {
			EGL();
			LOGE("[NativeApp] Failed to initialize egl display");
		}

		LOGD("[NativeApp] EGL Version: %s", eglQueryString(app->display, EGL_VERSION));
		LOGD("[NativeApp] EGL Vendor:  %s", eglQueryString(app->display, EGL_VENDOR));
		LOGD("[NativeApp] EGL Extensions: %s", eglQueryString(app->display, EGL_EXTENSIONS));
		LOGD("[NativeApp] EGL Client APIs: %s", eglQueryString(app->display, EGL_CLIENT_APIS));

		eglChooseConfig(app->display, attrib, &config, 1, &num_configs);

		int format;

		if (!eglGetConfigAttrib(app->display, config, EGL_NATIVE_VISUAL_ID, &format)) {
			LOGF("[NativeApp] Failed to get config");
		}

		ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

		int context_attrib[]{
			EGL_CONTEXT_CLIENT_VERSION, 3,
			EGL_NONE
		};

		app->surface = EGL(eglCreateWindowSurface(app->display, config, app->window, nullptr));
		app->context = EGL(eglCreateContext(app->display, config, nullptr, context_attrib));

		if (!app->context) {
			LOGW("[NativeApp] Failed to create OpenGL ES 3.x context! Falling back to 2.x.");

			context_attrib[1] = 2;

			app->context = EGL(eglCreateContext(app->display, config, nullptr, context_attrib));

			if (!app->context) {
				LOGE("[NativeApp] Failed to create OpenGL ES 2.x context! Exiting....");
				_exit(2);
			}

			app->glesVersion = GLES_VERSION::GLES_VERSION_2;
		}
		else {
			app->glesVersion = GLES_VERSION::GLES_VERSION_3;
			app->hasVaos = true;
		}



		if (eglMakeCurrent(app->display, app->surface, app->surface, app->context) == 0) {
			LOGE("[NativeApp] Failed to make context current during initialization!");
			_exit(2);
		}

		eglQuerySurface(app->display, app->surface, EGL_WIDTH, &app->surface_width);
		eglQuerySurface(app->display, app->surface, EGL_HEIGHT, &app->surface_height);

		GL(glViewport(0, 0, app->surface_width, app->surface_height));
			  
		LOGD("[NativeApp] OpenGL Version: %s", glGetString(GL_VERSION));
		LOGD("[NativeApp] OpenGL Vendor: %s", glGetString(GL_VENDOR));
		LOGD("[NativeApp] OpenGL Renderer: %s", glGetString(GL_RENDERER));
		LOGD("[NativeApp] GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

		LOGD("[NativeApp] Surface: width=%d height=%d", app->surface_width, app->surface_height);
		char model_id[PROP_VALUE_MAX], manufacturer_id[PROP_VALUE_MAX], fingerprint_id[PROP_VALUE_MAX], brand_id[PROP_VALUE_MAX], device_id[PROP_VALUE_MAX];
		__system_property_get("ro.product.model", model_id);
		__system_property_get("ro.product.manufacturer", manufacturer_id);
		__system_property_get("ro.build.fingerprint", fingerprint_id);
		__system_property_get("ro.product.brand", brand_id);
		__system_property_get("ro.product.device", device_id);
		String model = String(model_id), manufacturer = String(manufacturer_id), fingerprint = String(fingerprint_id), brand = String(brand_id), device = String(device_id);
		LOGD("[NativeApp] Model: %s", model.str);
		LOGD("[NativeApp] Manufacturer: %s", manufacturer.str);
		LOGD("[NativeApp] Fingerprint: %s", fingerprint.str);
		LOGD("[NativeApp] Brand: %s", brand.str);
		LOGD("[NativeApp] Device: %s", device.str);
		if (app->glesVersion != GLES_VERSION::GLES_VERSION_3) {
			if (model.Find("google_sdk") != (size_t)-1
				|| model.Find("Emulator") != (size_t)-1
				|| model.Find("Android SDK built for x86") != (size_t)-1

				|| fingerprint.StartsWith("generic")
				|| fingerprint.StartsWith("unknown")
				|| manufacturer.StartsWith("unknown")
				|| device.StartsWith("generic")
				|| (brand.Find("generic") != (size_t)-1 && device.Find("generic") != (size_t)-1)
				) {
				app->isEmulator = true;
			}
			else {
				NativeApp::glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
				NativeApp::glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
				NativeApp::glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
				if (!NativeApp::glGenVertexArraysOES || !NativeApp::glBindVertexArrayOES || !NativeApp::glDeleteVertexArraysOES)
					app->hasVaos = false;
				else
					app->hasVaos = true;

			}
		}
		else {
			NativeApp::glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArrays");
			NativeApp::glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArray");
			NativeApp::glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArrays");
		}
		EGL();
	}

	void DestroyDisplay(bool fuck_everything) {
		NativeApp* app = NativeApp::app;
		if (app->window) {
			EGL(eglMakeCurrent(app->display, 0, 0, 0));
			if (app->context && fuck_everything) {
				EGL(eglDestroyContext(app->display, app->context));
				app->context = nullptr;
			}

			if (app->surface) {
				EGL(eglDestroySurface(app->display, app->surface));
				app->surface = nullptr;
			}

			if (fuck_everything) {
				EGL(eglTerminate(app->display));
				app->display = nullptr;
			}
		}

		app->window = nullptr;

		if (fuck_everything) LOGD("[NativeApp] Destroyed display, contex and surface!");
		else LOGD("[NativeApp] Destroyed surface!");
	}

	void process_command() {
		int cmd = read_cmd();
		NativeApp* app = NativeApp::app;

		switch (cmd) {
		case CMD_WINDOW_CREATE:
			InitializeDisplay();
			app->shouldClose = false;
			break;
		case CMD_WINDOW_DESTROY:
			DestroyDisplay(false);
			//app->shouldClose = true;
			app->status = APP_STATUS_PAUSE;
			break;
		case CMD_ON_START:
		case CMD_ON_RESUME:
			app->status = APP_STATUS_RUNNING;
			break;
		case CMD_ON_PAUSE:
		case CMD_ON_STOP:
			app->status = APP_STATUS_PAUSE;
			break;
		case CMD_ON_DESTROY:
			app->status = APP_STATUS_TERMINATE;
			break;
		case CMD_INPUT_CREATED:
			AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, 0, (void*)app->input);
			break;
		case CMD_INPUT_DESTROYED:
			AInputQueue_detachLooper(app->inputQueue);
			app->inputQueue = nullptr;
			break;
		}
	}

	void process_input() {
		NativeApp* app = NativeApp::app;
		AInputEvent* event = nullptr;
		if (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
			if (AInputQueue_preDispatchEvent(app->inputQueue, event)) return;

			int h = 0;
			if (app->OnInput) h = app->OnInput(event);
			AInputQueue_finishEvent(app->inputQueue, event, h);
		}

	}

	int read_cmd() {
		int cmd = 0;
		if (read(NativeApp::app->msgRead, &cmd, sizeof(int)) == sizeof(int)) {
			return cmd;
		}

		LOGE("[NativeApp] No data in command pipe");
		return -1;
	}

	void write_cmd(int cmd) {
		if (write(NativeApp::app->msgWrite, &cmd, sizeof(int)) != sizeof(int)) {
			LOGE("[NativeApp] Failed to write cmd!");
		}
	}

}