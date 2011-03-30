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

#include "OISdllmain.h"
#include "OISSubsystem.h"
#include "OryxLogger.h"
#include "OryxMessageAny.h"

#include "OISListener.h"
#include "OIS.h"

namespace Oryx
{
	OISSubsystem::OISSubsystem()
        :EngineSubsystem(),mInitialized(false),
		mGrabbedMouse(false),mListener(0),mHandle(0)
	{
		EventHandler::registerDestination(getName(),this);
	}
    //-----------------------------------------------------------------------

    OISSubsystem::~OISSubsystem()
    {
    }
    //-----------------------------------------------------------------------

    void OISSubsystem::_init()
    {
        if(!mInitialized)
        {
            Logger::getPtr()->logMessage("OIS Subsystem starting up...");

			createSignal("keyPressed");   // passes keycode on press
			createSignal("keyReleased");  // passes keycode on release
			createSignal("charPressed");  // passes char value on press
			createSignal("mousePressed"); // passes mouse button code on click
			createSignal("mousePressed"); // passes mouse button code on release
			createSignal("mouseMoved");   // passes mouse pos on move
			createSignal("mouseMovedAbs");// passes absolute mouse pos when moved

			assignConversions();

			std::map<uint,String>::iterator it = mKeys.begin();
			for(it;it!=mKeys.end();++it)
			{
				mKeyNames[it->second] = it->first;
				mKeyStates[it->first] = false;
				createSignal("released_"+it->second);
				createSignal("pressed_"+it->second);
			}

			std::vector<String>::iterator iter = mButtons.begin();
			int i = 0;
			for(iter;iter!=mButtons.end();++iter)
			{
				mButtonNames[*iter] = i;
				mButtonStates.push_back(false);
				createSignal("released_"+(*iter));
				createSignal("pressed_"+(*iter));
				++i;
			}

			mKeyPresses = mKeyStates;
			mButtonPresses = mButtonStates;

            Logger::getPtr()->logMessage("OIS Subsystem started up.");
            mInitialized = true;
        }
    }
    //-----------------------------------------------------------------------

    void OISSubsystem::_deinit()
    {
        if(mInitialized)
        {
            Logger::getPtr()->logMessage("OIS Subsystem shutting down...");
			if(mListener)
			{
				delete mListener;
				mListener = 0;
			}
            Logger::getPtr()->logMessage("OIS Subsystem shut down.");
            mInitialized = false;
        }
    }
    //-----------------------------------------------------------------------

    void OISSubsystem::_update(Real delta)
    {
		if(mListener)
			mListener->update();
    }
    //-----------------------------------------------------------------------

    void OISSubsystem::_endState()
    {
		if(mListener)
		{
			delete mListener;
			mListener = 0;
		}
    }
    //-----------------------------------------------------------------------

    String OISSubsystem::getName()
    {
        return String("OISSubsystem");
    }
	//-----------------------------------------------------------------------

	bool OISSubsystem::isKeyDown(uint key)
	{
		return mKeyStates[key];
	}
	//-----------------------------------------------------------------------
	
	bool OISSubsystem::isKeyDown(String key)
	{
		return mKeyStates[mKeyNames[key]];
	}
	//-----------------------------------------------------------------------

	bool OISSubsystem::wasKeyPressed(uint key)
	{
		bool wasPressed = mKeyPresses[key];
		mKeyPresses[key] = false;
		return wasPressed;
	}
	//-----------------------------------------------------------------------
	
	bool OISSubsystem::wasKeyPressed(String key)
	{
		return wasKeyPressed(mKeyNames[key]);
	}
	//-----------------------------------------------------------------------
	
	bool OISSubsystem::isButtonDown(uint button)
	{
		return mButtonStates[button];
	}
	//-----------------------------------------------------------------------

	bool OISSubsystem::isButtonDown(String button)
	{
		return mButtonStates[mButtonNames[button]];
	}
	//-----------------------------------------------------------------------

	bool OISSubsystem::wasButtonPressed(uint button)
	{
		bool wasPressed = mButtonPresses[button];
		mButtonPresses[button] = false;
		return wasPressed;
	}
	//-----------------------------------------------------------------------
	
	bool OISSubsystem::wasButtonPressed(String button)
	{
		return wasButtonPressed(mButtonNames[button]);
	}
	//-----------------------------------------------------------------------

	void OISSubsystem::initInput(size_t handle, bool grabMouse = false)
	{
		mHandle = handle;
		mGrabbedMouse = grabMouse;
		if(!mListener)
			mListener = new OISListener(handle,this,grabMouse);
	}
	//-----------------------------------------------------------------------

	void OISSubsystem::deinitInput()
	{
		if(mListener)
			delete mListener;
		mListener = 0;
	}
	//-----------------------------------------------------------------------
	
	void OISSubsystem::toggleMouseGrab()
	{
		mGrabbedMouse = !mGrabbedMouse;
		deinitInput();
		initInput(mHandle,mGrabbedMouse);
	}
	//-----------------------------------------------------------------------
	
	void OISSubsystem::_setMousePos(int x,int y, int relx, int rely)
	{
		mMousePos = Vector2(x,y);
		getSignal("mouseMoved")->fire(MessageAny<Vector2>(Vector2(relx,rely)));
		getSignal("mouseMovedAbs")->fire(MessageAny<Vector2>(Vector2(x,y)));
	}
	//-----------------------------------------------------------------------

	void OISSubsystem::_key(uint key, bool up, uint val)
	{
		mKeyStates[key] = up;

		if(up)
		{
			getSignal("charPressed")->fire(MessageAny<uint>(val));
			getSignal("keyPressed")->fire(MessageAny<uint>(key));
			getSignal(String("pressed_")+String(mKeys[key]))->fire(0);
		}
		else
		{
			mKeyPresses[key] = true;
			getSignal(String("released_")+String(mKeys[key]))->fire(0);
			getSignal("keyReleased")->fire(MessageAny<uint>(key));
		}
	}
	//-----------------------------------------------------------------------	

	void OISSubsystem::_mouseButton(uint button, bool up)
	{
		mButtonStates[button] = up;
		if(up)
		{
			getSignal(String("released_")+String(mButtons[button]))->fire(0);
		}
		else
		{
			mButtonPresses[button] = true;
			getSignal("mousePressed")->fire(MessageAny<uint>(button));
			getSignal(String("pressed_")+String(mButtons[button]))->fire(0);
		}
	}
	//-----------------------------------------------------------------------
	
	void OISSubsystem::assignConversions()
	{
		mButtons.push_back(String("MB_Left"));
		mButtons.push_back(String("MB_Right"));
		mButtons.push_back(String("MB_Middle"));
		mButtons.push_back(String("MB_Button3"));
		mButtons.push_back(String("MB_Button4"));
		mButtons.push_back(String("MB_Button5"));
		mButtons.push_back(String("MB_Button6"));
		mButtons.push_back(String("MB_Button7"));

		mKeys[OIS::KC_UNASSIGNED] = String("KC_UNASSIGNED");
		mKeys[OIS::KC_ESCAPE] = String("KC_ESCAPE");
		mKeys[OIS::KC_1] = String("KC_1");
		mKeys[OIS::KC_2] = String("KC_2");
		mKeys[OIS::KC_3] = String("KC_3");
		mKeys[OIS::KC_4] = String("KC_4");
		mKeys[OIS::KC_5]  = String("KC_5");
		mKeys[OIS::KC_6] = String("KC_6");
		mKeys[OIS::KC_7] = String("KC_7");
		mKeys[OIS::KC_8] = String("KC_8");
		mKeys[OIS::KC_9] = String("KC_9");
		mKeys[OIS::KC_0] = String("KC_0");
		mKeys[OIS::KC_MINUS] = String("KC_MINUS");
		mKeys[OIS::KC_EQUALS] = String("KC_EQUALS");
		mKeys[OIS::KC_BACK] = String("KC_BACK");
		mKeys[OIS::KC_TAB] = String("KC_TAB");
		mKeys[OIS::KC_Q] = String("KC_Q");
		mKeys[OIS::KC_W] = String("KC_W");
		mKeys[OIS::KC_E] = String("KC_E");
		mKeys[OIS::KC_R] = String("KC_R");
		mKeys[OIS::KC_T] = String("KC_T");
		mKeys[OIS::KC_Y] = String("KC_Y");
		mKeys[OIS::KC_U] = String("KC_U");
		mKeys[OIS::KC_I] = String("KC_I");
		mKeys[OIS::KC_O] = String("KC_O");
		mKeys[OIS::KC_P] = String("KC_P");
		mKeys[OIS::KC_LBRACKET] = String("KC_LBRACKET");
		mKeys[OIS::KC_RBRACKET] = String("KC_RBRACKET");
		mKeys[OIS::KC_RETURN] = String("KC_RETURN");
		mKeys[OIS::KC_LCONTROL] = String("KC_LCONTROL");
		mKeys[OIS::KC_A] = String("KC_A");
		mKeys[OIS::KC_S] = String("KC_S");
		mKeys[OIS::KC_D] = String("KC_D");
		mKeys[OIS::KC_F] = String("KC_F");
		mKeys[OIS::KC_G] = String("KC_G");
		mKeys[OIS::KC_H] = String("KC_H");
		mKeys[OIS::KC_J] = String("KC_J");
		mKeys[OIS::KC_K] = String("KC_K");
		mKeys[OIS::KC_L] = String("KC_L");
		mKeys[OIS::KC_SEMICOLON] = String("KC_SEMICOLON");
		mKeys[OIS::KC_APOSTROPHE] = String("KC_APOSTROPHE");
		mKeys[OIS::KC_GRAVE] = String("KC_GRAVE");
		mKeys[OIS::KC_LSHIFT] = String("KC_LSHIFT");
		mKeys[OIS::KC_BACKSLASH] = String("KC_BACKSLASH");
		mKeys[OIS::KC_Z] = String("KC_Z");
		mKeys[OIS::KC_X] = String("KC_X");
		mKeys[OIS::KC_C] = String("KC_C");
		mKeys[OIS::KC_V] = String("KC_V");
		mKeys[OIS::KC_B] = String("KC_B");
		mKeys[OIS::KC_N] = String("KC_N");
		mKeys[OIS::KC_M] = String("KC_M");
		mKeys[OIS::KC_COMMA] = String("KC_COMMA");
		mKeys[OIS::KC_PERIOD] = String("KC_PERIOD");
		mKeys[OIS::KC_SLASH] = String("KC_SLASH");
		mKeys[OIS::KC_RSHIFT] = String("KC_RSHIFT");
		mKeys[OIS::KC_MULTIPLY] = String("KC_MULTIPLY");
		mKeys[OIS::KC_LMENU] = String("KC_LMENU");
		mKeys[OIS::KC_SPACE] = String("KC_SPACE");
		mKeys[OIS::KC_CAPITAL] = String("KC_CAPITAL");
		mKeys[OIS::KC_F1] = String("KC_F1");
		mKeys[OIS::KC_F2] = String("KC_F2");
		mKeys[OIS::KC_F3] = String("KC_F3");
		mKeys[OIS::KC_F4] = String("KC_F4");
		mKeys[OIS::KC_F5] = String("KC_F5");
		mKeys[OIS::KC_F6] = String("KC_F6");
		mKeys[OIS::KC_F7] = String("KC_F7");
		mKeys[OIS::KC_F8] = String("KC_F8");
		mKeys[OIS::KC_F9] = String("KC_F9");
		mKeys[OIS::KC_F10] = String("KC_F10");
		mKeys[OIS::KC_NUMLOCK] = String("KC_NUMLOCK");
		mKeys[OIS::KC_SCROLL] = String("KC_SCROLL");
		mKeys[OIS::KC_NUMPAD7] = String("KC_NUMPAD7");
		mKeys[OIS::KC_NUMPAD8] = String("KC_NUMPAD8");
		mKeys[OIS::KC_NUMPAD9] = String("KC_NUMPAD9");
		mKeys[OIS::KC_SUBTRACT] = String("KC_SUBTRACT");
		mKeys[OIS::KC_NUMPAD4] = String("KC_NUMPAD4");
		mKeys[OIS::KC_NUMPAD5] = String("KC_NUMPAD5");
		mKeys[OIS::KC_NUMPAD6] = String("KC_NUMPAD6");
		mKeys[OIS::KC_ADD] = String("KC_ADD");
		mKeys[OIS::KC_NUMPAD1] = String("KC_NUMPAD1");
		mKeys[OIS::KC_NUMPAD2] = String("KC_NUMPAD2");
		mKeys[OIS::KC_NUMPAD3] = String("KC_NUMPAD3");
		mKeys[OIS::KC_NUMPAD0] = String("KC_NUMPAD0");
		mKeys[OIS::KC_DECIMAL] = String("KC_DECIMAL");
		mKeys[OIS::KC_OEM_102] = String("KC_OEM_102");
		mKeys[OIS::KC_F11] = String("KC_F11");
		mKeys[OIS::KC_F12] = String("KC_F12");
		mKeys[OIS::KC_F13] = String("KC_F13");
		mKeys[OIS::KC_F14] = String("KC_F14");
		mKeys[OIS::KC_F15] = String("KC_F15");
		mKeys[OIS::KC_KANA] = String("KC_KANA");
		mKeys[OIS::KC_ABNT_C1] = String("KC_ABNT_C1");
		mKeys[OIS::KC_CONVERT] = String("KC_CONVERT");
		mKeys[OIS::KC_NOCONVERT] = String("KC_NOCONVERT");
		mKeys[OIS::KC_YEN] = String("KC_YEN");
		mKeys[OIS::KC_ABNT_C2] = String("KC_ABNT_C2");
		mKeys[OIS::KC_NUMPADEQUALS] = String("KC_NUMPADEQUALS");
		mKeys[OIS::KC_PREVTRACK] = String("KC_PREVTRACK");
		mKeys[OIS::KC_AT] = String("KC_AT");
		mKeys[OIS::KC_COLON] = String("KC_COLON");
		mKeys[OIS::KC_UNDERLINE] = String("KC_UNDERLINE");
		mKeys[OIS::KC_KANJI] = String("KC_KANJI");
		mKeys[OIS::KC_STOP] = String("KC_STOP");
		mKeys[OIS::KC_AX] = String("KC_AX");
		mKeys[OIS::KC_UNLABELED ] = String("KC_UNLABELED");
		mKeys[OIS::KC_NEXTTRACK] = String("KC_NEXTTRACK");
		mKeys[OIS::KC_NUMPADENTER] = String("KC_NUMPADENTER");
		mKeys[OIS::KC_RCONTROL] = String("KC_RCONTROL");
		mKeys[OIS::KC_MUTE] = String("KC_MUTE");
		mKeys[OIS::KC_CALCULATOR] = String("KC_CALCULATOR");
		mKeys[OIS::KC_PLAYPAUSE] = String("KC_PLAYPAUSE");
		mKeys[OIS::KC_MEDIASTOP] = String("KC_MEDIASTOP");
		mKeys[OIS::KC_VOLUMEDOWN] = String("KC_VOLUMEDOWN");
		mKeys[OIS::KC_VOLUMEUP] = String("KC_VOLUMEUP");
		mKeys[OIS::KC_WEBHOME] = String("KC_WEBHOME");
		mKeys[OIS::KC_NUMPADCOMMA] = String("KC_NUMPADCOMMA");
		mKeys[OIS::KC_DIVIDE] = String("KC_DIVIDE");
		mKeys[OIS::KC_SYSRQ] = String("KC_SYSRQ");
		mKeys[OIS::KC_RMENU] = String("KC_RMENU");
		mKeys[OIS::KC_PAUSE] = String("KC_PAUSE");
		mKeys[OIS::KC_HOME] = String("KC_HOME");
		mKeys[OIS::KC_UP] = String("KC_UP");
		mKeys[OIS::KC_PGUP] = String("KC_PGUP");
		mKeys[OIS::KC_LEFT] = String("KC_LEFT");
		mKeys[OIS::KC_RIGHT] = String("KC_RIGHT");
		mKeys[OIS::KC_END] = String("KC_END");
		mKeys[OIS::KC_DOWN] = String("KC_DOWN");
		mKeys[OIS::KC_PGDOWN] = String("KC_PGDOWN");
		mKeys[OIS::KC_INSERT] = String("KC_INSERT");
		mKeys[OIS::KC_DELETE] = String("KC_DELETE");
		mKeys[OIS::KC_LWIN] = String("KC_LWIN");
		mKeys[OIS::KC_RWIN] = String("KC_RWIN");
		mKeys[OIS::KC_APPS] = String("KC_APPS");
		mKeys[OIS::KC_POWER] = String("KC_POWER");
		mKeys[OIS::KC_SLEEP] = String("KC_SLEEP");
		mKeys[OIS::KC_WAKE] = String("KC_WAKE");
		mKeys[OIS::KC_WEBSEARCH] = String("KC_WEBSEARCH");
		mKeys[OIS::KC_WEBFAVORITES] = String("KC_WEBFAVORITES");
		mKeys[OIS::KC_WEBREFRESH] = String("KC_WEBREFRESH");
		mKeys[OIS::KC_WEBSTOP] = String("KC_WEBSTOP");
		mKeys[OIS::KC_WEBFORWARD] = String("KC_WEBFORWARD");
		mKeys[OIS::KC_WEBBACK] = String("KC_WEBBACK");
		mKeys[OIS::KC_MYCOMPUTER] = String("KC_MYCOMPUTER");
		mKeys[OIS::KC_MAIL] = String("KC_MAIL");
		mKeys[OIS::KC_MEDIASELECT] = String("KC_MEDIASELECT");
	}
	//-----------------------------------------------------------------------
}
