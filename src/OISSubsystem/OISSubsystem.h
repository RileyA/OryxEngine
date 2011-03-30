//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010-2011

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

		/** Gets whether or not a key is down by keycode */
		bool isKeyDown(uint key);
		/** Gets whether or not a key is down by name */
		bool isKeyDown(String key);

		/** Shortcut for detecting a single key press */
		bool wasKeyPressed(uint key);
		/** Shortcut for detecting a single key press */
		bool wasKeyPressed(String key);

		/** Gets whether or not a mouse button is down by index */
		bool isButtonDown(uint button);
		/** Gets whether or not a mouse button is down by name */
		bool isButtonDown(String button);

		/** Shortcut for handling a single button press (by index) */
		bool wasButtonPressed(uint button);
		/** Shortcut for handling a single button press (by name) */
		bool wasButtonPressed(String button);

		/** Starts up the input system (must be done per state) 
		 *		@param handle Handle of the window from which to track input 
		 *		@param grabMouse Does the application take over the OS mouse cursor	*/	
		void initInput(size_t handle, bool grabMouse);
		/** Shuts the input system down */
		void deinitInput();
		
		/** Toggles whether or not the mouse is "trapped" by the window */
		void toggleMouseGrab();

		/** Called when the mouse moves */
		void _setMousePos(int x,int y,int relx,int rely);
		/** Called on each key event */
		void _key(uint key,bool up,uint val);
		/** Called on mouse button events */
		void _mouseButton(uint button,bool up);

		/** Set up string -> keycode conversions */
		void assignConversions();

    protected:

        bool mInitialized;
		size_t mHandle;
		OISListener* mListener;
		std::map<uint,String> mKeys;
		std::map<String,uint> mKeyNames;
		std::vector<String> mButtons;
		std::map<String,uint> mButtonNames;
		std::map<uint, bool> mKeyStates;
		std::map<uint, bool> mKeyPresses;
		std::vector<bool> mButtonStates;
		std::vector<bool> mButtonPresses;

		Vector2 mMousePos;

		bool mGrabbedMouse;

    };
}

#endif
