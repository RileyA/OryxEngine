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
#include "OryxLogger.h"
#include "GUIEmpty.h"
#include "Gorilla.h"
#include "OgreConversions.h"
#include "GUIScreen.h"

namespace Oryx
{
	GUIEmpty::GUIEmpty(GUIElement* parent,String name,int layer,Vector2 pos,Vector2 dimensions)
		:GUIElement(parent,name,layer)
	{
		setPosition(pos);
		setScale(dimensions);
	}

	GUIEmpty::GUIEmpty(GUIScreen* screen,String name,int layer,Vector2 pos,Vector2 dimensions)
		:GUIElement(screen,name,layer)
	{
		setPosition(pos);
		setScale(dimensions);
	}
	//-----------------------------------------------------------------------

	GUIEmpty::~GUIEmpty()
	{

	}
	//-----------------------------------------------------------------------

	void GUIEmpty::_setPos(Vector2 pos){}
	void GUIEmpty::_setScale(Vector2 dims){}
	//-----------------------------------------------------------------------
}
