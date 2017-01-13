#include <sys/stat.h>
#include <stdio.h>

#include "fileIO.h"
#include "types.h"
#include "memoryManager.h"

namespace DeltaEngine {
	namespace FileIO {

		std::string File::read() const
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "r");

			if (file == nullptr)
			{
				DELTAENGINE_ERROR("[FileIO] Unable to read the file!");
				return std::string("");
			}

			char* data = NEW char[getFileSize() + 1];
			memset(data, 0, getFileSize() + 1);
			fread(data, 1, getFileSize(), file);
			fclose(file);

			std::string result(data);

			delete[] data;
			return result;
		}

		Types::byte* File::readBinary() const
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "rb");

			if (file == nullptr)
			{
				DELTAENGINE_ERROR("[FileIO] Unable to read the binary file!");
				return nullptr;
			}

			Types::byte* data = NEW Types::byte[getFileSize() + 1];
			memset(data, 0, getFileSize() + 1);
			fread(data, 1, getFileSize(), file);
			fclose(file);

			//delete[] data; // TODO: Fix memory leak!
			return data;
		}

		void File::write(std::string data)
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "w");

			if (file == nullptr)
			{
				DELTAENGINE_ERROR("[FileIO] Unable to create the file!");
				return;
			}

			fputs(data.c_str(), file);
			fclose(file);

			this->fSize = getFileSize();
		}

		void File::append(std::string data)
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "a");

			if (file == nullptr)
			{
				DELTAENGINE_ERROR("[FileIO] Unable to create the file!");
				return;
			}

			fputs(data.c_str(), file);
			fclose(file);

			this->fSize = getFileSize();
		}

		bool File::exists() const
		{
			struct stat buffer;
			return (stat(this->path.c_str(), &buffer) == 0);
		}

		void File::changeFilePath(std::string path)
		{
			this->path = path;
			this->fSize = getFileSize();
		}

		Types::uint32 File::getFileSize() const
		{
			FILE* file;
			fopen_s(&file, this->path.c_str(), "r");

			if (file == nullptr)
			{
				DELTAENGINE_ERROR("[FileIO] Unable to read the file size!");
				return 0 ;
			}

			fseek(file, 0, SEEK_END);
			Types::uint32 len = ftell(file);

			fclose(file);

			return len;
		}
	}
}