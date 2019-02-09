workspace "Simple-Bezier-Curve-OpenGL"
    location "build"
    startproject "Simple-Bezier-Curve-OpenGL"
    configurations { "Debug", "Release" }
    platforms { "x64", "x86" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Simple-Bezier-Curve-OpenGL"
    location "build/Simple-Bezier-Curve-OpenGL"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "src/**.h", "src/**.cpp", "src/**.c", "src/**.vert", "src/**.frag" }
    includedirs { "src/freetype", "src" }

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    filter "system:windows"
      systemversion "latest"
      
    filter "platforms:x86"
      architecture "x32"
      links { "lib/glfw3_32.lib", "OpenGL32.lib", "lib/freetype32/freetype.lib" }
      postbuildcommands {
			("{COPY} %{wks.location}../lib/freetype32/freetype.dll %{cfg.targetdir}")
		}

    filter "platforms:x64"
      architecture "x64"
      links { "lib/glfw3_64.lib", "OpenGL32.lib", "lib/freetype64/freetype.lib" }
      postbuildcommands {
        ("{COPY} %{wks.location}../lib/freetype64/freetype.dll %{cfg.targetdir}")
      }

