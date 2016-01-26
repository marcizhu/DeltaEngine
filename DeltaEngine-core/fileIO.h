#pragma once

#include <string>

#include "DeltaEngine.h"
#include "errors.h"
#include "types.h"

//using namespace std;
//using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace FileIO {

		class File {
		private:
			Types::uint32 fSize;
			std::string path;

		public:
			DELTAENGINE_API File(std::string path);

			DELTAENGINE_API std::string read();
			DELTAENGINE_API int write(std::string data);
			DELTAENGINE_API int append(std::string data);

			DELTAENGINE_API bool exists();
			//DELTAENGINE_API bool rename(string newName);

			DELTAENGINE_API void changeFilePath(std::string path);

			DELTAENGINE_API Types::uint32 getFileSize();
		};

	}
}