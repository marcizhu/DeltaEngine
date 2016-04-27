#include <DeltaEngine.h>

#include "Application.h"

int main(int argc, char* argv[])
{
	Memory::MemoryManager::start();

	Application game;
	game.start();
	return 0;
}