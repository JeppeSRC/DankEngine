#include "vertexbuffer.h"

namespace dank {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
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
}