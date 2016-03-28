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

using namespace DeltaEngine;

namespace DeltaEngine {
	namespace Memory {

		struct FreeBlock
		{
			size_t size;
			FreeBlock* nextBlock;
		};

		class MemoryManager
		{
		private:
			static bool initialized;
			static void* memStart;
			static Types::uint32 allocatedMemory;
			static Types::uint32 freedMemory;
			static Types::uint32 currentMemory;
			static std::atomic<FreeBlock*> firstBlock;

			static void freeMem();

		public:
			DELTAENGINE_API static void start();
			DELTAENGINE_API static void refresh();
			DELTAENGINE_API static void end();

			DELTAENGINE_API static Types::uint32 getAllocatedMemory();
			DELTAENGINE_API static Types::uint32 getFreedMemory();
			DELTAENGINE_API static Types::uint32 getCurrentMemory();

			DELTAENGINE_API static std::string getAllocatedMemoryString();
			DELTAENGINE_API static std::string getFreedMemoryString();
			DELTAENGINE_API static std::string getCurrentMemoryString();

			DELTAENGINE_API static Types::byte* allocate(size_t amount);
			DELTAENGINE_API static void deallocate(void* address);
		};

	}
}

inline void* operator new(size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	return Memory::MemoryManager::allocate(size);
}

inline void* operator new(size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
	}

	return Memory::MemoryManager::allocate(size);
}

inline void* operator new[](size_t size)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_ERROR("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) from an unknown source!");
	}

	return Memory::MemoryManager::allocate(size);
}

inline void* operator new[](size_t size, const char* file, unsigned int line)
{
	if (size > 1024 * 1024 * 1024) DELTAENGINE_FATAL("Invalid allocation size! (> 1 Gb!)");

	if (size > 1024 * 1024)
	{
		float mb = (float)size / (1024 * 1024);
		DELTAENGINE_WARN("Large allocation (", Utils::precision_to_string(mb, 3), " Mb) at ", file, ":", line);
	}

	return Memory::MemoryManager::allocate(size);
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