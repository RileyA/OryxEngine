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
	/** An implementation of the Observer Pattern, based heavily on Qt's
	 *		signals and slots. Also supports sending one-time messages. */
	class EventHandler
	{
	public:

		/** Constructor */
		EventHandler(){}
		/** Destructor */
		virtual ~EventHandler(){};

		/** Creates a named Signal object 
		 *		@param name What this Signal will be called*/
		void createSignal(String name);

		/** Gets whether or not a named Signal exists
		 *		@param name The name to look for 
		 *		@return Whether or not the Signal was found*/
		bool hasSignal(String name) const;

		/** Returns a named signal
		 *		@param name The name to look for
		 *		@return The Signal (NULL otherwise) */
		Signal* getSignal(String name);

		/** Creates a Slot
		 *		@param name What to call the new Slot 
		 *		@param del The Delegate corresponding to the callback function */
		void createSlot(String name,Delegate del);

		/** Creates a Slot
		 *		@param name What to call the new Slot 
		 *		@param context The context from which to call the function
		 *		@param function The function to call */
		template <typename obj,typename func> void createSlot(String name, obj context, func function)
		{
			createSlot(name,fastdelegate::MakeDelegate(context,function));
		}
		
		/** Gets whether or not a named Slot exists
		 *		@param name The name to look for
		 *		@return Whether or not it was found */
		bool hasSlot(String name) const;

		/** Retrieves a named Slot 
		 *		@param name The name to look for
		 *		@return The Slot, or NULL if not found */
		Slot* getSlot(String name);

		/** Sends a message to an ID'd Oryx::Object 
		 *		@param Message The message to send 
		 *		@param destination The ID to send it to */
		void sendMessage(const Message& message,OryxID destination);

		/** Sends a message to soem other destination (subsystem, state, etc)
		 *		@param message The message to semd 
		 *		@param destination The name of the destination */
		void sendMessage(const Message& message,String destination);

		/** Recieves a message sent with sendMessage()
		 *		@param message The message
		 *		@param sender Pointer to the sender */
		virtual void recieveMessage(const Message& message,EventHandler* sender);

		/** Regsisters a destination
		 *		@param name The name (becomes its address) 
		 *		@param handler Pointer to the Handler that will recieve the messages */
		static void registerDestination(String name,EventHandler* handler);

		/** Returns a named destination
		 *		@param name The address to look for
		 *		@return A pointer to the destination (or NULL if not found) */
		static EventHandler* getDestination(String name);

	private:

		// This handler's Signals
		std::map<String,Signal> mSignals;
		// This handler's Slots
		std::map<String,Slot> mSlots;

		// stores a list of non Oryx::Object places messages can be sent (states, subsystems, etc)
		static std::map<String,EventHandler*> mMessageDestinations;

	};
}

#endif
