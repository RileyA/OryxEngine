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
#include "OryxSlot.h"
#include "OryxSignal.h"

namespace Oryx
{
	void Slot::listenTo(Signal* signal,bool notify)
	{
		mSignals.push_back(signal);
		if(notify)
			signal->addListener(this,false);
	}
	//-----------------------------------------------------------------------
	
	void Slot::stopListeningTo(Signal* signal,bool notify)
	{
		std::list<Signal*>::iterator it = mSignals.begin();
		for(it;it!=mSignals.end();++it)
		{
			if(signal==(*it))
			{
				if(notify)
					(*it)->removeListener(this,false);
				mSignals.erase(it);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	
	void Slot::stopAllListening()
	{
		std::list<Signal*>::iterator it = mSignals.begin();
		for(it;it!=mSignals.end();++it)
		{
			(*it)->removeListener(this);
		}
		mSignals.clear();
	}
	//-----------------------------------------------------------------------
	
	void Slot::operator += (Signal* signal)
	{
		listenTo(signal);
	}
	//-----------------------------------------------------------------------
	
	void Slot::operator -= (Signal* signal)
	{
		stopListeningTo(signal);
	}
	//-----------------------------------------------------------------------
}
