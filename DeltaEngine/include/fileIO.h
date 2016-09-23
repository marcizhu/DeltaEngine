#pragma once

#include <string>

#include "internal.h"
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
			DELTAENGINE_API File(string path) : path(path) { fSize = getFileSize(); };

			DELTAENGINE_API string read() const;
			DELTAENGINE_API Types::byte* readBinary() const;
			DELTAENGINE_API void write(string data);
			DELTAENGINE_API void append(string data);

			DELTAENGINE_API bool exists() const;

			DELTAENGINE_API void changeFilePath(string path);

			DELTAENGINE_API uint32 getFileSize() const;
		};

	}
}