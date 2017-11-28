#include "uiimage.h"

namespace dank {

	UIImage::UIImage(const String& name, Texture2D* texture, const vec2& position, const vec2& size)
		: UIItem(name, position, size) {
		SetTexture(texture);
	}

	void UIImage::OnRender(Renderer* renderer) {
		renderer->SubmitTopLeft(vec3(position), size, texture, 0xFFFFFFFF);
	}

}