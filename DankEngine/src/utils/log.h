#pragma once
#include <android/log.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

namespace dank {
#ifdef _DEBUG
#define DBG(code) code
#define ASSERT(x) if (x) { LOGF("Assertion Failed: \"%s\" in \"%s:%u\"", #x, __FILE__, __LINE__); int* abcdefghijklmnopqrstuvwxyz123456789 = nullptr; *abcdefghijklmnopqrstuvwxyz123456789 = 1;}
#define ASSERT_MSG(x, msg) if (x) { LOGF("Assertion Failed: \"%s\" in \"%s:%u\" %s", #x, __FILE__, __LINE__, msg); int* abcdefghijklmnopqrstuvwxyz123456789 = nullptr; *abcdefghijklmnopqrstuvwxyz123456789 = 1;}
#define GL(func) func; GLCallLog(#func, __FILE__, __LINE__)
#define SL(func) SLCallLog(#func, func, __FILE__, __LINE__)
#define EGL(func) func; EGLCallLog(#func, __FILE__, __LINE__)
#define _EGL()  EGLCallLog("", __FILE__, __LINE__)

#else
#define ASSERT(x)
#define ASSERT_MSG(x, msg...)
#define DBG(code)
#define GL(func) func
#define SL(func) func
#define EGL(func) func
#define _EGL() 
#endif

#define LOGDEF(fmt...) __android_log_print(ANDROID_LOG_DEFAULT,   "DankEngine", fmt)
#define LOGD(fmt...)   __android_log_print(ANDROID_LOG_DEBUG,     "DankEngine", fmt)
#define LOGE(fmt...)   __android_log_print(ANDROID_LOG_ERROR,     "DankEngine", fmt)
#define LOGF(fmt...)   __android_log_print(ANDROID_LOG_FATAL,     "DankEngine", fmt)
#define LOGI(fmt...)   __android_log_print(ANDROID_LOG_INFO,      "DankEngine", fmt)
#define LOGS(fmt...)   __android_log_print(ANDROID_LOG_SILENT,    "DankEngine", fmt)
#define LOGU(fmt...)   __android_log_print(ANDROID_LOG_UNKNOWN,   "DankEngine", fmt)
#define LOGV(fmt...)   __android_log_print(ANDROID_LOG_VERBOSE,   "DankEngine", fmt)
#define LOGW(fmt...)   __android_log_print(ANDROID_LOG_WARN,      "DankEngine", fmt)

	inline void GLCallLog(const char* const func, const char* const file, int line) {
		unsigned int error = 0;
		while (error = glGetError()) {
			LOGF("[GL] Error %u calling %s in %s:%u", error, func, file, line);
		}
	}

	inline void EGLCallLog(const char* const func, const char* const file, int line) {
		unsigned int error = eglGetError();
		if(error != EGL_SUCCESS)
			LOGF("[EGL] Error %u calling %s in %s:%u", error, func, file, line);
	}

	inline void SLCallLog(const char* const func, SLresult result, const char* const file, int line) {
		if (result != SL_RESULT_SUCCESS) {
			LOGF("[SL] Error %u calling %s in %s:%u", result, func, file, line);
		}

	}

}