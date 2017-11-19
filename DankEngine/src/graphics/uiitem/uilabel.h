#pragma once

#include "uiitem.h"

namespace dank {

class UILabel : public UIItem {
protected:
	String content;

	Font* font;

	unsigned int contentColor;

public:
	UILabel(const String& name, const vec2& position, const String& content);

	virtual void OnRender(Renderer* renderer);

	virtual void SetContent(const String& content);
	virtual void SetFont(Font* font);

	inline void SetContentColor(unsigned int color) { this->contentColor = color; }

	inline const String& GetContent() const { return content; }
	
};

}