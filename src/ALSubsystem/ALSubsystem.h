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
#include "ALSubsystem/ALdllmain.h"
#include "OryxEngineSubsystem.h"

#include "SoundPtr.h"
#include "BufferedSound.h"
#include "ActiveSound.h"

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

        SoundPtr play2D(String filename);
		bool bufferSound(String filename);
		void update();
		bool loadSound(String filename);
		// hacky, to be fixed:
		void setDefaultVolume(float volume);
		void setDefaultVolumeOgg(float volume);

		ActiveSound* getActiveSound(unsigned int index);

    protected:

        bool mInitialized;

        std::map<std::string,BufferedSound*> mBuffers;
		std::vector<ActiveSound*> mSounds;
		unsigned int mMaxSources;

		float mDefaultVolume;
		float mDefaultVolumeOgg;
        bool mVolumeDirty;
        bool mVolumeOggDirty;
    };
}

#endif
