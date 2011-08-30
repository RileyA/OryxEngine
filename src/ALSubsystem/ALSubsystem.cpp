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
#include "ALSubsystem.h"
#include "OryxLogger.h"

#include <AL/al.h>
#include <AL/alc.h>

#include "OryxStringUtils.h"

namespace Oryx
{
	ALSubsystem::ALSubsystem()
		:EngineSubsystem(),mInitialized(0){}
	//-----------------------------------------------------------------------

	ALSubsystem::~ALSubsystem()
	{
		_deinit();
	}
	//-----------------------------------------------------------------------

	void ALSubsystem::_init()
	{
		if(!mInitialized)
		{
			Logger::getPtr()->logMessage("AL Subsystem starting up...");

			// open default device
			if(!(mDevice = alcOpenDevice(0)))
				throw Oryx::Exception("Audio device could not be opened.");

			// create context (accept defaults, not passing an attrlist)
			if(!(mContext = alcCreateContext(mDevice, 0)))
				throw Oryx::Exception("Audio context could not be created.");

			// make this context current, and we're good to go
			alcMakeContextCurrent(mContext);

			// put the listener at the origin
			ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
			ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
			ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
			alListenerfv(AL_POSITION,    ListenerPos);
			alListenerfv(AL_VELOCITY,    ListenerVel);
			alListenerfv(AL_ORIENTATION, ListenerOri);

			// generate up to 64 sources
			for(int i = 0; i < 64; ++i)
			{
				ALuint source;
				alGenSources(1,&source);
				if(alGetError() != AL_NO_ERROR)
				{
					break;
				}
				else
				{
					mSources.push_back(source);
					mSourceAvailability[source] = true;
				}
			}

			Logger::getPtr()->logMessage("Audio Sources Allocated: "+StringUtils::toString(
				static_cast<int>(mSources.size())) + ".");

			// Set up audio loaders
			mAudioLoaders["wav"] = &mWavLoader;
			mAudioLoaders["ogg"] = &mOggLoader;

			Logger::getPtr()->logMessage("AL Subsystem started up.");
			mInitialized = true;
		}
	}
	//-----------------------------------------------------------------------

	void ALSubsystem::_deinit()
	{
		if(mInitialized)
		{
			Logger::getPtr()->logMessage("AL Subsystem shutting down...");

			// stop all playing sounds
			for(std::list<SoundPtr>::iterator it = mActiveSounds.begin(); 
				it != mActiveSounds.end(); ++it) 
				(*it)->stop();

			// Any hanging references elsewhere should destruct gracefully, though
			// attempting to use them in any other way will (probably) error
			mActiveSounds.clear();
		
			// free all sound sources
			alDeleteSources(mSources.size(), &mSources[0]);
			mSources.clear();
			mSourceAvailability.clear();

			// clear out buffers
			for(std::map<String, ALuint>::iterator it = mAudioBuffers.begin(); 
				it != mAudioBuffers.end(); ++it)
				alDeleteBuffers(1, &(it->second));
			mAudioBuffers.clear();

			// shut down context and device
			alcMakeContextCurrent(0);
			alcDestroyContext(mContext);
			alcCloseDevice(mDevice);

			Logger::getPtr()->logMessage("AL Subsystem shut down.");
			mInitialized = false;
		}
	}
	//-----------------------------------------------------------------------

	void ALSubsystem::_update(Real delta)
	{
		for(std::list<SoundPtr>::iterator it = mActiveSounds.begin(); 
			it != mActiveSounds.end(); ++it)
		{	
			// this really only matters if it's a streaming sound
			(*it)->update();

			// free up any sounds that can be
			if((*it).isDone())
			{
				mSourceAvailability[(*it)->getSource()] = true;
				it = mActiveSounds.erase(it);
			}
		}
	}
	//-----------------------------------------------------------------------

	void ALSubsystem::_endState()
	{
		for(std::list<SoundPtr>::iterator it = mActiveSounds.begin(); 
			it != mActiveSounds.end(); ++it)
		{
			// we're free to reuse any sources from sounds that don't have leftover refs
			// (this allows background music or whatever to persist between states)
			if((*it).getRefCount() == 1)
			{
				mSourceAvailability[(*it)->getSource()] = true;
				it = mActiveSounds.erase(it);
			}
		}
	}
	//-----------------------------------------------------------------------

	String ALSubsystem::getName()
	{
		return String("ALSubsystem");
	}
	//-----------------------------------------------------------------------

	SoundPtr ALSubsystem::play2D(String name, bool startPaused)
	{
		SoundPtr out;

		if(mAudioBuffers.find(name) == mAudioBuffers.end())
		{
			loadSound(name);

			if(mAudioBuffers.find(name) == mAudioBuffers.end())
			{
				Logger::getPtr()->logMessage("Could not play sound, could not find or load audio.");
				return out;
			}
		}

		if(!hasSources())
		{
			Logger::getPtr()->logMessage("Could not play sound, no available sound sources.");
		}
		else
		{
			out.bind(new BufferedSound(getSource(), mAudioBuffers[name]));
			mActiveSounds.push_back(out);
			if(!startPaused)
				out->play();
		}

		return out;
	}
	//-----------------------------------------------------------------------
	
	SoundPtr ALSubsystem::stream2D(String filename)
	{
		SoundPtr out;
		return out;
	}
	//-----------------------------------------------------------------------
	
	void ALSubsystem::loadSound(String filename, String name)
	{
		if(name == "AUTO")
			name = filename;

		String ext = filename.substr(filename.find_last_of(".") + 1);

		Logger::getPtr()->logMessage("Loading " + filename.substr(filename.find_last_of("/") + 1) + "... ", false);

		if(mAudioLoaders.find(ext) != mAudioLoaders.end())
		{
			try
			{
				ALuint buff;
				mAudioLoaders[ext]->loadSound(filename, buff);
				mAudioBuffers[name] = buff;
				Logger::getPtr()->logMessage("Done.", true, false);
			}
			catch(Oryx::Exception e)
			{
				Logger::getPtr()->logMessage(String("Failed! ") + e.what(), true, false);
			}
		}
		else
		{
			Logger::getPtr()->logMessage("Failed! No audio loader found for ." + ext + " files!", true, false);
		}
	}
	//-----------------------------------------------------------------------

	ALuint ALSubsystem::getSource()
	{
		for(std::map<ALuint, bool>::iterator it = mSourceAvailability.begin(); 
			it != mSourceAvailability.end(); ++it)
		{
			if(it->second)
			{
				it->second = false;
				return it->first;
			}
		}
	}
	//-----------------------------------------------------------------------

	bool ALSubsystem::hasSources()
	{
		for(std::map<ALuint, bool>::iterator it = mSourceAvailability.begin(); 
			it != mSourceAvailability.end(); ++it)
			if(it->second)
				return true;
		return false;
	}
	//-----------------------------------------------------------------------
}
