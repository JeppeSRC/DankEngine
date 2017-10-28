#include "memoryallocator.h"
typedef char byte;

namespace dank {

	float MemoryAllocator::allocated = 0;

	void* MemoryAllocator::allocate(unsigned int size) {
		allocated += size;

		byte* memory = (byte*)malloc(size + sizeof(unsigned int));
		unsigned int* addr = (unsigned int*)memory;
		*addr = size;
		memory += sizeof(unsigned int);
		return (void*)memory;
	}

	void MemoryAllocator::deallocate(void* memory) {
		if (memory == nullptr)
			return; //hackerman

		byte* addr = (byte*)memory;
		addr -= sizeof(unsigned int);
		unsigned int size = *(unsigned int*)addr;
		free(addr);

		allocated -= size;
		memory = 0;
	}

}