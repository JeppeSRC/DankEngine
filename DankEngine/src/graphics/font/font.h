#pragma once

#include <graphics/texture/texture.h>
#include <utils/string.h>
#include <utils/map.h>

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

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

	void LoadFont(const void* const data, size_t size, float fontSize);
public:
	Font(const String& filename, float fontSize, const String& fontName);
	Font(const void* const data, size_t size, float fontSize, const String& fontName);
	~Font();

	inline float GetSize() const { return size; }
	inline const String& GetName() const { return name; }
	inline Texture* GetTexture() const { return atlas; }
	inline ftgl::texture_font_t* GetFont() const { return font; }
};

class FontManager {
private:
	struct FONT_DATA {
		String name;
		const void* data;
		size_t size;
	};

private:
	static List<Font*> fonts;
	static List<FONT_DATA*> data;

	static FONT_DATA* GetFontData(const String& fontName);
public:
	static void AddFont(const void* const data, size_t size, const String& fontName);
	static void AddFont(const String& filename, const String& fontName);
	static Font* GetFont(const String& fontName, float font_size);

};

}