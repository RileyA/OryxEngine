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

#include "WavStream.h"

namespace Oryx
{
	WavStream::WavStream(std::ifstream* file, int format, int rate, int dataSize)
		:AudioStream(rate, format), mFile(file), mSize(dataSize), mPosition(0)
	{}
	//---------------------------------------------------------------------------

	WavStream::~WavStream()
	{
		close();
	}
	//---------------------------------------------------------------------------

	int WavStream::stream(char* buffer, int length)
	{
		if(mSize == mPosition)
		{
			return 0;
		}
		else if(mSize - mPosition <= length)
		{
			mFile->read(buffer, mSize - mPosition);
			int wrote = mSize - mPosition;
			mPosition = mSize;
			return wrote;
		}
		else
		{
			mFile->read(buffer, length);
			mPosition += length;
			return length;
		}
	}
	//---------------------------------------------------------------------------

	void WavStream::close()
	{	
		delete mFile;
		mFile = 0;
	}
	//---------------------------------------------------------------------------
}

