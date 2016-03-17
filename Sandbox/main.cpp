//main.cpp: For testing purposes only

#include "Sandbox.h"

int main(int argc, char *argv[])
{
	Internal::MemoryInfo::start();

	Sandbox testGame(argc, argv);
	testGame.start();
}