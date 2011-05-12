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

#ifndef ORYXCHAISCRIPTSUBSYSTEM
#define ORYXCHAISCRIPTSUBSYSTEM

#include "Oryx.h"
#include "Chaidllmain.h"
#include "OryxEngineSubsystem.h"

namespace Oryx
{
	class ChaiWrapper;

	class ORYX_CHAI_EXPORT ChaiscriptSubsystem : public EngineSubsystem
	{
	public:

		ChaiscriptSubsystem();
		~ChaiscriptSubsystem();

		/** Starts the scripting system up */
		virtual void _init();

		/** Shuts the scripting system down */
		virtual void _deinit();

		/** Updates the scripting system
		 *		@param delte The time since the last frame */
		virtual void _update(Real delta);

		/** Called when the current state ends  */
		virtual void _endState();

		/** Returns the name of this susbsystem */
		virtual String getName();

		/** Runs a .chai script
			@param filename The name of the file to open */
		void runScript(String filename);

		/** Runs a line of script
			@param script The scripting code */
		void runString(String script);

		/** Gets a pointer to the ChaiWrapper */
		ChaiWrapper* getWrapper();

	protected:

		void _registerBasicTypes();

		bool mInitialized;
		ChaiWrapper* mChai;

	};
}

#endif
