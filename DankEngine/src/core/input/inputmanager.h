#pragma once
#include <android/input.h>
#include <jni.h>

#include <iostream>

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

		static bool keys[MAX_KEYS];

	public:
		static void Init();

		static int OnGameInput(AInputEvent* event);

		static void ShowKeyboard();
		static void HideKeyboard();

		inline static float GetX() { return x; }
		inline static float GetY() { return y; }

		inline static bool GetKey(short key) { return keys[key]; }
		inline static void Update() {
			memset(keys, 0, MAX_KEYS);
		}
	};

}