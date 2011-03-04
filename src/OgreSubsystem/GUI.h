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

#ifndef ORYX_GUI
#define ORYX_GUI

#include "Oryx.h"
#include "Ogredllmain.h"
#include "GUIScreen.h"

namespace Gorilla
{
	class Silverback;
	class Layer;
	class Screen;
}

namespace Ogre
{
	class Viewport;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT GUI
	{
	public:

		GUI();
		~GUI();

		GUIScreen* createScreen(Ogre::Viewport* vp,String atlas,String name);
		GUIScreen* getScreen(String name);
		void destroyScreen(String name);
		void destroyScreen(GUIScreen* screen);
		void update(Real delta);

	private:

		Gorilla::Silverback* mGUI;
		std::map<String,GUIScreen*> mScreens;

	};
}

#endif
