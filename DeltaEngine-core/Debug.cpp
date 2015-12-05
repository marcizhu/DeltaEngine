#include <GLEW\glew.h>
#include <iostream>

#include "debug.h"
#include "types.h"

using namespace std;

namespace DeltaEngine {
	namespace Debug {

		void Debug::checkErrors()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) cout << "OpenGL Error: " << error << endl;
		}

		void Debug::dump(void* object, Types::uint32 size)
		{
			Types::byte* x = (Types::byte*)object;

			for (Types::uint32 i = 0; i < size; i++)
			{
				printf("0x%X ", x[i]);
			}

			printf("\n");
		}

		//TODO: Add more debug features!
		
	}
}