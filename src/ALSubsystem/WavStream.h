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

#ifndef ORYX_WAV_STREAM
#define ORYX_WAV_STREAM

#include "AudioStream.h"
#include "ALdllmain.h"

namespace Oryx
{
	class ORYX_AL_EXPORT WavStream : public AudioStream
	{
	public:

		WavStream(std::ifstream* file, int format, int rate, int dataSize);
		virtual ~WavStream();

		virtual int stream(char* buffer, int length);
		virtual void close();

	private:

		std::ifstream* mFile;
		int mSize;
		int mPosition;

	};
}

#endif
