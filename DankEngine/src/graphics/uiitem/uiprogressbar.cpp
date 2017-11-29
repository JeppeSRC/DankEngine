#include "uiprogressbar.h"


namespace dank {

	UIProgressBar::UIProgressBar(const String& name, const vec2& position, const vec2& size, unsigned int completionColor)
		: UIItem(name, position, size), completionColor(completionColor) {

	}

	void UIProgressBar::OnRender(Renderer* renderer) {
		renderer->SubmitTopLeft(vec3(position), size, texture, color);
		CLAMP(completion, 0, 100);
		vec2 progressSize = vec2(size.GetX() / 100 * completion, size.GetY());
		renderer->SubmitTopLeft(vec3(position), progressSize, nullptr, completionColor);
	}

}
