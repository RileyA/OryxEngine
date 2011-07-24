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

#include "GUIElement.h"
#include "GUIBatch.h"
#include "Oyster.h"
#include "OysterDrawable.h"

namespace Oryx
{
	GUIElement::GUIElement(GUIElement* parent, int layer)
		:mPosition(Vector2(0,0)),mScale(Vector2(1,1)),mLayer(layer),mAlignment(
			VA_TOP | HA_LEFT)
	{
		mParent = parent;

		//createSlot("mouseReleased", this, &GUIElement::_releasedMouse);
		//createSlot("mouseMoved", this, &GUIElement::_movedMouse);
		createSignal("pressed");
		createSignal("released");
		createSignal("clicked");
		createSignal("hover_enter");
		createSignal("hover_exit");

		if(mParent)
		{
			mParent->addChild(this);
			mAbsLayer = mParent->getAbsoluteLayer();
			mBatch = mParent->getBatch();
		}
		else
		{
			mBatch = 0;
			mAbsLayer = 0;
		}
	}
	//-----------------------------------------------------------------------

	GUIElement::~GUIElement()
	{
		for(std::list<GUIElement*>::iterator it = mChildren.begin(); 
			it != mChildren.end(); ++it)
			delete *it;
		int l = mAbsLayer;
		for(int i = 0; i < mDrawables.size(); ++i)
		{
			std::pair<Oyster::Drawable*,int>& p = mDrawables[i];
			_getLayer(l + p.second)->removeDrawable(p.first, true);
		}
	}
	//-----------------------------------------------------------------------

	void GUIElement::setPosition(Vector2 pos)
	{
		mPosition = pos;
		_update();
	}
	//-----------------------------------------------------------------------

	void GUIElement::setPosition(Real x, Real y)
	{
		setPosition(Vector2(x,y));
	}
	//-----------------------------------------------------------------------

	void GUIElement::setPositionPx(int x, int y)
	{
		Vector2 ascale = mParent->getAbsoluteScale();
		setPosition(Vector2(x / static_cast<Real>(mBatch->getWidth()),
			y / static_cast<Real>(mBatch->getHeight())));
	}
	//-----------------------------------------------------------------------

	void GUIElement::setScale(Vector2 scale)
	{
		mScale = scale;
		_update();
	}
	//-----------------------------------------------------------------------

	void GUIElement::setScale(Real x, Real y)
	{
		setScale(Vector2(x,y));
	}
	//-----------------------------------------------------------------------

	void GUIElement::setScalePx(int x, int y)
	{
		setScale(Vector2(x / static_cast<Real>(mBatch->getWidth()),
			y / static_cast<Real>(mBatch->getHeight())));
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getPosition()
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getAbsolutePosition()
	{
		return (mPosition + mAlignOffset) * mParent->getScale() + mParent->getAbsolutePosition();
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getPositionPixels()
	{
		Vector2 apos = getAbsolutePosition();
		return Vector2(apos.x * mBatch->getWidth(), apos.y * mBatch->getHeight());
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getScale()
	{
		return mScale;
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getAbsoluteScale()
	{
		return mScale;
	}
	//-----------------------------------------------------------------------

	Vector2 GUIElement::getScalePixels()
	{ 
		Vector2 ascale = getAbsoluteScale();
		return Vector2(ascale.x * mBatch->getWidth(), ascale.y * mBatch->getHeight());
	}
	//-----------------------------------------------------------------------

	void GUIElement::setVerticalAlign(VerticalAlign v)
	{	
		setAlign(v, getHorizontalAlign());
	}
	//-----------------------------------------------------------------------

	void GUIElement::setHorizontalAlign(HorizontalAlign h)
	{
		setAlign(getVerticalAlign(), h);
	}
	//-----------------------------------------------------------------------

	void GUIElement::setAlign(Align a)
	{
		mAlignment = a;

		mAlignOffset = Vector2(0.f,0.f);

		// vertical
		if(mAlignment & VA_CENTER)
			mAlignOffset.y = (1.f - mScale.y) / 2;
		else if(mAlignment & VA_BOTTOM)
			mAlignOffset.y = (1.f - mScale.y);

		// horizontal
		if(mAlignment & HA_CENTER)
			mAlignOffset.x = (1.f - mScale.x) / 2;
		else if(mAlignment & HA_RIGHT)
			mAlignOffset.x = (1.f - mScale.x);

		_update();
	}
	//-----------------------------------------------------------------------

	void GUIElement::setAlign(VerticalAlign v, HorizontalAlign h)
	{
		setAlign(static_cast<Align>(v | h));
	}
	//-----------------------------------------------------------------------

	Align GUIElement::getAlign()
	{
		return static_cast<Align>(mAlignment);
	}
	//-----------------------------------------------------------------------

	VerticalAlign GUIElement::getVerticalAlign()
	{
		return static_cast<VerticalAlign>(mAlignment & (VA_TOP | VA_BOTTOM | VA_CENTER));
	}
	//-----------------------------------------------------------------------

	HorizontalAlign GUIElement::getHorizontalAlign()
	{
		return static_cast<HorizontalAlign>(mAlignment & (HA_LEFT | HA_RIGHT | HA_CENTER));
	}
	//-----------------------------------------------------------------------

	void GUIElement::setLayer(int layer)
	{
		int l = getAbsoluteLayer();
		int move = layer - mLayer;
		if(layer !=  mLayer)
		{
			for(int i = 0; i < mDrawables.size(); ++i)
			{
				std::pair<Oyster::Drawable*,int>& p = mDrawables[i];
				// swap layers
				_getLayer(l + p.second)->removeDrawable(p.first, false);
				_getLayer(l + p.second + move)->addDrawable(p.first);
			}
			layer = mLayer;
		}
		mAbsLayer = l;
	}
	//-----------------------------------------------------------------------

	void GUIElement::addChild(GUIElement* element)
	{
		mChildren.push_back(element);
	}
	//-----------------------------------------------------------------------

	void GUIElement::destroyChild(GUIElement* element)
	{
		for(std::list<GUIElement*>::iterator it = mChildren.begin();
			it != mChildren.end(); ++it)
		{
			delete *it;
			mChildren.erase(it);
			return;
		}
	}
	//-----------------------------------------------------------------------

	GUIElement* GUIElement::removeChild(GUIElement* element)
	{
		for(std::list<GUIElement*>::iterator it = mChildren.begin();
			it != mChildren.end(); ++it)
		{
			GUIElement* temp = *it;
			mChildren.erase(it);
			return temp;
		}
		return 0;
	}
	//-----------------------------------------------------------------------

	/*bool GUIElement::_click(Vector2 pos)
	{
		Vector2 pxp = mPosition;
		Vector2 sxp = mScale;

		if(pos.x >= pxp.x && pos.x <= pxp.x + sxp.x &&
			pos.y >= pxp.y && pos.y <= pxp.y + sxp.y)
		{
			for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
				it != mChildren.rend(); ++it)
			{
				if((*it)->_click((pos - pxp) * sxp))
					return true;
			}

			getSignal("pressed")->fire(MessageAny<int>(5));
			pressed();
			getSlot("mouseReleased")->listenTo(mBatch->getSignal("clickUp"));

			return true;
		}
	}
	//-----------------------------------------------------------------------

	bool GUIElement::_hover(Vector2 pos)
	{
		Vector2 pxp = mPosition;
		Vector2 sxp = mScale;

		if(pos.x >= pxp.x && pos.x <= pxp.x + sxp.x &&
			pos.y >= pxp.y && pos.y <= pxp.y + sxp.y)
		{
			//for(std::list<GUIElement*>::iterator it = mChildren.begin();
			//	it != mChildren.end(); ++it)
			for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
				it != mChildren.rend(); ++it)
			{
				if((*it)!=mBatch->getCursor() && (*it)->_hover((pos - pxp) * sxp))
					return true;
			}

			if(getType() != "Batch")
			{
				if(!mHovered)
				{
					hovered();
					getSignal("hover_enter")->fire(MessageAny<int>(5));
				}
				mHovered = true;
				getSlot("mouseMoved")->listenTo(mBatch->getSignal("mouseMoved"));
			}

			return true;
		}
	}*/
	//-----------------------------------------------------------------------

	GUIElement* GUIElement::_search(Vector2 pos)
	{
		Vector2 pxp = mPosition + mAlignOffset;
		Vector2 sxp = mScale;

		if(pos.x >= pxp.x && pos.x <= pxp.x + sxp.x &&
			pos.y >= pxp.y && pos.y <= pxp.y + sxp.y)
		{
			for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
				it != mChildren.rend(); ++it)
			{
				if(GUIElement* g = (*it)->_search((pos - pxp) * sxp))
					return g;
			}
			
			return this;
		}

		return 0;
	}
	//-----------------------------------------------------------------------

	void GUIElement::pressed()
	{

	}
	//-----------------------------------------------------------------------

	void GUIElement::released()
	{

	}
	//-----------------------------------------------------------------------

	void GUIElement::clicked()
	{

	}
	//-----------------------------------------------------------------------

	void GUIElement::hovered()
	{
	
	}
	//-----------------------------------------------------------------------

	void GUIElement::unHovered()
	{

	}
	//-----------------------------------------------------------------------

	/*void GUIElement::_releasedMouse(const Message& m)
	{
		Vector2 p = static_cast<const MessageAny<Vector2>&>(m).data;
		Vector2 pxp = getPositionPixels();
		Vector2 sxp = getScalePixels();
		if(p.x >= pxp.x && p.x <= pxp.x + sxp.x &&
			p.y >= pxp.y && p.y <= pxp.y + sxp.y)
		{
			getSignal("clicked")->fire(MessageAny<int>(5));
			clicked();
		}
		else
		{
			getSignal("released")->fire(MessageAny<int>(5));
			released();
		}
	}
	//-----------------------------------------------------------------------

	void GUIElement::_movedMouse(const Message& m)
	{
		if(!mHovered)
			return;
		Vector2 p = static_cast<const MessageAny<Vector2>&>(m).data;
		Vector2 pxp = getPositionPixels();
		Vector2 sxp = getScalePixels();
		if(p.x >= pxp.x && p.x <= pxp.x + sxp.x &&
			p.y >= pxp.y && p.y <= pxp.y + sxp.y)
		{
			// still hoverin', carry on...
		}
		else
		{
			mHovered = false;
			unHovered();
			getSignal("hover_exit")->fire(MessageAny<int>(5));
		}
	}*/
	//-----------------------------------------------------------------------

	void GUIElement::_update()
	{
		for(std::list<GUIElement*>::iterator it = mChildren.begin();
			it != mChildren.end(); ++it)
		{
			(*it)->_update();
		}
	}
	//-----------------------------------------------------------------------

	Oyster::Layer* GUIElement::_getLayer(int offset)
	{
		return mBatch->getLayer(getAbsoluteLayer()+offset);
	}
	//-----------------------------------------------------------------------
}
