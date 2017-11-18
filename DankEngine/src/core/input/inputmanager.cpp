#include "inputmanager.h"
#include "core/nativeapp.h"

namespace dank {

	float InputManager::x;
	float InputManager::y;
	JNIEnv* InputManager::env = nullptr;
	jobject InputManager::inputmanager;
	jmethodID InputManager::toggleSoftInput;

	List<EventListenerComponent*> InputManager::eventListeners;

	bool InputManager::keys[MAX_KEYS];



	void InputManager::Init() {
		NativeApp* app = NativeApp::app;
		app->activity->vm->AttachCurrentThread(&env, NULL);

		jclass nativeclass = env->GetObjectClass(app->activity->clazz);
		jmethodID method = env->GetMethodID(nativeclass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
		char inputMethodString[] = "input_method";
		jstring string = env->NewStringUTF(inputMethodString);
		inputmanager = env->CallObjectMethod(app->activity->clazz, method, string);
		jclass inputmanagerclass = env->FindClass("android/view/inputmethod/InputMethodManager");
		toggleSoftInput = env->GetMethodID(inputmanagerclass, "toggleSoftInput", "(II)V");
	}

	int InputManager::OnGameInput(AInputEvent* event) {
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
			int code = AKeyEvent_getKeyCode(event);
			keys[code] = true;

			switch (AKeyEvent_getAction(event)) {
			case AKEY_EVENT_ACTION_UP:
				for(size_t i=0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnKeyRelease(code);
				break;
			case AKEY_EVENT_ACTION_DOWN:
				for (size_t i = 0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnKeyPress(code);
				break;
			case AKEY_EVENT_ACTION_MULTIPLE:
				for (size_t i = 0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnKeyRepeat(code);
				break;
			}
			return 1;
		}
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
			x = AMotionEvent_getX(event, 0) * NativeApp::app->xUnitsPerPixel;
			y = AMotionEvent_getY(event, 0) * NativeApp::app->yUnitsPerPixel;
			
			int e = AMotionEvent_getAction(event);

			switch (e) {
			case AMOTION_EVENT_ACTION_MOVE:
				for (size_t i = 0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnMove(x, y);
				break;
			case AMOTION_EVENT_ACTION_DOWN:
				for (size_t i = 0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnPress(x, y);
				break;
			case AMOTION_EVENT_ACTION_UP:
				for (size_t i = 0; i < eventListeners.GetSize(); i++)
					eventListeners[i]->OnRelease(x, y);
				break;
			}

			return 1;
		}
		return 0;
	}

	void InputManager::ShowKeyboard() {
		env->CallVoidMethod(inputmanager, toggleSoftInput, 2, 0);
	}

	void InputManager::HideKeyboard() {
		env->CallVoidMethod(inputmanager, toggleSoftInput, 0, 0);
	}
}