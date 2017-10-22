#pragma once
#include <android/native_activity.h>
#include <EGL/egl.h>
#include <mutex>

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

#include "utils/log.h"

namespace dank {
#	define CMD_WINDOW_CREATE		0x01
#	define CMD_WINDOW_DESTROY		0x02
#	define CMD_INPUT_CREATED		0x03
#	define CMD_INPUT_DESTROYED		0x04
#	define CMD_ON_START				0x05
#	define CMD_ON_STOP				0x06
#	define CMD_ON_PAUSE				0x07
#	define CMD_ON_RESUME			0x08
#	define CMD_ON_DESTROY			0x09
#	define CMD_ON_FOCUS				0x0A
#	define CMD_ON_FOCUS_LOST		0x0B

#	define APP_STATUS_TERMINATE		0x0
#	define APP_STATUS_RUNNING		0x1
#	define APP_STATUS_PAUSE			0x2

#	define LOOPER_ID_CMD			0x10
#	define LOOPER_ID_INPUT			0x11

	typedef void(*CMD_CALLBACK)();
	typedef int(*INPUT_CALLBACK)(AInputEvent*);


	enum GLES_VERSION {
		GLES_VERSION_2,
		GLES_VERSION_3
	};

	struct NativeApp {
	public:
		static NativeApp* app;

		static bool Intialize(ANativeActivity* activity);
		static void Destroy();

		static float GetAspectRatio() { return (float)app->surface_width / app->surface_height; }

	public:
		ANativeActivity* activity;
		ANativeWindow* window;

		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;

		int surface_width;
		int surface_height;

		int msgRead;
		int msgWrite;

		int status;

		pthread_mutex_t mutex;
		pthread_cond_t cond;

		pthread_t thread;

		CMD_CALLBACK cmd;
		CMD_CALLBACK input;

		INPUT_CALLBACK OnInput;

		ALooper* looper;
		AInputQueue* inputQueue;

		GLES_VERSION glesVersion;

	private:
		NativeApp(ANativeActivity* activity);
		~NativeApp();

	public:
		void Lock();
		void Unlock();

		void Start(void*(*startRoutine)(void*));
	};


	int read_cmd();
	void write_cmd(int cmd);
}