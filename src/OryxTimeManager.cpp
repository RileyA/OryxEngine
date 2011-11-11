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

#include "Oryx.h"
#include "OryxTimeManager.h"

namespace Oryx
{
	Real tDifference(struct timeval start,struct timeval end)
	{
		long seconds  = end.tv_sec  - start.tv_sec;
		long useconds = end.tv_usec - start.tv_usec;
		long ms = (seconds*1000+useconds/1000.f)+0.5;
		return (seconds*1000.f+useconds/1000.f)/1000.f;
	}
	//-----------------------------------------------------------------------

	void TimeManager::setTimeSpeed(Real speed)
	{
		mTimeSpeed = speed;
	}
	//-----------------------------------------------------------------------

	Real TimeManager::getTimeSpeed()
	{
		return mTimeSpeed;
	}
	//-----------------------------------------------------------------------

	Real TimeManager::getTimeDecimal()
	{
#if ORYX_PLATFORM == PLATFORM_WIN32
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		long long tm = now.QuadPart - mStart.QuadPart;
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		return static_cast<Real>(tm)/freq.QuadPart;
#else
		struct timeval now;
		gettimeofday(&now, 0);
		long seconds  = now.tv_sec  - mStart.tv_sec;
		long useconds = now.tv_usec - mStart.tv_usec;
		return (seconds*1000.f+useconds/1000.f)/1000.f;
#endif
	}
	//-----------------------------------------------------------------------

	long TimeManager::getTime()
	{
		return clock();
	}
	//-----------------------------------------------------------------------

	Real TimeManager::getDeltaTime()
	{
		return mDeltaTime;
	}
	//-----------------------------------------------------------------------

	void TimeManager::update()
	{
		Real currentTime = getTimeDecimal();
		mDeltaTime = currentTime-mLastTime;
		mLastTime = currentTime;
	}
	//-----------------------------------------------------------------------

	String TimeManager::getTimestamp()
	{
		int currentTime = getTimeDecimal();
		int hours = currentTime/3600;
		currentTime %= 3600;
		int minutes = currentTime/60;
		currentTime %= 60;
		int seconds = currentTime;

		std::stringstream ss;
		ss<<String((hours<10)?"0":"")<<hours<<":"<<String((minutes<10)?"0":"")
			<<minutes<<":"<<String((seconds<10)?"0":"")<<seconds<<":";

		String out = "";
		ss>>out;
		return out;
	}
	//-----------------------------------------------------------------------

	String TimeManager::getTimestampMilli(Real offset)
	{
		int currentTime = (getTimeDecimal() - offset)*100;
		int minutes = currentTime/6000;
		currentTime %= 6000;
		int seconds = currentTime/100;
		currentTime %= 100;
		int milliseconds = currentTime;
		if(milliseconds>=100)
			milliseconds = 99;

		std::stringstream ss;
		ss<<String((minutes<10)?"0":"")<<minutes<<":"<<String((seconds<10)?"0":"")
			<<seconds<<":"<<String((milliseconds<10)?"0":"")<<milliseconds;

		String out = "";
		ss>>out;
		return out;
	}
	//-----------------------------------------------------------------------
	void TimeManager::start()
	{
#if ORYX_PLATFORM == PLATFORM_WIN32
		QueryPerformanceCounter(&mStart);
#else
		gettimeofday(&mStart, 0);
#endif
	}
	//-----------------------------------------------------------------------

	TimeManager* TimeManager::getPtr()
	{
		static TimeManager tmgr;
		return &tmgr;
	}
	//-----------------------------------------------------------------------
}
