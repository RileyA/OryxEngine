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

#include "GUIPanel.h"
#include "Oyster.h"
#include "OryxColor.h"

namespace Oryx
{
	Panel::Panel(GUIElement* parent, int layer)
		:GUIElement(parent, layer)
	{
		mRect = _getLayer(0)->createRectangle(0,0,100,100);
		setPosition(0.f,0.f);
		setScale(1.f,1.f);
		registerDrawable(mRect, 0);
	}
	//-----------------------------------------------------------------------
	
	Panel::~Panel()
	{

	}
	//-----------------------------------------------------------------------
	
	void Panel::_update()
	{
		GUIElement::_update();
		Vector2 posPix = getPositionPixels();
		Vector2 sclPix = getScalePixels();
		mRect->setPosition(posPix.x, posPix.y);
		mRect->setScale(sclPix.x, sclPix.y);
	}
	//-----------------------------------------------------------------------
	
	void Panel::setColor(Color c)
	{
		mRect->setColor(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
	}
	//-----------------------------------------------------------------------
	
	void Panel::setSolidColor()
	{
		mRect->setSolidColor();
	}
	//-----------------------------------------------------------------------
	
	void Panel::setSprite(String name)
	{
		mRect->setSprite(name);
	}
	//-----------------------------------------------------------------------
}
