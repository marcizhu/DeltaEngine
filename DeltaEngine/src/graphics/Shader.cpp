#include <GLEW\glew.h>
#include <string>
#include <vector>

#include "shader.h"
#include "fileIO.h"
#include "log.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		//TODO: Allow the user to load vertex + fragment shaders at once (both in the same file)
		Shader::Shader(const string& vertex, const string& fragment, ShaderDataType dType)
		{
			switch (dType)
			{
			default:
				cout << "[Shader] Invalid shader type!" << endl; break;

			case SOURCE:
				shaderID = load(vertex, fragment); break;

			case FILE:
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
				break;
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

			return new Shader(vShader.read(), fShader.read(), SOURCE);
		}

		Shader* Shader::loadFromSource(const string& vertSource, const string& fragSource)
		{
			return new Shader(vertSource, fragSource, SOURCE);
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
				std::vector<char> error(length);
				glGetShaderInfoLog(shader, length, &length, &error[0]);
				std::cout << "[Shader] Failed to compile " << shaderType << " shader!" << std::endl << &error[0] << std::endl;
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

			glDetachShader(program, vertex);
			glDetachShader(program, fragment);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			auto it = uniformLocations.find(std::string(name));
			GLint location;

			if (it != uniformLocations.end())
			{
				location = it->second;
			}
			else
			{
				location = glGetUniformLocation(shaderID, name);
				if (location == -1) DELTAENGINE_ERROR("Could not find uniform \'", name, "\' in shader!");
			
				uniformLocations[name] = location;
			}

			return location;
		}

	}
}