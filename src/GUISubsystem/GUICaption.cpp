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

#include "GUICaption.h"
#include "Oyster.h"
#include "OryxColour.h"

namespace Oryx
{
	Caption::Caption(GUIElement* parent, int layer)
		:GUIElement(parent, layer),mTextAlign(HA_LEFT | VA_TOP)
	{
		mText = _getLayer(0)->createText("[N/A]",0,0,100,100);
		setPosition(0.f,0.f);
		setScale(1.f,1.f);
		registerDrawable(mText, 0);
	}
	//-----------------------------------------------------------------------
	
	Caption::~Caption()
	{

	}
	//-----------------------------------------------------------------------
	
	void Caption::_update()
	{
		GUIElement::_update();
		Vector2 posPix = getPositionPixels();
		Vector2 sclPix = getScalePixels();
		mText->setPosition(posPix.x, posPix.y);
		mText->setScale(sclPix.x, sclPix.y);
	}
	//-----------------------------------------------------------------------
	
	void Caption::setColor(Colour c)
	{
		mText->setColor(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
	}
	//-----------------------------------------------------------------------
	
	void Caption::setCaption(String caption)
	{
		mCaption = caption;
		mText->setCaption(mCaption);
	}
	//-----------------------------------------------------------------------
	
	void Caption::setTextAlign(Align a)
	{
		mTextAlign = a;
		mText->setAlign(static_cast<Oyster::HorizontalAlign>(getTextHorizontalAlign()));
		mText->setAlign(static_cast<Oyster::VerticalAlign>(getTextVerticalAlign()));
	}
	//-----------------------------------------------------------------------
	
	void Caption::setTextAlign(VerticalAlign v, HorizontalAlign h)
	{
		setTextAlign(static_cast<Align>(v | h));
	}
	//-----------------------------------------------------------------------
	
	void Caption::setTextVerticalAlign(VerticalAlign v)
	{
		setTextAlign(v, getTextHorizontalAlign());
	}
	//-----------------------------------------------------------------------
	
	void Caption::setTextHorizontalAlign(HorizontalAlign h)
	{
		setTextAlign(getTextVerticalAlign(), h);
	}
	//-----------------------------------------------------------------------

	Align Caption::getTextAlign()
	{
		return static_cast<Align>(mTextAlign);
	}
	//-----------------------------------------------------------------------
	
	HorizontalAlign Caption::getTextHorizontalAlign()
	{
		return static_cast<HorizontalAlign>(mTextAlign & (HA_LEFT|HA_RIGHT|HA_CENTER));
	}
	//-----------------------------------------------------------------------
	
	VerticalAlign Caption::getTextVerticalAlign()
	{
		return static_cast<VerticalAlign>(mTextAlign & (VA_TOP|VA_BOTTOM|VA_CENTER));
	}
	//-----------------------------------------------------------------------
}
