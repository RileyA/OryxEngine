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
#include "GUIScreen.h"
#include "Gorilla.h"
#include "OryxLogger.h"
#include "OryxStringUtils.h"
#include "OryxMessageAny.h"
#include "OryxSlot.h"
#include "FastDelegate.h"

namespace Oryx
{
	GUIScreen::GUIScreen(Gorilla::Screen* screen,String name)
		:mScreen(screen),mName(name),mCursor(0)
	{
		createSlot("moveCursor",this,&GUIScreen::moveCursor);
		createSlot("click",this,&GUIScreen::click);
		createSlot("release",this,&GUIScreen::release);
		for(int i=0;i<16;++i)
		{
			mLayers[i] = screen->createLayer(i);
			mRootElements[i] = new GUIEmpty(this,"Layer "+StringUtils::toString(i)+" Root Element",i);
		}
	}
	//-----------------------------------------------------------------------

	GUIScreen::~GUIScreen()
	{
		for(int i=0;i<16;++i)
			delete mRootElements[i];
	}
	//-----------------------------------------------------------------------

	Gorilla::Screen* GUIScreen::getScreen()
	{
		return mScreen;
	}
	//-----------------------------------------------------------------------

	Gorilla::Layer* GUIScreen::getLayer(int index)
	{
		if(index>=0&&index<16)
			return mLayers[index];
		return 0;
	}
	//-----------------------------------------------------------------------

	void GUIScreen::setVisible(bool visible)
	{
		mScreen->setVisible(visible);
	}
	//-----------------------------------------------------------------------

	bool GUIScreen::isVisible()
	{
		return mScreen->isVisible();
	}
	//-----------------------------------------------------------------------

	void GUIScreen::update(Real delta)
	{
		for(int i=0;i<16;++i)
			mRootElements[i]->update(delta);
	}
	//-----------------------------------------------------------------------

	GUIElement* GUIScreen::getRootElement(int layer)
	{
		return mRootElements[layer];
	}
	//-----------------------------------------------------------------------

	void GUIScreen::addElement(GUIElement* elem,int layer)
	{
		if(layer>=0&&layer<16)
			mElements[layer].push_back(elem);
		else
			Logger::getPtr()->logMessage("Invalid GUI layer! Element not registered.");
	}
	//-----------------------------------------------------------------------

	Real GUIScreen::getWidth()
	{
		return mScreen->getWidth();
	}
	//-----------------------------------------------------------------------
	
	Real GUIScreen::getHeight()
	{
		return mScreen->getHeight();
	}
	//-----------------------------------------------------------------------
	
	void GUIScreen::setCursor(GUIElement* cursor)
	{
		mCursor = cursor;
	}
	//-----------------------------------------------------------------------
	
	GUIElement* GUIScreen::getCursor()
	{
		return mCursor;
	}
	//-----------------------------------------------------------------------
	
	void GUIScreen::moveCursor(const Message& m)
	{
		if(!mCursor)
			return;
		if(const MessageAny<Vector2>* ms = message_cast<Vector2>(m))
		{
			mCursor->setPosition(ms->data/Vector2(getWidth(),getHeight()));
			for(uint i=0;i<16;++i)
				mRootElements[i]->hover(mCursor->getDerivedPosition());
		}
	}
	//-----------------------------------------------------------------------
	
	void GUIScreen::click(const Message& m)
	{
		if(!mCursor)
			return;
		for(uint i=0;i<16;++i)
			mRootElements[i]->click(mCursor->getDerivedPosition(),true);
	}
	//-----------------------------------------------------------------------
	
	void GUIScreen::release(const Message& m)
	{
		if(!mCursor)
			return;
		for(uint i=0;i<16;++i)
			mRootElements[i]->click(mCursor->getDerivedPosition(),false);
	}
}
