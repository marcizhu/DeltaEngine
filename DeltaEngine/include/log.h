#pragma once

#ifdef DELTAENGINE_RELEASE
#	pragma warning(disable:4390)
#endif

#pragma warning(disable:4996)

#include <sstream>

#include "internal.h"
#include "vector2d.h"
#include "vector3d.h"
#include "PlatformUtils.h"
#include "LogLevels.h"
#include "debug.h"

//namespace std {

	template <typename T>
	std::string to_string(const T& t)
	{
		return std::string("[Unsupported type (") + typeid(T).name() + std::string(")!] (to_string)");
	}

//}

using namespace std;

namespace DeltaEngine {
	namespace Internal {

		static char to_string_buffer[10240];
		static char sprintf_buffer[10240];

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t) { return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>()); }

		template <>
		static const char* to_string<char>(char const& t) { return &t; }

		template <>
		static const char* to_string<char*>(char* const& t) { return t; }

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t) { return (const char*)t; }

		template <>
		static const char* to_string<char const*>(char const* const& t) { return t; }

		template <>
		static const char* to_string<unsigned short>(const unsigned short& t)
		{
			std::stringstream ss;
			ss << t;

			return ss.str().c_str();
		}

		template <>
		static const char* to_string<std::string>(const std::string& t) { return t.c_str(); }

		template <>
		static const char* to_string<bool>(const bool& t) { return t ? "true" : "false"; }

		template <>
		static const char* to_string<Maths::Vector2D>(const Maths::Vector2D& t)
		{
			// TODO: sprintf
			std::string string = t.toString();

			char* result = new char[string.length()]; // TODO: Fix memory leak
			return strcpy(result, &string[0]);
		}

		template <>
		static const char* to_string<Maths::Vector3D>(const Maths::Vector3D& t)
		{
			// TODO: sprintf
			std::string string = t.toString();
			char* result = new char[string.length()]; // TODO: Fix memory leak
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

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = std::to_string(t);
			return strcpy(to_string_buffer, x.c_str());
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

			Platform::PlatformLogMessage(level, buffer);
		}

	}
}


#ifndef DELTAENGINE_LOG_LEVEL
	#define DELTAENGINE_LOG_LEVEL DELTAENGINE_LOG_LEVEL_TRACE
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_FATAL && defined(DELTAENGINE_DEBUG)
	#define DELTAENGINE_FATAL(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_FATAL, true, "DeltaEngine: ", __VA_ARGS__)
	#define _DELTAENGINE_FATAL(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
	#define DELTAENGINE_FATAL(...)
	#define _DELTAENGINE_FATAL(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_ERROR && defined(DELTAENGINE_DEBUG)
	#define DELTAENGINE_ERROR(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_ERROR, true, "DeltaEngine: ", __VA_ARGS__)
	#define _DELTAENGINE_ERROR(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
	#define DELTAENGINE_ERROR(...)
	#define _DELTAENGINE_ERROR(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_WARN && defined(DELTAENGINE_DEBUG)
	#define DELTAENGINE_WARN(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_WARN, true, "DeltaEngine: ", __VA_ARGS__)
	#define _DELTAENGINE_WARN(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
	#define DELTAENGINE_WARN(...)
	#define _DELTAENGINE_WARN(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_INFO && defined(DELTAENGINE_DEBUG)
	#define DELTAENGINE_INFO(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_INFO, true, "DeltaEngine: ", __VA_ARGS__)
	#define _DELTAENGINE_INFO(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
	#define DELTAENGINE_INFO(...)
	#define _DELTAENGINE_INFO(...)
#endif

#if DELTAENGINE_LOG_LEVEL >= DELTAENGINE_LOG_LEVEL_TRACE && defined(DELTAENGINE_DEBUG)
	#define DELTAENGINE_TRACE(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_TRACE, true, __VA_ARGS__)
	#define _DELTAENGINE_TRACE(...) DeltaEngine::Internal::log_message(DELTAENGINE_LOG_LEVEL_TRACE, false, __VA_ARGS__)
#else
	#define DELTAENGINE_TRACE(...)
	#define _DELTAENGINE_TRACE(...)
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
			Debug::breakpoint(); \
		}
#else
	#define DELTAENGINE_ASSERT(x, ...)
#endif

#pragma warning(default:4996)
#pragma warning(default:4390)