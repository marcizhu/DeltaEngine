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
			}

			initialized = false;
			free(memStart);
		}

		void MemoryManager::end()
		{
			std::thread killThread(freeMem);
			killThread.detach();
		}

		void MemoryManager::start()
		{
			static_assert(MEMORY_CHUNK > sizeof(FreeBlock), "Invalid MEMORY_CHUNK value: MEMORY_CHUNK < sizeof(FreeBlock)");
			static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)!");

			if (initialized)
			{
				DELTAENGINE_WARN("[Memory] Reinitialization");
				return;
			}

			memStart = malloc(MEMORY_CHUNK);
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

		Types::byte* MemoryManager::allocate(size_t amount, size_t flags)
		{
			if (!initialized) start();

			memoryMutex.lock();

			DELTAENGINE_ASSERT(amount != 0, "Attempted to allocate 0 bytes!");

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
					flags |= AllocationFlags::RESIZED;

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

				flags |= AllocationFlags::MAGIC | AllocationFlags::ALLOCATED;

				header->flags = flags;

				allocatedMemory += total_size;
				currentMemory += total_size;
				numAllocations++;

				memoryMutex.unlock();

				return (Types::byte*)free_block + sizeof(AllocationHeader);
			}

			//Couldn't find free block large enough!
			memoryMutex.unlock();

			if (prev_free_block == nullptr)
			{
				__debugbreak();
				return nullptr;
			}
			else
			{
				FreeBlock* newBlock = (FreeBlock*)malloc(MEMORY_CHUNK);
				newBlock->nextBlock = prev_free_block->nextBlock;
				newBlock->size = MEMORY_CHUNK;

				prev_free_block->nextBlock = newBlock;

				return allocate(amount);
			}

			//return nullptr;
		}

		void MemoryManager::deallocate(void* address)
		{
			if (!initialized) start();

			memoryMutex.lock();

			DELTAENGINE_ASSERT(address != nullptr);
			Types::byte* addr = (Types::byte*)address - sizeof(AllocationHeader);

			AllocationHeader* header = (AllocationHeader*)addr;

			DELTAENGINE_ASSERT(header->flags & AllocationFlags::MAGIC == AllocationFlags::MAGIC);

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
			FreeBlock* block = firstBlock;

			while (block->nextBlock)
			{
				if (block->nextBlock < block) __debugbreak();

				if ((Types::byte*)block + block->size == (Types::byte*)block->nextBlock)
				{
					__debugbreak();
					block->size += block->nextBlock->size;
					block->nextBlock = block->nextBlock->nextBlock;
				}
				else if ((Types::byte*)block + block->size >(Types::byte*)block->nextBlock)
				{
					__debugbreak();
				}

				block = block->nextBlock;
			}
		}

		std::string MemoryManager::getAllocatedMemoryString()
		{
			return std::string("Memory allocated: ") + getMemoryString(getAllocatedMemory());
		}

		std::string MemoryManager::getFreedMemoryString()
		{
			return std::string("Memory freed: ") + getMemoryString(getFreedMemory());
		}

		std::string MemoryManager::getCurrentMemoryString()
		{
			if (getCurrentMemory() >= 1024 * 1024 * 1024)
			{
				DELTAENGINE_ERROR("USING OVER 1 Gb OF MEMORY!");
			}

			std::string ret = "Current memory: " + getMemoryString(getCurrentMemory());

			return ret;
		}

		std::string MemoryManager::getMemoryString(uint32 bytes)
		{
			int exp = (int)Maths::nlog(1024, bytes);

			float mem = (float)bytes / pow(1024.0f, exp);

			std::string ret = Utils::precision_to_string(mem, 3);

			switch (exp)
			{
			case 3: ret += " Gb"; break;
			case 2: ret += " Mb"; break;
			case 1: ret += " Kb"; break;
			case 0: ret += " b"; break;
			default: ret += " ??"; break;
			}

			return ret;
		}

		uint32 MemoryManager::getAllocations()
		{
			return numAllocations;
		}

		size_t MemoryManager::getFlags(void* address)
		{
			DELTAENGINE_ASSERT(address != nullptr);

			Types::byte* addr = (Types::byte*)address - sizeof(AllocationHeader);

			AllocationHeader* header = (AllocationHeader*)addr;

			if (header->flags & AllocationFlags::MAGIC != AllocationFlags::MAGIC) return 0;

			return header->flags;
		}

	}
}