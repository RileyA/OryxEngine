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

#ifndef ORYX_SERVER_H
#define ORYX_SERVER_H

#include "Oryx.h"
#include "ENetdllmain.h"
#include "Packet.h"

typedef struct _ENetPeer ENetPeer;
typedef struct _ENetHost  ENetHost;
typedef struct _ENetPacket ENetPacket;

namespace Oryx
{
	class Server
	{
	public:

		Server();
		~Server();

		bool init(int port, int channels);
		void pollEvents();
		void sendPacket(Packet* pack,bool broadcast=true,byte clientID=0);

		void recievePacket(ENetPacket* packet);

		void addCallback(packetCallback call);
		void addConnectCallback(clientCallback call);
		void addDisconnectCallback(clientCallback call);

		String getClientName(byte id);

	private:

		ENetHost* mServer;
		std::map<byte,ENetPeer*> mClients;
		std::map<byte,String> mClientNames;
		std::vector<packetCallback> mCallbacks;
		std::vector<clientCallback> mConnectCallbacks;
		std::vector<clientCallback> mDisconnectCallbacks;
	};
}

#endif
