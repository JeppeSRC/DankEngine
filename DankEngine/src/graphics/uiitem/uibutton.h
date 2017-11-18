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

	FPBUTTONCALLBACK callback;

	void* callbackData;
public:
	UIButton(const String& name, const vec2& position, const vec2& size, const String& title, FPBUTTONCALLBACK callback);

	virtual void OnPress(const vec2& point) override;
	virtual void OnRelease() override;

	inline void SetCallback(FPBUTTONCALLBACK callback, void* data) { this->callback = callback; this->callbackData = data; }
	inline void SetTitle(const String& title) { this->title = title; }

	inline const String& GetTitle() const { return title; }
};

}
