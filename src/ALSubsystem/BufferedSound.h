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

#ifndef BUFFEREDSOUND_H
#define BUFFEREDSOUND_H

#include "ALSubsystem/ALdllmain.h"

namespace Oryx
{
	class ORYX_AL_EXPORT BufferedSound
	{
	public:

		/** Constructor
		@remarks
			Give it a filename and it loads the data up, you also have the option
			to not immediately load the sound up (and later call BufferedSound::load())
			The file should be verified to be a sound file prior to being loaded.
		@param filename The file to be loaded (.wav only for now)
		@param delayLoading Don't immediately load the sound (default: false) */
		BufferedSound(const String& filename,bool isOgg,bool delayLoading=false);

		/** Destructor */
		~BufferedSound();

		/** (re)Loads the sound, unless otherwise specified, this will be done automatically
		@returns Whether or not it was sucessful */
		bool load();

		/** Unloads the sound from memory (it can still be reloaded with BufferedSound::load()) */
		void unload();

		/** Whether or not the sound is currently loaded
		@returns Whether or not it's loaded */
		bool isLoaded();

		/** Whether or not the sound is an Ogg Vorbis stream
		@remarks
			Ogg sounds will not be loaded into memory, only streamed (for now at least)
		@returns Whether or not it is an .ogg */
		bool isOgg();

		unsigned int getBuffer();
		#ifdef ORYX_H
		String getFilename();
		#endif

	protected:

		// The OpenAL "name" for the buffer
		unsigned int mBuffer;

		// The filename for the sound
		String mFilename;

		// Whether or not it is loaded
		bool mLoaded;

		// If this sound is a .ogg
		bool mOgg;

	};
};

#endif
