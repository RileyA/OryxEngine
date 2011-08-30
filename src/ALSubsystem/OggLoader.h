
//---------------------------------------------------------------------------
//
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

#ifndef ORYX_OGG_LOADER_H
#define ORYX_OGG_LOADER_H

#include "AudioLoader.h"

namespace Oryx
{
	/** Loads and decodes Ogg Vorbis files */
	class OggLoader : public AudioLoader
	{
	public: 

		OggLoader(){}
		virtual ~OggLoader(){}

		virtual void loadSound(String filename, ALuint& out);
		virtual StreamedSound* streamSound(String filename){return 0;};

	};
}

#endif
