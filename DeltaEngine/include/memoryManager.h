#pragma once

#pragma warning(disable:4595)

#include <atomic>

#include "internal.h"
#include "log.h"
#include "MemoryManager.h"
#include "maths.h"
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

#define MEMORY_ALIGNMENT	sizeof(size_t)

using namespace DeltaEngine;

namespace DeltaEngine {
	namespace Memory {

		enum AllocationFlags
		{
			ALLOCATED			= 1 << 0,
			RESIZED				= 1 << 1,
			ALIGNED				= 1 << 2,
			UNKNOWN_SOURCE		= 1 << 3,
			KNOWN_SOURCE		= 1 << 4,
			ALLOCATION_LARGE	= 1 << 5,
			ALLOCATION_ARRAY	= 1 << 6,
			ALLOCATION_CUSTOM	= 1 << 7,
			ALIGNMENT_4_BYTES	= 1 << 8,
			ALIGNMENT_8_BYTES	= 1 << 9,
			ALIGNMENT_CUSTOM	= 1 << 10,
			MAGIC				= ('D' << 24) | 'E' << 16
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
	size_t flags = Memory::AllocationFlags::UNKNOWN_SOURCE;

	if (size > MB_IN_BYTES)
	{
		float mb = (float)size / (MB_IN_BYTES);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, Maths::nlen<float>(mb) + 2), " Mb) from an unknown source!");
		flags |= Memory::AllocationFlags::ALLOCATION_LARGE;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new(size_t size, const char* file, unsigned int line)
{
	size_t flags = Memory::AllocationFlags::KNOWN_SOURCE;

	if (size > MB_IN_BYTES)
	{
		float mb = (float)size / (MB_IN_BYTES);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, Maths::nlen<float>(mb) + 2), " Mb) at ", file, ":", line);
		flags |= Memory::AllocationFlags::ALLOCATION_LARGE;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new[](size_t size)
{
	size_t flags = Memory::AllocationFlags::UNKNOWN_SOURCE | Memory::AllocationFlags::ALLOCATION_ARRAY;

	if (size > MB_IN_BYTES)
	{
		float mb = (float)size / (MB_IN_BYTES);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, Maths::nlen<float>(mb) + 2), " Mb) from an unknown source!");
		flags |= Memory::AllocationFlags::ALLOCATION_LARGE;
	}

	return Memory::MemoryManager::allocate(size, flags);
}

inline void* operator new[](size_t size, const char* file, unsigned int line)
{
	size_t flags = Memory::AllocationFlags::KNOWN_SOURCE | Memory::AllocationFlags::ALLOCATION_ARRAY;

	if (size > MB_IN_BYTES)
	{
		float mb = (float)size / (MB_IN_BYTES);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, Maths::nlen<float>(mb) + 2), " Mb) at ", file, ":", line);
		flags |= Memory::AllocationFlags::ALLOCATION_LARGE;
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