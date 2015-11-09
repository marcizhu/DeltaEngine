#include <string>
#include <Windows.h>

#include "logger.h"
#include "utils.h"
#include "types.h"
#include "fileIO.h"
#include "errors.h"

using namespace std;
using namespace DeltaEngine;

namespace DeltaEngine {
	namespace Logger {

		int Logger::Log(const string& tag, unsigned char align, const string& message) const
		{
			string result = "";

			if (this->_showDate)
			{
				Types::date t = Utils::timestampToDate(Utils::getSystemTime());
				result += "[" + to_string(t.Day) + "/" + to_string(t.Month) + "/" + to_string(t.Year) + "] ";
			}

			if (this->_showTime)
			{
				Types::time t = Utils::timestampToTime(Utils::getSystemTime());
				result += "[" + to_string(t.Hour) + ":" + to_string(t.Minute) + ":" + to_string(t.Second) + "] ";
			}

			result += "[";
			//unsigned char() casting needed!
			if ((align - unsigned char(tag.size())) > 0)
			{

				int spc1 = (align - tag.size()) / 2;
				int spc2 = ((align - tag.size()) / 2) + ((align - tag.size()) % 2);

				for (int i = 0; i < spc1; i++)
				{
					result += " ";
				}

				result += tag;

				for (int i = 0; i < spc2; i++)
				{
					result += " ";
				}
			} else if (tag.size() - align == 0)
			{
				result += tag;
			} else return -ERR_INVALID_ARGUMENT;
			result += "] ";

			if (this->_showGameName)
			{
				if(this->gameName == "") return -ERR_EXPECTED_ARGUMENT;
				result += "[" + gameName + "] ";
			}

			result += message + "\r\n";

			return FileIO::File(this->file).append(result);
		}

		int Logger::Log(const string& message) const
		{
			if (this->_showTags) return -ERR_EXPECTED_ARGUMENT;

			string result = "";

			if (this->_showDate)
			{
				Types::date t = Utils::timestampToDate(Utils::getSystemTime());
				result += "[" + to_string(t.Day) + "/" + to_string(t.Month) + "/" + to_string(t.Year) + "] ";
			}

			if (this->_showTime)
			{
				Types::time t = Utils::timestampToTime(Utils::getSystemTime());
				result += "[" + to_string(t.Hour) + ":" + to_string(t.Minute) + ":" + to_string(t.Second) + "] ";
			}

			if (this->_showGameName && this->gameName != "")
			{
				result += "[" + gameName + "] ";
			} else return -ERR_EXPECTED_ARGUMENT;

			result += message + "\r\n";
			
			return FileIO::File(this->file).append(result);
		}
	}
}