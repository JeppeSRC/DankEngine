#include "uilabel.h"

namespace dank {

UILabel::UILabel(const String& name, const vec2& position, const String& content) : UIItem(name, position, vec2(0, 0)), font(FontManager::GetDefaultFont()) {
	SetContent(content);
}

void UILabel::OnRender(Renderer* renderer) {
	renderer->SubmitTopLeft(vec3(position), size, texture, color);
	renderer->Submit(content, font, position + vec2(2, size.y * 0.80f), contentColor);
}

void UILabel::SetContent(const String& content) {
	this->content = content;

	ASSERT(font == nullptr);

	size = font->GetMetrics(content);
	size.y *= 1.25f;
}

void UILabel::SetFont(Font* font) {
	this->font = font;

	SetContent(content);
}

}