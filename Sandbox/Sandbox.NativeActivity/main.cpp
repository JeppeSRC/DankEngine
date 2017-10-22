#include <application.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

using namespace dank;

class MainApp : public Application {
private:
	float r = 0, g = 0 , b = 0;
public:
	MainApp(ANativeActivity* activity, void* savedState, size_t savedStateSize)
		: Application(activity, savedState, savedStateSize) {
		Application::Set(this);
		Start();
	}

	~MainApp() {

	}

	void Render() override {
		if (r > 1.0)
			r = 0;
		if (g > 1.0) {
			r += 0.01f;
			g = 0;
		}
		if (b > 1.0) {
			g += 0.01f;
			b = 0;
		}
		b += 0.01f;

		glClearColor(r, g, b, 1.0f);
	}

	void Update() override {

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