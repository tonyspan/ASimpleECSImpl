workspace "ASimpleECSImpl"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ASimpleECSImpl"
	location "ASimpleECSImpl"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "ASimpleECSImpl/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		--glm
		"%{prj.name}/deps/glm/glm/**.hpp",
		"%{prj.name}/deps/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",

		--glm
		"%{prj.name}/deps/glm"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
