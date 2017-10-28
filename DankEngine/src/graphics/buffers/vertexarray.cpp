#include "vertexarray.h"

namespace dank {

	VertexArray::VertexArray() {
		GL(NativeApp::glGenVertexArraysOES(1, &id));
	}

	VertexArray::VertexArray(unsigned int stride): stride(stride) {
		GL(NativeApp::glGenVertexArraysOES(1, &id));
	}

	VertexArray::~VertexArray() {
		GL(NativeApp::glDeleteVertexArraysOES(1, &id));
	}

	void VertexArray::AddAttribute(unsigned int index, unsigned int comp, unsigned int type, bool normalize, unsigned int offset) const {
		GL(glEnableVertexAttribArray(index));
		GL(glVertexAttribPointer(index, comp, type, normalize, stride, (const void*)offset));
	}


	void VertexArray::Bind() const {
		GL(NativeApp::glBindVertexArrayOES(id));
	}

}