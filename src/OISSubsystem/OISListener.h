//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010-2011

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

#ifndef ORYX_OISLISTENER_H
#define ORYX_OISLISTENER_H

#include "Oryx.h"
#include "OIS/OIS.h"

namespace Oryx
{
	class OISSubsystem;

	/** Internal class that serves as the OIS lsitener
	 *		TODO: add joystick support */
	class OISListener : public OIS::KeyListener, public OIS::MouseListener
	{
	public:

		OISListener(size_t windowHandle,OISSubsystem* sys,bool grabMouse);
		~OISListener();

		void update();
		void setMousePosition(int x,int y);
		void setInputViewSize(int width, int hieght);
		void checkPosition();

	protected:

		bool mouseMoved(const OIS::MouseEvent& arg);
		bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
		bool keyPressed(const OIS::KeyEvent& arg);
		bool keyReleased(const OIS::KeyEvent& arg);

	private:

		OIS::InputManager* mInputManager;
		OIS::Keyboard* mKeyboard;
		OIS::Mouse* mMouse;

		int mCursorX;
		int mCursorY;

		OISSubsystem* mSubsystem;
		
	};
}

#endif
