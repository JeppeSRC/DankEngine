#include "uislider.h"

namespace dank {



UISlider::UISlider(const String& name, const vec2& position, const vec2& size, const vec2& handleSize) : UIItem(name, position, size), percent(0), handlePosition(0, size.y * 0.5f - handleSize.y * 0.5f), handleSize(handleSize), handleColor(0xFFFFFFFF), handleTexture(nullptr) {

}

void UISlider::OnPress(const vec2& point) {
	if (point.x > handlePosition.x && point.x < handlePosition.x + handleSize.x) {
		if (point.y > handlePosition.y & point.y < handlePosition.y + handleSize.y) {
			grabbed = point.x - handlePosition.x;
			return;
		}
	}

	grabbed = handleSize.x * 0.5f;
	handlePosition.x = point.x - grabbed;
}

void UISlider::OnMove(const vec2& point) {
	if (grabbed > -1.0f) {
		handlePosition.x = point.x - grabbed;

		if (handlePosition.x + handleSize.x > size.x) handlePosition.x = size.x - handleSize.x;
		else if (handlePosition.x < 0.0f) handlePosition.x = 0.0f;

		percent = handlePosition.x / size.x;
	}
}

void UISlider::OnRelease() {
	
}

void UISlider::OnRender(Renderer* renderer) {
	renderer->SubmitTopLeft(vec3(position), size, texture, color);
	renderer->SubmitTopLeft(vec3(position + handlePosition), handleSize, handleTexture, handleColor);

}

template<typename T>
void UISlider::Interpolate(T& other) const {
	other *= percent;
}

template void UISlider::Interpolate<float>(float&) const;
template void UISlider::Interpolate<double>(double&) const;
template void UISlider::Interpolate<vec2>(vec2&) const;
template void UISlider::Interpolate<vec3>(vec3&) const;
template void UISlider::Interpolate<vec4>(vec4&) const;

}