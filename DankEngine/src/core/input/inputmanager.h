#pragma once
#include <android/input.h>
#include <jni.h>

#include "utils/log.h"
namespace dank {

#define MAX_KEYS 10000

	class InputManager {
	private:
		static float x;
		static float y;

		static JNIEnv* env;
		static jobject inputmanager;
		static jmethodID toggleSoftInput;

		static int keys[MAX_KEYS];

	public:
		static void Init();

		static int OnGameInput(AInputEvent* event);

		static void ShowKeyboard();
		static void HideKeyboard();

		inline static float GetX() { return x; }
		inline static float GetY() { return y; }

	};

}