#include "indexbuffer.h"

namespace dank {

	IndexBuffer::IndexBuffer(const void* indices, unsigned int size, unsigned int format) {
		GL(glGenBuffers(1, &ibo));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		this->format = format;
	}

	IndexBuffer::IndexBuffer(const unsigned short* indices, unsigned int num) 
		: IndexBuffer(indices, num * sizeof(unsigned short), GL_UNSIGNED_SHORT) { count = num; }

	IndexBuffer::IndexBuffer(const unsigned char* indices, unsigned int num) 
		: IndexBuffer(indices, num * sizeof(unsigned char), GL_UNSIGNED_BYTE) { count = num; }

	IndexBuffer::~IndexBuffer() {
		GL(glDeleteBuffers(1, &ibo));
	}

	void IndexBuffer::Bind() const {
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	}

}