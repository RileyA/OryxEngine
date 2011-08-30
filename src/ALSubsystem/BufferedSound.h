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
#include "ALSubsystem/Sound.h"

namespace Oryx
{
	class ORYX_AL_EXPORT BufferedSound : public Sound
	{
	public:

		BufferedSound(ALuint source, ALuint buffer);
		virtual ~BufferedSound();
		virtual void update();

	protected:

		ALuint mBuffer;

	};
};

#endif
