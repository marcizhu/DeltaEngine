#pragma once

#include "internal.h"
#include "vector2d.h"
#include "vector3d.h"
#include "PlatformLog.h"

#define DELTAENGINE_LOG_LEVEL_FATAL 0
#define DELTAENGINE_LOG_LEVEL_ERROR 1
#define DELTAENGINE_LOG_LEVEL_WARN  2
#define DELTAENGINE_LOG_LEVEL_INFO  3

/*namespace std {

	template <typename T>
	std::string to_string(const T& t)
	{ 
		return std::string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)"); 
	}

}*/

namespace DeltaEngine {
	namespace Internal {

		template <typename T>
		static const char* to_string(const T& t) { return std::string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)").c_str(); }

		template <>
		static const char* to_string<char>(char const& t) { return &t; }

		template <>
		static const char* to_string<char*>(char* const& t) { return t; }

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t) { return (const char*)t; }

		template <>
		static const char* to_string<char const*>(char const* const& t) { return t; }

		template <>
		static const char* to_string<std::string>(const std::string& t) { return t.c_str(); }

		template <>
		static const char* to_string<bool>(const bool& t) { return t ? "true" : "false"; }

		template <>
		static const char* to_string<Maths::Vector2D>(const Maths::Vector2D& t)
		{
			// TODO: sprintf
			std::string string = std::string("Vector2D: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
			char* result = new char[string.length()];
			strcpy_s(result, string.length(), &string[0]);
			return result;
		}

		template <> 
		static const char* to_string<Maths::Vector3D>(const Maths::Vector3D& t)
		{
			// TODO: sprintf
			std::string string = std::string("Vector3D: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ", " + std::to_string(t.z) + ")";
			char* result = new char[string.length()];
			strcpy_s(result, string.length(), &string[0]);
			return result;
		}

		template <typename T>
		static std::string format_iterators(T& begin, T& end)
		{
			std::string result;
			bool first = true;
			while (begin != end)
			{
				if (!first) result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int& position, First&& first)
		{
			const char* formatted = DeltaEngine::Internal::to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&&... args)
		{
			const char* formatted = DeltaEngine::Internal::to_string<First>(first);
			int length = strlen(formatted);
			
			memcpy(&buffer[position], formatted, length);
			position += length;
			
			if (sizeof...(Args)) print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(int level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline) buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}

	}
}


#ifndef DELTAENGINE_LOG_LEVEL
	#define DELTAENGINE_LOG_LEVEL DELTAENGINE_LOG_LEVEL_INFO
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_FATAL
	#define DELTAENGINE_FATAL(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_FATAL, true, "DELTAENGINE: ", __VA_ARGS__)
	#define _DELTAENGINE_FATAL(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
	#define DELTAENGINE_FATAL(...)
	#define _DELTAENGINE_FATAL(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_ERROR
	#define DELTAENGINE_ERROR(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_ERROR, true, "DELTAENGINE: ", __VA_ARGS__)
	#define _DELTAENGINE_ERROR(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
	#define DELTAENGINE_ERROR(...)
	#define _DELTAENGINE_ERROR(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_WARN
	#define DELTAENGINE_WARN(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_WARN, true, "DELTAENGINE: ", __VA_ARGS__)
	#define _DELTAENGINE_WARN(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
	#define DELTAENGINE_WARN(...)
	#define _DELTAENGINE_WARN(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_INFO
	#define DELTAENGINE_INFO(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_INFO, true, "DELTAENGINE: ", __VA_ARGS__)
	#define _DELTAENGINE_INFO(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
	#define DELTAENGINE_INFO(...)
	#define _DELTAENGINE_INFO(...)
#endif

#ifdef DELTAENGINE_DEBUG
	#define DELTAENGINE_ASSERT(x, ...) \
		if (!(x)) {\
			DELTAENGINE_FATAL("*************************"); \
			DELTAENGINE_FATAL("    ASSERTION FAILED!    "); \
			DELTAENGINE_FATAL("*************************"); \
			DELTAENGINE_FATAL(__FILE__, ": ", __LINE__); \
			DELTAENGINE_FATAL("Condition: ", #x); \
			DELTAENGINE_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
	#define DELTAENGINE_ASSERT(x, ...)
#endif