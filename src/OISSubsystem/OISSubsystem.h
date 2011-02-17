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

#ifndef ORYX_OISSUBSYSTEM_H
#define ORYX_OISSUBSYSTEM_H

#include "Oryx.h"
#include "OISSubsystem/OISdllmain.h"
#include "OryxEngineSubsystem.h"
#include "OryxVector2.h"


namespace Oryx
{
	class OISListener;

	/** Input subsystem using OIS */
    class ORYX_OIS_EXPORT OISSubsystem : public EngineSubsystem
    {
    public:

		OISSubsystem();
        virtual ~OISSubsystem();

		/** INTERNAL: inits the system */
        virtual void _init();
		/** INTERNAL: deinits the system */
        virtual void _deinit();
		/** INTERNAL: updates the system */
        virtual void _update(Real delta);
		/** INTERNAL: called at the end of a state */
        virtual void _endState();
		/** Gets the name of the system 
			@return The name ("OgreSubsystem") */
        virtual String getName();

		bool isKeyDown(uint key);
		bool isKeyDown(String key);

		bool isButtonDown(uint button);
		bool isButtonDown(String button);

		/** Starts up the input system (must be done per state) 
		 *		@param handle Handle of the window from which to track input */
		void initInput(size_t handle);

		void _setMousePos(int x,int y,int relx,int rely);
		void _key(uint key,bool up);
		void _mouseButton(uint button,bool up);

		void assignConversions();

        static const size_t mDependencyCount;
        static const String mDependencies[];

    protected:

        bool mInitialized;
		OISListener* mListener;
		std::map<uint,String> mKeys;
		std::map<String,uint> mKeyNames;
		std::vector<String> mButtons;
		std::map<String,uint> mButtonNames;
		std::map<uint, bool> mKeyStates;
		std::vector<bool> mButtonStates;

		Vector2 mMousePos;

    };
}

#endif
