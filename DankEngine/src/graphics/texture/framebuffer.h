#pragma once

#include "texture.h"


namespace dank {

class Framebuffer : public Texture2D {
private:
	unsigned int fbo;
	unsigned int dbo;

public:
	Framebuffer(unsigned int width, unsigned int height, TextureFormat format, TextureFormat depthFormat);
	~Framebuffer();

	void BindAsRenderTarget() const;
	void DisplayFramebuffer() const;

	inline unsigned int GetID() const { return fbo; }
};

}
