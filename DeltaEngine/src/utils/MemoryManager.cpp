#include <malloc.h>
#include <Windows.h>
#include <mutex>
#include <atomic>

#include "MemoryManager.h"
#include "utils.h"
#include "log.h"
#include "types.h"
#include "maths.h"

std::mutex memoryMutex;

namespace DeltaEngine {
	namespace Memory {

		bool MemoryManager::initialized = false;
		void* MemoryManager::memStart;
		std::atomic<FreeBlock*> MemoryManager::firstBlock;
		Types::uint32 MemoryManager::allocatedMemory;
		Types::uint32 MemoryManager::freedMemory;
		Types::uint32 MemoryManager::currentMemory;

		void MemoryManager::freeMem()
		{
			while (currentMemory)
			{
				Sleep(10);
			}

			free(memStart);
		}

		void MemoryManager::end()
		{
			if (currentMemory)
			{
				OutputDebugString("\n\n[DeltaEngine] Unfreed memory: ");
				OutputDebugString(std::to_string(currentMemory).c_str());
				OutputDebugString(" bytes\n\n");
			}

			initialized = false;

			std::thread killThread(freeMem);
			killThread.detach();
		}

		void MemoryManager::start()
		{
			if (initialized)
			{
				DELTAENGINE_WARN("[Memory] Reinitialization");
				return;
			}

			// TODO: Replace with a #define MEMORY_CHUNK or something
			memStart = malloc(4 * 1024 * 1024); // 4 Mb
			memset(memStart, 0, 4 * 1024 * 1024);

			firstBlock.store((FreeBlock*)memStart);
			firstBlock.load()->size = 4 * 1024 * 1024;
			firstBlock.load()->nextBlock = nullptr;

			allocatedMemory = 0;
			freedMemory = 0;
			currentMemory = 0;

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

			FreeBlock* block = firstBlock;
			FreeBlock* lastBlock = nullptr;
			Types::byte* address = nullptr;

			while (block != nullptr)
			{
				if (block->size == (amount + sizeof(size_t)))
				{
					if (block->nextBlock != nullptr)
					{
						firstBlock = block->nextBlock;
					}
					else
					{
						void* nextAddress = malloc(4 * 1024 * 1024);

						FreeBlock* newBlock = (FreeBlock*)nextAddress;
						newBlock->size = 4 * 1024 * 1024;
						newBlock->nextBlock = nullptr;

						block->nextBlock = newBlock;
					}

					address = (Types::byte*)block;
					memcpy(address, &amount, sizeof(size_t));
					address += sizeof(size_t);

					break;
				}
				else if (block->size > (amount + sizeof(size_t)))
				{
					Types::byte* nextAddress = (Types::byte*)block + (amount + sizeof(size_t));
					Types::uint32 newSize = block->size - (amount + sizeof(size_t));

					FreeBlock* newBlock = (FreeBlock*)nextAddress;
					newBlock->nextBlock = block->nextBlock;
					newBlock->size = newSize;

					// FIXME: Investigate this (possible memory leak!)
					firstBlock.store(newBlock);

					address = (Types::byte*)block;
					memcpy(address, &amount, sizeof(size_t));
					address += sizeof(size_t);

					break;
				}
				else
				{
					lastBlock = block;
					block = block->nextBlock;
				}
			}

			allocatedMemory += amount;
			currentMemory += amount;

			memoryMutex.unlock();

			if(address == nullptr) __debugbreak();

			return address;
		}

		void MemoryManager::deallocate(void* address)
		{
			if (!initialized) start();

			memoryMutex.lock();

			Types::byte* mem = ((Types::byte*)address) - sizeof(size_t);

			size_t amount = *(size_t*)mem;

			FreeBlock* newBlock = (FreeBlock*)mem;
			newBlock->size = amount;

			if (newBlock < firstBlock)
			{
				newBlock->nextBlock = firstBlock;
				firstBlock = newBlock;
			}
			else
			{
				newBlock->nextBlock = firstBlock.load()->nextBlock;
				firstBlock.load()->nextBlock = newBlock;
			}

			freedMemory += amount;
			currentMemory -= amount;

			memoryMutex.unlock();
		}

		void MemoryManager::refresh()
		{
			FreeBlock* block = firstBlock.load();
			int i = 0;

			// TODO: First, sort all the blocks!

			while (block != nullptr)
			{
				if (block->nextBlock == nullptr) break;

				Types::byte* nextAddr = (Types::byte*)block;
				Types::byte* nextBlockAddr = (Types::byte*)block->nextBlock;
				nextAddr += block->size;

				if (nextAddr == nextBlockAddr)
				{
					block->size += block->nextBlock->size;
					block->nextBlock = block->nextBlock->nextBlock;
					OutputDebugString("Merging two blocks...\n");
				}

				block = block->nextBlock;
			}
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