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

#ifndef ORYX_SLOT_H
#define ORYX_SLOT_H

#include "FastDelegate.h"
#include "Oryx.h"

namespace Oryx
{
	class Message;
	class Signal;

	// save some typing...
	typedef fastdelegate::FastDelegate1<const Message&> Delegate;

	/** A Qt-inspired Slot, recieves messages sent from Signals */
	class Slot
	{
	public:

		// The delegate itself
		Delegate slot;

		/** Default Constructor */
		Slot(){}
		/** Constructor
		 *		@param _slot The delegate to use */
		Slot(Delegate _slot):slot(_slot){}
		~Slot(){stopAllListening();}

		/** Listen to a given Signal 
		 *		@param signal The signal to listen to */
		void listenTo(Signal* signal,bool notify=true);

		/** Stop listening to a given Signal 
		 *		@param signal The signal to stop listening to */
		void stopListeningTo(Signal* signal,bool notify = true);

		/** Stop listening to all Signals */
		void stopAllListening();

		/** Listen to a Signal */
		void operator += (Signal* signal);
		/** Stop listening to a Signal */
		void operator -= (Signal* signal);

	private:
		
		// list of Signals being listened to
		std::list<Signal*> mSignals;

	};
}

#endif
