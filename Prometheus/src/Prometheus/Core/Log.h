#pragma once
#include "ptpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core.h"

namespace Prometheus {

	class  Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define PT_CORE_ERROR(...) :: Prometheus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PT_CORE_WARN(...) :: Prometheus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PT_CORE_INFO(...) :: Prometheus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PT_CORE_TRACE(...) :: Prometheus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PT_CORE_FATAL(...) :: Prometheus::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define PT_ERROR(...) :: Prometheus::Log::GetClientLogger()->error(__VA_ARGS__)
#define PT_WARN(...) :: Prometheus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PT_INFO(...) :: Prometheus::Log::GetClientLogger()->info(__VA_ARGS__)
#define PT_TRACE(...) :: Prometheus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PT_FATAL(...) :: Prometheus::Log::GetClientLogger()->critical(__VA_ARGS__)