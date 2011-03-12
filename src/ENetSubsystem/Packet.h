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

#ifndef ORYX_PACKET_H
#define ORYX_PACKET_H

#include "Oryx.h"
#include "Oryx3DMath.h"


namespace Oryx
{
	// a few basic types of packets
	enum PacketID
	{
		PI_EMPTY,
		PI_STRING,
		PI_VECTOR3,
		PI_INTRO,// new client tells server its username/prefs
		PI_ASSIGN,// server assigns client an id
		PI_SPAWN,// server tells clients about new client
		PI_QUIT,// serve telling remaining clients that a client quit
		PI_LOCATION// basic loc/ori packet with an id field
	};

	class Packet
	{
	public:

		// constructor for interpreting a recieved packet
		Packet()
			:mData(0),mID(0)
		{

		}
		
		// used when creating a new packet
		Packet(byte id)
			:mID(id),mData(0)
		{

		}

		virtual ~Packet()
		{
			clean();
		}

		byte getID()
		{
			return mID;
		}

		void clean()
		{
			if(mData)
			{
				delete[] mData;
				mData = 0;
			}
		}

		void unpack(byte* data,size_t length);


		/** Prepares the data that will be included in a packet */
		virtual void serialize() = 0;
		/** Takes the raw data and recionstructs it into something useful */
		virtual void deserialize(byte* data,size_t length) = 0;

		/** Returns a formatted char array ready for sending */
		byte* getFormattedPacket(uint& length);

	protected:

		// pack/unpack methods to ensure proper endians
		void pack(uint32_t val);
		void pack(int val);
		void pack(uint16_t val);
		void pack(short val);
		void pack(float val);
		void pack(byte val);
		void pack(String str);

		int unpackInt(byte** data);
		uint32_t unpackUInt(byte** data);
		short unpackShort(byte** data);
		uint16_t unpackUShort(byte** data);
		float unpackFloat(byte** data);
		byte unpackByte(byte** data);
		String unpackString(byte** data);

		// packs a sized array of bytes into the packet for sending
		void packBytes(byte* data,size_t length);

	private:

		byte mID;
		std::queue<byte> mPackage;// this gets converted to a char array for sendinug
		byte* mData;// the data send in the packet (this must be deleted here somewhere)
	};

	class StringPacket : public Packet
	{
	public:

		StringPacket(String data);
		StringPacket(byte* data,size_t length);
		virtual void serialize();
		virtual void deserialize(byte* data,size_t length);

		//virtual void deserialize(byte* data,size_t length);
		
		String message;
	};

	class Vector3Packet : public Packet
	{
	public:
		Vector3Packet(Vector3 data);
		Vector3Packet(byte* data,size_t length);
		virtual void serialize();
		virtual void deserialize(byte* data,size_t length);

		Vector3 vector;
	};


	// sent from client to the server to give username, etc
	class IntroPacket : public Packet
	{
	public:
		IntroPacket(String username,byte id_)
			:Packet(PI_INTRO)
		{
			name = username;
			id = id_;
		}

		IntroPacket(byte* data,size_t length)
		{
			unpack(data,length);
		}

		virtual void serialize()
		{
			pack(id);
			pack(name);
		}

		virtual void deserialize(byte* data,size_t length)
		{
			id = unpackByte(&data);
			name = unpackString(&data);
		}

		String name;
		byte id;
	};

	class AssignPacket : public Packet
	{
	public:
		AssignPacket(byte id_)
			:Packet(PI_ASSIGN)
		{
			id = id_;
		}

		AssignPacket(byte* data,size_t length)
		{
			unpack(data,length);
		}

		virtual void serialize()
		{
			pack(id);
		}

		virtual void deserialize(byte* data,size_t length)
		{
			id = unpackByte(&data);
		}

		byte id;
	};

	// sent from server to the clients after intro, to set an id, spawn point etc for the new player
	// tells the new client what's what and lets the old clients know about the new one
	class SpawnPacket : public Packet
	{
	public:
		SpawnPacket(String username,byte id_)
			:Packet(PI_SPAWN)
		{
			name = username;
			id = id_;
		}

		SpawnPacket(byte* data,size_t length)
		{
			unpack(data,length);
		}

		virtual void serialize()
		{
			pack(id);
			pack(name);
		}

		virtual void deserialize(byte* data,size_t length)
		{
			id = unpackByte(&data);
			name = unpackString(&data);
		}

		String name;
		byte id;
		// bool team, etc...
	};

	class QuitPacket : public Packet
	{
	public:
		
		QuitPacket(byte _id)
			:Packet(PI_QUIT)
		{
			id = _id;
		}

		QuitPacket(byte* data,size_t length)
		{
			unpack(data,length);
		}

		virtual void serialize()
		{
			pack(id);
		}

		virtual void deserialize(byte* data,size_t length)
		{
			id = unpackByte(&data);
		}

		byte id;

	};

	// lets clients know the location of a player (by id)
	class LocationPacket : public Packet
	{
	public:
		LocationPacket(byte id_,Vector3 pos,Quaternion ori)
			:Packet(PI_LOCATION)
		{
			position = pos;
			orientation = ori;
			pid = id_;
		}

		LocationPacket(byte* data,size_t length)
		{
			unpack(data,length);
		}

		virtual void serialize()
		{
			pack(pid);
			pack(position.x);
			pack(position.y);
			pack(position.z);
			pack(orientation.x);
			pack(orientation.y);
			pack(orientation.z);
			pack(orientation.w);
		}

		virtual void deserialize(byte* data,size_t length)
		{
			pid = unpackByte(&data);
			position.x = unpackFloat(&data);
			position.y = unpackFloat(&data);
			position.z = unpackFloat(&data);

			orientation.x = unpackFloat(&data);
			orientation.y = unpackFloat(&data);
			orientation.z = unpackFloat(&data);
			orientation.w = unpackFloat(&data);
		}

		Quaternion orientation;
		Vector3 position;
		byte pid;
	};

}

#endif
