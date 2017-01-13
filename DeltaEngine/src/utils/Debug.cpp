#include <GLEW\glew.h>
#include <vector>

#include "debug.h"
#include "types.h"
#include "utils.h"
#include "log.h"
#include "maths.h"

using namespace std;

namespace DeltaEngine {
	namespace Debug {

		__forceinline void breakpoint(const char* file, int line)
		{
#ifdef DELTAENGINE_DEBUG
			if(file) DELTAENGINE_ERROR("Breakpoint occurred on file ", file, " (line ", line, ")");

			_asm int 3;
#endif
		}

		void checkErrors()
		{
			GLenum error = glGetError();

			if (error != GL_NO_ERROR)
			{
				_DELTAENGINE_ERROR("[OpenGL] OpenGL Error: ", error);

				switch (error)
				{
				case GL_INVALID_VALUE:
					_DELTAENGINE_ERROR(" (Invalid value)\n"); break;

				case GL_INVALID_OPERATION:
					_DELTAENGINE_ERROR(" (Invalid operation)\n"); break;

				case GL_OUT_OF_MEMORY:
					_DELTAENGINE_ERROR(" (Out of memory)\n"); break;

				case GL_CONTEXT_LOST:
					_DELTAENGINE_ERROR(" (Context lost)\n"); break;

				default:
					_DELTAENGINE_ERROR(" (Unknown error)\n"); break;
				}

				breakpoint();
			}
		}

		void dump(const void* object, Types::uint32 size, int color)
		{
#ifdef DELTAENGINE_RELEASE
			DELTAENGINE_WARN("[Debug] Executing a memory dump operation in release mode!");
#endif

			if (Maths::nlog(16, size) > 4) DELTAENGINE_WARN("[Debug] Not all the addresses will be shown!");

			Types::byte* x = (Types::byte*)object;
			vector<Types::byte> data;

			Utils::setConsoleColor(0x0F);
			printf("0000:  ");

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
						Maths::isBetween<Types::byte>(chars, 32, 126) ? Utils::setConsoleColor(color) : Utils::setConsoleColor(0x07);
						Maths::isBetween<Types::byte>(chars, 32, 126) ? printf("%c", chars) : printf(".");
					}

					if (i != size)
					{
						Maths::isBetween<uint32>(i, 0, 0x10000) ? Utils::setConsoleColor(0x0F) : Utils::setConsoleColor(0x0E);
						printf("%04X:  ", Maths::constrain<uint32>(i, 0, 0xFFFF));
					}

					data.clear();
				}
			}

			printf("\n\n");
			Utils::setConsoleColor(0x07);
		}

		void dump(const void* object, Types::uint32 size, FileIO::File& file)
		{
#ifdef DELTAENGINE_RELEASE
			DELTAENGINE_WARN("[Debug] Executing a memory dump operation in release mode (output: file)!");
#endif

			Types::byte* x = (Types::byte*)object;
			vector<Types::byte> data;

			std::string out = "0000:  ";

			for (Types::uint32 i = 1; i <= size; i++)
			{
				char buffer[2];

				itoa(x[i - 1], buffer, 16);

				if (x[i - 1] < 0x10) out += "0";

				out += std::string(buffer) + " ";
				data.push_back(x[i - 1]);

				if (((i % 16 == 0) && (i > 0)) || (i == size))
				{
					out += "        ";

					for (Types::byte chars : data)
					{
						if (Maths::isBetween<Types::byte>(chars, 32, 126))
						{
							stringstream stream;

							stream << chars;

							out += stream.str();
						}
						else
						{
							out += ".";
						}
					}

					if (i != size)
					{
						stringstream stream;

						stream << "\n" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << Maths::constrain<uint32>(i, 0, 0xFFFF) << ":  ";

						out += stream.str();
					}

					data.clear();
				}
			}

			file.write(out);
		}

		//TODO: Add more debug features!
	}
}