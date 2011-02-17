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

	class Signal
	{
	public:

		Signal(){}
		~Signal(){removeAllListeners();}

		void fire(const Message* message);
		void fire(const Message& message);

		void addListener(Slot* slot,bool notify=true);
		void removeListener(Slot* slot,bool notify=false);
		void removeAllListeners();

		void operator += (Slot* slot);
		void operator -= (Slot* slot);
	
	private:

		std::list<Slot*> mListeners;

	};
}

#endif
