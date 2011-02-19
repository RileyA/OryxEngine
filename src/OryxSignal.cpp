//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the license, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTEE; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have recieved a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "OryxMessageAny.h"
#include "FastDelegate.h"
#include "OryxSignal.h"
#include "OryxSlot.h"

namespace Oryx
{
	void Signal::fire(const Message* message)
	{
		std::list<Slot*>::iterator it = mListeners.begin();
		for(it;it!=mListeners.end();++it)
		{
			(*it)->slot(*message);
		}
	}
	//-----------------------------------------------------------------------
	
	void Signal::fire(const Message& message)
	{
		std::list<Slot*>::iterator it = mListeners.begin();
		for(it;it!=mListeners.end();++it)
		{
			(*it)->slot(message);
		}
	}
	//-----------------------------------------------------------------------
	
	void Signal::addListener(Slot* slot,bool notify)
	{
		mListeners.push_back(slot);
		if(notify)
			slot->listenTo(this,false);
	}
	//-----------------------------------------------------------------------
	
	void Signal::removeListener(Slot* slot,bool notify)
	{
		std::list<Slot*>::iterator it = mListeners.begin();
		for(it;it!=mListeners.end();++it)
		{
			if((*it)==slot)
			{
				if(notify)
					(*it)->stopListeningTo(this,false);
				mListeners.erase(it);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	
	void Signal::removeAllListeners()
	{
		std::list<Slot*>::iterator it = mListeners.begin();
		for(it;it!=mListeners.end();++it)
		{
			(*it)->stopListeningTo(this,false);
		}
		mListeners.clear();
	}
	void Signal::operator +=(Slot* slot)
	{
		addListener(slot);
	}
	//-----------------------------------------------------------------------
	
	void Signal::operator -=(Slot* slot)
	{
		removeListener(slot);
	}
	//-----------------------------------------------------------------------
}
