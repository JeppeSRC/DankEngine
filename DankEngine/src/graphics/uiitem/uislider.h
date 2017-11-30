#pragma once

#include "uiitem.h"

namespace dank {


class UISlider : public UIItem {
protected:
	float percent;

	vec2 handlePosition;
	vec2 handleSize;

	unsigned int handleColor;
	Texture2D* handleTexture;

	float grabbed;

public:
	UISlider(const String& name, const vec2& position, const vec2& size, const vec2& handleSize);

	virtual void OnPress(const vec2& point) override;
	virtual void OnMove(const vec2& point) override;
	virtual void OnRelease() override;

	virtual void OnRender(Renderer* renderer) override;

	template<typename T>
	void Interpolate(T& value) const;

	inline float GetPercent() const { return percent; }
	inline unsigned int GetHandleColor() const { return handleColor; }
	inline Texture2D* GetHandleTexture() const { return handleTexture; }
	
	inline void SetHandleSize(const vec2& size) { this->handleSize = size; }
	inline void SetHandleColor(unsigned int color) { this->handleColor = color; }
	inline void SetHandleTexture(Texture2D* texture) { this->handleTexture = texture; }

};

}