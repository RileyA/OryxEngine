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

#include "Oryx.h"
#include "OISListener.h"
#include "OISSubsystem.h"
#include "OryxLogger.h"

namespace Oryx
{
	OISListener::OISListener(size_t handle,OISSubsystem* sys,bool grabMouse)
	{
		mSubsystem = sys;

		std::ostringstream windowHndStr;
		windowHndStr << handle;

		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		if(!grabMouse)
		{
		#ifdef OIS_WIN32_PLATFORM
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
			pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
			pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
			pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
			pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
			pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
			pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif
		}

		mInputManager = OIS::InputManager::createInputSystem(pl);
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
		mKeyboard->setEventCallback(this);
		mMouse->setEventCallback(this);
		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = 1024;
		ms.height = 768;
		setMousePosition(512,350);
	}

	OISListener::~OISListener()
	{
		if (mInputManager)
		{
			if (mMouse)
			{
				mInputManager->destroyInputObject(mMouse);
				mMouse = 0;
			}
			if (mKeyboard)
			{
				mInputManager->destroyInputObject(mKeyboard);
				mKeyboard = 0;
			}
			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}

	void OISListener::update()
	{
		mMouse->capture();
		mKeyboard->capture();
	}

	void OISListener::setMousePosition(int x,int y)
	{
		mCursorX = x;
		mCursorY = y;
		checkPosition();
	}

	void OISListener::setInputViewSize(int width,int height)
	{
		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = width;
		ms.height = height;
		checkPosition();
	}

	void OISListener::checkPosition()
	{
		const OIS::MouseState &ms = mMouse->getMouseState();
		if (mCursorX < 0)
			mCursorX = 0;
		else if (mCursorX >= ms.width)
			mCursorX = ms.width - 1;
		if (mCursorY < 0)
			mCursorY = 0;
		else if (mCursorY >= ms.height)
			mCursorY = ms.height - 1;
		mSubsystem->_setMousePos(mCursorX,mCursorY,ms.X.rel,ms.Y.rel);
	}

	bool OISListener::mouseMoved(const OIS::MouseEvent& arg)
	{
		const OIS::MouseState &ms = mMouse->getMouseState();
		mCursorX = ms.X.abs;
		mCursorY = ms.Y.abs;
		checkPosition();
		return true;
	}

	bool OISListener::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
	{
		mSubsystem->_mouseButton(id,true);
		return true;
	}

	bool OISListener::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
	{
		mSubsystem->_mouseButton(id,false);
		return true;
	}

	bool OISListener::keyPressed(const OIS::KeyEvent& arg)
	{
		mSubsystem->_key(arg.key,true);
		return true;
	}

	bool OISListener::keyReleased(const OIS::KeyEvent& arg)
	{
		mSubsystem->_key(arg.key,false);
		return true;
	}
}
