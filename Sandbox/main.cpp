//main.cpp: For testing purposes only

#include "Sandbox.h"

int main(int argc, char *argv[])
{
	Memory::MemoryManager::start();

	Sandbox testGame;
	testGame.start();
}