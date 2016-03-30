#include <malloc.h>
#include <Windows.h>
#include <mutex>
#include <atomic>

#include "MemoryManager.h"
#include "utils.h"
#include "log.h"
#include "types.h"
#include "maths.h"
#include "debug.h"

std::mutex memoryMutex;

namespace DeltaEngine {
	namespace Memory {

		bool MemoryManager::initialized = false;
		void* MemoryManager::memStart;
		std::atomic<FreeBlock*> MemoryManager::firstBlock;
		Types::uint32 MemoryManager::allocatedMemory;
		Types::uint32 MemoryManager::freedMemory;
		Types::uint32 MemoryManager::currentMemory;
		Types::uint32 MemoryManager::numAllocations;

		void MemoryManager::freeMem()
		{
			while (currentMemory)
			{
				if (numAllocations == 0) __debugbreak();

				OutputDebugString("[DeltaEngine] Unfreed memory: ");
				OutputDebugString(std::to_string(currentMemory).c_str());
				OutputDebugString(" bytes\n");

				Sleep(1);
			}

			initialized = false;
			free(memStart);
		}

		void MemoryManager::end()
		{
			if (currentMemory)
			{
				OutputDebugString("\n\n[DeltaEngine] Unable to deinitialize memory!\n");
				OutputDebugString("[DeltaEngine] Unfreed memory: ");
				OutputDebugString(std::to_string(currentMemory).c_str());
				OutputDebugString(" bytes\n");
			}
			else
			{
				initialized = false;
				OutputDebugString("[DeltaEngine] Memory deinitialized\n");
			}

			std::thread killThread(freeMem);
			killThread.detach();
		}

		void MemoryManager::start()
		{
			static_assert(MEMORY_CHUNK > sizeof(FreeBlock), "Invalid MEMORY_CHUNK value: MEMORY_CHUNK < sizeof(FreeBlock)");

			if (initialized)
			{
				DELTAENGINE_WARN("[Memory] Reinitialization");
				return;
			}

			// TODO: Replace with a #define MEMORY_CHUNK or something
			memStart = malloc(MEMORY_CHUNK); // 4 Mb
			memset(memStart, 0, MEMORY_CHUNK);

			firstBlock.store((FreeBlock*)memStart);
			firstBlock.load()->size = MEMORY_CHUNK;
			firstBlock.load()->nextBlock = nullptr;

			allocatedMemory = 0;
			freedMemory = 0;
			currentMemory = 0;
			numAllocations = 0;

			initialized = true;
		}

		Types::uint32 MemoryManager::getAllocatedMemory()
		{
			return allocatedMemory;
		}

		Types::uint32 MemoryManager::getFreedMemory()
		{
			return freedMemory;
		}

		Types::uint32 MemoryManager::getCurrentMemory()
		{
			return currentMemory;
		}

		Types::byte* MemoryManager::allocate(size_t amount)
		{
			if (!initialized) start();

			memoryMutex.lock();

			DELTAENGINE_ASSERT(amount != 0);

			FreeBlock* prev_free_block = nullptr;
			FreeBlock* free_block = firstBlock.load();

			while (free_block != nullptr)
			{
				size_t total_size = amount + sizeof(AllocationHeader);

				if (free_block->size < total_size)
				{
					prev_free_block = free_block;
					free_block = free_block->nextBlock;
					continue;
				}

				if (free_block->size - total_size <= sizeof(AllocationHeader))
				{
					total_size = free_block->size;

					if (prev_free_block != nullptr)
					{
						prev_free_block->nextBlock = free_block->nextBlock;
					}
					else
					{
						firstBlock.store(free_block->nextBlock);
					}
				}
				else
				{
					Types::byte* nextAddr = (Types::byte*)free_block + total_size;

					FreeBlock* next_block = (FreeBlock*)nextAddr;
					next_block->size = free_block->size - total_size;
					next_block->nextBlock = free_block->nextBlock;

					if (prev_free_block != nullptr)
					{
						prev_free_block->nextBlock = next_block;
					}
					else
					{
						firstBlock.store(next_block);
					}
				}

				Types::byte* headerAddr = (Types::byte*)free_block;
				AllocationHeader* header = (AllocationHeader*)headerAddr;
				header->size = total_size;
				header->magic = 0x11223344;

				allocatedMemory += total_size;
				currentMemory += total_size;
				numAllocations++;

				memoryMutex.unlock();

				return (Types::byte*)free_block + sizeof(AllocationHeader);
			}

			//Couldn't find free block large enough!

			// TODO: Reallocate more memory and create a new block. Then, return a free block
			__debugbreak();

			return nullptr;
		}

		void MemoryManager::deallocate(void* address)
		{
			if (!initialized) start();

			memoryMutex.lock();

			DELTAENGINE_ASSERT(address != nullptr);
			Types::byte* addr = (Types::byte*)address - sizeof(AllocationHeader);

			AllocationHeader* header = (AllocationHeader*)addr;

			Types::byte* block_start = (Types::byte*)address - sizeof(AllocationHeader);
			size_t block_size = header->size;
			Types::byte* block_end = block_start + block_size;

			FreeBlock* prev_free_block = nullptr;
			FreeBlock* free_block = firstBlock.load();

			while (free_block != nullptr)
			{
				if ((Types::byte*)free_block >= block_end) break;

				prev_free_block = free_block;
				free_block = free_block->nextBlock;
			}

			if (prev_free_block == nullptr)
			{
				prev_free_block = (FreeBlock*)block_start;
				prev_free_block->size = block_size;
				prev_free_block->nextBlock = firstBlock.load();

				firstBlock.store(prev_free_block);
			}
			else if ((Types::byte*)prev_free_block + prev_free_block->size == block_start)
			{
				prev_free_block->size += block_size;
			}
			else
			{
				FreeBlock* temp = (FreeBlock*)block_start;
				temp->size = block_size;
				temp->nextBlock = prev_free_block->nextBlock;
				prev_free_block->nextBlock = temp;

				prev_free_block = temp;
			}

			if (free_block != nullptr && (Types::byte*)free_block == block_end)
			{
				prev_free_block->size += free_block->size;
				prev_free_block->nextBlock = free_block->nextBlock;
			}

			currentMemory -= block_size ;
			freedMemory += block_size;
			numAllocations--;

			memoryMutex.unlock();
		}

		void MemoryManager::refresh()
		{

		}

		std::string MemoryManager::getAllocatedMemoryString()
		{
			unsigned int bytes = getAllocatedMemory();
			std::string ret = "Allocated memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

		std::string MemoryManager::getFreedMemoryString()
		{
			unsigned int bytes = getFreedMemory();
			std::string ret = "Freed memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

		std::string MemoryManager::getCurrentMemoryString()
		{
			unsigned int bytes = getCurrentMemory();
			std::string ret = "Current memory: ";

			if (bytes >= 1024 * 1024 * 1024)
			{
				float gb = (float)bytes / (1024.0f * 1024.0f * 1024.0f);
				ret += Utils::precision_to_string(gb, 3) + " Gb";
				DELTAENGINE_ERROR("USING OVER 1 Gb OF MEMORY!");
			}
			else if (bytes >= 1024 * 1024)
			{
				float mb = (float)bytes / (1024.0f * 1024.0f);
				ret += Utils::precision_to_string(mb, 3) + " Mb";
			}
			else if (bytes >= 1024)
			{
				float kb = (float)bytes / 1024.0f;
				ret += Utils::precision_to_string(kb, 3) + " Kb";
			}
			else
			{
				ret += std::to_string(bytes) + " b";
			}

			return ret;
		}

	}
}