#include <string>
#include <GLEW\glew.h>
#include <vector>

#include "shader.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "Matrix4.h"
#include "fileIO.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		Shader::Shader(string vertPath, string fragPath)
		{
			this->vertPath = vertPath;
			this->fragPath = fragPath;
			shaderID = load();
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			string vertSourceString = FileIO::File(vertPath).read();
			string fragSourceString = FileIO::File(fragPath).read();

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
#ifdef DELTAENGINE_DEBUG
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				cout << "Failed to compile vertex shader!" << endl << &error[0] << endl;
#endif
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
#ifdef DELTAENGINE_DEBUG
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				cout << "Failed to compile fragment shader!" << endl << &error[0] << endl;
#endif
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

	}
}