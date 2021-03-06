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

#ifndef ORYXTIMEMANAGER_H
#define ORYXTIMEMANAGER_H

#include "Oryx.h"
#include <stdio.h>

#if (ORYX_PLATFORM == ORYX_PLATFORM_LINUX)
#include <sys/time.h>
#include <unistd.h>
#endif

namespace Oryx
{
	
	class ORYX_EXPORT TimeManager
	{
	public:

		static TimeManager* getPtr();

		/** Set the speed of time
		 *		@param speed The desired speed of time (1 is normal, 0 is paused) */
		void setTimeSpeed(Real speed);

		/** Get the speed of time
		 *		@returns The current speed of time */
		Real getTimeSpeed();

		/** Gets the current time in seconds as a Real number
		 *		@returns The current time (in seconds) */
		Real getTimeDecimal();

		/** Gets the current time as a long int
		 *		@returns The current time as returned by clock() */
		long getTime();

		/** The global change in time from the last frame time (more sensitive subsystems
		 *		might need to implement a delta timer of their own). */
		Real getDeltaTime();

		/** Pretty much just updates the delta time. */
		void update();

		/** returns a nicely formatted timestamp string hh::mm::ss: */
		String getTimestamp();

		/** returns a nicely formatted timestamp string mm::ss::ms 
		 *		@param offset An offset in seconds */
		String getTimestampMilli(Real offset = 0.f);

		/** Starts up the clock */
		void start();

	private:

		Real mLastTime;
		Real mDeltaTime;
		Real mTimeSpeed;

		#if (ORYX_PLATFORM == ORYX_PLATFORM_WIN32)
			LARGE_INTEGER mStart;
		#else
			struct timeval mStart;
		#endif

		TimeManager()
			:mLastTime(static_cast<Real>(clock())/CLOCKS_PER_SEC),
			mDeltaTime(0),
			mTimeSpeed(1){}

		TimeManager(TimeManager const&);
		TimeManager& operator=(TimeManager const&);
		~TimeManager(){}

	};
}

#endif
