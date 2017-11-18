#include "uibutton.h"

namespace dank {

UIButton::UIButton(const String& name, const vec2& position, const vec2& size, FPBUTTONCALLBACK callback) : UIItem(name, position, size), title(title), callback(callback) {

}

void UIButton::OnPress(const vec2& point) {
	if (callback) callback(BtnCallbackType::PRESS, point, callbackData);
	else LOGD("[UIButton] Callback not set for %s Position: X=%f Y=%f", *name, point.x, point.y);
}

void UIButton::OnRelease() {
	if (callback) callback(BtnCallbackType::RELEASE, vec2(-1, -1), callbackData);
	else LOGD("[UIButton] callback not set for %s", *name);
}

void UIButton::OnRender(Renderer* renderer) {
	renderer->SubmitTopLeft(vec3(position), size, texture, color);
	renderer->Submit(title, font, position + titlePosition, titleColor);
}

void UIButton::SetTitle(const String& title) {
	this->title = title;

	vec2 metrics = font->GetMetrics(title);

	titlePosition = size * 0.5f; 
	titlePosition.x -= metrics.x * 0.5f;
	titlePosition.y += metrics.y * 0.5f;
}

}