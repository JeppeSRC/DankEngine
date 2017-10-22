#pragma once

#include <core/nativeapp.h>
#include <utils/map.h>
#include <utils/utils.h>

namespace dank {

	class Shader {
	public:
		static unsigned int activeShaderID;
		static Shader* activeShader;
	private:
		unsigned int shader;

		Map<unsigned int, unsigned int> cache;
	public:
		Shader(const char* vertex, const char* fragment);
		~Shader();

		void Bind();

		unsigned int GetUniformLocation(const char* name);
		unsigned int GetAttributeLocation(const char* name);

		void SetFloat(const char* name, float v);
		void SetFloat(unsigned int location, float v) const;
		void SetVec2(const char* name, float x, float y);
		void SetVec2(unsigned int location, float x, float y) const;
		void SetVec3(const char* name, float x, float y, float z);
		void SetVec3(unsigned int location, float x, float y, float z) const;
		void SetVec4(const char* name, float x, float y, float z, float w);
		void SetVec4(unsigned int location, float x, float y, float z, float w) const;
		void SetMat4(const char* name, float* data);
		void SetMat4(unsigned int location, float* data) const;
	};

}