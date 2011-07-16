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

#ifndef ORYX_GUIELEMENT_H
#define ORYX_GUIELEMENT_H

#include "Oryx.h"
#include "Ogredllmain.h"
#include "OryxVector2.h"
#include "OryxEventHandler.h"

namespace Gorilla
{
	class Silverback;
	class Layer;
	class Screen;
}

namespace Oryx
{
	class GUIScreen;

	// This is a generic alignment enum used for text, elements, etc
	enum GUI_Align
	{
		GA_NONE,

		// basic 1-d aligns:
		GA_CENTER,
		GA_LEFT,
		GA_RIGHT,
		GA_TOP,
		GA_BOTTOM,

		// 2 dimensional align-age
		GA_LEFT_CENTER,
		GA_LEFT_TOP,
		GA_LEFT_BOTTOM,
		GA_CENTER_CENTER,
		GA_CENTER_TOP,
		GA_CENTER_BOTTOM,
		GA_RIGHT_CENTER,
		GA_RIGHT_TOP,
		GA_RIGHT_BOTTOM
	};

	// very simple for the time being, a more robust solution to come later...
	class ORYX_OGRE_EXPORT GUIElement : public EventHandler
	{
	public:

		GUIElement(GUIElement* parent,String name,int layer=0);
		GUIElement(GUIScreen* screen,String name,int layer=0);
		virtual ~GUIElement();

		void update(Real delta);

		void setPosition(Vector2 pos=Vector2(0,0));
		Vector2 getPosition();
		Vector2 getDerivedPosition();
		void _refreshPosition();

		void setScale(Vector2 dim=Vector2(1,1));
		Vector2 getScale();
		Vector2 getDerivedScale();
		void _refreshScale();

		// force this element into an aspect ratio (useful for making standardized
		// menus with
		void setAspectRatio(int h,int v, bool preserveHeight=true);

		int getLayer();
		GUIScreen* getScreen();

		void addChild(GUIElement* elem);
		virtual void click(Vector2 coords,bool up);	
		virtual void hover(Vector2 coords);	
		virtual void unhover();	
		virtual void release();	

	protected:

		virtual void _setPos(Vector2 pos) = 0;
		virtual void _setScale(Vector2 dim) = 0;

		virtual void _clicked();
		virtual void _hovered(bool on);

		bool mClickedOver;
		bool mHover;

		Vector2 mPosition;
		Vector2 mScale;

		String mName;

		GUIScreen* mScreen;
		int mLayer;

		std::vector<GUIElement*> mElements;
		GUIElement* mParent;

		static long long msAutoNameIndex;

	};
}

#endif
