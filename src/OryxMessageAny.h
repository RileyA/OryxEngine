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

#ifndef ORYX_MESSAGEANY_H
#define ORYX_MESSAGEANY_H

#include "Oryx.h"
#include "OryxMessage.h"

namespace Oryx
{
	/** A Message holding some arbitrary data */
	template<class T> class MessageAny : public Message
	{
	public:
		T data;

		MessageAny(T _data,String _type="")
			:Message(_type),data(_data)
		{}
	};

	template<class T> const T* unpackMsg(const Message& msg)
	{
		if(const MessageAny<T>* message = dynamic_cast<const MessageAny<T>* >(&msg))
			return &(message->data);
		else
			return 0;
	}

	/** Convenience function for casting a message into a given type */
	template<class T> const MessageAny<T>* message_cast(const Message& msg)
	{
		if(const MessageAny<T>* message = dynamic_cast<const MessageAny<T>* >(&msg))
			return message;
		else
			return 0;
	}
}

#endif
