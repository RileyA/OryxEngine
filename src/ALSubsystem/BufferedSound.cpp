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

#include "ALdllmain.h"
#include "BufferedSound.h"
#include "OryxLogger.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace Oryx
{
	BufferedSound::BufferedSound(ALuint source, ALuint buffer)
		:Sound(source),mBuffer(buffer)
	{
		// set buffer up, don't play automatically though
		alSourcei(mSource, AL_BUFFER, mBuffer);
	}

	BufferedSound::~BufferedSound()
	{
		// ... nothin' to see here ...
	}

	void BufferedSound::update()
	{
		// ... nothin' to see here ...
	}
}
