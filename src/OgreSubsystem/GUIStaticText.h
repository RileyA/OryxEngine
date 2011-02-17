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

#ifndef ORYX_GUISTATICTEXT_H
#define ORYX_GUISTATICTEXT_H

#include "Oryx.h"
#include "Ogredllmain.h"
#include "GUIElement.h"
#include "OryxColour.h"

namespace Gorilla
{
	class Silverback;
	class Layer;
	class Screen;
	class Caption;
}

namespace Oryx
{
	// very simple for the time being, a more robust solution to come later...
	class ORYX_OGRE_EXPORT StaticText : public GUIElement
	{
	public:

		StaticText(GUIElement* parent,String name,int layer=0,int text=24,Vector2 pos=Vector2(0,0),Vector2 dimensions=Vector2(0,0),String caption="");
		virtual ~StaticText();

		void setCaption(String cap);
		String getCaption();

		void setColour(Colour colour);
		Colour getColour();

		void setBackgroundColor(Colour colour);
		Colour getBackgroundColour();

		void setAlign(GUI_Align align);
		GUI_Align getAlign();

	protected:

		virtual void _setPos(Vector2 pos);
		virtual void _setScale(Vector2 dims);

		Gorilla::Caption* mCaption;

	};
}

#endif
