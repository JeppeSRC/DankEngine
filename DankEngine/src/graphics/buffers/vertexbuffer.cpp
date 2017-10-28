#include "vertexbuffer.h"

namespace dank {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size) : size(size) {
		GL(glGenBuffers(1, &vbo));
		GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

		GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer() {
		GL(glDeleteBuffers(1, &vbo));
	}

	void VertexBuffer::Bind() const {
		GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	}

	void VertexBuffer::SetData(const void* const data, unsigned int size) const {
		GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void* VertexBuffer::Map(unsigned int mode) const {
		Bind();
		void* ptr = GL(glMapBufferRange(GL_ARRAY_BUFFER, 0, size, mode));
		return ptr;
	}


	void VertexBuffer::Unmap() const {
		GL(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

}