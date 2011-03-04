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

#ifndef ORYX_SIGNAL_H
#define ORYX_SIGNAL_H

#include "Oryx.h"

namespace Oryx
{
	class Message;
	class Slot;

	/** A Qt-inspired Signal, maintains a list of listeners (Slots)
	 *		and calls their delegates when fired */
	class ORYX_EXPORT Signal
	{
	public:

		/** Constructor */
		Signal(){}
		/** Destructor */
		~Signal(){removeAllListeners();}

		/** Fires this signal (calls all listeners' delegates) with a given message
		 *		@param message The message to send */
		void fire(const Message* message) const;

		/** Fires this signal (calls all listeners' delegates) with a given message
		 *		@param message The message to send */
		void fire(const Message& message) const;

		/** Adds a listener to this Signal
		 *		@param Slot Pointer to the Slot */
		void addListener(Slot* slot,bool notify=true);

		/** Removes a Listener from this Signal
		 *		@param slot Pointer to the desired slot */
		void removeListener(Slot* slot,bool notify=false);

		/** Removes all listeners from this Signal */
		void removeAllListeners();

		/** Adds a listener */
		void operator += (Slot* slot);
		/** Removes a Listener */
		void operator -= (Slot* slot);
	
	private:

		// This Signal's list of listeners
		std::list<Slot*> mListeners;

	};
}

#endif
