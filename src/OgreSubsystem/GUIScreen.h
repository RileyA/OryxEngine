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

#ifndef ORYX_GUISCREEN_H
#define ORYX_GUISCREEN_H

#include "Oryx.h"
#include "Ogredllmain.h"
#include "GUIElement.h"

// include these so client apps don't have to do so separately
#include "GUIStaticText.h"
#include "GUIText.h"
#include "GUIEmpty.h"
#include "GUIRectangle.h"

#include "OryxEventHandler.h"

namespace Gorilla
{
	class Silverback;
	class Layer;
	class Screen;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT GUIScreen : public EventHandler
	{
	public:

		GUIScreen(Gorilla::Screen* screen,String name);
		~GUIScreen();

		Gorilla::Screen* getScreen();
		Gorilla::Layer* getLayer(int index);

		void setVisible(bool visible);
		bool isVisible();

		void update(Real delta);

		GUIElement* getRootElement(int layer);

		void addElement(GUIElement* elem,int layer);

		Real getWidth();
		Real getHeight();

		void setCursor(GUIElement* cursor);
		GUIElement* getCursor();
		void moveCursor(const Message& m);
		void click(const Message& m);
		void release(const Message& m);

	private:

		String mName;
		Gorilla::Screen* mScreen;
		Gorilla::Layer* mLayers[16];
		GUIElement* mRootElements[16];// one per layer
		std::vector<GUIElement*> mElements[16];

		GUIElement* mCursor;

	};
}

#endif
