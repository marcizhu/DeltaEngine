#pragma once

#include <malloc.h>

#include "log.h"
#include "memoryInfo.h"
#include "utils.h"

#define NEW			new(__FILE__, __LINE__)
#define DELETE		delete

inline void* operator new(size_t size) noexcept
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	void* address = malloc(size + 4);

	int* amount = (int*)address;
	*amount = size;

	amount += 1;

	return amount;
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

	void* address = malloc(size + 4);

	int* amount = (int*)address;
	*amount = size;

	amount += 1;

	return amount;
}

inline void* operator new[](size_t size) noexcept
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", DeltaEngine::Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	DeltaEngine::Internal::MemoryInfo::allocate(size);

	void* address = malloc(size + 4);

	int* amount = (int*)address;
	*amount = size;

	amount += 1;

	return amount;
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

	void* address = malloc(size + 4);

	int* amount = (int*)address;
	*amount = size;

	amount += 1;

	return amount;
}

inline void operator delete(void* block)
{
	int* amount = (int*)block;
	amount -= 1;

	DeltaEngine::Internal::MemoryInfo::deallocate(*amount);
	//if(*amount > 1024 * 1024) DELTAENGINE_INFO("MEM: ", *amount, " bytes freed");

	free(amount);
}

inline void operator delete[](void* block)
{
	int* amount = (int*)block;
	amount -= 1;

	DeltaEngine::Internal::MemoryInfo::deallocate(*amount);
	//if (*amount > 1024 * 1024) DELTAENGINE_INFO("MEM: ", *amount, " bytes freed");

	free(amount);
}