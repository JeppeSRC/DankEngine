#include "uijoystick.h"

namespace dank {

	UIJoystick::UIJoystick(const String& name, const vec2& position, const vec2& size, const vec2& innerSize)
		: UIItem(name, position, size), innerSize(innerSize) {
		innerPosition = vec2(position.x + (size.x - innerSize.x) / 2, position.y + (size.y - innerSize.y) / 2);
		centerPosition = innerPosition;
	}


	UIJoystick::~UIJoystick() {

	}

	void UIJoystick::OnMove(const vec2& point) {
		innerPosition = point + position - innerSize / 2;
		vec2 deltaPos = -(centerPosition - innerPosition);
		if (std::abs(deltaPos.x) > innerSize.x) {
			innerPosition.x = centerPosition.x + (std::abs(deltaPos.x) / deltaPos.x * innerSize.x);
		}
		if (std::abs(deltaPos.y) > innerSize.y) {
			innerPosition.y = centerPosition.y + (std::abs(deltaPos.y) / deltaPos.y * innerSize.y);
		}
	}

	void UIJoystick::OnRelease() {
		innerPosition = centerPosition;
	}

	void UIJoystick::OnRender(Renderer* renderer) {
		renderer->SubmitTopLeft(vec3(innerPosition), innerSize, texture, innerColor);
		renderer->SubmitTopLeft(vec3(position), size, texture, color);
	}

	void UIJoystick::OnUpdate(float delta) {
		vec2 offsets = -(centerPosition - innerPosition) / innerSize;
		if(offsets.x != 0 && offsets.y != 0)
			callback(offsets.x, offsets.y, callbackData);
	}

}