#pragma once

#include "vector2d.h"
#include "vector4d.h"

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

#pragma pack(push, S_COLOR, 1)
		typedef struct Color {
			Color(byte r, byte g, byte b, byte alpha) : R(r), G(g), B(b), A(alpha) {};
			Color(uint32 rgba) { R = (rgba >> 24) & 0xFF; G = (rgba >> 16) & 0xFF; B = (rgba >> 8) & 0xFF; A = rgba & 0xFF; };
			Color() : R(0), G(0), B(0), A(0) {};

			uint32 getABGRColor() const { return A << 24 | B << 16 | G << 8 | R; };
			uint32 getARGBColor() const { return A << 24 | R << 16 | G << 8 | B; };
			uint32 getBGRAColor() const { return B << 24 | G << 16 | R << 8 | A; };
			uint32 getRGBAColor() const { return R << 24 | G << 16 | B << 8 | A; };
			
			uint32 getBGRColor() const { return B << 16 | G << 8 | R; };
			uint32 getRGBColor() const { return R << 16 | G << 8 | B; };
			
			void setColor(uint32& rgba) { R = (rgba >> 24) & 0xFF; G = (rgba >> 16) & 0xFF; B = (rgba >> 8) & 0xFF; A = rgba & 0xFF; };
			void setColor(byte r, byte g, byte b, byte alpha) { R = r; G = g; B = b, A = alpha; };
			
			// HACK: This way we have an ABGR color (little-endian)
			byte R;
			byte G;
			byte B;
			byte A;
		} Color;
#pragma pack(pop, S_COLOR)

#pragma pack(push, S_VERTEX_DATA, 1)
		struct VertexData
		{
			Maths::Vector2D vertex;
			Maths::Vector2D uv;
			float tid;
			unsigned int color; //ABGR format
		};
#pragma pack(pop, S_VERTEX_DATA)

	}
}