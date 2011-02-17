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

#include "ALdllmain.h"

#include "SoundPtr.h"
#include "ALSubsystem.h"

namespace Oryx
{
	SoundPtr::SoundPtr(unsigned int index,time_t start,ALSubsystem* amgr)
	{
		mStart = start;
		mSoundIndex = index;
		mAudioMgr = amgr;
	}

	SoundPtr::SoundPtr()
	{
		mStart = false;
		mAudioMgr = 0;
		mSoundIndex = 5000;
	}

	SoundPtr::~SoundPtr()
	{

	}

	SoundData& SoundPtr::getData()
	{
		return mAudioMgr->getActiveSound(mSoundIndex)->getData();
	}

	bool SoundPtr::isValid()
	{
		if(mAudioMgr->getActiveSound(mSoundIndex)->getStartTime()==mStart)
			return true;
		else
			return false;
	}
}
