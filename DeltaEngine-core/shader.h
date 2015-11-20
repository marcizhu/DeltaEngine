#pragma once

#ifndef __DELTAENGINE_SHADER__
#define __DELTAENGINE_SHADER__

#include <string>
#include <GLEW\glew.h>

#include "DeltaEngine.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "Matrix4.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		class Shader
		{
		private:
			GLuint shaderID;
			string vertPath;
			string fragPath;

			GLuint load();
			GLint getUniformLocation(const GLchar* name) { return glGetUniformLocation(shaderID, name); };

		public:
			DELTAENGINE_API Shader(string vertPath, string fragPath);
			DELTAENGINE_API ~Shader() { glDeleteProgram(shaderID); };

			DELTAENGINE_API void setUniform1f(const GLchar* name, float value) { glUniform1f(getUniformLocation(name), value); };
			DELTAENGINE_API void setUniform1i(const GLchar* name, int value) { glUniform1i(getUniformLocation(name), value); };
			DELTAENGINE_API void setUniform2f(const GLchar* name, const Maths::Vector2D& vector) { glUniform2f(getUniformLocation(name), vector.x, vector.y); };
			DELTAENGINE_API void setUniform3f(const GLchar* name, const Maths::Vector3D& vector) { glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);	};
			DELTAENGINE_API void setUniform4f(const GLchar* name, const Maths::Vector4D& vector) { glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w); };
			DELTAENGINE_API void setUniformMat4(const GLchar* name, const Maths::Matrix4& matrix) {	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);	};
						    
			DELTAENGINE_API void enable() const { glUseProgram(this->shaderID); };
			DELTAENGINE_API void disable() const { glUseProgram(0); };
		};

	}
}

#endif