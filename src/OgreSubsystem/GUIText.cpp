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
#include "GUIText.h"
#include "Gorilla.h"
#include "OgreConversions.h"
#include "GUIScreen.h"

namespace Oryx
{
	Text::Text(GUIElement* parent,String name,int layer,int text,Vector2 pos,Vector2 dimensions,String caption)
		:GUIElement(parent,name,layer)
	{
		mText = mScreen->getLayer(layer)->createMarkupText(text,pos.x,pos.y,caption);
		setPosition(pos);
		setScale(dimensions);
	}
	//-----------------------------------------------------------------------

	Text::~Text()
	{
		mScreen->getLayer(mLayer)->destroyMarkupText(mText);
	}
	//-----------------------------------------------------------------------

	void Text::setText(String cap)
	{
		mText->text(cap);
	}
	//-----------------------------------------------------------------------

	String Text::getText()
	{
		return mText->text();
	}
	//-----------------------------------------------------------------------

	void Text::addText(String text)
	{
		return mText->text(mText->text()+text);
	}
	//-----------------------------------------------------------------------

	void Text::backspace(int count)
	{
		return mText->text(mText->text().substr(0,mText->text().length()-count));
	}
	//-----------------------------------------------------------------------

	void Text::_setPos(Vector2 pos)
	{
		mText->left(pos.x);
		mText->top(pos.y);
	}
	//-----------------------------------------------------------------------

	void Text::_setScale(Vector2 dims)
	{
		mText->width(dims.x);
		mText->height(dims.y);
	}
	//-----------------------------------------------------------------------
}
