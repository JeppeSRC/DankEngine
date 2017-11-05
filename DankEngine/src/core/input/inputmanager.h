#pragma once
#include <android/input.h>
#include <jni.h>

#include "utils/log.h"
namespace dank {

	class InputManager {
	private:
		static float x;
		static float y;

		static JNIEnv* env;
		static jobject inputmanager;
		static jmethodID toggleSoftInput;
	public:
		static void Init();

		static int OnGameInput(AInputEvent* event);

		static void ShowKeyboard();
		static void HideKeyboard();

	};

}