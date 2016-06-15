#pragma once

namespace DeltaEngine {
	namespace Physics {

		class Force
		{
		private:
			float force;
			float angle;
			float duration; // in seconds;

		public:
			Force(float force, float angle, float duration) : force(force), angle(angle), duration(duration) { };
		};

	}
}