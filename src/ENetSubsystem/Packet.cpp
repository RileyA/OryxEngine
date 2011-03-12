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
// auint32_t with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "Packet.h"

namespace Oryx
{
	void Packet::pack(int val)
	{
		// just cast to a uint, and we'll cast back on the other end
		pack(*(reinterpret_cast<uint32_t*>(&val)));
	}
	//-----------------------------------------------------------------------	

	void Packet::pack(uint32_t val)
	{
		val = htonl(val);
		byte* data = new byte[sizeof(uint32_t)];
		memcpy(data,&val,sizeof(uint32_t));
		packBytes(data,sizeof(uint32_t));
		delete[] data;
	}
	//-----------------------------------------------------------------------
	
	void Packet::pack(uint16_t val)
	{
		val = htons(val);
		byte* data = new byte[sizeof(uint16_t)];
		memcpy(data,&val,sizeof(uint16_t));
		packBytes(data,sizeof(uint16_t));
		delete[] data;
	}
	//-----------------------------------------------------------------------
	
	void Packet::pack(short val)
	{
		pack(*(reinterpret_cast<uint16_t*>(&val)));
	}
	//-----------------------------------------------------------------------
	
	void Packet::pack(float val)
	{
		pack(*(reinterpret_cast<uint32_t*>(&val)));
	}
	//-----------------------------------------------------------------------
	
	void Packet::pack(byte val)
	{
		packBytes(&val,sizeof(byte));
	}
	//-----------------------------------------------------------------------
	
	void Packet::pack(String str)
	{
		// pack length as a byte
		pack(static_cast<byte>(str.size()));
		// followed by string itself
		packBytes((byte*)str.data(),str.size());
	}
	//-----------------------------------------------------------------------
	
	void Packet::packBytes(byte* data,size_t length)
	{
		for(int i=0;i<length;++i)
			mPackage.push(data[i]);
	}
	//-----------------------------------------------------------------------
	
	byte* Packet::getFormattedPacket(uint& length)
	{
		clean();
		while(!mPackage.empty()){mPackage.pop();}// clear this
		mPackage.push(getID());
		serialize();
		length = mPackage.size();
		byte* out = new byte[mPackage.size()+1];
		int i = 0;
		while(!mPackage.empty())	
		{
			out[i] = mPackage.front();
			mPackage.pop();
			++i;
		}
		mData = out;// hold onto a ptr so it can be deleted
		return out;
	}
	//-----------------------------------------------------------------------
	
	void Packet::serialize()
	{
		// pack up
	}
	//-----------------------------------------------------------------------
	
	//void Packet::deserialize(byte* data,size_t length)
	//{
		// unpack
	//	std::cout<<"deserializing blank packet!\n";
	//}
	//-----------------------------------------------------------------------
	
	int Packet::unpackInt(byte** data)
	{
		uint32_t temp;
		memcpy(&temp,*data,sizeof(int));
		temp = ntohl(temp);
		int out = *reinterpret_cast<int*>(&temp);
		(*data)+=sizeof(uint32_t);
		return out;
	}
	//-----------------------------------------------------------------------
	
	uint32_t Packet::unpackUInt(byte** data)
	{
		uint32_t out;
		memcpy(&out,*data,sizeof(uint32_t));
		out = ntohl(out);
		(*data)+=sizeof(uint32_t);
		return out;
	}
	//-----------------------------------------------------------------------
	
	short Packet::unpackShort(byte** data)
	{
		uint16_t temp;
		memcpy(&temp,*data,sizeof(short));
		temp = ntohs(temp);
		short out = *reinterpret_cast<short*>(&temp);
		(*data)+=sizeof(uint16_t);
		return out;
	}
	//-----------------------------------------------------------------------
	
	uint16_t Packet::unpackUShort(byte** data)
	{
		uint16_t out;
		memcpy(&out,*data,sizeof(uint16_t));
		out = ntohs(out);
		(*data)+=sizeof(uint16_t);
		return out;
	}
	//-----------------------------------------------------------------------
	
	float Packet::unpackFloat(byte** data)
	{
		uint32_t temp;
		memcpy(&temp,*data,sizeof(float));
		temp = ntohl(temp);
		float out = *reinterpret_cast<float*>(&temp);
		(*data)+=sizeof(float);
		return out;
		//float out = *reinterpret_cast<float*>(unpackUInt(data));
	}
	//-----------------------------------------------------------------------
	
	byte Packet::unpackByte(byte** data)
	{
		byte out = (*data)[0];
		++(*data);
		return out;
	}
	//-----------------------------------------------------------------------
	
	String Packet::unpackString(byte** data)
	{
		byte len = unpackByte(data);
		String out = String((char*)*data,len);
		(*data)+=len*sizeof(byte);
		return out;
	}
	//-----------------------------------------------------------------------

	void Packet::unpack(byte* data,size_t length)
	{
		if(length>=1)
			mID = data[0];
		deserialize(data+1,length);
	}

	StringPacket::StringPacket(String data)
		:Packet(1),message(data)
	{}

	StringPacket::StringPacket(byte* data,size_t length)
	{
		unpack(data,length);
	}

	void StringPacket::serialize()
	{
		pack(message);
	}

	void StringPacket::deserialize(byte* data,size_t length)
	{
		message = unpackString(&data);
	}

	Vector3Packet::Vector3Packet(Vector3 data)
		:Packet(2)
	{

		vector = data;	
	}

	Vector3Packet::Vector3Packet(byte* data,size_t length)
	{
		unpack(data,length);
	}

	void Vector3Packet::serialize()
	{
		pack(vector.x);
		pack(vector.y);
		pack(vector.z);
	}

	void Vector3Packet::deserialize(byte* data,size_t length)
	{
		vector.x = unpackFloat(&data);	
		vector.y = unpackFloat(&data);	
		vector.z = unpackFloat(&data);
	}

}
