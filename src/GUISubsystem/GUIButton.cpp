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

#include "GUIButton.h"
#include "Oyster.h"
#include "OysterLayer.h"

namespace Oryx
{
	Button::Button(GUIElement* parent, int layer)
		:Panel(parent, layer),mCurrent(0)
	{
		mText = _getLayer(layer + 1)->createText("[BUTTON]",0,0,100,100);
		mText->setAlign(static_cast<Oyster::VerticalAlign>(VA_CENTER));
		mText->setAlign(static_cast<Oyster::HorizontalAlign>(HA_CENTER));
		mPressed = false;
		mOver = false;
		setDefaultAppearance(Color(1.f,1.f,1.f,1.f), Color(0.f,0.f,0.f,1.f));
		setMouseOverAppearance(Color(1.f,1.f,1.f,1.f), Color(0.f,0.f,0.f,1.f));
		setClickAppearance(Color(1.f,1.f,1.f,1.f), Color(0.f,0.f,0.f,1.f));
		setAppearance(mDefault);
	}
	//-----------------------------------------------------------------------

	Button::~Button()
	{

	}
	//-----------------------------------------------------------------------

	void Button::setDefaultAppearance(Color rect, Color text, String sprite)
	{
		mDefault.rectColor = rect;
		mDefault.textColor = text;
		mDefault.sprite = sprite;
		mCurrent = 0;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::setMouseOverAppearance(Color rect, Color text, String sprite)
	{
		mHover.rectColor = rect;
		mHover.textColor = text;
		mHover.sprite = sprite;
		mCurrent = 0;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::setClickAppearance(Color rect, Color text, String sprite)
	{
		mClick.rectColor = rect;
		mClick.textColor = text;
		mClick.sprite = sprite;
		mCurrent = 0;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::setAppearance(Button::StateAppearance& appear)
	{
		if(&appear == mCurrent)
			return;
		mCurrent = &appear;

		setColor(appear.rectColor);
		mText->setColor(appear.textColor.r * 255, appear.textColor.g * 255, 
			appear.textColor.b * 255, appear.textColor.a * 255);
		if(appear.sprite == "WhitePixel") 
			setSolidColor();
		else
			setSprite(appear.sprite);
	}
	//-----------------------------------------------------------------------

	void Button::chooseAppearance()
	{
		if(mPressed)
			setAppearance(mClick);
		else
			setAppearance(mOver ? mHover : mDefault);
	}
	//-----------------------------------------------------------------------

	void Button::clicked()
	{
		mPressed = false;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::pressed()
	{
		mPressed = true;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::released()
	{
		mPressed = false;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::hovered()
	{
		mOver = true;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::unHovered()
	{
		mOver = false;
		chooseAppearance();
	}
	//-----------------------------------------------------------------------

	void Button::_update()
	{
		Panel::_update();
		Vector2 posPix = getPositionPixels();
		Vector2 sclPix = getScalePixels();
		mText->setPosition(posPix.x, posPix.y);
		mText->setScale(sclPix.x, sclPix.y);
	}
	//-----------------------------------------------------------------------

	void Button::setCaption(String caption)
	{
		mCaption = caption;
		mText->setCaption(mCaption);
	}
	//-----------------------------------------------------------------------

	String Button::getCaption()
	{
		return mCaption;
	}
	//-----------------------------------------------------------------------
}
