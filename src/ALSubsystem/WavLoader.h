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

#ifndef ORYX_WAV_LOADER_H
#define ORYX_WAV_LOADER_H

#include "AudioLoader.h"

namespace Oryx
{
	enum WavCompressionType
	{
		WCT_UNKNOW = 0,
		WCT_PCM = 1,              // uncompressed (the only one this actually handles at the moment)
		WCT_MS_ADPCM = 2,         // Microsoft ADPCM
		WCT_ITU_G711_A_LAW = 6,   // ITU G.711 a-law
		WCT_ITU_G711_A_uLAW = 7,  // ITU G.711 a-ulaw
		WCT_IMA_ADPCM = 17,       // IMA ADPCM
		WCT_ITU_G723_ADPCM = 20,  // Yamaha ITU G.732 ADPCM
		WCT_GSM = 49,             // GSM 6.10
		WCT_ITU_G721_ADPCM = 64,  // IU G.721 ADPCM
		WCT_MPEG = 80,            // MPEG
		WCT_EXPERIMENTAL = 0xFFFF // Experimental
	};

	/** Loads plain (PCM, uncompressed) WAV files */
	class WavLoader : public AudioLoader
	{
	public:

		WavLoader(){}
		virtual ~WavLoader(){}

		virtual void loadSound(String filename, ALuint& out);

		virtual StreamedSound* streamSound(String filename){return 0;};

	};
}

#endif
