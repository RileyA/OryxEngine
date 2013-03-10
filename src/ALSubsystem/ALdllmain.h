//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010

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

#ifndef ORYX_AL_SUBSYSTEM_H
#define ORYX_AL_SUBSYSTEM_H

#include "Oryx.h"

#ifdef WIN32

	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>

	#ifdef ALSubsystem_EXPORTS 
		#define ORYX_AL_EXPORT __declspec(dllexport)
	#else
		#define ORYX_AL_EXPORT __declspec(dllimport)
	#endif

#else
	#define ORYX_AL_EXPORT
#endif

#endif
