#include <GLEW\glew.h>
#include <iostream>
#include <vector>

#include "debug.h"
#include "types.h"
#include "utils.h"

using namespace std;

namespace DeltaEngine {
	namespace Debug {

		void checkErrors()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) cout << "OpenGL Error: " << error << endl;
		}

		void dump(const void* object, Types::uint32 size, int color)
		{
			Types::byte* x = (Types::byte*)object;
			vector<Types::byte> data;

			for (Types::uint32 i = 1; i <= size; i++)
			{
				x[i - 1] >= 32 ? x[i - 1] < 127 ? Utils::setConsoleColor(color) : Utils::setConsoleColor(0x07) : Utils::setConsoleColor(0x07);

				printf("%02X ", x[i - 1]);
				data.push_back(x[i - 1]);

				if (((i % 16 == 0) && (i > 0)) || (i == size))
				{
					Utils::gotoxy(64, -1);

					for (Types::byte chars : data)
					{
						chars >= 32 ? chars < 127 ? Utils::setConsoleColor(color) : Utils::setConsoleColor(0x07) : Utils::setConsoleColor(0x07);
						chars >= 32 ? chars < 127 ? printf("%c", chars) : printf(".") : printf(".");
					}

					data.clear();
				}
			}

			printf("\n\n");
			Utils::setConsoleColor(0x07);
		}

		//TODO: Add more debug features!
	}
}