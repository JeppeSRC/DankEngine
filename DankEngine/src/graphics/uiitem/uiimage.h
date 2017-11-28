#pragma once

#include "uiitem.h"

#include "graphics/texture/texture.h"

namespace dank {

	class UIImage : public UIItem {
	protected:

	public:
		UIImage(const String& name, Texture2D* texture, const vec2& position, const vec2& size);

		virtual void OnRender(Renderer* renderer) override;

	};


}
