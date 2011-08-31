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

#include "StreamedSound.h"
#include <AL/alc.h>
#include <AL/al.h>

namespace Oryx
{
	StreamedSound::StreamedSound(AudioStream* stream, ALuint source)
		:Sound(source),mStream(stream),mDone(false)
	{
		alGenBuffers(2, mBuffers);
		if(updateBuffer(mBuffers[0]))
			alSourceQueueBuffers(mSource, 1, &mBuffers[0]);
		if(updateBuffer(mBuffers[1]))
			alSourceQueueBuffers(mSource, 1, &mBuffers[1]);
	}
	//--------------------------------------------------------------------------

	StreamedSound::~StreamedSound()
	{
		mStream->close();
		stop();
		alDeleteBuffers(2, mBuffers);
	}
	//--------------------------------------------------------------------------

	void StreamedSound::update()
	{
		// once it's all been streamed, it's just a matter of waiting for the
		// buffers to be finished off...
		if(!mDone)
		{
			int processed = 0;
			alGetSourcei(mSource, AL_BUFFERS_PROCESSED, &processed);

			// unqueue, stream to and requeue any processed buffers
			while(processed--)
			{
				ALuint buffer;
				alSourceUnqueueBuffers(mSource, 1, &buffer);

				if(updateBuffer(buffer))
					alSourceQueueBuffers(mSource, 1, &buffer);
			}
		}
	}
	//--------------------------------------------------------------------------

	bool StreamedSound::updateBuffer(ALuint buffer)
	{
		if(mDone)
			return false;

		char data[BUFFER_SIZE];
		int bytesStreamed = mStream->stream(data, BUFFER_SIZE);

		if(bytesStreamed == 0)
		{
			// no more data can be grabbed, close the source and mark it done
			mStream->close();
			mDone = true;
		}
		else
		{
			// write to the buffer
			alBufferData(buffer, mStream->getFormat(), static_cast<void*>(data), 
				bytesStreamed, mStream->getRate());
		}

		return !mDone;
	}
	//--------------------------------------------------------------------------
}
