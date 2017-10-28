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

	BatchRenderer* renderer;
	bool vaoe;
public:
	MainApp(ANativeActivity* activity) 
		: Application(activity) {
		Application::Set(this);
		
	}

	~MainApp() {
		delete renderer;
	}

	void Init() override {
		renderer = new BatchRenderer(30);
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glDisable(GL_BLEND);
	}

	void Render() override {
		renderer->Begin();
		renderer->Submit(vec3(0.3f, 0.9f, 0.0f), vec2(1.f, 1.f), 0xfffafd32);
		renderer->End();
		renderer->Present();
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
	app = new MainApp(activity);
	
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

	app->Start();
}