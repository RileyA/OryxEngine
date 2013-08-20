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

#ifndef ORYX_GUI_BUTTON
#define ORYX_GUI_BUTTON

#include "GUIPanel.h"

namespace Oryx
{
	class ORYX_GUI_EXPORT Button : public Panel
	{
	protected:

		// a set of info about appearance during a state (mouseover, etc)
		struct StateAppearance
		{
			Color rectColor;
			Color textColor;
			String sprite;
		};

	public:

		Button(GUIElement* parent, int layer = 0);
		virtual ~Button();

		/** Gets the name of the type of element */
		virtual String getType(){return "Button";}

		void setDefaultAppearance(Color rect, Color text, String sprite = "WhitePixel");
		void setMouseOverAppearance(Color rect, Color text, String sprite = "WhitePixel");
		void setClickAppearance(Color rect, Color text, String sprite = "WhitePixel");

		void setAppearance(StateAppearance& appear);
		void chooseAppearance();

		virtual void clicked();
		virtual void pressed();
		virtual void released();
		virtual void hovered();
		virtual void unHovered();

		virtual void _update();

		void setCaption(String caption);
		String getCaption();

	protected:

		StateAppearance mDefault;
		StateAppearance mClick;
		StateAppearance mHover;
		StateAppearance* mCurrent;

		Oyster::Text* mText;
		String mCaption;

		bool mPressed;
		bool mOver;

	};
}


#endif
