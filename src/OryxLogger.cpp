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
#include "OryxLogger.h"
#include "OryxTimeManager.h"

namespace Oryx
{
	Logger::Logger() : mActive(true)
	{
		mLogFile.open("Oryx.log");
		createSignal("Log");
	}
	//-----------------------------------------------------------------------

	Logger::~Logger()
	{
		if(mLogFile.is_open())
			mLogFile.close();
	}
	//-----------------------------------------------------------------------

	void Logger::logMessage(String message)
	{
		if(mActive)
		{
			String timeStampStr = TimeManager::getPtr()->getTimestamp();
			std::cout<<timeStampStr<<" "<<message<<"\n";
			if(mLogFile.is_open())
				mLogFile<<timeStampStr<<" "<<message<<"\n";
			mLogFile.flush();
			getSignal("Log")->send(message);
		}
	}
	//-----------------------------------------------------------------------

	void Logger::supressOutput()
	{
		mActive = false;
	}
	//-----------------------------------------------------------------------

	void Logger::suppressFileOutput()
	{
		if(mLogFile.is_open())
			mLogFile.close();
	}
	//-----------------------------------------------------------------------

	Logger* Logger::getPtr()
	{
		static Logger lgr;
		return &lgr;
	}
	//-----------------------------------------------------------------------
}
