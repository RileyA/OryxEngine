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
#include "GUIElement.h"
#include "Gorilla.h"
#include "GUIScreen.h"
#include "OryxLogger.h"
#include "OryxException.h"
#include "OryxStringUtils.h"
#include "OryxSignal.h"
#include "OryxSlot.h"
#include "OryxMessageAny.h"

namespace Oryx
{
	long long GUIElement::msAutoNameIndex=0;
	GUIElement::GUIElement(GUIElement* parent,String name,int layer)
		:mPosition(0,0),mScale(1,1),mParent(parent),mLayer(layer),mName(name),
			mHover(0),mClickedOver(0)
	{
		createSignal("clicked");
		createSignal("hovered");
		createSignal("unhovered");
		createSignal("released");

		mHover = false;

		if(mName==""||mName=="AUTO")
		{
			mName = "GUIElementAutoName"+StringUtils::toString(msAutoNameIndex);
			++msAutoNameIndex;
		}
		if(mParent)// inherit the parent's screen and layer
		{
			mParent->addChild(this);
			mScreen = mParent->getScreen();
			mLayer = mParent->getLayer()+layer;// relative layer
		}
		else
			throw Exception("Invalid GUI Parent!");
	}
	//-----------------------------------------------------------------------
	
	GUIElement::GUIElement(GUIScreen* screen,String name,int layer)
		:mPosition(0,0),mScale(1,1),mParent(0),mScreen(screen),mLayer(layer),mName(name)
	{
		createSignal("clicked");
		createSignal("hovered");
		createSignal("unhovered");
		createSignal("released");

		if(mScreen)
			mScreen->addElement(this,layer);
		else
			throw Exception("Invalid GUI Screen!");
	}
	//-----------------------------------------------------------------------

	GUIElement::~GUIElement()
	{
		for(unsigned int i=0;i<mElements.size();++i)
			delete mElements[i];
	}
	//-----------------------------------------------------------------------
	
	void GUIElement::update(Real delta)
	{
		for(uint i=0;i<mElements.size();++i)
			mElements[i]->update(delta);
	}
	//-----------------------------------------------------------------------
	
	void GUIElement::setPosition(Vector2 pos)
	{
		mPosition = pos;
		_refreshPosition();
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getPosition()
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getDerivedPosition()
	{
		if(mParent)
			return mPosition*mParent->getScale()+mParent->getDerivedPosition();
		return mPosition;
	}
	//-----------------------------------------------------------------------

	void GUIElement::_refreshPosition()
	{
		_setPos(getDerivedPosition()*Vector2(mScreen->getWidth(),mScreen->getHeight()));
		for(unsigned int i=0;i<mElements.size();++i)
			mElements[i]->_refreshPosition();// get the children to recalculate their positions
	}
	//-----------------------------------------------------------------------

	void GUIElement::setScale(Vector2 dim)
	{
		mScale = dim;
		_refreshScale();
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getScale()
	{
		return mScale;
	}
	//-----------------------------------------------------------------------
	
	Vector2 GUIElement::getDerivedScale()
	{
		if(mParent)
			return mScale*mParent->getDerivedScale();
		return mScale;
	}
	//-----------------------------------------------------------------------

	void GUIElement::_refreshScale()
	{
		_setScale(getDerivedScale()*Vector2(mScreen->getWidth(),mScreen->getHeight()));
		for(unsigned int i=0;i<mElements.size();++i)
			mElements[i]->_refreshScale();// get the children to recalculate their scales
	}
	//-----------------------------------------------------------------------

	void GUIElement::setAspectRatio(int w,int h,bool preserveHeight)
	{
		Real ratio = static_cast<float>(w)/h;
		Real curRatio = mScreen->getWidth()/mScreen->getHeight();// screen ratio

		if(preserveHeight)
		{
			Real oldX = mScale.x;
			mScale.x *= ratio/curRatio;
			mPosition.x += (oldX-mScale.x)/2;
		}
		else
		{
			Real oldY = mScale.y;
			mScale.y *= 1.f/(ratio/curRatio);
			mPosition.y += (oldY-mScale.y)/2;
		}
		_refreshPosition();
	}
	//-----------------------------------------------------------------------
	
	int GUIElement::getLayer()
	{
		return mLayer;
	}
	//-----------------------------------------------------------------------

	GUIScreen* GUIElement::getScreen()
	{
		return mScreen;
	}
	//-----------------------------------------------------------------------

	void GUIElement::addChild(GUIElement* elem)
	{
		mElements.push_back(elem);
	}
	//-----------------------------------------------------------------------
	
	void GUIElement::click(Vector2 coords,bool up)
	{
		coords-=getPosition();
		coords /= mScale;
		if(coords.x<1.f&&coords.x>0.f&&coords.y<1.f&&coords.y>0.f)
		{
			if(!up)
				mClickedOver = true;
			else if(mClickedOver)
			{
				_clicked();
				mClickedOver = false;
			}
			for(unsigned int i=0;i<mElements.size();++i)
				mElements[i]->click(coords,up);// notify children
		}
		else if(up)
		{
			release();
		}
	}
	//-----------------------------------------------------------------------

	void GUIElement::release()
	{
		mClickedOver = false;
		for(int i=0;i<mElements.size();++i)
			mElements[i]->release();
	}

	void GUIElement::hover(Vector2 coord)
	{
		Vector2 coords = coord;
		coords-=getPosition();
		coords /= mScale;
		if(coords.x<1.f&&coords.x>0.f&&coords.y<1.f&&coords.y>0.f)
		{
			if(!mHover)
			{
				mHover = true;
				_hovered(true);
			}

			for(unsigned int i=0;i<mElements.size();++i)
				mElements[i]->hover(coords);// notify children
		}
		else if(mHover)
		{
			unhover();
		}
	}
	
	void GUIElement::unhover()
	{
		if(mHover)
		{
			_hovered(false);
		}
		mHover = false;
		for(unsigned int i=0;i<mElements.size();++i)
			mElements[i]->unhover();// notify children
	}
	//-----------------------------------------------------------------------
	
	void GUIElement::_hovered(bool on)
	{
		if(on)
			getSignal("hovered")->fire(0);
		else
			getSignal("unhovered")->fire(0);
	}
	//-----------------------------------------------------------------------
	void GUIElement::_clicked()
	{
		getSignal("clicked")->fire(0);
	}
}
