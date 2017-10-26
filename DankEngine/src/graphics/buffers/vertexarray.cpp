#include "vertexarray.h"

namespace dank {

	VertexArray::VertexArray() {
		GL(NativeApp::glGenVertexArraysOES(1, &id));
	}

	VertexArray::~VertexArray() {
		GL(NativeApp::glDeleteVertexArraysOES(1, &id));
	}

	void VertexArray::Bind() const {
		GL(NativeApp::glBindVertexArrayOES(id));
	}

}