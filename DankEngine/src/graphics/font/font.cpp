#include "font.h"
#include <utils/asset/fileutils.h>

namespace dank {

void Font::LoadFont(const void* const data, size_t size, float font_size) {
	ASSERT(data == nullptr);
	ftgl::texture_atlas_t* tmpAtlas = ftgl::texture_atlas_new(2048, 2048, 1);
	font = texture_font_new_from_memory(tmpAtlas, font_size, data, size);

	texture_font_get_glyph(font, '0');

	atlas = new FontAtlas(tmpAtlas);

	this->size = font_size;
}

Font::Font(const String& filename, float font_size) {
	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(*filename, &data, &size);

	LoadFont(data, (size_t)size, font_size);
}

Font::Font(const void* const data, size_t size, float font_size) {
	LoadFont(data, size, font_size);
}

Font::~Font() {
	texture_font_delete(font);
}

}