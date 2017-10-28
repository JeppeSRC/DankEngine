#pragma once


#include <core/nativeapp.h>
#include <utils/string.h>

namespace dank {

class Texture {
protected:
	unsigned int textureID;
	unsigned int width;
	unsigned int height;
	bool deleteTexture;

	Texture();
	Texture(unsigned int id, unsigned int width, unsigned int height, bool deleteID);
	Texture(unsigned int width, unsigned int height);
public:
	virtual ~Texture();

	virtual void Bind(unsigned int slot = 0) const = 0;

	inline unsigned int GetID() const { return textureID; }
};

class Texture2D : public Texture {
protected:

	void Load(const unsigned char* const data, int size);

public:
	Texture2D(const String& filename);
	Texture2D(const void* const data, unsigned int width, unsigned int height, unsigned int format);

	void Bind(unsigned int slot = 0) const override;
};

};