//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the license, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTEE; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have recieved a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "GUIButton.h"

namespace Oryx
{
	GUIButton::GUIButton(GUIElement* parent,int layer,String sprite)
		:GUIRectangle(parent,sprite,"nombre",layer)
	{
		createSignal("buttonClicked");
		createSignal("buttonHovered");
	}
	
	GUIButton::~GUIButton()
	{
		// not much to do here just yet..
	}
	//-----------------------------------------------------------------------
	
	void GUIButton::_clicked()
	{
		mClicked = true;
		std::cout<<"clicked a button!\n";
	}
	//-----------------------------------------------------------------------
	
	void GUIButton::setUpSprite(String sprite)
	{
		mUp = sprite;
	}
	//-----------------------------------------------------------------------
	
	void GUIButton::setDownSprite(String sprite)
	{
		mDown = sprite;
	}
	//-----------------------------------------------------------------------
	
	void GUIButton::setHoverSprite(String sprite)
	{
		mHover = sprite;
	}
	//-----------------------------------------------------------------------
	
	String GUIButton::getUpSprite()
	{
		return mUp;
	}
	//-----------------------------------------------------------------------
	
	String GUIButton::getDownSprite()
	{
		return mDown;
	}
	//-----------------------------------------------------------------------
	
	String GUIButton::getHoverSprite()
	{
		return mHover;
	}
	//-----------------------------------------------------------------------
}
