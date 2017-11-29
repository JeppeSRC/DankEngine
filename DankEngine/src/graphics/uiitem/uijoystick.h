#pragma once

#include "uiitem.h"


namespace dank {

	class UIJoystick : public UIItem {
	public:
		typedef void(*FPJOYSTICKCALLBACK)(float, float, void*);

	private:
		FPJOYSTICKCALLBACK callback;

		vec2 innerSize;
		vec2 innerPosition, centerPosition;

		unsigned int innerColor;
		void *callbackData;
	public:
		UIJoystick(const String& name, const vec2& position, const vec2& size, const vec2& innerSize);
		~UIJoystick();

		void OnRender(Renderer* renderer) override;
		void OnUpdate(float delta) override;

		void OnMove(const vec2& point) override;
		void OnRelease() override;

		inline void SetInnerColor(unsigned int innerColor) { this->innerColor = innerColor; }
		inline void SetCallback(FPJOYSTICKCALLBACK callback, void *callbackData) { this->callback = callback; this->callbackData = callbackData; }

		inline unsigned int GetInnerColor() { return innerColor; }
	};

}