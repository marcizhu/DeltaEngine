#pragma once

#include <malloc.h>

#include "log.h"
#include "memoryInfo.h"
#include "utils.h"
#include "types.h"

#ifdef DELTAENGINE_DEBUG
#	define NEW			new(__FILE__, __LINE__)
#else
#	define NEW			new
#endif

using namespace DeltaEngine;

inline void* operator new(size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	Types::byte* address = (Types::byte*)malloc(size + sizeof(size_t));
	memcpy(address, &size, sizeof(size_t));
	address += sizeof(size_t);

	return address;
}

inline void* operator new(size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	Types::byte* address = (Types::byte*)malloc(size + sizeof(size_t));
	memcpy(address, &size, sizeof(size_t));
	address += sizeof(size_t);

	return address;
}

inline void* operator new[](size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	Types::byte* address = (Types::byte*)malloc(size + sizeof(size_t));
	memcpy(address, &size, sizeof(size_t));
	address += sizeof(size_t);

	return address;
}

inline void* operator new[](size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	Types::byte* address = (Types::byte*)malloc(size + sizeof(size_t));
	memcpy(address, &size, sizeof(size_t));
	address += sizeof(size_t);

	return address;
}

inline void operator delete(void* block)
{
	Types::byte* amount = ((Types::byte*)block) - sizeof(size_t);

	DeltaEngine::Internal::MemoryInfo::deallocate(*(size_t*)amount);

	free(amount);
}

inline void operator delete(void* block, const char* file, unsigned int line)
{
	Types::byte* amount = ((Types::byte*)block) - sizeof(size_t);

	DeltaEngine::Internal::MemoryInfo::deallocate(*(size_t*)amount);

	free(amount);
}

inline void operator delete[](void* block)
{
	Types::byte* amount = ((Types::byte*)block) - sizeof(size_t);

	DeltaEngine::Internal::MemoryInfo::deallocate(*(size_t*)amount);

	free(amount);
}

inline void operator delete[](void* block, const char* file, unsigned int line)
{
	Types::byte* amount = ((Types::byte*)block) - sizeof(size_t);

	DeltaEngine::Internal::MemoryInfo::deallocate(*(size_t*)amount);

	free(amount);
}