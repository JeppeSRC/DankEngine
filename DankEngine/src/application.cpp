#include "application.h"

#include <unistd.h>
#include <ctime>
namespace dank {

	void* app_main(void*);
	void game_main();

	int OnGameInput(AInputEvent* event);

	Application* Application::application = nullptr;

	Application::Application(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
		NativeApp::Intialize(activity);
	}


	Application::~Application() {
		
	}

	void Application::OnDestroy(ANativeActivity* activity) {
		NativeApp::Destroy();
	}

	void Application::OnConfigurationChanged(ANativeActivity* activity) {

	}

	void Application::OnLowMemory(ANativeActivity* activity) {

	}

	void Application::OnWindowFocusChanged(ANativeActivity* activity, int focus) {

	}

	void Application::OnPause(ANativeActivity* activity) {
		write_cmd(CMD_ON_PAUSE);
	}

	void Application::OnResume(ANativeActivity* activity) {
		write_cmd(CMD_ON_RESUME);
	}

	void Application::OnStart(ANativeActivity* activity) {
		write_cmd(CMD_ON_START);
		
	}

	void Application::OnStop(ANativeActivity* activity) {
		write_cmd(CMD_ON_STOP);
	}

	void Application::OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
		((NativeApp*)activity->instance)->window = window;
		write_cmd(CMD_WINDOW_CREATE);
	}

	void Application::OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
		((NativeApp*)activity->instance)->window = nullptr;
		write_cmd(CMD_WINDOW_DESTROY);
	}
	
	void Application::OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {

	}

	void Application::OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {

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

	}

	void game_main() {
		NativeApp* app = NativeApp::app;

		int ident;
		int events;
		CMD_CALLBACK process_cmd;

		glDisable(GL_DEPTH_TEST);

		eglSwapInterval(app->display, 0);
		while (app->status) {
			glClear(GL_COLOR_BUFFER_BIT);

			while ((ident = ALooper_pollAll(app->status == 2 ? -1 : 0, nullptr, &events, (void**)&process_cmd)) >= 0) {
				if (ident == LOOPER_ID_CMD) process_cmd();
			}

			Application::Get()->Update();
			Application::Get()->Render();


			eglSwapBuffers(app->display, app->surface);
		}

	}

}