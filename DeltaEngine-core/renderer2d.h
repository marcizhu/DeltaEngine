#pragma once

#include "DeltaEngine.h"
#include "renderable2d.h"
#include "stack.h"

namespace DeltaEngine {
	namespace Graphics {

		class Renderer2D
		{
		protected:
			const Maths::Matrix4* transformationStackTop;
			Utils::Stack<Maths::Matrix4> transformationStack;

			Renderer2D()
			{
				transformationStack.push(Maths::Matrix4::identity());
				transformationStackTop = &transformationStack.front();
			}

		public:
			void push(const Maths::Matrix4& matrix, bool override = false)
			{
				transformationStack.push(override ? matrix : matrix * transformationStack.front());
				transformationStackTop = &transformationStack.front();
			}

			void pop()
			{
				if (transformationStack.size() > 1) transformationStack.pop();
				transformationStackTop = &transformationStack.front();
			}

			DELTAENGINE_API virtual void begin() { };
			DELTAENGINE_API virtual void submit(const Renderable2D* renderable) = 0;
			DELTAENGINE_API virtual void end() { };
			DELTAENGINE_API virtual void flush() = 0;
		};

	}
}
