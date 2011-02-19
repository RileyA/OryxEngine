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
#include "OryxEventHandler.h"
#include "OryxEngine.h"
#include "OryxObject.h"

#include "OryxLogger.h"

namespace Oryx
{
	std::map<String,EventHandler*> EventHandler::mMessageDestinations 
		= std::map<String,EventHandler*>();

	void EventHandler::createSignal(String name)
	{
		mSignals[name] = Signal();
	}
	//-----------------------------------------------------------------------
	
	bool EventHandler::hasSignal(String name) const
	{
		return mSignals.find(name)!=mSignals.end();
	}
	//-----------------------------------------------------------------------
	
	Signal* EventHandler::getSignal(String name)
	{
		if(hasSignal(name))
			return &(mSignals.find(name)->second);
		return 0;
	}
	//-----------------------------------------------------------------------
	
	void EventHandler::createSlot(String name,Delegate del)
	{
		mSlots[name] = Slot(del);
	}
	//-----------------------------------------------------------------------
	
	bool EventHandler::hasSlot(String name) const
	{
		return mSlots.find(name)!=mSlots.end();
	}
	//-----------------------------------------------------------------------
	
	Slot* EventHandler::getSlot(String name)
	{
		if(hasSlot(name))
			return &(mSlots.find(name)->second);
	}
	//-----------------------------------------------------------------------
	
	void EventHandler::sendMessage(const Message& message,OryxID destination)
	{
		if(Engine::getPtr()->getObject(destination))
			Engine::getPtr()->getObject(destination)->recieveMessage(message,this);
	}
	//-----------------------------------------------------------------------
	
	void EventHandler::sendMessage(const Message& message,String destination)
	{
		if(mMessageDestinations.find(destination)!=mMessageDestinations.end())
			mMessageDestinations[destination]->recieveMessage(message,this);
	}
	//-----------------------------------------------------------------------
	
	void EventHandler::recieveMessage(const Message& message,EventHandler* sender)
	{
		// by default don't do anything...
	}
	//-----------------------------------------------------------------------
	
	void EventHandler::registerDestination(String name,EventHandler* handler)
	{
		mMessageDestinations[name] = handler;
	}
	//-----------------------------------------------------------------------
	
	EventHandler* EventHandler::getDestination(String name)
	{
		return mMessageDestinations[name];
	}
	//-----------------------------------------------------------------------
}
