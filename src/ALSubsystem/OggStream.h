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

#ifndef OGGSTREAM_H
#define OGGSTREAM_H

#include "ALSubsystem/ALdllmain.h"

// OpenAl includes
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
// Ogg Vorbis stuff
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#define BUFFER_SIZE (4096 * 8)

namespace Oryx
{
	class OggStream
	{
	public:

		OggStream();
		~OggStream();

		void open(String path,unsigned int source);
		void release();
		void display();
		bool playback();
		bool playing();
		bool update();

		unsigned int getSource();

	protected:

		bool stream(unsigned int buffer);
		void empty();
		void check();
		String errorString(int code);

		FILE*           mOggFile;       // file handle
		OggVorbis_File  mOggStream;     // stream handle
		vorbis_info*    mVorbisInfo;    // some formatting data
		vorbis_comment* mVorbisComment; // user comments

		unsigned mBuffers[2]; // front and back buffers
		int mFormat;     // internal format

		unsigned int mSource;

		bool mOpen;
	};
}


#endif
