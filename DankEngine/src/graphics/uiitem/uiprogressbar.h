#pragma once

#include "uiitem.h"

namespace dank {

	class UIProgressBar : public UIItem {
	private:
		int completion;

		unsigned int completionColor;

	public:
		UIProgressBar(const String& name, const vec2& position, const vec2& size, unsigned int completionColor);
		~UIProgressBar() {}

		void OnRender(Renderer* renderer) override;

		inline void AddStep() { completion++; }
		inline void RemoveStep() { completion--; }
		
		inline void SetStep(int step) { completion = step; }

	};



}