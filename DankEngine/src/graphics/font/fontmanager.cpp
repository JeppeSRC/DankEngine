#include "font.h"
#include <utils/asset/fileutils.h>

namespace dank {

List<Font*> FontManager::fonts;
List<FontManager::FontData*> FontManager::data;


FontManager::FontData* FontManager::GetFontData(const String& fontName) {
	size_t index = data.Find<const String&>([](FontData* data, const String& name) -> bool {
		if (data->name == name) return true; return false;
	}, fontName);

	ASSERT(index == (size_t)~0);

	return data[index];
}

//Fuck vs
void FontManager::AddFont(const void* const fontData, unsigned int size, const String& fontName) {
	size_t index = data.Find<const String&>([](FontData* data, const String& name) -> bool {
		if (data->name == name) return true; return false;
	}, fontName);

	if (index == (size_t)~0) return;

	FontData* d = denew FontData(fontData, size, fontName);

	data.Push_back(d);
}

void FontManager::AddFont(const String& filename, const String& fontName) {
	size_t index = data.Find<const String&>([](FontData* data, const String& name) -> bool {
		if (data->name == name) return true; return false;
	}, fontName);

	FontData* d = denew FontData(filename, fontName);

	data.Push_back(d);
}

Font* FontManager::GetFont(const String& fontName, float fontSize) {
	struct ShitStruct {
		String name;
		float size;
	};

	ShitStruct* dank = denew ShitStruct;

	dank->name = fontName;
	dank->size = fontSize;

	size_t index = fonts.Find<ShitStruct*>([](Font* font, ShitStruct* shit) -> bool {
		if (font->GetName() == shit->name && font->GetSize() == shit->size) return true; return false;
	}, dank);

	if (index == (size_t)~0) {
		FontData* fData = GetFontData(fontName);

		Font* font = new Font(fData->data, fData->size, fontSize, fontName);

		fonts.Push_back(font);
		return font;
	}
	else {
		return fonts[index];
	}

	return nullptr;
}

}
