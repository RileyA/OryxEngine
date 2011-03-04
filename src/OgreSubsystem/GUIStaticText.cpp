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
#include "GUIStaticText.h"
#include "Gorilla.h"
#include "OgreConversions.h"
#include "GUIScreen.h"

namespace Oryx
{
	StaticText::StaticText(GUIElement* parent,String name,int layer,int text,Vector2 pos,Vector2 dimensions,String caption)
		:GUIElement(parent,name,layer)
	{
		mCaption = mScreen->getLayer(parent->getLayer())->createCaption(text,pos.x,pos.y,caption);
		setPosition(pos);
		setScale(dimensions);
	}
	//-----------------------------------------------------------------------

	StaticText::~StaticText()
	{
		mScreen->getLayer(mLayer)->destroyCaption(mCaption);
	}
	//-----------------------------------------------------------------------

	void StaticText::setCaption(String cap)
	{
		mCaption->text(cap);
	}
	//-----------------------------------------------------------------------

	String StaticText::getCaption()
	{
		return mCaption->text();
	}
	//-----------------------------------------------------------------------

	void StaticText::_setPos(Vector2 pos)
	{
		mCaption->left(pos.x);
		mCaption->top(pos.y);
	}
	//-----------------------------------------------------------------------

	void StaticText::_setScale(Vector2 dims)
	{
		mCaption->width(dims.x);
		mCaption->height(dims.y);
	}
	//-----------------------------------------------------------------------

	void StaticText::setColour(Colour colour)
	{
		mCaption->colour(convertOgre(colour));
	}
	//-----------------------------------------------------------------------

	Colour StaticText::getColour()
	{
		return convertOgre(mCaption->colour());
	}
	//-----------------------------------------------------------------------

	void StaticText::setBackgroundColor(Colour colour)
	{
		mCaption->background(convertOgre(colour));
	}
	//-----------------------------------------------------------------------

	Colour StaticText::getBackgroundColour()
	{
		return convertOgre(mCaption->background());
	}
	//-----------------------------------------------------------------------

	void StaticText::setAlign(GUI_Align align)
	{
		// horizontal only for now...
		switch(align)
		{
		case GA_CENTER:
			mCaption->align(Gorilla::TextAlign_Centre);
			break;
		case GA_LEFT:
			mCaption->align(Gorilla::TextAlign_Left);
			break;
		case GA_RIGHT:
			mCaption->align(Gorilla::TextAlign_Right);
			break;
		}
	}
	//-----------------------------------------------------------------------

	GUI_Align StaticText::getAlign()
	{
		Gorilla::TextAlignment align = mCaption->align();
		switch(align)
		{
			case Gorilla::TextAlign_Centre:
				return GA_CENTER;
			case Gorilla::TextAlign_Left:
				return GA_LEFT;
			case Gorilla::TextAlign_Right:
				return GA_RIGHT;
		}
		return GA_LEFT;// default for now...
	}
	//-----------------------------------------------------------------------
}
