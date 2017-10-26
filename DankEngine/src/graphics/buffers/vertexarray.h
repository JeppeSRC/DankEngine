#pragma once

#include "core/nativeapp.h"

namespace dank {

	class VertexArray {
	private:
		unsigned int id;
	
	public:
		VertexArray();
		~VertexArray();
		
		void Bind() const;
	};

}
