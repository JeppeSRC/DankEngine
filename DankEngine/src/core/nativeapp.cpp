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
		LOGD("Creating NativeApp");
		NativeApp::app = denew NativeApp(activity);
		return true;
	}

	void NativeApp::Destroy() {
		LOGD("Destroying NativeApp");
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
			LOGF("Failed to get pipes!");
			_exit(1);
		}

		cmd = process_command;
		input = process_input;
		OnInput = nullptr;
	}

	NativeApp::~NativeApp() {
		activity->instance = nullptr;

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

		app->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		if (eglInitialize(app->display, 0, 0) == 0) {
			LOGE("Failed to initialize egl display");
		}

		LOGD("EGL Version: %s", eglQueryString(app->display, EGL_VERSION));
		LOGD("EGL Vendor:  %s", eglQueryString(app->display, EGL_VENDOR));
		LOGD("EGL Extensions: %s", eglQueryString(app->display, EGL_EXTENSIONS));
		LOGD("EGL Client APIs: %s", eglQueryString(app->display, EGL_CLIENT_APIS));

		int num_configs;
		EGLConfig config;

		eglChooseConfig(app->display, attrib, &config, 1, &num_configs);

		int format;

		if (!eglGetConfigAttrib(app->display, config, EGL_NATIVE_VISUAL_ID, &format)) {
			LOGF("Failed to get config");
		}

		ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

		int context_attrib[]{
			EGL_CONTEXT_CLIENT_VERSION, 3,
			EGL_NONE
		};

		app->surface = eglCreateWindowSurface(app->display, config, app->window, nullptr);
		app->context = eglCreateContext(app->display, config, nullptr, context_attrib);

		if (!app->context) {
			LOGW("Failed to create OpenGL ES 3.x context! Falling back to 2.x.");

			context_attrib[1] = 2;

			app->context = eglCreateContext(app->display, config, nullptr, context_attrib);

			if (!app->context) {
				LOGE("Failed to create OpenGL ES 2.x context! Exiting....");
				_exit(2);
			}

			app->glesVersion = GLES_VERSION_2;
		}
		else {
			app->glesVersion = GLES_VERSION_3;
			app->hasVaos = true;
		}



		if (eglMakeCurrent(app->display, app->surface, app->surface, app->context) == 0) {
			LOGE("Failed to make context current!");
			_exit(2);
		}

		eglQuerySurface(app->display, app->surface, EGL_WIDTH, &app->surface_width);
		eglQuerySurface(app->display, app->surface, EGL_HEIGHT, &app->surface_height);

		GL(glViewport(0, 0, app->surface_width, app->surface_height));

		LOGD("OpenGL Version: %s", glGetString(GL_VERSION));
		LOGD("OpenGL Vendor: %s", glGetString(GL_VENDOR));
		LOGD("OpenGL Renderer: %s", glGetString(GL_RENDERER));
		LOGD("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

		LOGD("Surface: width=%d height=%d", app->surface_width, app->surface_height);
		char model_id[PROP_VALUE_MAX], manufacturer_id[PROP_VALUE_MAX], fingerprint_id[PROP_VALUE_MAX], brand_id[PROP_VALUE_MAX], device_id[PROP_VALUE_MAX];
		__system_property_get("ro.product.model", model_id);
		__system_property_get("ro.product.manufacturer", manufacturer_id);
		__system_property_get("ro.build.fingerprint", fingerprint_id);
		__system_property_get("ro.product.brand", brand_id);
		__system_property_get("ro.product.device", device_id);
		String model = String(model_id), manufacturer = String(manufacturer_id), fingerprint = String(fingerprint_id), brand = String(brand_id), device = String(device_id);
		LOGD("Model: %s", model.str);
		LOGD("Manufacturer: %s", manufacturer.str);
		LOGD("Fingerprint: %s", fingerprint.str);
		LOGD("Brand: %s", brand.str);
		LOGD("Device: %s", device.str);
		if (app->glesVersion != GLES_VERSION_3) {
			if (model.Find("google_sdk") != (size_t)-1
				|| model.Find("Emulator") != (size_t)-1
				|| model.Find("Android SDK built for x86") != (size_t)-1

				|| fingerprint.StartsWith("generic")
				|| fingerprint.StartsWith("unknown")
				
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

			unsigned int id;
			NativeApp::glGenVertexArraysOES(1, &id);
			LOGD("ID: %i", id);
		}
	}

	void DestroyDisplay() {
		NativeApp* app = NativeApp::app;
		if (app->window) {
			eglMakeCurrent(app->display, 0, 0, 0);
			if (app->context) {
				eglDestroyContext(app->display, app->context);
				app->context = nullptr;
			}

			if (app->surface) {
				eglDestroySurface(app->display, app->surface);
			}

			eglTerminate(app->display);
		}

		app->display = nullptr;
		app->context = nullptr;
		app->surface = nullptr;
	}

	void process_command() {
		int cmd = read_cmd();
		NativeApp* app = NativeApp::app;

		switch (cmd) {
		case CMD_WINDOW_CREATE:
			InitializeDisplay();
			break;
		case CMD_WINDOW_DESTROY:
			DestroyDisplay();
			break;
		case CMD_ON_START:
		case CMD_ON_RESUME:
			app->status = APP_STATUS_RUNNING;
			break;
		case CMD_ON_PAUSE:
		case CMD_ON_STOP:
			app->status = APP_STATUS_PAUSE;
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
		while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
			if (AInputQueue_preDispatchEvent(app->inputQueue, event)) continue;

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

		LOGE("No data in command pipe");
		return -1;
	}

	void write_cmd(int cmd) {
		if (write(NativeApp::app->msgWrite, &cmd, sizeof(int)) != sizeof(int)) {
			LOGE("Failed to write cmd!");
		}
	}

}