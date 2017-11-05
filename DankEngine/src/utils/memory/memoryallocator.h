#pragma once

#include "utils/log.h"

#include <iostream>

namespace dank {

	class MemoryAllocator {
	private:
		
		static unsigned int allocated;

	public:
		static void* Allocate(size_t size);
		static void Deallocate(void* memory);

		static float GetAllocated() { return allocated; }
	};

}