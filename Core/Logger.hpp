#pragma once
#include <Core.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Alice 
{
	class Logger
	{
	public:
		static void Init();
		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetIOLogger() { return s_IOLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_IOLogger;
	};
}

#define ALICE_TRACE_CORE(...)    \
	::Alice::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define ALICE_INFO_CORE(...)     \
	::Alice::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define ALICE_WARN_CORE(...)     \
	::Alice::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define ALICE_ERROR_CORE(...)	\
	::Alice::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define ALICE_CRITICAL_CORE(...) \
	::Alice::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define ALICE_TRACE_IO(...)    \
	::Alice::Logger::GetIOLogger()->trace(__VA_ARGS__)
#define ALICE_INFO_IO(...)     \
	::Alice::Logger::GetIOLogger()->info(__VA_ARGS__)
#define ALICE_WARN_IO(...)     \
	::Alice::Logger::GetIOLogger()->warn(__VA_ARGS__)
#define ALICE_ERROR_IO(...)	  \
	::Alice::Logger::GetIOLogger()->error(__VA_ARGS__)
#define ALICE_CRITICAL_IO(...) \
	::Alice::Logger::GetIOLogger()->critical(__VA_ARGS__)