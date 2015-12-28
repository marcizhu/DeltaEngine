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

		Shader::Shader(string& vertPath, string& fragPath)
		{
			shaderID = load(vertPath, fragPath);
		}

		//TODO: Add "Internal:" parameter to load from an array instead of a file
		GLuint Shader::load(string& vertPath, string& fragPath)
		{
#ifdef DELTAENGINE_DEBUG
			if (vertPath.find("Internal:") != string::npos)
			{
				cout << "[Shader] Shaders cannot be loaded from memory yet!" << endl;
				return 0;
			}

			if (fragPath.find("Internal:") != string::npos)
			{
				cout << "[Shader] Shaders cannot be loaded from memory yet!" << endl;
				return 0;
			}
#endif

			FileIO::File vShader = FileIO::File(vertPath);
			FileIO::File fShader = FileIO::File(fragPath);

			if (vShader.exists() == false || fShader.exists() == false)
			{
#ifdef DELTAENGINE_DEBUG
				if (vShader.exists() == false) cout << "[Shader] Vertex shader file doesn't exists!" << endl;
				if (fShader.exists() == false) cout << "[Shader] Fragment shader file doesn't exists!" << endl;
#endif
				return 0;
			}

			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			string vertexShader = vShader.read();
			string fragmentShader = fShader.read();

			const char* vertSource = vertexShader.c_str();
			const char* fragSource = fragmentShader.c_str();

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
				cout << "[Shader] Failed to compile vertex shader!" << endl << &error[0] << endl;
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
				cout << "[Shader] Failed to compile fragment shader!" << endl << &error[0] << endl;
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