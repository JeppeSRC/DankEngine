#pragma once

#include <core/nativeapp.h>

namespace dank {

	class IndexBuffer {
	private:
		unsigned int ibo;
		unsigned int count;
		unsigned int format;

	public:
		IndexBuffer(const void* indices, unsigned int size, unsigned int format);
		IndexBuffer(const unsigned short* indices, unsigned int num);
		IndexBuffer(const unsigned char* indices, unsigned int num);
		~IndexBuffer();

		void Bind() const;

		inline unsigned int GetCount() const { return count; }
		inline unsigned int GetFormat() const { return format; }
		inline unsigned int GetIBO() const { return ibo; }
	};

}