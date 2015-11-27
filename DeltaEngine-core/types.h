#pragma once

#ifndef __DELTAENGINE_TYPES__
#define __DELTAENGINE_TYPES__

//#include <Windows.h>

namespace DeltaEngine {
	namespace Types {

		//basic types:
		typedef unsigned char byte;
		typedef unsigned short word;
		typedef unsigned long dword;

		//unix-like types:
		typedef unsigned char uchar8;
		typedef unsigned short ushort16;
		typedef unsigned int uint32;
		typedef unsigned long long uint64;

		typedef signed char schar8;
		typedef signed short sshort16;
		typedef signed int sint32;
		typedef signed long long sint64;

		typedef struct timestamp {
			word Year;
			word Month;
			word DayOfWeek;
			word Day;
			word Hour;
			word Minute;
			word Second;
			word Milliseconds;
		} timestamp;

		typedef struct date {
			word Year;
			word Month;
			word DayOfWeek;
			word Day;
		} date;

		typedef struct time {
			word Hour;
			word Minute;
			word Second;
			word Milliseconds;
		} time;

		/*typedef struct Color {
			Color(byte r, byte g, byte b, byte alpha) : R(r), G(g), B(b), A(alpha) {};
			Color(unsigned int rgba) { R = (rgba >> 24) & 0xFF; G = (rgba >> 16) & 0xFF; B = (rgba >> 8) & 0xFF; A = rgba & 0xFF; };
			Color() : R(0), G(0), B(0), A(0) {};

			unsigned int getColor() { return R << 24 | G << 16 | B << 8 | A; };
			void setColor(unsigned int& rgba) { R = (rgba >> 24) & 0xFF; G = (rgba >> 16) & 0xFF; B = (rgba >> 8) & 0xFF; A = rgba & 0xFF; };
			void setColor(byte r, byte g, byte b, byte alpha) { R = r; G = g; B = b, A = alpha; };

			byte R;
			byte G;
			byte B;
			byte A;
		} Color;*/

		typedef struct Color {
			Color(float r, float g, float b, float alpha) : R(r), G(g), B(b), A(alpha) {};
			Color() : R(0), G(0), B(0), A(0) {};

			void setColor(float r, float g, float b, float alpha) { R = r; G = g; B = b, A = alpha; };

			float R;
			float G;
			float B;
			float A;
		} Color;
	}
}

#endif