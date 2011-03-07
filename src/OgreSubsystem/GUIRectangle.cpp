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
#include "GUIRectangle.h"
#include "Gorilla.h"
#include "OgreConversions.h"
#include "OryxLogger.h"
#include "GUIScreen.h"

namespace Oryx
{
	GUIRectangle::GUIRectangle(GUIElement* parent,String sprite,String name,int layer,Vector2 pos,Vector2 dimensions)
		:GUIElement(parent,name,layer)
	{
		mRectangle = mScreen->getLayer(mLayer)->createRectangle(pos.x,pos.y,dimensions.x,dimensions.y);
		mRectangle->background_image(sprite);
		setPosition(pos);
		setScale(dimensions);
	}
	//-----------------------------------------------------------------------

	GUIRectangle::GUIRectangle(GUIElement* parent,String name,Colour background,Colour border,Real borderWidth,int layer,Vector2 pos,Vector2 dimensions)
		:GUIElement(parent,name,layer)
	{
		mRectangle = mScreen->getLayer(mLayer)->createRectangle(pos.x,pos.y,dimensions.x,dimensions.y);
		mRectangle->background_colour(convertOgre(background));
		mRectangle->border_colour(convertOgre(border));
		mRectangle->border_width(borderWidth);
		setPosition(pos);
		setScale(dimensions);
	}
	//-----------------------------------------------------------------------
	
	GUIRectangle::~GUIRectangle()
	{
		mScreen->getLayer(mLayer)->destroyRectangle(mRectangle);
	}
	//-----------------------------------------------------------------------

	void GUIRectangle::_setPos(Vector2 pos)
	{
		mRectangle->left(pos.x);
		mRectangle->top(pos.y);
	}
	//-----------------------------------------------------------------------

	void GUIRectangle::_setScale(Vector2 dims)
	{
		mRectangle->width(dims.x);
		mRectangle->height(dims.y);
	}
	//-----------------------------------------------------------------------
	
	void GUIRectangle::setSprite(String sprite)
	{
		mRectangle->background_image(sprite);
	}
}
