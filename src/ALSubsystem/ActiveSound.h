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

#ifndef ORYX_ACTIVESOUND_H
#define ORYX_ACTIVESOUND_H

#include "ALSubsystem/ALdllmain.h"
#include "BufferedSound.h"
#include "Oryx3DMath.h"

namespace Oryx
{
	class OggStream;

	struct ORYX_AL_EXPORT SoundData
	{
	public:

		SoundData()
		{
			toDefaults();
			mBuffer = 0;
		}
		SoundData(BufferedSound* buffer)
		{
			toDefaults();
			mBuffer = buffer;
		}
		~SoundData()
		{

		}

		void toDefaults()
		{
			mPosition = Vector3(0,0,0);
			mVelocity = Vector3(0,0,0);
			mGain = 1.f;
			mPitch = 1.f;
			mRolloff = 1.f;
			mMinGain = 0.f;
			mMaxGain = 1.f;
			mLooping = 0;
			mRefDist = 1.f;
			mMaxDist = 2000.f;
			mOffset = 0.f;
		}

		Vector3 mPosition;
		Vector3 mVelocity;
		float mGain;
		float mPitch;
		float mRolloff;
		float mMinGain;
		float mMaxGain;
		bool mLooping;
		float mRefDist;
		float mMaxDist;
		float mOffset;

		BufferedSound* mBuffer;
	};

	class ORYX_AL_EXPORT ActiveSound
	{
	public:

		ActiveSound();
		~ActiveSound();

		void update();
		void clear();
		bool isActive();
		void playSound(SoundData data);

		/** Get a reference to the sound data,  */
		SoundData& getData();

		/** Updates the sound to reflect any changes made to the sound properties */
		void updateData();

		time_t getStartTime();

	protected:

		unsigned int mSource;
		SoundData mData;
		bool mActive;
		time_t mStart;
		OggStream* mOgg;

	};
}

#endif
