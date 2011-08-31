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

#include "OggStream.h"
#include <vorbis/vorbisfile.h>

namespace Oryx
{
	OggStream::OggStream(OggVorbis_File* file, int format, int rate)
		:AudioStream(format, rate), mFile(file)
	{}
	//---------------------------------------------------------------------------

	OggStream::~OggStream()
	{
		close();
	}
	//---------------------------------------------------------------------------

	int OggStream::stream(char* buffer, int length)
	{
		int bytesWritten = 0;
		int section;

		while(bytesWritten < length)
		{
			int wrote = ov_read(mFile, buffer + bytesWritten, 
				length - bytesWritten, 0, 2, 1, &section);
			if(wrote > 0)
				bytesWritten += wrote;
			else if(wrote < 0)
				return 0;
			else
				break;
		}

		return bytesWritten;
	}
	//---------------------------------------------------------------------------

	void OggStream::close()
	{	
		if(mFile)
			ov_clear(mFile);
		free(mFile);
		mFile = 0;
	}
	//---------------------------------------------------------------------------
}

