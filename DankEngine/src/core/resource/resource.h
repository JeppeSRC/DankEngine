#pragma once

#include <utils/string.h>

namespace dank {

enum ResourceType {
	RESOURCE_UNKNOWN,
	RESOURCE_BINARY,
	RESOURCE_SHADER,
	RESOURCE_TEXTURE,
	RESOURCE_FONT,
};

enum ResourceStorageType {
	RESOURCE_STORAGE_UNKNOWN,
	RESOURCE_STORAGE_BINARY,
	RESOURCE_STORAGE_FILE
};

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
	RESOURCE_STORAGE_BINARY:
		- width
		- height
		- format
		- data

	RESOURCE_STORAGE_FILE:
		- filename + null terminator

*/
enum ResourceTextureType {
	RESOURCE_TEXTURE_UNKNOWN,
	RESOURCE_TEXTURE_TEXTURE2D,
};

class ResourceTexture : public Resource {
protected:
	ResourceTextureType textureType;

	ResourceTexture(const ResourceTexture* other);
	ResourceTexture(ResourceTextureType type, unsigned int resourceID);
	ResourceTexture(const char* filename, ResourceTextureType type, unsigned int resourceID);
	ResourceTexture(unsigned int width, unsigned int height, unsigned int pixelSize, const void* const data, ResourceTextureType type, unsigned int resourceID);
public:

	const char* GetFilename() const;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	unsigned int GetPixelSize() const;
	const void* GetPixelData() const;

	inline ResourceTextureType GetTextureType() const { return textureType; }
};

/*
Data layout:
	RESOURCE_STORAGE_BINARY:
		- size
		- name + null terminator
		- font data

	RESOURCE_STORAGE_FILE:
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
