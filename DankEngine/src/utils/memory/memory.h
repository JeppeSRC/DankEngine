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
										LOGE("[Memory] Error: Double deletion at %s, %i", file, line)
#else
#define DoubleDeletion(ptr, file, line)
#endif

inline void* operator new(size_t count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("[Memory] Large allocation, size: %.2f MB", size);
	}
	return dank::MemoryAllocator::Allocate(count);
}

inline void* operator new[](size_t count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("[Memory] Large allocation, size: %.2f MB", size);
	}
	return dank::MemoryAllocator::Allocate(count);
}

inline void* operator new(size_t count, const char* file, size_t line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("[Memory] Large allocation, size: %.2f MB %s", size, file);
	}
	return dank::MemoryAllocator::Allocate(count);
}

inline void* operator new[](size_t count, const char* file, size_t line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		LOGW("[Memory] Large allocation, size: %.2f MB %s", size, file);
	}
	return dank::MemoryAllocator::Allocate(count);
}

inline void operator delete(void* ptr) noexcept {
	dank::MemoryAllocator::Deallocate(ptr);
}

inline void operator delete[](void* ptr) noexcept {
	dank::MemoryAllocator::Deallocate(ptr);
}

inline void operator delete(void* ptr, const char* file, unsigned int line) noexcept {
	dank::MemoryAllocator::Deallocate(ptr);
	DoubleDeletion(ptr, file, line);
}

inline void operator delete[](void* ptr, const char* file, unsigned int line) noexcept {
	dank::MemoryAllocator::Deallocate(ptr);
	DoubleDeletion(ptr, file, line);
}