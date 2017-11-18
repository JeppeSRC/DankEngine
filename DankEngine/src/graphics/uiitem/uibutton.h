#pragma once

#include "uiitem.h"

namespace dank {

enum class BtnCallbackType {
	PRESS,
	RELEASE
};

typedef void(*FPBUTTONCALLBACK)(BtnCallbackType, const vec2&, void*);

class UIButton : public UIItem {
protected:
	String title;
	Font* font;

	vec2 titlePosition;

	unsigned int titleColor;

	FPBUTTONCALLBACK callback;

	void* callbackData;
public:
	UIButton(const String& name, const vec2& position, const vec2& size, FPBUTTONCALLBACK callback);

	virtual void OnRender(Renderer* renderer) override;

	virtual void OnPress(const vec2& point) override;
	virtual void OnRelease() override;

	inline void SetCallback(FPBUTTONCALLBACK callback, void* data) { this->callback = callback; this->callbackData = data; }
	void SetTitle(const String& title);
	inline void SetFont(Font* font) { this->font = font; }
	inline void SetTitleColor(unsigned int color) { this->titleColor = color; }

	inline const String& GetTitle() const { return title; }
	inline Font* GetFont() const { return font; }
	inline unsigned int GetTitleColor() const { return titleColor; }
};

}
