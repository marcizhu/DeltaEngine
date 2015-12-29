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

		//TODO: Allow the user to load vertex + fragment shaders at once (both in the same file)
		Shader::Shader(const string& vertex, const string& fragment, ShaderDataType dType)
		{
			if (dType == ShaderDataType::SOURCE) shaderID = load(vertex, fragment);
			else if (dType == ShaderDataType::FILE)
			{
				FileIO::File vShader = FileIO::File(vertex);
				FileIO::File fShader = FileIO::File(fragment);

				if (vShader.exists() == false || fShader.exists() == false)
				{
#ifdef DELTAENGINE_DEBUG
					if (vShader.exists() == false) cout << "[Shader] Vertex shader file doesn't exists!" << endl;
					if (fShader.exists() == false) cout << "[Shader] Fragment shader file doesn't exists!" << endl;
#endif
					shaderID = 0;
					return;
				}

				shaderID = load(vShader.read(), fShader.read());
			}
			else
			{
				cout << "[Shader] Invalid shader type!" << endl;
			}
		}

		Shader* Shader::loadFromFile(const string& vertPath, const string& fragPath)
		{
			FileIO::File vShader = FileIO::File(vertPath);
			FileIO::File fShader = FileIO::File(fragPath);

			if (vShader.exists() == false || fShader.exists() == false)
			{
#ifdef DELTAENGINE_DEBUG
				if (vShader.exists() == false) cout << "[Shader] Vertex shader file doesn't exists!" << endl;
				if (fShader.exists() == false) cout << "[Shader] Fragment shader file doesn't exists!" << endl;
#endif
				return nullptr;
			}

			return new Shader(vShader.read(), fShader.read(), ShaderDataType::SOURCE);
		}

		Shader* Shader::loadFromSource(const string& vertSource, const string& fragSource)
		{
			return new Shader(vertSource, fragSource, ShaderDataType::SOURCE);
		}

		bool Shader::compileAndCheckStatus(GLuint shader, const char* source, string shaderType)
		{
			glShaderSource(shader, 1, &source, NULL);
			glCompileShader(shader);

			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
#ifdef DELTAENGINE_DEBUG
				GLint length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				vector<char> error(length);
				glGetShaderInfoLog(shader, length, &length, &error[0]);
				cout << "[Shader] Failed to compile " << shaderType << " shader!" << endl << &error[0] << endl;
#endif
				glDeleteShader(shader);
				return false;
			}

			return true;
		}

		GLuint Shader::load(const string& vertData, const string& fragData)
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			const char* vertSource = vertData.c_str();
			const char* fragSource = fragData.c_str();

			if (compileAndCheckStatus(vertex, vertSource, "vertex") == false) return 0;
			if (compileAndCheckStatus(fragment, fragSource, "fragment") == false) return 0;

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