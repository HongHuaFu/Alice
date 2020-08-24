#include <PathTracingCPU/Logger.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Alice::PathTracingCPU
{
	Ref<spdlog::logger> Logger::s_CoreLogger;
	Ref<spdlog::logger> Logger::s_IOLogger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Runtime.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("Core", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_IOLogger = std::make_shared<spdlog::logger>("IO", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_IOLogger);
		s_IOLogger->set_level(spdlog::level::trace);
		s_IOLogger->flush_on(spdlog::level::trace);
	}
}