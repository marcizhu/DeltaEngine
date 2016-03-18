#include <sys/stat.h>
#include <stdio.h>

#include "fileIO.h"
#include "types.h"
#include "memoryManager.h"

using namespace DeltaEngine::Types;

namespace DeltaEngine {
	namespace FileIO {

		File::File(std::string path)
		{
			this->path = path;
			this->fSize = getFileSize();
		}

		std::string File::read()
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "r");
			if (file == nullptr) return std::string("");

			char* data = NEW char[getFileSize() + 1];
			memset(data, 0, getFileSize() + 1);
			fread(data, 1, getFileSize(), file);
			fclose(file);

			std::string result(data);

			delete[] data;
			return result;
		}

		int File::write(std::string data)
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "w");
			if (file == nullptr) return -ERR_CREATING_FILE;

			fputs(data.c_str(), file);
			fclose(file);

			this->fSize = getFileSize();
			return 0;
		}

		int File::append(std::string data)
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "a");
			if (file == nullptr) return -ERR_CREATING_FILE;

			fputs(data.c_str(), file);
			fclose(file);

			this->fSize = getFileSize();
			return 0;
		}

		bool File::exists()
		{
			struct stat buffer;
			return (stat(this->path.c_str(), &buffer) == 0);
		}

		void File::changeFilePath(std::string path)
		{
			this->path = path;
			this->fSize = getFileSize();
		}

		uint32 File::getFileSize()
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "r");
			if (file == nullptr) return 0;

			fseek(file, 0, SEEK_END);
			uint32 len = ftell(file);

			fclose(file);

			return len;
		}
	}
}