#include "memoryallocator.h"
typedef char byte;

namespace dank {

	float MemoryAllocator::allocated = 0;

	void* MemoryAllocator::allocate(size_t size) {
		allocated += size;

		byte* memory = (byte*)malloc(size + sizeof(size_t));
		size_t* addr = (size_t*)memory;
		*addr = size;
		memory += sizeof(size_t);
		return (void*)memory;
	}

	void MemoryAllocator::deallocate(void* memory) {
		if (memory == nullptr)
			return; //hackerman

		byte* addr = (byte*)memory;
		addr -= sizeof(size_t);
		size_t size = *(size_t*)addr;
		free(addr);

		allocated -= size;
		memory = 0;
	}

}