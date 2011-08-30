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
//--------------------------------------------------------------------------

#ifndef ORYX_AUDIO_LOADER_H
#define ORYX_AUDIO_LOADER_H

#include "Oryx.h"

typedef unsigned int ALuint;
class StreamedSound;

namespace Oryx
{
	/** Abstract audio loading class (to be extended for each loadable filetype) */
	class AudioLoader
	{
	public:
		
		AudioLoader(){};
		virtual ~AudioLoader(){};
	
		virtual void loadSound(String filename, ALuint& out) = 0;
		virtual StreamedSound* streamSound(String filename) = 0;
	};
}

#endif
