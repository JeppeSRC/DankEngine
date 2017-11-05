#include "inputmanager.h"
#include "core/nativeapp.h"

namespace dank {

	float InputManager::x;
	float InputManager::y;
	JNIEnv* InputManager::env = nullptr;
	jobject InputManager::inputmanager;
	jmethodID InputManager::toggleSoftInput;

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
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
			x = AMotionEvent_getX(event, 0);
			y = AMotionEvent_getY(event, 0);
		}
		x *= NativeApp::app->xUnitsPerPixel;
		y *= NativeApp::app->yUnitsPerPixel;
	}

	void InputManager::ShowKeyboard() {
		env->CallVoidMethod(inputmanager, toggleSoftInput, 2, 0);
	}

	void InputManager::HideKeyboard() {
		env->CallVoidMethod(inputmanager, toggleSoftInput, 0, 0);
	}
}