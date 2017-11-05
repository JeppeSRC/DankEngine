#pragma once
#include <android/native_activity.h>

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

#include <android/sensor.h>

#include "core/nativeapp.h"
#include "core/input/inputmanager.h"

#include <core/resource/resourcemanager.h>

#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexbuffer.h"
#include "graphics/buffers/vertexarray.h"

#include "graphics/shaders/shader.h"

#include "graphics/renderers/batchrenderer.h"

#include "maths/math.h"

#include "utils/utils.h"
#include "utils/list.h"
#include "utils/log.h"
#include "utils/string.h"
#include "utils/asset/fileutils.h"
#include "utils/memory/memory.h"

#define APP_START(x) static x *app = nullptr; \
static void OnConfigurationChanged(ANativeActivity* activity) { app->OnConfigurationChanged(activity); } \
static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueCreated(activity, queue); } \
static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) { app->OnInputQueueDestroyed(activity, queue); } \
static void OnLowMemory(ANativeActivity* activity) { app->OnLowMemory(activity); } \
static void OnWindowFocusChanged(ANativeActivity* activity, int focus) { app->OnWindowFocusChanged(activity, focus); } \
static void OnPause(ANativeActivity* activity) { app->OnPause(activity); } \
static void OnResume(ANativeActivity* activity) { app->OnResume(activity); } \
static void OnStart(ANativeActivity* activity) { app->OnStart(activity); } \
static void OnStop(ANativeActivity* activity) { app->OnStop(activity); } \
static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowCreated(activity, window); } \
static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) { app->OnNativeWindowDestroyed(activity, window); } \
static void OnDestroy(ANativeActivity* activity) { app->OnDestroy(activity); delete app; } \
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {  \
	app = new x(activity); \
	activity->callbacks->onConfigurationChanged = OnConfigurationChanged; \
	activity->callbacks->onDestroy = OnDestroy; \
	activity->callbacks->onInputQueueCreated = OnInputQueueCreated; \
	activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed; \
	activity->callbacks->onLowMemory = OnLowMemory; \
	activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated; \
	activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed; \
	activity->callbacks->onPause = OnPause; \
	activity->callbacks->onResume = OnResume; \
	activity->callbacks->onStart = OnStart; \
	activity->callbacks->onStop = OnStop; \
	activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged; \
	app->Start(); \
}

namespace dank {

	class Application {
	private:
		bool thingyIDontKnowWhatToName = false;
	public:
		static Application* application;
		static Application* Get() { return application; }
		static void Set(Application* application) { Application::application = application;  }

	protected:
		ANativeActivity* activity;
		float width;
		float height;

		ResourceManager* resourceManager;

	public:
		Application(ANativeActivity* activity, float width, float height)
			: width(width), height(height) {
			NativeApp::Initialise(activity);
			FileUtils::assetManager = activity->assetManager;
			resourceManager = new ResourceManager(nullptr);
		}

		virtual ~Application();

		virtual void OnDestroy(ANativeActivity* activity);

		virtual void OnConfigurationChanged(ANativeActivity* activity);
		
		virtual void OnLowMemory(ANativeActivity* activity);
		virtual void OnWindowFocusChanged(ANativeActivity* activity, int focus);

		virtual void OnPause(ANativeActivity* activity);
		virtual void OnResume(ANativeActivity* activity);

		virtual void OnStart(ANativeActivity* activity);
		virtual void OnStop(ANativeActivity* activity);

		virtual void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
		virtual void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);

		virtual void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
		virtual void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);

		virtual void Render() = 0;
		virtual void Update(float delta) = 0;

		void Start();

		virtual void Init() = 0;
		virtual void End() = 0;

		inline float GetGameWidth() { return width; }
		inline float GetGameHeight() { return height; }
		
	};
}