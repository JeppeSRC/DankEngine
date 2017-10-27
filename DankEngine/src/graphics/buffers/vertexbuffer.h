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

		void SetData(const void* const data, unsigned int size) const {
			GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
			GL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
			GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	};
}
