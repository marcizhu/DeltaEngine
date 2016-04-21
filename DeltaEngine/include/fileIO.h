#pragma once

#include <string>

#include "internal.h"
#include "errors.h"
#include "types.h"

using namespace std;
using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace FileIO {

		class File {
		private:
			uint32 fSize;
			string path;

		public:
			DELTAENGINE_API File(string path);

			DELTAENGINE_API string read();
			DELTAENGINE_API int write(string data);
			DELTAENGINE_API int append(string data);

			DELTAENGINE_API bool exists();
			//DELTAENGINE_API bool rename(string newName);

			DELTAENGINE_API void changeFilePath(string path);

			DELTAENGINE_API uint32 getFileSize();
		};

	}
}