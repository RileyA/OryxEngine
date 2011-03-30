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
#include <AL/alut.h>
// Ogg Vorbis stuff
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

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
			mDefaultVolume = 1.f;
			mDefaultVolumeOgg = 1.f;

			alutInit(NULL,NULL);

			ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
			ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
			ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
			alListenerfv(AL_POSITION,    ListenerPos);
			alListenerfv(AL_VELOCITY,    ListenerVel);
			alListenerfv(AL_ORIENTATION, ListenerOri);

			unsigned int a = 0;
			bool failed = false;
			ALuint sources[64];
			while(!failed&&a<64)
			{
				alGenSources(1,&sources[a]);
				if(alGetError()!=AL_NO_ERROR)
				{
					failed = true;
				}
				else
				{
					a++;
				}
			}
			mMaxSources = a;// good info to have on hand...

			Logger::getPtr()->logMessage("Max Audio sources: "+StringUtils::toString(mMaxSources)+" or more.");

			unsigned int b = 0;
			while(b<a)
			{
				alDeleteSources(1,&sources[b]);
				b++;
			}

			b = 0;
			while(b<a)
			{
				mSounds.push_back(new ActiveSound());// empty sound source
				b++;
			}
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
			for(unsigned int i=0;i<mSounds.size();++i)
			{
				delete mSounds[i];
				mSounds[i] = 0;
			}
			mSounds.clear();

			std::map<String,BufferedSound*>::iterator iter;
			for(iter = mBuffers.begin();iter != mBuffers.end();++iter)
			{
				delete iter->second;
				iter->second = 0;
			}
			mBuffers.clear();

			alutExit();
            Logger::getPtr()->logMessage("AL Subsystem shut down.");
            mInitialized = false;
        }
    }
    //-----------------------------------------------------------------------

    void ALSubsystem::_update(Real delta)
    {
		for(unsigned int i=0;i<mSounds.size();++i)
		{
			mSounds[i]->update();
			if(mSounds[i]->isActive())
			{
				if(!mSounds[i]->getData().mBuffer->isOgg())
				{
					mSounds[i]->getData().mGain = mDefaultVolume;
				}
				else
				{
					mSounds[i]->getData().mGain = mDefaultVolumeOgg;
				}
				mSounds[i]->updateData();
			}
		}
    }
    //-----------------------------------------------------------------------

    void ALSubsystem::_endState()
    {

    }
    //-----------------------------------------------------------------------

    String ALSubsystem::getName()
    {
        return String("ALSubsystem");
    }
    //-----------------------------------------------------------------------

    SoundPtr ALSubsystem::play2D(String filename)
    {
        if(mBuffers.find(filename)!=mBuffers.end())
		{
			if(!mBuffers[filename]->isLoaded())
			{
				mBuffers[filename]->load();
			}
		}
		else
		{
			if(!loadSound(filename))
			{
				Logger::getPtr()->logMessage("Invalid audio file!");
				return SoundPtr(0,0,0);
			}
		}

		unsigned int index = 0;
		for(unsigned int a = 0;a<mSounds.size();++a)
		{
			if(!mSounds[a]->isActive())
			{
				index = a;
				mSounds[a]->playSound(SoundData(mBuffers[filename]));
				break;
			}
		}

		return SoundPtr(index,mSounds[index]->getStartTime(),this);
    }
    //-----------------------------------------------------------------------

    bool ALSubsystem::bufferSound(String filename)
    {
        return false;
    }
    //-----------------------------------------------------------------------

    bool ALSubsystem::loadSound(String filename)
    {
        String outName,outExt;
		outExt = filename.substr(filename.size()-3);
		if(outExt=="wav")
		{
			mBuffers[filename] = new BufferedSound(filename,false);
			return true;
		}
		else if(outExt=="ogg")
		{
			mBuffers[filename] = new BufferedSound(filename,true);
			return true;
		}
		return false;
    }
    //-----------------------------------------------------------------------

    void ALSubsystem::setDefaultVolume(float volume)
    {
        mDefaultVolume = volume;
    }
    //-----------------------------------------------------------------------

    void ALSubsystem::setDefaultVolumeOgg(float volume)
    {
		mDefaultVolumeOgg = volume;
    }

    //-----------------------------------------------------------------------
    ActiveSound* ALSubsystem::getActiveSound(unsigned int index)
	{
		if(index<mSounds.size())
		{
			return mSounds[index];
		}
		return 0;
	}


}
