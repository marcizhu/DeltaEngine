#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include "utils.h"
#include "types.h"
#include "PlatformUtils.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		Types::timestamp getSystemTime()
		{
			return Platform::getSystemTime();
		}

		Types::timestamp getUTCTime()
		{
			return Platform::getUTCTime();
		}

		Types::time timestampToTime(const Types::timestamp& t)
		{
			Types::time ret;
			memcpy_s(&ret, sizeof(ret), &t.Hour, sizeof(ret));
			return ret;
		}

		Types::date timestampToDate(const Types::timestamp& t)
		{
			Types::date ret;
			memcpy_s(&ret, sizeof(ret), &t.Year, sizeof(ret));
			return ret;
		}

		string getCurrentPath()
		{
			char path[1024];
			memset(path, 0, 1024);
			if (!GetCurrentDir(path, sizeof(path))) return string("NULL");

			return path;
		}

		vector<string> splitString(const std::string& str, char delimiter)
		{
			vector<string> split;
			stringstream ss(str);
			string item;

			while (getline(ss, item, delimiter)) split.push_back(item);

			return split;
		}

		void gotoxy(int x, int y)
		{
			Platform::PlatformGotoxy(x, y);
		}

		void setConsoleColor(int color)
		{
			Platform::PlatformSetConsoleColor(color);
		}

		string precision_to_string(const float val, char n)
		{
			std::ostringstream out;
			out << std::setprecision(n) << val;
			return out.str();
		}

		Physics::PhysicsRenderable2D* toPhysicsRenderable(const Graphics::Renderable2D* renderable)
		{
			Physics::PhysicsRenderable2D* object = dynamic_cast<Physics::PhysicsRenderable2D*>(const_cast<Graphics::Renderable2D*>(renderable));

			DELTAENGINE_ASSERT(object != nullptr, "The renderable is not an instance of a physicsRenderable2D object!");

			return object;
		}

	}
}