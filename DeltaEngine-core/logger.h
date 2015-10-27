#pragma once

#ifndef __DELTAENGINE_LOGGER__
#define __DELTAENGINE_LOGGERR__

#include "DeltaEngine.h"

#include <string>

using namespace std;

namespace DeltaEngine {
	namespace Logger {

		class Logger {
		private:
			bool _showTime = false;
			bool _showDate = false;
			bool _showTags = false;
			bool _showGameName = false;

			string gameName;
			string file;

		public:
			DELTAENGINE_API inline Logger(string file) { this->file = file; }

			DELTAENGINE_API inline void showTime() { this->_showTime = true; }
			DELTAENGINE_API inline void showDate() { this->_showDate = true; }
			DELTAENGINE_API inline void showTags() { this->_showTags = true; }
			DELTAENGINE_API inline void showGameName(string gameName) { this->_showGameName = true; this->gameName = gameName; }

			DELTAENGINE_API int Log(const string& tag, unsigned char align, const string& message) const;
			DELTAENGINE_API int Log(const string& message) const;
		};

	}
}

#endif