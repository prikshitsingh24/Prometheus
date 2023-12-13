#pragma once

#ifdef PT_PLATFORM_WINDOWS
	#ifdef PT_BUILD_DLL
		#define PROMETHEUS_API __declspec(dllexport)
	#else
		#define PROMETHEUS_API __declspec(dllimport)
	#endif
#else
	#error Prometheus only supports Windows!
#endif

#define BIT(x) (1<<x)