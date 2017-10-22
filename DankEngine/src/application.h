#pragma once
#include <android/native_activity.h>

namespace dank {
	class Application {
	private:
		ANativeActivity* activity;
		
	public:

		Application(ANativeActivity* activity, void* savedState, size_t savedStateSize);
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
	};
}