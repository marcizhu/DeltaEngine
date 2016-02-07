#include <GLEW\glew.h>
#include <string>
#include <vector>

#include "shader.h"
#include "fileIO.h"
#include "utils.h"
#include "log.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		Shader::Shader(const string& shader, ShaderSource dType)
		{
			string vertex, fragment;
			std::vector<std::string> temp;

			switch (dType)
			{
			default:
				DELTAENGINE_ERROR("[Shader] Invalid shader type!"); break;

			case SOURCE:
				temp = preProcess(shader, vertex, fragment);
				shaderID = load(vertex, fragment);
				parseUniforms(temp);
				break;

			case FILE:
				FileIO::File fShader = FileIO::File(shader);

				if (fShader.exists() == false)
				{
					DELTAENGINE_FATAL("[Shader] Shader file doesn't exists!");
					shaderID = 0;
					return;
				}

				temp = preProcess(fShader.read(), vertex, fragment);
				shaderID = load(vertex, fragment);
				parseUniforms(temp);
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
			return new Shader(vertPath, fragPath, FILE);
		}

		Shader* Shader::loadFromFile(const string& file)
		{
			return new Shader(file, FILE);
		}

		Shader* Shader::loadFromSource(const string& vertSource, const string& fragSource)
		{
			return new Shader(vertSource, fragSource, SOURCE);
		}

		Shader* Shader::loadFromSource(const string& source)
		{
			return new Shader(source, SOURCE);
		}

		bool Shader::compileAndCheckStatus(GLuint shader, const char* source, const string& shaderType)
		{
			glShaderSource(shader, 1, &source, NULL);
			glCompileShader(shader);

			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(shader, length, &length, &error[0]);
				DELTAENGINE_FATAL("[Shader] Failed to compile ", shaderType, " shader!\n", &error[0]);
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

		// TODO: Detect unused uniforms
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
				if (location == -1) DELTAENGINE_ERROR("[Shader] Could not find uniform \'", name, "\' in shader!");

				uniformLocations[name] = location;
				// just to test if it really works, you can delete it without a problem :)
				DELTAENGINE_INFO("[Shader] Caching uniform \'", name, '\'');
			}

			return location;
		}

		void Shader::parseUniforms(const std::vector<std::string>& source)
		{
			for (uint32 i = 0; i < source.size(); i++)
			{
				if (source[i].find("uniform") != string::npos)
				{
					std::vector<std::string> line = Utils::splitString(source[i], ' ');
					
					for (uchar8 j = 0; j < line.size(); j++)
					{
						if (getUniformType(line[j]) != UniformType::NONE)
						{
							string name = line[j + 1];
							if (name[name.size() - 1] == ';') name = name.substr(0, name.size() - 1);
						
							uint32 start = name.find('[');
							if (start != string::npos)
							{
								name = name.substr(0, start);
								uint32 end = line[j + 1].find(']');
								//uint32 count = atoi(line[j + 1].substr(start + 1, end - start - 1).c_str());
							}

							GLint location = glGetUniformLocation(shaderID, name.c_str());
							if (location >= 0) uniformLocations[name] = location;
						}
					}
				}
			}
		}

		UniformType Shader::getUniformType(const string& token)
		{
			if (token == "float") return UniformType::FLOAT32;
			if (token == "int") return UniformType::INT32;
			if (token == "vec2") return UniformType::VEC2;
			if (token == "vec3") return UniformType::VEC3;
			if (token == "vec4") return UniformType::VEC4;
			if (token == "mat3") return UniformType::MAT3;
			if (token == "mat4") return UniformType::MAT4;
			if (token == "sampler2D") return UniformType::SAMPLER2D;

			return UniformType::NONE;
		}

		std::vector<std::string> Shader::preProcess(const std::string& input, std::string& vertexOut, std::string& fragmentOut)
		{
			std::vector<std::string> file = Utils::splitString(input, '\n');
			
			vertexOut = "";
			fragmentOut = "";

			//0 = unknown, 1 = vertex, 2 = fragment
			byte shaderType = 0;

			for (uint32 i = 0; i < file.size(); i++)
			{
				if (file[i].find("#shader vertex") != std::string::npos)
				{
					shaderType = 1;
					continue;
				}
				if (file[i].find("#shader fragment") != std::string::npos)
				{
					shaderType = 2;
					continue;
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
					DELTAENGINE_FATAL("Unknown shader type!"); break;
				}
			}

			return file;
		}

	}
}