#pragma once
#include <android/input.h>
#include <jni.h>

#include <iostream>

#include "core/rtti.h"

#include "utils/log.h"


namespace dank {

#define MAX_KEYS 10000

	class InputComponent : public RTTI {
		RTTI_IMPLEMENTATION(InputComponent, RTTI);

	public:
		virtual void OnMove(float x, float y) = 0;
		virtual void OnPress(float x, float y) = 0;
		virtual void OnRelease(float x, float y) = 0;

		virtual void OnKeyPress(bool keys[]) = 0;
		virtual void OnKeyRelease(bool keys[]) = 0;
		virtual void OnKeyRepeat(bool keys[]) = 0;
	};

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