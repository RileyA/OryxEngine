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

#ifndef ORYX_GUI_BATCH
#define ORYX_GUI_BATCH

#include "Oryx.h"
#include "GUIElement.h"
#include "GUIdllmain.h"

namespace Oryx
{
	class Empty;

	class Batch : public GUIElement
	{
	public:
		
		Batch(Oyster::Batch* b);
		virtual ~Batch();

		Vector2 getAbsolutePosition(){return Vector2(0,0);}
		Vector2 getAbsoluteScale(){return Vector2(1,1);}
		int getAbsoluteLayer(){return mLayer;}

		String getType(){return "Batch";}

		Batch* getBatch(){return this;};

		int getHeight(){return mHeight;}
		int getWidth(){return mWidth;}

		Oyster::Layer* getLayer(int index);

		GUIElement* getCursor();
		void setCursor(GUIElement* cursor);

		void update();

		// slot callbacks
		void mouseMoved(const Message& m);
		void mouseUp(const Message& m);
		void mouseDown(const Message& m);
		void keyUp(const Message& m);
		void keyDown(const Message& m);
		void charUp(const Message& m);
		void charDown(const Message& m);

	private:

		int mHeight;
		int mWidth;

		Oyster::Batch* mOysterBatch;
		GUIElement* mCursor;
		GUIElement* mHovered;
		GUIElement* mClicked;

	};
}

#endif
