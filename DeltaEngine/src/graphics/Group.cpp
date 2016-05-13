#include "group.h"

namespace DeltaEngine {
	namespace Graphics {

		Group::~Group()
		{
			for (Types::uint32 i = 0; i < renderables.size(); i++)
				delete renderables[i];
		}

		void Group::add(Renderable2D* renderable)
		{
			renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push(transformationMatrix);

			for (const Renderable2D* renderable : renderables)
				renderable->submit(renderer, true);

			renderer->pop();
		}
	}
}
