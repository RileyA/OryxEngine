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

#ifndef ORYX_GAMESTATE
#define ORYX_GAMESTATE

#include "Oryx.h"
#include "OryxState.h"

namespace Oryx
{
	class Engine;

	/** A game state almost identical to State, except it 
	 *		automagically gets a pointer to the Engine */
	class ORYX_EXPORT GameState : public State
	{
	public:

		GameState();

		void setReturnParam(String param, String value);
		void setReturnPtr(void* ptr);
		void* getReturnPtr();
		std::map<String, String> getReturnParams();
		void setInputParams(std::map<String, String> in, void* inptr);

	protected:

		Engine* mEngine;

		std::map<String, String> mInputParams;
		void* mInputPtr;
		std::map<String, String> mReturnParams;
		void* mUserPtr;

	};
}

#endif
