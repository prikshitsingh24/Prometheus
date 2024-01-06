workspace "Prometheus"
	architecture "x64"
startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}
IncludeDir['GLFW']="Prometheus/vendor/GLFW/include"
IncludeDir['Glad']="Prometheus/vendor/Glad/include"
IncludeDir['ImGui']="Prometheus/vendor/imgui"
IncludeDir['glm']="Prometheus/vendor/glm"
include "Prometheus/vendor/GLFW"
include "Prometheus/vendor/Glad"
include "Prometheus/vendor/imgui"


project "Prometheus"
	location "Prometheus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
		 "PT_PLATFORM_WINDOWS",
		 "PT_BUILD_DLL",
		 "GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "on"
	
	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "PT_DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	staticruntime "on"

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
		"Prometheus/src",
		"%{IncludeDir.glm}"
	}
	links
	{
		"Prometheus"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
		 "PT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "on"
	
	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "PT_DIST"
		optimize "on"