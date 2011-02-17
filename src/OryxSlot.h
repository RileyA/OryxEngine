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

	typedef fastdelegate::FastDelegate1<const Message&> Delegate;

	class Slot
	{
	public:

		Delegate slot;

		Slot(){}
		Slot(Delegate _slot):slot(_slot){}
		~Slot(){stopAllListening();}

		void listenTo(Signal* signal,bool notify=true);
		void stopListeningTo(Signal* signal,bool notify = true);

		void stopAllListening();

		void operator += (Signal* signal);
		void operator -= (Signal* signal);

		std::list<Signal*> mSignals;

	};
}

#endif
