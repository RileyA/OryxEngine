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

#ifndef ORYX_GUI_ELEMENT
#define ORYX_GUI_ELEMENT

#include "Oryx.h"
#include "OryxEventHandler.h"
#include "GUIdllmain.h"

namespace Oryx
{
	class Batch;

	class ORYX_GUI_EXPORT GUIElement : public EventHandler
	{
	public:

		GUIElement(GUIElement* parent, int layer = 0);
		virtual ~GUIElement();

		void setPosition(Vector2 pos);
		void setPosition(Real x, Real y);
		void setPositionPx(int x, int y);

		void setScale(Vector2 scale);
		void setScale(Real x, Real y);
		void setScalePx(int x, int y);

		Vector2 getPosition();
		virtual Vector2 getAbsolutePosition();
		Vector2 getPositionPixels();

		Vector2 getScale();
		virtual Vector2 getAbsoluteScale();
		Vector2 getScalePixels();

		void setVerticalAlign(VerticalAlign v);
		void setHorizontalAlign(HorizontalAlign h);
		void setAlign(Align a);
		void setAlign(VerticalAlign v, HorizontalAlign h);
		Align getAlign();
		VerticalAlign getVerticalAlign();
		HorizontalAlign getHorizontalAlign();

		int getLayer(){return mLayer;}
		virtual int getAbsoluteLayer(){return mLayer + mAbsLayer;}
		void setLayer(int layer);

		void addChild(GUIElement* element);
		void destroyChild(GUIElement* element);
		GUIElement* removeChild(GUIElement* element);

		virtual Batch* getBatch(){return mBatch;}

		/*bool _click(Vector2 pos);
		bool _hover(Vector2 pos);*/
		GUIElement* _search(Vector2 pos);

		virtual void pressed();
		virtual void released();
		virtual void clicked();
		virtual void hovered();
		virtual void unHovered();

		//void _releasedMouse(const Message& m);
		//void _movedMouse(const Message& m);

		void registerDrawable(Oyster::Drawable* d, int layer = 0)
		{
			mDrawables.push_back(std::make_pair(d, layer));
		}

		/** internal: updates position/scaling */
		virtual void _update();

		/** Gets the name of the type of element */
		virtual String getType() = 0;

	protected:

		Oyster::Layer* _getLayer(int offset);

		// relative coordinates
		Vector2 mPosition;
		Vector2 mScale;
		GUIElement* mParent;
		std::list<GUIElement*> mChildren;
		std::vector<std::pair<Oyster::Drawable*, int> > mDrawables;

		Batch* mBatch;
		int mLayer;
		int mAbsLayer;

		Vector2 mAlignOffset;
		int mAlignment;

	};
}


#endif
