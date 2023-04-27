workspace "Developing"  
    architecture "x64"
    configurations { "Debug", "Release" } 
    startproject "Testbed"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

project "Core"  
    location "Core"
    kind "StaticLib"   
    staticruntime "Off"
    language "C++"   
    cppdialect "C++latest" 
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Developing/src/pch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/**.hlsl",
    }
    includedirs {
        "%{prj.name}/src/",
        "%{prj.name}/vendor/spdlog/include",
    }

    links {
        "d3d11",
        "dxguid",
        "D3DCompiler",
    }

    optimize "Speed"

    floatingpoint "Fast"

    characterset "MBCS"

    filter "files:**.hlsl"
        shaderentry "main"
        shadermodel "5.0"
        shaderobjectfileoutput "%{wks.location}/Testbed/ShaderLib/%{file.basename}.cso"

    filter "files:**PS.hlsl"
        shadertype "Pixel"

    filter "files:**VS.hlsl"
        shadertype "Vertex"

    filter "system:windows"
        systemversion "latest"
        defines {
            "GW_PLATFORM_WINDOWS",
            --"GW_BUILD_DLL",
        }    
        
    filter "system:linux"
        systemversion "latest"
        defines {
            "GW_PLATFORM_LINUX",
            --"GW_BUILD_DLL",
        }

    filter "configurations:Debug"
        defines { "GW_DEBUG=1" }  
        runtime "Debug"
        symbols "on" 

    filter "configurations:Release"  
        defines { "GW_DEBUG=0", "GW_RELEASE" }    
        runtime "Release"
        optimize "on" 

project "Testbed"
    location "Testbed"
    kind "ConsoleApp"
    language "C++"   
    cppdialect "C++latest" 
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "Developing/src",
    }

    links {
        "Core"
    }

    optimize "Speed"

    floatingpoint "Fast"

    characterset "MBCS"

    filter "system:windows"
        systemversion "latest"
        defines {
            "GW_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines { "GW_DEBUG=1" }  
        runtime "Debug"
        symbols "on" 

    filter "configurations:Release"  
        defines { "GW_DEBUG=0", "GW_RELEASE" }    
        runtime "Release"
        optimize "on" 