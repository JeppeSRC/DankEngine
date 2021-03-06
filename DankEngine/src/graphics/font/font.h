#pragma once

#include <graphics/texture/texture.h>
#include <utils/string.h>
#include <utils/map.h>
#include <core/resource/resource.h>
#include <maths/vec2.h>

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
	void LoadFont(const String& filename, float fontSize);
public:
	Font(const String& filename, float fontSize, const String& fontName);
	Font(const void* const data, size_t size, float fontSize, const String& fontName);
	~Font();

	inline float GetSize() const { return size; }
	inline const String& GetName() const { return name; }
	inline Texture* GetTexture() const { return atlas; }
	inline ftgl::texture_font_t* GetFont() const { return font; }

	vec2 GetMetrics(const String& text) const;
};

class FontManager {
public:
	class FontData : public ResourceFont {
	public:
		String name;
		const void* data;
		unsigned int size;

	private:
		void OnCreate(ResourceCreateState state) override;
	public:
		FontData(const ResourceFont* resource);
		FontData(const void* const data, unsigned int size, const String& name);
		FontData(const String& filename, const String& name);
		~FontData();

	};


private:
	static Font* defaultFont;
	static List<Font*> fonts;
	static List<FontData*> data;

	static FontData* GetFontData(const String& fontName);
public:
	static void AddFont(const void* const data, unsigned int size, const String& fontName);
	static void AddFont(const String& filename, const String& fontName);
	static Font* GetFont(const String& fontName, float font_size);
	
	inline static Font* GetDefaultFont() { return defaultFont; }

	static void SetDefaultFont(const String& fontName, float font_size);
	static void SetDefaultFont(Font* font);
};

}