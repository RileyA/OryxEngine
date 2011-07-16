//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the license, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTEE; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have recieved a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#include "OryxRand.h"

namespace Oryx
{
	const ruint Rand::ORYX_RAND_MAX = RAND_MAX;
	Rand Rand::mRand = Rand();

	Rand::Rand(ruint seed)
	{
		mSeed = (seed == 0 ? time(0) : seed);
	}

	// based on MS implementation of rand()
	ruint Rand::gen()
	{
		mSeed = mSeed * 1103515245 + 12345;
		return static_cast<ruint>(mSeed >> 16) & ORYX_RAND_MAX;
	}

	ruint Rand::gen(int min, int max)
	{
		return min < max ?
			min + gen() % (max - min + 1):
			min + gen() % (max - min + 1);
	}

	ruint Rand::gen(int minmax)
	{
		gen(-minmax, minmax);
	}

	float Rand::genFloat(float min, float max)
	{
		return (min < max) ?
			gen()/(1.f + ORYX_RAND_MAX) * (max - min) + min:
			gen()/(1.f + ORYX_RAND_MAX) * (min - max) + max;
	}

	float Rand::genFloat(float minmax)
	{
		return genFloat(-minmax, minmax);
	}

	char Rand::genChar()
	{
		return static_cast<char>(gen(0,127));
	}
}
