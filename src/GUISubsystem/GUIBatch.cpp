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

#include "GUIBatch.h"
#include "GUIEmpty.h"
#include "Oyster.h"

namespace Oryx
{
	Batch::Batch(Oyster::Batch* b)
		:GUIElement(0),mOysterBatch(b),mWidth(b->getWidth()),mHeight(b->getHeight())
	{
		createSignal("update");
		createSignal("clickUp");
		createSignal("mouseMoved");

		mHovered = 0;
		mClicked = 0;

		mBatch = this;
		mCursor = 0;//new Empty(this, 9001);// the layer is OVER NINE THOUSAND (aka, it's always on top)
		//addChild(mCursor);
	
		createSlot("mouseMoved", this, &Batch::mouseMoved);
		createSlot("mouseUp", this, &Batch::mouseUp);
		createSlot("mouseDown", this, &Batch::mouseDown);
		createSlot("keyUp", this, &Batch::keyUp);
		createSlot("keyDown", this, &Batch::keyDown);
		createSlot("charUp", this, &Batch::charUp);
		createSlot("charDown", this, &Batch::charDown);
	}
	//----------------------------------------------------------------------

	Batch::~Batch()
	{
		//delete mOysterBatch;
	}
	//----------------------------------------------------------------------
	
	void Batch::update()
	{
		// update the internal Oyster::Batch
		if(unsigned char f = mOysterBatch->update())
		{
			MeshUpdate mu;
			mu.flags = f;
			mu.indices = mOysterBatch->getMesh().getIndices();
			mu.vertices = mOysterBatch->getMesh().getVertices();
			mu.diffuse = mOysterBatch->getMesh().getColors();
			mu.texcoords = mOysterBatch->getMesh().getTexcoords();
			mu.normals = 0;
			mu.vertexCount = mOysterBatch->getMesh().getVertexCount();
			mu.faceCount = mOysterBatch->getMesh().getFaceCount();
			if(mu.vertexCount > 0)
				getSignal("update")->fire(MessageAny<MeshUpdate&>(mu));
		}
	}
	//----------------------------------------------------------------------
	
	Oyster::Layer* Batch::getLayer(int index)
	{
		return mOysterBatch->getOrCreateLayer(index);
	}
	//----------------------------------------------------------------------

	GUIElement* Batch::getCursor()
	{
		return mCursor;
	}
	//----------------------------------------------------------------------

	void Batch::setCursor(GUIElement* cursor)
	{
		mCursor = cursor;
	}
	//----------------------------------------------------------------------

	void Batch::mouseMoved(const Message& m)
	{
		Vector2 v = static_cast<const MessageAny<Vector2>&>(m).data;

		if(mCursor)
			mCursor->setPositionPx(v.x, v.y);

		GUIElement* under = 0;
		
		for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
			it != mChildren.rend(); ++it)
		{
			if((*it) == mCursor)
				continue;

			under = (*it)->_search(mCursor->getPosition());

			if(under)
				break;
		}

		if(under == mHovered)
		{
			// still hovering on the same thing, do nothin'
		}
		else
		{
			// tell the previous one it's time in the spotlight is over (poor, poor, GUI element... :( )
			if(mHovered)
			{
				mHovered->unHovered();
				mHovered->getSignal("hover_exit")->fire(MessageAny<GUIElement*>(mHovered));
			}
			mHovered = under;
			if(mHovered)
			{
				mHovered->hovered();
				mHovered->getSignal("hover_enter")->fire(MessageAny<GUIElement*>(mHovered));
			}
		}
	}
	//----------------------------------------------------------------------

	void Batch::mouseUp(const Message& m)
	{
		uint btn = static_cast<const MessageAny<uint>&>(m).data;

		if(btn == 0)
		{
			GUIElement* under = 0;

			for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
				it != mChildren.rend(); ++it)
				if((*it)!=mCursor && (under = (*it)->_search(mCursor->getPosition())))
					break;

			if(under == mClicked && under)
			{
				mClicked->clicked();
				mClicked->getSignal("clicked")->fire(MessageAny<GUIElement*>(mClicked));
			}
			else
			{
				if(mClicked)
				{
					mClicked->released();
					mClicked->getSignal("released")->fire(MessageAny<GUIElement*>(mClicked));
				}
			}

			mClicked = 0;
		}
	}
	//----------------------------------------------------------------------

	void Batch::mouseDown(const Message& m)
	{
		uint btn = static_cast<const MessageAny<uint>&>(m).data;

		if(btn == 0)
		{
			GUIElement* under = 0;

			for(std::list<GUIElement*>::reverse_iterator it = mChildren.rbegin();
				it != mChildren.rend(); ++it)
				if((*it)!=mCursor && (under = (*it)->_search(mCursor->getPosition())))
					break;

			if(under)
			{
				mClicked = under;
				mClicked->pressed();
				mClicked->getSignal("pressed")->fire(MessageAny<GUIElement*>(mClicked));
			}
		}
	}
	//----------------------------------------------------------------------

	void Batch::keyUp(const Message& m)
	{
		//uint btn = static_cast<const MessageAny<uint>&>(m).data;
	}
	//----------------------------------------------------------------------

	void Batch::keyDown(const Message& m)
	{
		//uint btn = static_cast<const MessageAny<uint>&>(m).data;
	}
	//----------------------------------------------------------------------

	void Batch::charUp(const Message& m)
	{
		//char c = static_cast<const MessageAny<char>&>(m).data;
	}
	//----------------------------------------------------------------------

	void Batch::charDown(const Message& m)
	{
		//char c = static_cast<const MessageAny<char>&>(m).data;
	}
	//----------------------------------------------------------------------
}
