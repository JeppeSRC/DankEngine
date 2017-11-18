#include "uibutton.h"

namespace dank {

UIButton::UIButton(const String& name, const vec2& position, const vec2& size, const String& title, FPBUTTONCALLBACK callback) : UIItem(name, position, size), title(title), callback(callback) {

}

void UIButton::OnPress(const vec2& point) {
	if (callback) callback(BtnCallbackType::PRESS, point, callbackData);
	else LOGD("[UIButton] Callback not set for %s Position: X=%f Y=%f", *name, point.x, point.y);
}

void UIButton::OnRelease() {
	if (callback) callback(BtnCallbackType::RELEASE, vec2(-1, -1), callbackData);
	else LOGD("[UIButton] callback not set for %s", *name);
}

}