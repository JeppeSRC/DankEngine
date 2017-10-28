#include "font.h"
#include <utils/asset/fileutils.h>

namespace dank {

List<Font*> FontManager::fonts;
List<FontManager::FONT_DATA*> FontManager::data;


FontManager::FONT_DATA* FontManager::GetFontData(const String& fontName) {
	size_t index = data.Find<const String&>([](FONT_DATA* data, const String& name) -> bool {
		if (data->name == name) return true; return false;
	}, fontName);

	ASSERT(index == (size_t)~0);

	return data[index];
}

//Fuck vs
void FontManager::AddFont(const void* const fontData, size_t size, const String& fontName) {
	size_t index = data.Find<const String&>([](FONT_DATA* data, const String& name) -> bool {
		if (data->name == name) return true; return false;
	}, fontName);

	if (index == (size_t)~0) return;

	FONT_DATA* d = denew FONT_DATA;
	d->data = fontData;
	d->size = size;
	d->name = fontName;

	data.Push_back(d);
}

void FontManager::AddFont(const String& filename, const String& fontName) {
	unsigned int size = 0;
	void* data = nullptr;

	FileUtils::ReadFile(*filename, &data, &size);

	ASSERT(data == nullptr);

	AddFont(data, size, fontName);

	delete[] data;
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
		FONT_DATA* fData = GetFontData(fontName);

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
