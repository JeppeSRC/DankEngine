#pragma once

#include "utils/log.h"

#include <iostream>

namespace dank {

	class MemoryAllocator {
	private:
		
		static float allocated;

	public:
		static void* allocate(unsigned int size);
		static void deallocate(void* memory);

		static float getAllocated() { return allocated; }
	};

}