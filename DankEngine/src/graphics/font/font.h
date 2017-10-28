#pragma once

#include <graphics/texture/texture.h>
#include <utils/string.h>
#include <freetype-gl.h>

namespace dank {

class FontAtlas : public Texture {
private:
	ftgl::texture_atlas_t* atlas;

public:
	FontAtlas(ftgl::texture_atlas_t* atlas);
	~FontAtlas();

	void Bind(unsigned int slot = 0) const override;
};

class Font {
private:
	String name;

	float size;

	ftgl::texture_font_t* font;

	FontAtlas* atlas;

	void LoadFont(const void* const data, size_t size, float font_size);
public:
	Font(const String& filename, float font_size);
	Font(const void* const data, size_t size, float font_size);
	~Font();

	inline float GetSize() const { return size; }
};

}