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

#include "ALdllmain.h"

#include "OggStream.h"
#include "OryxLogger.h"

namespace Oryx
{
	// Ogg callbacks
	size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource)
	{
		return fread(ptr, size, nmemb, (FILE*)datasource);
	}

	int ov_seek_func(void *datasource, ogg_int64_t offset, int whence)
	{
		return fseek((FILE*)datasource, (long)offset, whence);
	}

	int ov_close_func(void *datasource)
	{
	   return fclose((FILE*)datasource);
	}

	long ov_tell_func(void *datasource)
	{
		return ftell((FILE*)datasource);
	}

	OggStream::OggStream()
		:mOpen(0)
	{

	}

	OggStream::~OggStream()
	{
		release();
	}

	void OggStream::open(String filename,unsigned int source)
	{
		#pragma warning (push)
		#pragma warning (disable: 4996)// ahhh shut up...
		if(!(mOggFile = fopen(filename.c_str(), "rb")))
			throw String("Could not open Ogg file.");
		#pragma warning (pop)

		ov_callbacks sCallbacks;

		sCallbacks.read_func = ov_read_func;
		sCallbacks.seek_func = ov_seek_func;
		sCallbacks.close_func = ov_close_func;
		sCallbacks.tell_func = ov_tell_func;

		int result;

		if((result = ov_open_callbacks(mOggFile, &mOggStream, NULL, 0,sCallbacks)) < 0)
		{
			fclose(mOggFile);
			throw String("Could not open Ogg stream. ") + errorString(result);
		}

		mOpen = true;

		mVorbisInfo = ov_info(&mOggStream, -1);
		mVorbisComment = ov_comment(&mOggStream, -1);

		if(mVorbisInfo->channels == 1)
		{
			mFormat = AL_FORMAT_MONO16;
		}
		else
		{
			mFormat = AL_FORMAT_STEREO16;
		}

		alGenBuffers(2, mBuffers);
		check();

		// set some basic properties
		alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
		alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
		alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
		alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
		alSourcef (source, AL_PITCH,  1.f          );
		alSourcef (source, AL_GAIN,  1.f          );
		alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );

		mSource = source;
	}

	void OggStream::release()
	{
		if(mOpen)
		{
			mOpen = false;
			alSourceStop(mSource);
			empty();
			alSourcei(mSource,AL_BUFFER,0);
			alDeleteBuffers(1, mBuffers);
			check();
			ov_clear(&mOggStream);
		}
	}

	void OggStream::display()
	{
		std::cout
			<< "version         " << mVorbisInfo->version         << "\n"
			<< "channels        " << mVorbisInfo->channels        << "\n"
			<< "rate (hz)       " << mVorbisInfo->rate            << "\n"
			<< "bitrate upper   " << mVorbisInfo->bitrate_upper   << "\n"
			<< "bitrate nominal " << mVorbisInfo->bitrate_nominal << "\n"
			<< "bitrate lower   " << mVorbisInfo->bitrate_lower   << "\n"
			<< "bitrate window  " << mVorbisInfo->bitrate_window  << "\n"
			<< "\n"
			<< "vendor " << mVorbisComment->vendor << "\n";

		for(int i = 0; i < mVorbisComment->comments; i++)
			std::cout << "   " << mVorbisComment->user_comments[i] << "\n";

		std::cout << std::endl;
	}

	bool OggStream::playback()
	{
		if(playing())
			return true;

		if(!stream(mBuffers[0]))
			return false;

		if(!stream(mBuffers[1]))
			return false;

		alSourceQueueBuffers(mSource, 2, mBuffers);
		alSourcePlay(mSource);

		return true;
	}

	bool OggStream::playing()
	{
		ALenum state;
		alGetSourcei(mSource, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}

	bool OggStream::update()
	{

		int processed;
		bool active = true;

		alGetSourcei(mSource, AL_BUFFERS_PROCESSED, &processed);

		while(processed--)
		{
			ALuint buffer;

			alSourceUnqueueBuffers(mSource, 1, &buffer);
			check();
			active = stream(buffer);

			if(active)
			{
				alSourceQueueBuffers(mSource, 1, &buffer);
				check();
			}
		}

		return active;
	}

	unsigned int OggStream::getSource()
	{
		return mSource;
	}

	bool OggStream::stream(unsigned int buffer)
	{
		char data[BUFFER_SIZE];
		int  size = 0;
		int  section;
		int  result;

		while(size < BUFFER_SIZE)
		{
			result = ov_read(&mOggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, & section);

			if(result > 0)
				size += result;
			else
				if(result < 0)
					throw errorString(result);
				else
					break;
		}

		if(size == 0)
			return false;

		alBufferData(buffer, mFormat, data, size, mVorbisInfo->rate);
		check();
		return true;
	}

	void OggStream::empty()
	{
		int queued;

		alGetSourcei(mSource, AL_BUFFERS_QUEUED, &queued);

		while(queued--)
		{
			ALuint buffer;

			alSourceUnqueueBuffers(mSource, 1, &buffer);
			check();
		}
	}

	void OggStream::check()
	{
		int error = alGetError();
		if(error != AL_NO_ERROR)
		{
			std::cout<<"OpenAL error was raised "<<error<<"\n";
			throw String("OpenAL error was raised.");
		}
	}

	String OggStream::errorString(int code)
	{
		switch(code)
		{
			case OV_EREAD:
				return String("Read from media.");
			case OV_ENOTVORBIS:
				return String("Not Vorbis data.");
			case OV_EVERSION:
				return String("Vorbis version mismatch.");
			case OV_EBADHEADER:
				return String("Invalid Vorbis header.");
			case OV_EFAULT:
				return String("Internal logic fault (bug or heap/stack corruption.");
			default:
				return String("Unknown Ogg error.");
		}
	}
}
