#include <string>

#include "logger.h"
#include "utils.h"
#include "types.h"
#include "fileIO.h"
#include "log.h"

using namespace std;

namespace DeltaEngine {
	namespace Utils {

		void Logger::Log(const string& tag, unsigned char align, const string& message) const
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
			}
			else
			{
				DELTAENGINE_ERROR("[Logger] Invalid argument!");
				return;
			}

			result += "] ";

			if (this->_showGameName)
			{
				if(this->gameName == "")
				{
					DELTAENGINE_ERROR("[Logger] Expected an argument!!");
					return;
				}

				result += "[" + gameName + "] ";
			}

			result += message + "\r\n";

			FileIO::File(this->file).append(result);
		}

		void Logger::Log(const string& message) const
		{
			if (this->_showTags)
			{
				DELTAENGINE_ERROR("[Logger] Expected an argument!!");
				return;
			}

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
			}
			else
			{
				DELTAENGINE_ERROR("[Logger] Expected an argument!!");
				return;
			}

			result += message + "\r\n";

			FileIO::File(this->file).append(result);
		}
	}
}