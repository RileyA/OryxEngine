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

#ifndef ORYX_RAND_H
#define ORYX_RAND_H

#include "Oryx.h"
#include <cstdlib>

namespace Oryx
{
	typedef long long ruint;

	/** Very simple pseudorandom number generator */
	class Rand
	{
	public:

		/** Creates a random number generator
		 *		@param seed The seed to use (or 0 for time(0)) */
		Rand(ruint seed = 0);

		/** Destructor */
		virtual ~Rand(){}
		
		/** Gets a (pseudo) random number */
		virtual ruint gen();

		/** Gets a random number within a range */
		ruint gen(int min, int max);

		/** Gets a random float */
		float genFloat(float min, float max);
	
		/** Gets a random character */
		char genChar();

		/** Gets the static Rand instance */
		static Rand& get(){return mRand;}

		// Maximum value this can return
		static const ruint ORYX_RAND_MAX;

	private:

		// The seed
		ruint mSeed;

		// a static Rand, for one-off generation, so we don't need to
		// create a new one every time, saves manually calling rand(), etc
		static Rand mRand;


	};
}

#endif
