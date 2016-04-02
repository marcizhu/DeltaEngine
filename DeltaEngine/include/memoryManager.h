#pragma once
#include <atomic>

#include "internal.h"
#include "log.h"
#include "MemoryManager.h"
#include "utils.h"
#include "types.h"
#include "fileIO.h"

#ifdef DELTAENGINE_DEBUG
#	define NEW			new(__FILE__, __LINE__)
#else
#	define NEW			new
#endif

#define KB_IN_BYTES		1024
#define MB_IN_BYTES		1024 * 1024
#define GB_IN_BYTES		1024 * 1024 * 1024

#define MEMORY_CHUNK	4 * MB_IN_BYTES

using namespace DeltaEngine;

namespace DeltaEngine {
	namespace Memory {

		enum AllocationFlags
		{
			ALLOCATED			= 1 << 0,
			RESIZED				= 1 << 1,
			UNKNOWN_SOURCE		= 1 << 2,
			KNOWN_SOURCE		= 1 << 3,
			LARGE_ALLOCATION	= 1 << 4,
			ALIGNED				= 1 << 5,
			ARRAY_ALLOCATION	= 1 << 6,
			// TODO: Add more flags
			MAGIC				= 0x130A0000
		};

		struct FreeBlock
		{
			size_t size;
			FreeBlock* nextBlock;
		};

		struct AllocationHeader
		{
			size_t size;
			size_t flags;
		};

		class MemoryManager
		{
		private:
			static bool initialized;
			static void* memStart;
			static uint32 allocatedMemory;
			static uint32 freedMemory;
			static uint32 currentMemory;
			static uint32 numAllocations;
			static std::atomic<FreeBlock*> firstBlock;

			static void freeMem();

		public:
			DELTAENGINE_API static void start();
			DELTAENGINE_API static void refresh();
			DELTAENGINE_API static void end();

			DELTAENGINE_API static uint32 getAllocatedMemory();
			DELTAENGINE_API static uint32 getFreedMemory();
			DELTAENGINE_API static uint32 getCurrentMemory();

			DELTAENGINE_API static uint32 getAllocations();

			DELTAENGINE_API static size_t getFlags(void* address);

			DELTAENGINE_API static std::string getAllocatedMemoryString();
			DELTAENGINE_API static std::string getFreedMemoryString();
			DELTAENGINE_API static std::string getCurrentMemoryString();

			DELTAENGINE_API static std::string getMemoryString(uint32 bytes);

			DELTAENGINE_API static Types::byte* allocate(size_t amount, size_t flags = 0);
			DELTAENGINE_API static void deallocate(void* address);
		};

	}
}

inline void* operator new(size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	size_t flags = Memory::AllocationFlags::UNKNOWN_SOURCE;

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
		flags |= Memory::AllocationFlags::LARGE_ALLOCATION;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new(size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	size_t flags = Memory::AllocationFlags::KNOWN_SOURCE;

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
		flags |= Memory::AllocationFlags::LARGE_ALLOCATION;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new[](size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	size_t flags = Memory::AllocationFlags::UNKNOWN_SOURCE | Memory::AllocationFlags::ARRAY_ALLOCATION;

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
		flags |= Memory::AllocationFlags::LARGE_ALLOCATION;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new[](size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	size_t flags = Memory::AllocationFlags::KNOWN_SOURCE | Memory::AllocationFlags::ARRAY_ALLOCATION;

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
		flags |= Memory::AllocationFlags::LARGE_ALLOCATION;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void operator delete(void* block)
{
	Memory::MemoryManager::deallocate(block);
}

inline void operator delete(void* block, const char* file, unsigned int line)
{
	Memory::MemoryManager::deallocate(block);
}

inline void operator delete[](void* block)
{
	Memory::MemoryManager::deallocate(block);
}

inline void operator delete[](void* block, const char* file, unsigned int line)
{
	Memory::MemoryManager::deallocate(block);
}