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
#include "GUIElement.h"
#include "GUIRectangle.h"

namespace Oryx
{
	// A simple button, based on the gui rectangle
	class ORYX_OGRE_EXPORT GUIButton : public GUIRectangle
	{
	public:

		GUIButton(GUIElement* parent,int layer,String sprite);
		virtual ~GUIButton();

		void setUpSprite(String sprite);
		void setDownSprite(String sprite);
		void setHoverSprite(String sprite);

		String getUpSprite();
		String getDownSprite();
		String getHoverSprite();

	protected:

		virtual void _clicked();

	private:

		String mUp;
		String mDown;
		String mHover;
		bool mClicked;// if the mouse was clicked over this (and not yet released)
	};
}
