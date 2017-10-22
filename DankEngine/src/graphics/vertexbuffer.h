#pragma once

#include <core/nativeapp.h>


namespace dank {
	class VertexBuffer {
	private:
		unsigned int vbo;

	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
	};
}
