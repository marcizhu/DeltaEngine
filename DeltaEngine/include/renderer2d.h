#pragma once

#include <string>

#include "internal.h"
#include "vector2d.h"
#include "types.h"
#include "font.h"
#include "stack.h"
#include "matrix4.h"
//#include "log.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			const Maths::Matrix4* transformationStackTop;
			Utils::Stack<Maths::Matrix4> transformationStack;

			Renderer2D()
			{
				transformationStack.push(Maths::Matrix4::identity());
				transformationStackTop = &transformationStack.top();
			}

		public:
			DELTAENGINE_API virtual ~Renderer2D() { };

			void push(const Maths::Matrix4& matrix, bool override = false)
			{
				transformationStack.push(override ? matrix : matrix * transformationStack.top());
				transformationStackTop = &transformationStack.top();
			}

			void pop()
			{
				if (transformationStack.size() > 1)
				{
					transformationStack.pop();
					transformationStackTop = &transformationStack.top();
				}
				/*else
				{
					DELTAENGINE_ERROR("Attempted to pop the identity matrix from the transformation stack!");
				}*/
			}


			DELTAENGINE_API virtual void begin() { };
			DELTAENGINE_API virtual void submit(const Renderable2D* renderable, bool stransformationStack = false) = 0;
			DELTAENGINE_API virtual void end() { };
			DELTAENGINE_API virtual void flush() = 0;

			DELTAENGINE_API virtual void drawString(const std::string& text, const Maths::Vector2D& position, const Font& font, const Types::uint32 color) { };
			DELTAENGINE_API virtual void drawLine(const Maths::Vector2D& start, const Maths::Vector2D& end, float thickness, unsigned int color) { };
		};

	}
}
