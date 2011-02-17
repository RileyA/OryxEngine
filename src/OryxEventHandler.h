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

#ifndef ORYX_EVENT_HANDLER
#define ORYX_EVENT_HANDLER

#include "Oryx.h"
#include "OryxSlot.h"
#include "OryxSignal.h"

namespace Oryx
{
	class EventHandler
	{
	public:

		EventHandler(){}
		virtual ~EventHandler(){};

		void createSignal(String name);
		bool hasSignal(String name);
		Signal* getSignal(String name);

		void createSlot(String name,Delegate del);
		bool hasSlot(String name);
		Slot* getSlot(String name);

		void sendMessage(const Message& message,OryxID destination);
		void sendMessage(const Message& message,String destination);

		virtual void recieveMessage(const Message& message,EventHandler* sender);

		static void registerDestination(String name,EventHandler* handler);
		static EventHandler* getDestination(String name);

	private:

		std::map<String,Signal> mSignals;
		std::map<String,Slot> mSlots;

		// stores a list of non Oryx::Object places messages can be sent (states, subsystems, etc)
		static std::map<String,EventHandler*> mMessageDestinations;

	};
}

#endif
