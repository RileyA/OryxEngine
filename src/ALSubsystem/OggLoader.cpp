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
#include "OggLoader.h"

#include <AL/alc.h>
#include <AL/al.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

namespace Oryx
{
	void OggLoader::loadSound(String filename, ALuint& out)
	{
		// do basic opening stuff
		OggVorbis_File oggFile = openOgg(filename);
		
		// grab info
		vorbis_info* info = ov_info(&oggFile, -1);

		// determine format based on channels (always 16 bit)
		int format = info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

		// determine uncompressed PCM size (assuming stream formats within the file are consistent..)
		int size = ov_pcm_total(&oggFile, -1) * info->channels * 2;

		// allocate buffer
		char* data = new char[size];

		int pos = 0;
		int section; // not used atm...
	
		// read it all into the buffer
		while(pos < size)
		{
			int result = ov_read(&oggFile, data + pos, size - pos, 0, 2, 1, &section);

			if(result > 0)
				pos += result;
			else if(result == 0)
				break;
			else
				throw Oryx::Exception("Vorbis Error! " + StringUtils::toString(result));
		}

		// create and write to output buffer
		alGenBuffers(1, &out);
		alBufferData(out, format, static_cast<void*>(data), size, info->rate);
		
		// cleanup
		delete[] data;
		ov_clear(&oggFile);
	}
	//---------------------------------------------------------------------------

	AudioStream* OggLoader::streamSound(String filename)
	{
		return 0;
	}
	//---------------------------------------------------------------------------

	size_t OggLoader::ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource)
	{
		return fread(ptr, size, nmemb, (FILE*)datasource);
	}
	//---------------------------------------------------------------------------

	int OggLoader::ov_seek_func(void *datasource, ogg_int64_t offset, int whence)
	{
		return fseek((FILE*)datasource, (long)offset, whence);
	}
	//---------------------------------------------------------------------------

	int OggLoader::ov_close_func(void *datasource)
	{
	   return fclose((FILE*)datasource);
	}
	//---------------------------------------------------------------------------

	long OggLoader::ov_tell_func(void *datasource)
	{
		return ftell((FILE*)datasource);
	}
	//---------------------------------------------------------------------------

	OggVorbis_File OggLoader::openOgg(String filename)
	{
		FILE* file;
		OggVorbis_File oggFile;

		// open the file up
		file = fopen(filename.c_str(), "rb");

		if(!file)
			throw Oryx::Exception("Could not open Ogg file.");
	
		ov_callbacks callbacks;
		callbacks.read_func = ov_read_func;
		callbacks.seek_func = ov_seek_func;
		callbacks.close_func = ov_close_func;
		callbacks.tell_func = ov_tell_func;

		// open the stream, with custom callbacks
		if(ov_open_callbacks(file, &oggFile, 0, 0, callbacks) < 0)
		{
			fclose(file);
			throw Oryx::Exception("Could not open Ogg stream.");
		}

		return oggFile;
	}
	//---------------------------------------------------------------------------
}
