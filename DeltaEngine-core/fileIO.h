#pragma once

#ifndef __DELTAENGINE_FILEIO__
#define __DELTAENGINE_FILEIO__

#include <string>

#include "DeltaEngine.h"
#include "errors.h"

using namespace std;

namespace DeltaEngine {
	namespace FileIO {

		class File {
		private:
			unsigned long fSize;
			string path;

		public:
			DELTAENGINE_API File(string path);

			DELTAENGINE_API string read();
			DELTAENGINE_API int write(string data);
			DELTAENGINE_API int append(string data);

			DELTAENGINE_API bool exists();
			//DELTAENGINE_API bool rename(string newName);

			DELTAENGINE_API void changeFilePath(string path);

			DELTAENGINE_API unsigned long getFileSize();
		};

	}
}

#endif