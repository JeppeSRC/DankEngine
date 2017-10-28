#pragma once

#include "core/nativeapp.h"

namespace dank {

	class VertexArray {
	private:
		unsigned int id;
		unsigned int stride;

	public:
		VertexArray();
		VertexArray(unsigned int stride);
		~VertexArray();

		void AddAttribute(unsigned int index, unsigned int comp, unsigned int type, bool normalize, unsigned int offset) const;

		
		void Bind() const;
	};

}
