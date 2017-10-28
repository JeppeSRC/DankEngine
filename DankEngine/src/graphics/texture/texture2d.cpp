#include "texture.h"
#include <stb_image.h>
#include <utils/log.h>
#include <utils/asset/fileutils.h>

namespace dank {

void Texture2D::Load(const unsigned char* const data, int size) {
	int x = 0;
	int y = 0;
	int c = 0;

	unsigned char* data = stbi_load_from_memory(data, size, &x, &y, &c, 4);

	ASSERT(data == nullptr);

	this->width = x;
	this->height = y;

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

	GL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::Texture2D(const String& filename) {

	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(*filename, &data, &size);

	Load((unsigned char*)data, size);

	delete[] data;
}

Texture2D::Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format) : Texture(width, height) {
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, format, data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {

}

void Texture2D::Bind(unsigned int slot) const {
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

}