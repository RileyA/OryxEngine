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

#ifndef SOUNDPTR_H
#define SOUNDPTR_H

#include "ALSubsystem/ALdllmain.h"

#include "ActiveSound.h"
#include "BufferedSound.h"

namespace Oryx
{
	class ALSubsystem;

	/** An object representing a sound, (since the system uses/reuses sound buffers
	 *		this is sort of a wrapper representing an individual sound. 
	 *		@remarks Always check isValid() before messing with it, since sounds may immediately
	 *			be reused... */
	class ORYX_AL_EXPORT SoundPtr
	{
	public:

		SoundPtr(unsigned int index,time_t start,ALSubsystem* amgr);
		SoundPtr();

		bool isValid();

		SoundData& getData();

		unsigned int getIndex(){return mSoundIndex;}

	protected:

		time_t mStart;
		unsigned int mSoundIndex;
		bool mValid;
		ALSubsystem* mAudioMgr;

	};
}

#endif
