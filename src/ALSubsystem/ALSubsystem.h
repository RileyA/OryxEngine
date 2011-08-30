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

#ifndef ORYX_OAL_SUBSYSTEM_H
#define ORYX_OAL_SUBSYSTEM_H

#include "Oryx.h"
#include "ALdllmain.h"
#include "OryxEngineSubsystem.h"
#include "Sound.h"
#include "AudioLoader.h"
#include "WavLoader.h"
#include "OggLoader.h"
#include "BufferedSound.h"

typedef unsigned int ALuint;
struct ALCdevice_struct;
typedef struct ALCdevice_struct ALCdevice;
struct ALCcontext_struct;
typedef struct ALCcontext_struct ALCcontext;

namespace Oryx
{
	class ORYX_AL_EXPORT ALSubsystem : public EngineSubsystem
	{
	public:

		ALSubsystem();
		~ALSubsystem();

		virtual void _init();
		virtual void _deinit();
		virtual void _update(Real delta);
		virtual void _endState();
		virtual String getName();

		SoundPtr play2D(String name, bool startPaused = false);
		SoundPtr stream2D(String filename);

		void loadSound(String filename, String name = "AUTO");
		void unloadSound(String name);

		void registerAudioLoader(AudioLoader* loader, String filetype);

	protected:

		ALuint getSource();
		bool hasSources();

		bool mInitialized;

		ALCdevice* mDevice;
		ALCcontext* mContext;

		std::list<SoundPtr> mActiveSounds;
		std::vector<ALuint> mSources;
		std::map<ALuint, bool> mSourceAvailability;
		std::map<String, ALuint> mAudioBuffers;
		std::map<String, AudioLoader*> mAudioLoaders; 

		// Built-in loaders
		WavLoader mWavLoader;
		OggLoader mOggLoader;
	};
}

#endif
