#include "framebuffer.h"


namespace dank {

Framebuffer::Framebuffer(unsigned int width, unsigned int height, TextureFormat format, TextureFormat depthFormat) : Texture2D(format, width, height, nullptr), dbo(0) {
	GL(glGenFramebuffers(1, &fbo));
	GL(glBindBuffer(GL_FRAMEBUFFER, fbo));

	GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));

	if (depthFormat != TextureFormat::NONE) {
		GL(glGenRenderbuffers(1, &dbo));
		GL(glBindRenderbuffer(GL_RENDERBUFFER, dbo));
		
		switch (depthFormat) {
		case TextureFormat::D16:
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height));
			break;
		case TextureFormat::D24:
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height));
			break;
		case TextureFormat::D32:
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, width, height));
			break;
		case TextureFormat::D24S8:
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
			break;
		case TextureFormat::D32S8:
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height));
			break;
		}

		GL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dbo));
		GL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	}

	int res = GL(glCheckFramebufferStatus(GL_FRAMEBUFFER));

	if (res != GL_FRAMEBUFFER_COMPLETE) {
		LOGF("[Framebuffer2D] Failed to create framebuffer: W=%u H=%u Format=%s DepthFormat=%s", width, height, GetFormatString(format), GetFormatString(depthFormat));
	}

	GL(glBindBuffer(GL_FRAMEBUFFER, 0));
}

Framebuffer::~Framebuffer() {
	GL(glDeleteFramebuffers(1, &fbo));
	GL(glDeleteRenderbuffers(1, &dbo));
}

void Framebuffer::BindAsRenderTarget() const {
	GL(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
}

}