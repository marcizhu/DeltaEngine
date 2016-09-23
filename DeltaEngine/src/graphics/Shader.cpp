#include <GLEW\glew.h>
#include <string>
#include <vector>

#include "shader.h"
#include "fileIO.h"
#include "utils.h"
#include "log.h"
#include "memoryManager.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		Shader::Shader(const string& shader, ShaderSource dType)
		{
			string vertex, fragment;

			switch (dType)
			{
			default:
				DELTAENGINE_ERROR("[Shader] Invalid shader type!"); break;

			case SOURCE:
				preProcess(shader, vertex, fragment);
				shaderID = load(vertex, fragment);
				break;

			case FILE:
				FileIO::File fShader = FileIO::File(shader);

				if (fShader.exists() == false)
				{
					DELTAENGINE_FATAL("[Shader] Shader file doesn't exists!");
					shaderID = 0;
					return;
				}

				preProcess(fShader.read(), vertex, fragment);
				shaderID = load(vertex, fragment);
				break;
			}
		}

		Shader::Shader(const string& vertex, const string& fragment, ShaderSource dType)
		{
			switch (dType)
			{
			default:
				DELTAENGINE_ERROR("[Shader] Invalid shader type!"); break;

			case SOURCE:
				shaderID = load(vertex, fragment); break;

			case FILE:
				FileIO::File vShader = FileIO::File(vertex);
				FileIO::File fShader = FileIO::File(fragment);

				if (vShader.exists() == false || fShader.exists() == false)
				{
					if (vShader.exists() == false) DELTAENGINE_FATAL("[Shader] Vertex shader file doesn't exists!");
					if (fShader.exists() == false) DELTAENGINE_FATAL("[Shader] Fragment shader file doesn't exists!");

					shaderID = 0;
					return;
				}

				shaderID = load(vShader.read(), fShader.read());
				break;
			}
		}

		Shader* Shader::loadFromFile(const string& vertPath, const string& fragPath)
		{
			return NEW Shader(vertPath, fragPath, FILE);
		}

		Shader* Shader::loadFromFile(const string& file)
		{
			return NEW Shader(file, FILE);
		}

		Shader* Shader::loadFromSource(const string& vertSource, const string& fragSource)
		{
			return NEW Shader(vertSource, fragSource, SOURCE);
		}

		Shader* Shader::loadFromSource(const string& source)
		{
			return NEW Shader(source, SOURCE);
		}

		bool Shader::compile(GLuint shader, const char* source, uint32 shaderType)
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

				switch (shaderType)
				{
				case GL_VERTEX_SHADER:
					DELTAENGINE_FATAL("[Shader] Failed to compile vertex shader!\n", &error[0]); break;

				case GL_FRAGMENT_SHADER:
					DELTAENGINE_FATAL("[Shader] Failed to compile fragment shader!\n", &error[0]); break;

				default:
					DELTAENGINE_FATAL("[Shader] Failed to compile unknown type shader!\n", &error[0]); break;
				}

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

			if (compile(vertex, vertSource, GL_VERTEX_SHADER) == false) return 0;
			if (compile(fragment, fragSource, GL_FRAGMENT_SHADER) == false) return 0;

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

				if (location == -1)
				{
					DELTAENGINE_ERROR("[Shader] Could not find uniform \'", name, "\' in shader!");
					return 0;
				}

				uniformLocations[name] = location;
			}

			return location;
		}

		std::vector<std::string> Shader::preProcess(const std::string& input, std::string& vertexOut, std::string& fragmentOut)
		{
			std::vector<std::string> file = Utils::splitString(input, '\n');

			vertexOut = fragmentOut = "";

			//0 = unknown, 1 = vertex, 2 = fragment
			byte shaderType = 0;

			for (uint32 i = 0; i < file.size(); i++)
			{
				if (file[i].find("#shader") != std::string::npos)
				{
					if (file[i].find("vertex") != std::string::npos)
					{
						shaderType = 1;
						continue;
					}
					else if (file[i].find("fragment") != std::string::npos)
					{
						shaderType = 2;
						continue;
					}

					shaderType = 0;
				}

				switch (shaderType)
				{
				case 1:
					vertexOut.append(file[i]);
					vertexOut.append("\n");
					break;

				case 2:
					fragmentOut.append(file[i]);
					fragmentOut.append("\n");
					break;

				default:
					DELTAENGINE_FATAL("Unknown shader type!");
					break;
				}
			}

			return file;
		}

	}
}