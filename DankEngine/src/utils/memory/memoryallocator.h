#pragma once

#include "utils/log.h"

#include <iostream>

namespace dank {

	class MemoryAllocator {
	private:
		
		static float allocated;

	public:
		static void* Allocate(size_t size);
		static void Deallocate(void* memory);

		static float GetAllocated() { return allocated; }
	};

}