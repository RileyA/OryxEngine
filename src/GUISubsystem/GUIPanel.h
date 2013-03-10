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

#ifndef ORYX_GUI_PANEL
#define ORYX_GUI_PANEL

#include "Oryx.h"
#include "OryxColour.h"
#include "OryxEventHandler.h"
#include "GUIdllmain.h"
#include "GUIElement.h"

namespace Oryx
{
	class ORYX_GUI_EXPORT Panel : public GUIElement
	{
	public:

		Panel(GUIElement* parent, int layer = 0);

		virtual ~Panel();

		/** internal: updates position/scaling */
		virtual void _update();

		/** Gets the name of the type of element */
		virtual String getType(){return "Panel";}

		void setColor(Colour c);
		void setSolidColor();
		void setSprite(String name);

	protected:

		Oyster::Rectangle* mRect;	

	};
}


#endif
