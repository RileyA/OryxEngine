//-----------------------------------------------------------------------
// Copyright Riley Adams 2010

// This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#include "Oryx.h"
#include "Gorilla.h"
#include "Ogre.h"
#include "GUI.h"
#include "OryxLogger.h"

namespace Oryx
{
	GUI::GUI()
	{
		mGUI = new Gorilla::Silverback();
	}
	//-----------------------------------------------------------------------

	GUI::~GUI()
	{
		std::map<String,GUIScreen*>::iterator i = mScreens.begin();
		for(i;i!=mScreens.end();++i)
		{
			Gorilla::Screen* temp = i->second->getScreen();
			delete i->second;
			mGUI->destroyScreen(temp);
		}
		mScreens.clear();
		delete mGUI;
	}
	//-----------------------------------------------------------------------

	GUIScreen* GUI::createScreen(Ogre::Viewport* vp,String atlas,String name)
	{
		mGUI->loadAtlas(atlas);
		mScreens[name] = new GUIScreen(mGUI->createScreen(vp,atlas),name);
		return mScreens[name];
	}
	//-----------------------------------------------------------------------

	GUIScreen* GUI::getScreen(String name)
	{
		if(mScreens.find(name)!=mScreens.end())
			return mScreens[name];
		return 0;
	}
	//-----------------------------------------------------------------------

	void GUI::destroyScreen(String name)
	{
		if(mScreens.find(name)!=mScreens.end())
		{
			mGUI->destroyScreen(mScreens[name]->getScreen());
			delete mScreens[name];
			mScreens.erase(mScreens.find(name));
		}
	}
	//-----------------------------------------------------------------------

	void GUI::destroyScreen(GUIScreen* screen)
	{
		std::map<String,GUIScreen*>::iterator i = mScreens.begin();
		for(i;i!=mScreens.end();++i)
		{
			if(i->second==screen)
			{
				mGUI->destroyScreen(i->second->getScreen());
				delete i->second;
				mScreens.erase(i);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void GUI::update(Real delta)
	{
		std::map<String,GUIScreen*>::iterator it = mScreens.begin();
		while(it!=mScreens.end())
			it->second->update(delta);
	}
}
