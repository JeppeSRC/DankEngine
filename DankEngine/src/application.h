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

#include "graphics/indexbuffer.h"
#include "graphics/vertexbuffer.h"
#include "graphics/shader.h"

#include "maths/math.h"

#include "utils/utils.h"
#include "utils/list.h"
#include "utils/log.h"
#include "utils/string.h"
#include "utils/asset/fileutils.h"
#include "utils/memory/memory.h"

namespace dank {

	class Application {
	public:
		static Application* application;
		static Application* Get() { return application; }
		static void Set(Application* application) { Application::application = application;  }
	private:
		ANativeActivity* activity;

	public:
		Application(ANativeActivity* activity) {
			NativeApp::Initialise(activity);
			FileUtils::assetManager = activity->assetManager;
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
		virtual void Update() = 0;

		void Start();

		virtual void Init() = 0;
	};
}