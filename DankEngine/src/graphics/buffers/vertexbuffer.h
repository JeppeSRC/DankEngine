#pragma once

#include <core/nativeapp.h>


namespace dank {
	class VertexBuffer {
	private:
		unsigned int vbo;
		unsigned int size;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void* Map(unsigned int mode) const;
		void Unmap() const;

		void Bind() const;

		void SetData(const void* const data, unsigned int size) const;
	};
}
