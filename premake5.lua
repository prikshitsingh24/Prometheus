workspace "Prometheus"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}
IncludeDir['GLFW']="Prometheus/vendor/GLFW/include"
include "Prometheus/vendor/GLFW"

project "Prometheus"
	location "Prometheus"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
	pchheader "ptpch.h"
	pchsource "Prometheus/src/ptpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	links
	{
		"GLFW",
		"opengl32.lib"
		
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		 "PT_PLATFORM_WINDOWS",
		 "PT_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PT_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	targetdir ("bin/".. outputdir .."/%{prj.name}")
	objdir ("bin-int/".. outputdir .."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"Prometheus/vendor/spdlog/include",
		"Prometheus/src"
	}
	links
	{
		"Prometheus"
	}
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
		 "PT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PT_DIST"
		optimize "On"