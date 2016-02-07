#pragma once

#include <string>
#include <unordered_map>
#include <GLEW\glew.h>

#include "internal.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "Matrix4.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		enum ShaderSource { FILE, SOURCE };
		enum UniformType { NONE, FLOAT32, INT32, VEC2, VEC3, VEC4, MAT3, MAT4, SAMPLER2D };

		class Shader
		{
		private:
			GLuint shaderID;
			std::unordered_map<std::string, GLint> uniformLocations;

			GLuint load(const string& vertPath, const string& fragPath);
			GLint getUniformLocation(const GLchar* name);

			bool compileAndCheckStatus(GLuint shader, const char* source, const string& shaderType);
			vector<string> preProcess(const std::string& input, std::string& vertexOut, std::string& fragmentOut);
			void parseUniforms(const std::vector<string>& source);
			UniformType getUniformType(const string& token);

		public:
			DELTAENGINE_API Shader(const string& vertex, const string& fragment, ShaderSource dType);
			DELTAENGINE_API Shader(const string& file, ShaderSource dType);
			DELTAENGINE_API ~Shader() { glDeleteProgram(shaderID); };
			
			DELTAENGINE_API void setUniform1f(const GLchar* name, float x) { glUniform1f(getUniformLocation(name), x); };
			DELTAENGINE_API void setUniform2f(const GLchar* name, float x, float y) { glUniform2f(getUniformLocation(name), x, y); };
			DELTAENGINE_API void setUniform3f(const GLchar* name, float x, float y, float z) { glUniform3f(getUniformLocation(name), x, y, z); };
			DELTAENGINE_API void setUniform4f(const GLchar* name, float x, float y, float z, float w) { glUniform4f(getUniformLocation(name), x, y, z, w); };

			DELTAENGINE_API void setUniform1i(const GLchar* name, int x) { glUniform1i(getUniformLocation(name), x); };
			DELTAENGINE_API void setUniform2i(const GLchar* name, int x, int y) { glUniform2i(getUniformLocation(name), x, y); };
			DELTAENGINE_API void setUniform3i(const GLchar* name, int x, int y, int z) { glUniform3i(getUniformLocation(name), x, y, z); };
			DELTAENGINE_API void setUniform4i(const GLchar* name, int x, int y, int z, int w) { glUniform4i(getUniformLocation(name), x, y, z, w); };
						    
			DELTAENGINE_API void setUniform2f(const GLchar* name, const Maths::Vector2D& vector) { glUniform2f(getUniformLocation(name), vector.x, vector.y); };
			DELTAENGINE_API void setUniform3f(const GLchar* name, const Maths::Vector3D& vector) { glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);	};
			DELTAENGINE_API void setUniform4f(const GLchar* name, const Maths::Vector4D& vector) { glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w); };
			
			DELTAENGINE_API void setUniformMat4(const GLchar* name, const Maths::Matrix4& matrix) {	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);	};
			
			DELTAENGINE_API void setUniform1iv(const GLchar* name, int* value, int count) { glUniform1iv(getUniformLocation(name), count, value); }

			DELTAENGINE_API void enable() const { glUseProgram(this->shaderID); };
			DELTAENGINE_API void disable() const { glUseProgram(0); };

			DELTAENGINE_API GLuint getShaderID() const { return this->shaderID; };

			DELTAENGINE_API static Shader* loadFromFile(const string& vertPath, const string& fragPath);
			DELTAENGINE_API static Shader* loadFromFile(const string& file);
			DELTAENGINE_API static Shader* loadFromSource(const string& vertSource, const string& fragSource);
			DELTAENGINE_API static Shader* loadFromSource(const string& source);
		};

	}
}