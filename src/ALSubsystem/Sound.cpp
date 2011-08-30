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

#include "Sound.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace Oryx
{
	Sound::Sound(ALuint source)
		:mSource(source)
	{
		setDefaults();
	}
	//---------------------------------------------------------------------------
	
	Sound::~Sound()
	{
		if(alIsSource(mSource))
			stop();
	}
	//---------------------------------------------------------------------------

	void Sound::setDefaults()
	{
		setPosition(Vector3::ZERO);
		setDirection(Vector3::UNIT_Y);
		setPitch(1.f);
		setGain(1.f, 0.f, 1.f);
		setLooping(false);
		setRolloff(1.f);
		setReferenceDistance(1.f);
		setCone(360.f,360.f,0.f);
		setRelative(true);
		setOffsetSeconds(0.f);
		rewind();
	}
	//---------------------------------------------------------------------------

	void Sound::play()
	{
		alSourcePlay(mSource);
	}
	//---------------------------------------------------------------------------

	void Sound::rewind()
	{
		alSourceRewind(mSource);
	}
	//---------------------------------------------------------------------------

	void Sound::stop()
	{
		alSourceStop(mSource);
	}
	//---------------------------------------------------------------------------

	void Sound::pause()
	{
		alSourcePause(mSource);
	}
	//---------------------------------------------------------------------------

	bool Sound::isStarted()
	{
		return getInt(AL_SOURCE_STATE) != AL_INITIAL;
	}
	//---------------------------------------------------------------------------

	bool Sound::isStopped()
	{
		return getInt(AL_SOURCE_STATE) == AL_STOPPED;
	}
	//---------------------------------------------------------------------------

	bool Sound::isPlaying()
	{
		return getInt(AL_SOURCE_STATE) == AL_PLAYING;
	}
	//---------------------------------------------------------------------------

	bool Sound::isPaused()
	{
		return getInt(AL_SOURCE_STATE) == AL_PAUSED;
	}
	//---------------------------------------------------------------------------

	void Sound::setPosition(Vector3 pos)
	{
		setVector3(pos, AL_POSITION);
	}
	//---------------------------------------------------------------------------

	Vector3 Sound::getPosition()
	{
		return getVector3(AL_POSITION);
	}
	//---------------------------------------------------------------------------

	void Sound::setDirection(Vector3 direction)
	{
		setVector3(direction, AL_DIRECTION);
	}
	//---------------------------------------------------------------------------
	
	Vector3 Sound::getDirection()
	{
		return getVector3(AL_DIRECTION);
	}
	//---------------------------------------------------------------------------

	void Sound::setVelocity(Vector3 vel)
	{
		setVector3(vel, AL_VELOCITY);
	}
	//---------------------------------------------------------------------------
	
	Vector3 Sound::getVelocity()
	{
		return getVector3(AL_VELOCITY);
	}
	//---------------------------------------------------------------------------

	void Sound::setRelative(bool rel)
	{
		setBool(rel, AL_SOURCE_RELATIVE);
	}
	//---------------------------------------------------------------------------

	bool Sound::isRelative()
	{
		return getBool(AL_SOURCE_RELATIVE);
	}
	//---------------------------------------------------------------------------

	void Sound::setGain(Real min, Real max, Real gain)
	{
		setMinGain(min);
		setMaxGain(max);
		setGain(gain);
	}
	//---------------------------------------------------------------------------

	void Sound::setMinGain(Real min)
	{
		setFloat(min, AL_MIN_GAIN);
	}
	//---------------------------------------------------------------------------

	void Sound::setMaxGain(Real max)
	{
		setFloat(max, AL_MAX_GAIN);
	}
	//---------------------------------------------------------------------------

	void Sound::setGain(Real gain)
	{
		setFloat(gain, AL_GAIN);
	}
	//---------------------------------------------------------------------------

	Real Sound::getMinGain()
	{
		return getFloat(AL_MIN_GAIN);
	}
	//---------------------------------------------------------------------------

	Real Sound::getMaxGain()
	{
		return getFloat(AL_MAX_GAIN);
	}
	//---------------------------------------------------------------------------

	Real Sound::getGain()
	{
		return getFloat(AL_GAIN);
	}
	//---------------------------------------------------------------------------

	void Sound::setRolloff(Real roll)
	{
		setFloat(roll, AL_ROLLOFF_FACTOR);
	}
	//---------------------------------------------------------------------------

	Real Sound::getRolloff()
	{
		return getFloat(AL_ROLLOFF_FACTOR);
	}
	//---------------------------------------------------------------------------

	void Sound::setReferenceDistance(Real ref)
	{
		setFloat(ref, AL_REFERENCE_DISTANCE);
	}
	//---------------------------------------------------------------------------
	
	Real Sound::getReferenceDistance()
	{
		return getFloat(AL_REFERENCE_DISTANCE);
	}
	//---------------------------------------------------------------------------

	void Sound::setCone(Real inner, Real outer, Real gain)
	{
		setConeOuterAngle(outer);
		setConeInnerAngle(inner);
		setConeOuterGain(gain);
	}
	//---------------------------------------------------------------------------
	
	void Sound::setConeOuterAngle(Real angle)
	{
		setFloat(angle, AL_CONE_OUTER_ANGLE);
	}
	//---------------------------------------------------------------------------

	void Sound::setConeInnerAngle(Real angle)
	{
		setFloat(angle, AL_CONE_INNER_ANGLE);
	}
	//---------------------------------------------------------------------------

	void Sound::setConeOuterGain(Real gain)
	{
		setFloat(gain, AL_CONE_OUTER_GAIN);
	}
	//---------------------------------------------------------------------------

	Real Sound::getConeInnerAngle()
	{
		return getFloat(AL_CONE_INNER_ANGLE);
	}
	//---------------------------------------------------------------------------

	Real Sound::getConeOuterAngle()
	{
		return getFloat(AL_CONE_OUTER_ANGLE);
	}
	//---------------------------------------------------------------------------

	Real Sound::getConeOuterGain()
	{
		return getFloat(AL_CONE_OUTER_GAIN);
	}
	//---------------------------------------------------------------------------

	void Sound::setLooping(bool looping)
	{
		setBool(looping, AL_LOOPING);
	}
	//---------------------------------------------------------------------------

	bool Sound::isLooping()
	{
		return getBool(AL_LOOPING);
	}
	//---------------------------------------------------------------------------

	void Sound::setPitch(Real pitch)
	{
		setFloat(pitch, AL_PITCH);
	}
	//---------------------------------------------------------------------------

	Real Sound::getPitch()
	{
		return getFloat(AL_PITCH);
	}
	//---------------------------------------------------------------------------

	uint Sound::getNumBuffersQueued()
	{
		return getInt(AL_BUFFERS_QUEUED);
	}
	//---------------------------------------------------------------------------

	uint Sound::getNumBuffersProcessed()
	{
		return getInt(AL_BUFFERS_PROCESSED);
	}
	//---------------------------------------------------------------------------

	Real Sound::getSecondOffset()
	{
		return getFloat(AL_SEC_OFFSET);
	}
	//---------------------------------------------------------------------------

	Real Sound::getSampleOffset()
	{
		return getFloat(AL_SAMPLE_OFFSET);
	}
	//---------------------------------------------------------------------------

	Real Sound::getByteOffset()
	{
		return getFloat(AL_BYTE_OFFSET);
	}
	//---------------------------------------------------------------------------

	void Sound::setOffsetSeconds(Real offset)
	{
		setFloat(offset, AL_SEC_OFFSET);
	}
	//---------------------------------------------------------------------------

	void Sound::setOffsetSamples(Real offset)
	{
		setFloat(offset, AL_SAMPLE_OFFSET);
	}
	//---------------------------------------------------------------------------

	void Sound::setOffsetBytes(Real offset)
	{
		setFloat(offset, AL_BYTE_OFFSET);
	}
	//---------------------------------------------------------------------------
	
	Vector3 Sound::getVector3(ALenum value)
	{
		float out[3];
		alGetSourcefv(mSource, value, out);
		return Vector3(out);
	}
	//---------------------------------------------------------------------------

	int Sound::getInt(ALenum value)
	{
		int out;
		alGetSourcei(mSource, value, &out);
		return out;
	}
	//---------------------------------------------------------------------------

	ALenum Sound::getEnum(ALenum value)
	{
		ALenum out;
		alGetSourcei(mSource, value, &out);
		return out;
	}
	//---------------------------------------------------------------------------

	float Sound::getFloat(ALenum value)
	{
		float out;
		alGetSourcef(mSource, value, &out);
		return out;
	}
	//---------------------------------------------------------------------------

	double Sound::getDouble(ALenum value)
	{
		float out;
		alGetSourcef(mSource, value, &out);
		return static_cast<double>(out);
	}
	//---------------------------------------------------------------------------

	bool Sound::getBool(ALenum value)
	{
		int out;
		alGetSourcei(mSource, value, &out);
		return static_cast<bool>(out);
	}
	//---------------------------------------------------------------------------

	void Sound::setVector3(Vector3 v, ALenum value)
	{
		float val[] = {v.x, v.y, v.z};
		alSourcefv(mSource, value, val);
	}
	//---------------------------------------------------------------------------
	
	void Sound::setFloat(float v, ALenum value)
	{
		alSourcef(mSource, value, v);
	}
	//---------------------------------------------------------------------------

	void Sound::setDouble(double v, ALenum value)
	{
		alSourcef(mSource, value, v);
	}
	//---------------------------------------------------------------------------

	void Sound::setInt(int v, ALenum value)
	{
		alSourcei(mSource, value, v);
	}
	//---------------------------------------------------------------------------

	void Sound::setEnum(ALenum v, ALenum value)
	{
		alSourcei(mSource, value, v);
	}
	//---------------------------------------------------------------------------

	void Sound::setBool(bool v, ALenum value)
	{
		alSourcei(mSource, value, v);
	}
	//---------------------------------------------------------------------------
}
