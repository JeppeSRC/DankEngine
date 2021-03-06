#pragma once

#include <utils/string.h>

namespace dank {

enum class ResourceType {
	UNKNOWN,
	BINARY,
	SHADER,
	TEXTURE,
	FONT,
};

enum class ResourceStorageType {
	UNKNOWN,
	BINARY,
	FILE
};

//TODO: more dank names
enum class ResourceCreateState {
	UNKNOWN,
	COLD,
	HOT
};

enum class TextureFormat;
 
class Resource {
protected:
	ResourceType type;
	ResourceStorageType storageType;

	unsigned long long resourceData;
	unsigned int resourceDataSize;

	unsigned int resourceID;

	Resource(void* const data, unsigned int size, ResourceType type, ResourceStorageType storageType, unsigned int resourceID);
public:
	virtual ~Resource();

	virtual void OnCreate(ResourceCreateState state) {}

	inline const void* GetResourceData() const { return (void*)resourceData; }
	inline unsigned int GetResourceDataSize() const { return resourceDataSize; }

	inline ResourceType GetType() const { return type; }
	inline ResourceStorageType GetStorageType() const { return storageType; }

	inline void SetID(unsigned int resourceID) { this->resourceID = resourceID; }
	inline unsigned int GetResourceID() const { return resourceID; }
};

class ResourceBinary : public Resource {
private:
public:
	ResourceBinary(void* const data, unsigned int size, ResourceStorageType storageType, unsigned int resourceID);
	~ResourceBinary();

};

/*
Data layout:
	- vs code + null terminator
	- ps code + null terminator

*/
class ResourceShader : public Resource {
protected:

	ResourceShader(const ResourceShader* other);
	ResourceShader(const char* vertex, const char* fragment, unsigned int resourceID);
public:
	
	const char* GetVSCode() const;
	const char* GetPSCode() const;
};

/*
Data layout:
	BINARY:
		- width
		- height
		- format
		- data

	FILE:
		- filename + null terminator

*/
enum class ResourceTextureType {
	RESOURCE_TEXTURE_UNKNOWN,
	RESOURCE_TEXTURE_TEXTURE2D,
};

class ResourceTexture : public Resource {
protected:
	ResourceTextureType textureType;

	ResourceTexture(const ResourceTexture* other);
	ResourceTexture(ResourceTextureType type, unsigned int resourceID);
	ResourceTexture(const char* filename, ResourceTextureType type, unsigned int resourceID);
	ResourceTexture(unsigned int width, unsigned int height, TextureFormat format, const void* const data, ResourceTextureType type, unsigned int resourceID);
public:

	const char* GetFilename() const;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	TextureFormat GetFormat() const;
	const void* GetPixelData() const;

	inline ResourceTextureType GetTextureType() const { return textureType; }
};

/*
Data layout:
	BINARY:
		- size
		- name + null terminator
		- font data

	FILE:
		- filename + null terminator
		- name + null terminator
*/
class ResourceFont : public Resource {
protected:

	ResourceFont(const ResourceFont* other);
	ResourceFont(const char* filename, const char* name, unsigned int resourceID);
	ResourceFont(const void* const data, unsigned int size, const char* name, unsigned int resourceID);
public:

	const char* GetName() const;
	const char* GetFilename() const;
	const void*  GetFontData() const;
	unsigned int GetFontDataSize() const;
};

}
