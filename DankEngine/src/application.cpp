#include "application.h"

#include <unistd.h>
#include <ctime>
namespace dank {

	void* app_main(void*);
	void game_main();

	Application* Application::application = nullptr;


	Application::~Application() {
		
	}

	void Application::OnDestroy(ANativeActivity* activity) {
		LOGW("[Application] OnDestroy");
		write_cmd(CMD_ON_DESTROY);
		NativeApp::Destroy();
	}

	void Application::OnConfigurationChanged(ANativeActivity* activity) {
		LOGW("[Application] OnConfigurationChanged");
	}

	void Application::OnLowMemory(ANativeActivity* activity) {
		LOGW("[Application] OnLowMemory");
	}

	void Application::OnWindowFocusChanged(ANativeActivity* activity, int focus) {
		LOGW("[Application] OnWindowFocusChanged");
		write_cmd(focus ? CMD_ON_FOCUS : CMD_ON_FOCUS_LOST);
	}

	void Application::OnPause(ANativeActivity* activity) {
		LOGW("[Application] OnPause");
		write_cmd(CMD_ON_PAUSE);
	}

	void Application::OnResume(ANativeActivity* activity) {
		LOGW("[Application] OnResume");
		write_cmd(CMD_ON_RESUME);
	}

	void Application::OnStart(ANativeActivity* activity) {
		LOGW("[Application] OnStart");
		write_cmd(CMD_ON_START);
		
	}

	void Application::OnStop(ANativeActivity* activity) {
		LOGW("[Application] OnStop");
		write_cmd(CMD_ON_STOP);
	}

	void Application::OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
		LOGW("[Application] OnNativeWindowCreated");
		((NativeApp*)activity->instance)->window = window;
		write_cmd(CMD_WINDOW_CREATE);
	}

	void Application::OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
		LOGW("[Application] OnNativeWindowDestroyed");
		write_cmd(CMD_WINDOW_DESTROY);
	}
	
	void Application::OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
		LOGW("[Application] OnInputQueueCreated");
		NativeApp::app->inputQueue = queue;
		write_cmd(CMD_INPUT_CREATED);
	}

	void Application::OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
		LOGW("[Application] OnInputQueueDestroyed");
		thingyIDontKnowWhatToName = false;
		write_cmd(CMD_INPUT_DESTROYED);
	}

	void Application::Start() {
		NativeApp::app->Start(app_main); 
	}

	void* app_main(void*) {
		NativeApp* app = NativeApp::app;

		app->looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

		ALooper_addFd(app->looper, app->msgRead, LOOPER_ID_CMD, ALOOPER_EVENT_INPUT, nullptr, (void*)app->cmd);

		app->OnInput = InputManager::OnGameInput;

		pthread_mutex_lock(&app->mutex);
		app->status = 1;
		pthread_cond_broadcast(&app->cond);
		pthread_mutex_unlock(&app->mutex);

		game_main();

		return nullptr;
	}

	void game_main() {
		NativeApp* app = NativeApp::app;

		int ident;
		int events;
		CMD_CALLBACK process_cmd = nullptr;

		while (!app->display) {
			while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&process_cmd)) >= 0) {
				if (process_cmd) process_cmd();
			}
		}

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		EGL(eglSwapInterval(app->display, 0));

		app->xUnitsPerPixel = Application::Get()->GetGameWidth() / (float)app->surface_width;
		app->yUnitsPerPixel = Application::Get()->GetGameHeight() / (float)app->surface_height;

		InputManager::Init();

		AudioManager::Init();

		Application::Get()->Init();
		unsigned long long lastTime = mikrotime();
		while (app->status) {
			glClear(GL_COLOR_BUFFER_BIT);

			while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
				if (process_cmd) process_cmd();

				while (!app->display) {
					while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&process_cmd)) >= 0) {
						if (process_cmd) process_cmd();
					}
				}
			}

			unsigned long long now = mikrotime();
			float delta = ((float)(now - lastTime)) / (float)1000000;
			lastTime = now;

			Application::Get()->Update(delta);
			InputManager::Update();
			Application::Get()->Render();


			eglSwapBuffers(app->display, app->surface);
		}

		Application::Get()->End();

		AudioManager::Destroy();

		DestroyDisplay(true);

	}

}