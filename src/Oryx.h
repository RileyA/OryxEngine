//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

#ifndef ORYX_H
#define ORYX_H

// Possible platforms
#define ORYX_PLATFORM_WIN32 1
#define ORYX_PLATFORM_LINUX 2
#define ORYX_PLATFORM_APPLE 3

// Determine platform
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined (WIN32)
    #define ORYX_PLATFORM ORYX_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
    #define ORYX_PLATFORM ORYX_PLATFORM_APPLE
#else
    #define ORYX_PLATFORM ORYX_PLATFORM_LINUX
#endif

// Win32 dll stuff
#ifdef WIN32
	//#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>

    #ifdef BUILD_ORYX_DLL
        #define ORYX_EXPORT __declspec(dllexport)
    #else
        #define ORYX_EXPORT __declspec(dllimport)
    #endif

	// make msvc shut up about template export-age...
	#pragma warning(disable:4251)
#else
    #define ORYX_EXPORT
#endif

// If you want to reuse object id numbers, may be useful for an app that runs a 
// long time and creates _many_ objects (probably improbable...)
//#define ORYX_REUSE_OBJECT_IDS

// Version info
#define ORYX_VERSION "0.0.1"

// Some basic standard lib includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdexcept>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#if (ORYX_PLATFORM == ORYX_PLATFORM_LINUX )
#include <netinet/in.h>
#elif (ORYX_PLATFORM == ORYX_PLATFORM_WINDOWS )
#include <Winsock2.h>
#endif

// Define the namespace and some common typedefs
namespace Oryx
{
	typedef std::string String;
	typedef float Real;
	typedef unsigned int uint;
	typedef unsigned char byte;
	typedef unsigned char uint8;
	typedef signed char int8;
	typedef unsigned long long uint64;
	typedef unsigned long OryxID;// used to uniquely identify game objects
}

// Some basic stuff that should be accessible from just about anywhere:
#include "OryxStringUtils.h"
#include "OryxTimeManager.h"
#include "OryxLogger.h"
#include "OryxException.h"

#endif
