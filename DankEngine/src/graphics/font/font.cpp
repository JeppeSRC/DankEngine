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

Font::Font(const String& filename, float fontSize, const String& fontName) : name(fontName) {
	LoadFont(filename, fontSize);
}

Font::Font(const void* const data, size_t size, float fontSize, const String& fontName) : name(fontName) {
	LoadFont(data, size, fontSize);
}

Font::~Font() {
	texture_font_delete(font);
}

vec2 Font::GetMetrics(const String& text) const {
	vec2 metrics;

	float top = 0;
	float bottom = 0;

	for (size_t i = 0; i < text.length; i++) {
		char c = text[i];

		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(font, c);

		if (glyph->offset_y > top) top = glyph->offset_y;

		float tmp = glyph->height - glyph->offset_y;

		if (tmp > bottom) bottom = tmp;

		metrics.x += glyph->offset_x;

		if (i != 0) {
			float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			metrics.x += kerning;
		}

		if (i < text.length-1) metrics.x += glyph->advance_x;

	}

	metrics.y = top + bottom;

	metrics.x *= NativeApp::app->xUnitsPerPixel;
	metrics.y *= NativeApp::app->yUnitsPerPixel;

	return metrics;
}

}