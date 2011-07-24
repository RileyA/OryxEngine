//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010-2011

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

#include "Oryx.h"
#include "GUISubsystem.h"
#include "GUIBatch.h"
#include "Oyster.h"

namespace Oryx
{
	GUISubsystem::GUISubsystem(int w, int h)
		:EngineSubsystem(),mInitialized(0),mWidth(w),mHeight(h){}
	//-----------------------------------------------------------------------

	GUISubsystem::~GUISubsystem()
	{
	}
	//-----------------------------------------------------------------------

	void GUISubsystem::_init()
	{
		if(!mInitialized)
		{
			mInitialized = true;
			mOyster = new Oyster::Oyster(mWidth, mHeight); 
			Logger::getPtr()->logMessage("GUI Subsystem Initialized.");
		}
	}
	//-----------------------------------------------------------------------

	void GUISubsystem::_deinit()
	{
		if(mInitialized)
		{
			mInitialized = false;

			for(std::map<String,Batch*>::iterator it = mBatches.begin(); 
				it != mBatches.end(); ++it)
				delete it->second;
			mBatches.clear();

			Logger::getPtr()->logMessage("GUI Subsystem Deinitialized.");
		}
	}
	//-----------------------------------------------------------------------

	void GUISubsystem::_update(Real delta)
	{
		for(std::map<String,Batch*>::iterator it = mBatches.begin(); 
			it != mBatches.end(); ++it)
		{
			it->second->update();
		}
	}
	//-----------------------------------------------------------------------

	void GUISubsystem::_endState()
	{
		// clean up after every state
		for(std::map<String,Batch*>::iterator it = mBatches.begin(); 
			it != mBatches.end(); ++it)
			delete it->second;
		mBatches.clear();
		delete mOyster;
		mOyster = new Oyster::Oyster(mWidth, mHeight); 
	}
	//-----------------------------------------------------------------------

	String GUISubsystem::getName()
	{
		return String("GUISubsystem");
	}
	//-----------------------------------------------------------------------

	Batch* GUISubsystem::createBatch(String name, String atlas, int w, int h)
	{
		w = !w ? w : mWidth;
		h = !h ? h : mHeight;
		if(!mOyster->getAtlas(atlas))
			mOyster->createAtlas(atlas, atlas);
		mBatches[name] = new Batch(mOyster->createBatch(name, atlas, w, h));
		return mBatches[name];
	}
	//-----------------------------------------------------------------------
}
