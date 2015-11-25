#include <GLEW\glew.h>
#include <iostream>

#include "debug.h"

using namespace std;

namespace DeltaEngine {
	namespace Debug {

		void Debug::checkErrors()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) cout << "OpenGL Error: " << error << endl;
		}

		//TODO: Add more debug features!
		
	}
}