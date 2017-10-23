#pragma once

#include "memoryallocator.h"

#include "utils/Log.h"

#ifdef denew
#	error denew already defined.
#endif
#ifndef denew
#	define denew	new(__FILE__, __LINE__)
#endif

#define MB 1024 * 1024

#ifdef _DEBUG 
#define DoubleDeletion(ptr, file, line) if(ptr == nullptr) \
										LOGE("Error: Double deletion at %s, %i", file, line)
#else
#define DoubleDeletion(ptr, file, line)
#endif

inline void* operator new(unsigned int count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("Large allocation, size: %.2f MB", size);
	}
	return dank::MemoryAllocator::allocate(count);
}

inline void* operator new[](unsigned int count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("Large allocation, size: %.2f MB", size);
	}
	return dank::MemoryAllocator::allocate(count);
}

inline void* operator new(unsigned int count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("Large allocation, size: %.2f MB %s", size, file);
	}
	return dank::MemoryAllocator::allocate(count);
}

inline void* operator new[](unsigned int count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("Large allocation, size: %.2f MB %s", size, file);
	}
	return dank::MemoryAllocator::allocate(count);
}

inline void operator delete(void* ptr) noexcept {
	dank::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr) noexcept {
	dank::MemoryAllocator::deallocate(ptr);
}

inline void operator delete(void* ptr, const char* file, unsigned int line) noexcept {
	dank::MemoryAllocator::deallocate(ptr);
	DoubleDeletion(ptr, file, line);
}

inline void operator delete[](void* ptr, const char* file, unsigned int line) noexcept {
	dank::MemoryAllocator::deallocate(ptr);
	DoubleDeletion(ptr, file, line);
}