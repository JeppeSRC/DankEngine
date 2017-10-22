#include <application.h>

using namespace dank;

class MainApp : public Application {
private:

public:
	MainApp(ANativeActivity* activity, void* savedState, size_t savedStateSize)
		: Application(activity, savedState, savedStateSize) {

	}

	~MainApp() {

	}


};

static MainApp *app = nullptr;


static void OnConfigurationChanged(ANativeActivity* activity) { app->OnConfigurationChanged(activity); }

static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueCreated(activity, queue); }
static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueDestroyed(activity, queue); }

static void OnLowMemory(ANativeActivity* activity) { app->OnLowMemory(activity); }
static void OnWindowFocusChanged(ANativeActivity* activity, int focus) { app->OnWindowFocusChanged(activity, focus); }

static void OnPause(ANativeActivity* activity) { app->OnPause(activity); }
static void OnResume(ANativeActivity* activity) { app->OnResume(activity); }

static void OnStart(ANativeActivity* activity) { app->OnStart(activity); }
static void OnStop(ANativeActivity* activity) { app->OnStop(activity); }

static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowCreated(activity, window); }
static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowDestroyed(activity, window); }

static void OnDestroy(ANativeActivity* activity) { app->OnDestroy(activity); delete app; }

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
	app = new MainApp(activity, savedState, savedStateSize);

	activity->callbacks->onConfigurationChanged = OnConfigurationChanged;
	activity->callbacks->onDestroy = OnDestroy;
	activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;
	activity->callbacks->onLowMemory = OnLowMemory;
	activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
	activity->callbacks->onPause = OnPause;
	activity->callbacks->onResume = OnResume;
	activity->callbacks->onStart = OnStart;
	activity->callbacks->onStop = OnStop;
	activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged;
}