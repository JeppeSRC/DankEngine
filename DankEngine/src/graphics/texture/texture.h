#pragma once


#include <core/nativeapp.h>
#include <utils/string.h>
#include <core/resource/resource.h>

namespace dank {

class Texture : public ResourceTexture {
protected:
	unsigned int textureID;
	unsigned int width;
	unsigned int height;
	bool deleteTexture;

	Texture();
	Texture(const ResourceTexture* resource);
	Texture(const char* filename, ResourceTextureType type);
	Texture(unsigned int width, unsigned int height, unsigned int pixelSize, const void* const data, ResourceTextureType type);
	Texture(unsigned int id, unsigned int width, unsigned int height, bool deleteID);
	Texture(unsigned int width, unsigned int height);
public:
	virtual ~Texture();

	virtual void Bind(unsigned int slot = 0) const = 0;

	inline unsigned int GetID() const { return textureID; }
};

class Texture2D : public Texture {
private:
	void OnCreate(ResourceCreateState state);
protected:

	void Load(unsigned int width, unsigned int height, const void* const data);
	void Load(const unsigned char* const data, int size);
	void Load(const char* filename);

public:
	Texture2D(const ResourceTexture* resource);
	Texture2D(const String& filename);
	Texture2D(const void* const data, unsigned int width, unsigned int height);

	void Bind(unsigned int slot = 0) const override;
};

};