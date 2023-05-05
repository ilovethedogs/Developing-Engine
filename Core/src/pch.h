// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <optional>
#include <exception>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Log.h"

#ifdef PLATFORM_WINDOWS
    // target Windows 10 or later
    #define _WIN32_WINNT 0x0A00
    #include <sdkddkver.h>

    #define WIN32_LEAN_AND_MEAN
    #define NOGDICAPMASKS
    #define NOSYSMETRICS
    #define NOMENUS
    #define NOICONS
    #define NOSYSCOMMANDS
    #define NORASTEROPS
    #define OEMRESOURCE
    #define NOATOM
    #define NOCLIPBOARD
    //#define NOCOLOR
    //#define NOCTLMGR
    #define NODRAWTEXT
    #define NOKERNEL
    //#define NONLS
    #define NOMEMMGR
    #define NOMETAFILE
    #define NOMINMAX
    #define NOOPENFILE
    #define NOSCROLL
    #define NOSERVICE
    #define NOSOUND
    #define NOTEXTMETRIC
    #define NOWH
    #define NOCOMM
    #define NOKANJI
    #define NOHELP
    #define NOPROFILER
    #define NODEFERWINDOWPOS
    #define NOMCX
    #define NORPC
    #define NOPROXYSTUB
    #define NOIMAGE
    #define NOTAPE

    #define STRICT

	#include <Windows.h>
    #include <wrl.h>
    #include <d3dx12/d3dx12.h>
    #include <d3d12.h>
    #include <dxgi.h>
    #include <DirectxMath.h>

    // For UTF converter...
    #define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif

#endif //PCH_H
