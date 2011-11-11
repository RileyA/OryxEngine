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

#ifndef ORYX_SOUND_H
#define ORYX_SOUND_H

#include "Oryx.h"
#include "OryxSharedPtr.h"
#include "OryxVector3.h"
#include "ALdllmain.h"

typedef unsigned int ALuint;
typedef int ALenum;

namespace Oryx
{
	/** An abstract representation of a playing or ready-to-play sound */
	class ORYX_AL_EXPORT Sound : public EventHandler
	{
	public:

		Sound(ALuint source);
		virtual ~Sound();

		virtual void update() = 0;
		void setDefaults();

		ALuint getSource(){return mSource;}

		void play();
		void rewind();
		void stop();
		void pause();

		bool isStarted(); 
		bool isStopped();
		bool isPlaying();
		bool isPaused();
		
		/** Various setters and getters for properties */

		/** Position */
		void setPosition(Vector3 pos); 
		Vector3 getPosition();

		/** Velocity */
		void setVelocity(Vector3 vel);
		Vector3 getVelocity();

		/** Direction */
		void setDirection(Vector3 direction);
		Vector3 getDirection();

		/** Relative to listener */
		void setRelative(bool rel);
		bool isRelative();

		/** Gain */
		void setGain(Real min, Real max, Real gain);
		void setMinGain(Real min);
		void setMaxGain(Real max);
		void setGain(Real gain);
		Real getMinGain();
		Real getMaxGain();
		Real getGain();

		/** Attenuation */
		void setRolloff(Real roll);
		Real getRolloff();
		void setReferenceDistance(Real ref);
		Real getReferenceDistance();

		/** Cone */
		void setCone(Real inner, Real outer, Real gain);
		void setConeOuterAngle(Real angle);
		void setConeInnerAngle(Real angle);
		void setConeOuterGain(Real gain);
		Real getConeInnerAngle();
		Real getConeOuterAngle();
		Real getConeOuterGain();

		/** Looping */
		void setLooping(bool looping);
		bool isLooping();

		/** Pitch */
		void setPitch(Real pitch);
		Real getPitch();

		/** Buffers */
		uint getNumBuffersQueued();
		uint getNumBuffersProcessed();

		/** Playback position */
		Real getSecondOffset();
		Real getSampleOffset();
		Real getByteOffset();
		void setOffsetSeconds(Real offset);
		void setOffsetSamples(Real offset);
		void setOffsetBytes(Real offset);

	protected:

		ALuint mSource;

	private:

		Vector3 getVector3(ALenum value);
		int getInt(ALenum value);
		ALenum getEnum(ALenum value);
		float getFloat(ALenum value);
		double getDouble(ALenum value);
		bool getBool(ALenum value);

		void setVector3(Vector3 v, ALenum value);
		void setFloat(float v, ALenum value);
		void setDouble(double v, ALenum value);
		void setInt(int v, ALenum value);
		void setEnum(ALenum v, ALenum value);
		void setBool(bool v, ALenum value);

	};

	/** ref counted version that will be passed around */
	class SoundPtr : public SharedPtr<Sound>
	{
	public:

		/** Whether or not this sound is ready to be deleted by the
		 *		ALSubsystem, this must be the last reference, and the sound
		 *		must be stopped. */
		bool isDone()
		{
			return (*this)->isStopped() && (*refCount) == 1;
		}
	};
}

#endif
