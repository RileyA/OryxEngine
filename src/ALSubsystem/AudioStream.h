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

#ifndef ORYX_AUDIO_STREAM_H
#define ORYX_AUDIO_STREAM_H

#include "Oryx.h"
#include "ALdllmain.h"

typedef unsigned int ALuint;

namespace Oryx
{
	/** An abstract streaming audio source */
	class ORYX_AL_EXPORT AudioStream
	{
	public:

		AudioStream(int format, int rate)
			:mRate(rate),mFormat(format){}

		virtual ~AudioStream(){}

		/** Stream into the provided buffer */ 
		virtual int stream(char* buffer, int length) = 0;

		/** Close and free up the source */
		virtual void close() = 0;

		int getRate(){return mRate;}
		int getFormat(){return mFormat;}
	
	protected:

		int mRate;
		int mFormat;

	};
}

#endif
