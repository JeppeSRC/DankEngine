#include "font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "freetype-gl.h"
#include <utils/asset/fileutils.h>

namespace dank {

void Font::LoadFont(const void* const data, size_t size, float fontSize) {
	ASSERT(data == nullptr);
	ftgl::texture_atlas_t* tmpAtlas = ftgl::texture_atlas_new(2048, 2048, 1);
	font = texture_font_new_from_memory(tmpAtlas, fontSize, data, size);

	texture_font_get_glyph(font, '0');

	atlas = new FontAtlas(tmpAtlas);

	this->size = fontSize;
}

void Font::LoadFont(const String& filename, float fontSize) {
	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(*filename, &data, &size);

	LoadFont(data, (size_t)size, fontSize);
}

Font::Font(const String& filename, float fontSize, const String& fontName) : ResourceFont(*filename, *fontName, 0), name(fontName) {
	LoadFont(filename, fontSize);
}

Font::Font(const void* const data, size_t size, float fontSize, const String& fontName) : ResourceFont(data, size, *fontName, 0), name(fontName) {
	LoadFont(data, size, fontSize);
}

Font::~Font() {
	texture_font_delete(font);
}

}