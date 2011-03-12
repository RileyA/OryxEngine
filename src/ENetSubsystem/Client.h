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

#ifndef ORYX_CLIENT_H
#define ORYX_CLIENT_H

#include "Oryx.h"
#include "ENetdllmain.h"
#include "Packet.h"

typedef struct _ENetPeer ENetPeer;
typedef struct _ENetHost  ENetHost;
typedef struct _ENetPacket  ENetPacket;

namespace Oryx
{
	class Client
	{
	public:

		Client();
		~Client();

		bool init(int channels);

		bool connect(std::string ipaddress,int port);
		void disconnect();

		void addCallback(packetCallback call);
		void addConnectCallback(clientAddCallback call);
		void addDisconnectCallback(clientCallback call);

		void pollEvents();
		void sendPacket(Packet* pack);
		void recievePacket(ENetPacket* packet);
		//void sendPacket(void* data,size_t size);
		
		bool isConnected()
		{
			return mConnected;
		}

		byte getID()
		{
			return mID;
		}

	private:

		byte mID;// thsi client's id
		bool mConnected;
		ENetHost* mClient;
		ENetPeer* mServer;

		std::map<byte,String> mPeers;// peer id values
		std::vector<packetCallback> mCallbacks;
		std::vector<clientAddCallback> mConnectCallbacks;
		std::vector<clientCallback> mDisconnectCallbacks;

	};
}

#endif
