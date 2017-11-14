#pragma once
#include <android/input.h>
#include <jni.h>

#include <iostream>

#include "core/rtti.h"

#include "utils/log.h"


namespace dank {

#define MAX_KEYS 10000

	class EventListenerComponent : public RTTI {
		RTTI_IMPLEMENTATION(EventListenerComponent, RTTI);

	public:
		virtual void OnMove(float x, float y) {}
		virtual void OnPress(float x, float y) {}
		virtual void OnRelease(float x, float y) {}

		virtual void OnKeyPress(int key) {}
		virtual void OnKeyRelease(int key) {}
		virtual void OnKeyRepeat(int key) {}
	};

	class InputManager {
	private:
		static float x;
		static float y;

		static JNIEnv* env;
		static jobject inputmanager;
		static jmethodID toggleSoftInput;

		static List<EventListenerComponent*> eventListeners;

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

		inline static void AddEventListener(EventListenerComponent* eventListener) {
			eventListeners.Push_back(eventListener);
		}

		inline static void RemoveEventListener(EventListenerComponent* eventListener) {
			eventListeners.Remove(eventListener);
		}


	};

}