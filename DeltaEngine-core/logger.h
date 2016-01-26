#pragma once

#include <string>

#include "DeltaEngine.h"

//using namespace std;

namespace DeltaEngine {
	namespace Logger {

		class Logger {
		private:
			bool _showTime = false;
			bool _showDate = false;
			bool _showTags = false;
			bool _showGameName = false;

			std::string gameName;
			std::string file;

		public:
			DELTAENGINE_API inline Logger(std::string file) { this->file = file; }

			DELTAENGINE_API inline void showTime() { this->_showTime = true; }
			DELTAENGINE_API inline void showDate() { this->_showDate = true; }
			DELTAENGINE_API inline void showTags() { this->_showTags = true; }
			DELTAENGINE_API inline void showGameName(std::string gameName) { this->_showGameName = true; this->gameName = gameName; }

			DELTAENGINE_API int Log(const std::string& tag, unsigned char align, const std::string& message) const;
			DELTAENGINE_API int Log(const std::string& message) const;
		};

	}
}