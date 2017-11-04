#include "application.h"

#include <unistd.h>
#include <ctime>
namespace dank {

	void* app_main(void*);
	void game_main();

	int OnGameInput(AInputEvent* event);

	Application* Application::application = nullptr;


	Application::~Application() {
		
	}

	void Application::OnDestroy(ANativeActivity* activity) {
		LOGW("OnDestroy");
		NativeApp::Destroy();
	}

	void Application::OnConfigurationChanged(ANativeActivity* activity) {
		LOGW("OnConfigurationChanged");
	}

	void Application::OnLowMemory(ANativeActivity* activity) {
		LOGW("OnLowMemory");
	}

	void Application::OnWindowFocusChanged(ANativeActivity* activity, int focus) {
		LOGW("OnWindowFocusChanged");
		write_cmd(focus ? CMD_ON_FOCUS : CMD_ON_FOCUS_LOST);
	}

	void Application::OnPause(ANativeActivity* activity) {
		LOGW("OnPause");
		write_cmd(CMD_ON_PAUSE);
	}

	void Application::OnResume(ANativeActivity* activity) {
		LOGW("OnResume");
		write_cmd(CMD_ON_RESUME);
	}

	void Application::OnStart(ANativeActivity* activity) {
		LOGW("OnStart");
		write_cmd(CMD_ON_START);
		
	}

	void Application::OnStop(ANativeActivity* activity) {
		LOGW("OnStop");
		write_cmd(CMD_ON_STOP);
	}

	void Application::OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
		LOGW("OnNativeWindowCreated");
		((NativeApp*)activity->instance)->window = window;
		write_cmd(CMD_WINDOW_CREATE);
	}

	void Application::OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
		LOGW("OnNativeWindowDestroyed");
		((NativeApp*)activity->instance)->window = nullptr;
		write_cmd(CMD_WINDOW_DESTROY);
	}
	
	void Application::OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
		LOGW("OnInputQueueCreated");
		NativeApp::app->inputQueue = queue;
		write_cmd(CMD_INPUT_CREATED);
	}

	void Application::OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
		LOGW("OnInputQueueDestroyed");
		write_cmd(CMD_INPUT_DESTROYED);
	}

	void Application::Start() {
		NativeApp::app->Start(app_main); 
	}

	void* app_main(void*) {
		NativeApp* app = NativeApp::app;

		app->looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

		ALooper_addFd(app->looper, app->msgRead, LOOPER_ID_CMD, ALOOPER_EVENT_INPUT, nullptr, (void*)app->cmd);

		app->OnInput = OnGameInput;

		pthread_mutex_lock(&app->mutex);
		app->status = 1;
		pthread_cond_broadcast(&app->cond);
		pthread_mutex_unlock(&app->mutex);

		game_main();

		return nullptr;
	}

	int OnGameInput(AInputEvent* event) {
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
			float x = AMotionEvent_getX(event, 0);
			float y = AMotionEvent_getY(event, 0);
			LOGD("X: %f Y: %f", x, y);
		}
	}

	void game_main() {
		NativeApp* app = NativeApp::app;

		int ident;
		int events;
		CMD_CALLBACK process_cmd = nullptr;

		while (!NativeApp::app->display) {
			while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&process_cmd)) >= 0) {
				if (process_cmd) process_cmd();
			}
		}

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		eglSwapInterval(app->display, 0);

		Application::Get()->Init();
		unsigned long long lastTime = mikrotime();

		while (app->status) {
			glClear(GL_COLOR_BUFFER_BIT);

			while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
				if (process_cmd) process_cmd();
			}

			unsigned long long now = mikrotime();
			float delta = ((float)(now - lastTime)) / (float)1000000;
			lastTime = now;

			Application::Get()->Update(delta);
			Application::Get()->Render();


			eglSwapBuffers(app->display, app->surface);
		}
		Application::Get()->End();

		DestroyDisplay();

	}

}