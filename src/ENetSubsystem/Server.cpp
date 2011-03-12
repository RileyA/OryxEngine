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

#include "Oryx.h"
#include "Server.h"
#include <enet/enet.h>

namespace Oryx
{
	Server::Server()
	{
		mServer = 0;
	}
	//-----------------------------------------------------------------------
	
	Server::~Server()
	{
		enet_host_destroy(mServer);
	}
	//-----------------------------------------------------------------------
	
	bool Server::init(int port, int channels)
	{
		ENetAddress address;
		address.host = ENET_HOST_ANY;
		address.port = port;
		mServer = enet_host_create(&address,32,2,0,0);
		return mServer;
	}
	//-----------------------------------------------------------------------
	
	void Server::pollEvents()
	{
		ENetEvent event;

		if(enet_host_service (mServer, &event, 0) > 0)
		{
			if(event.type==ENET_EVENT_TYPE_CONNECT)
			{
				bool found = false;
				for(int i=0;i<255;++i)
				{
					if(mClients.find(i)==mClients.end())
					{
						found = true;
						mClients[i] = event.peer;
						AssignPacket ap(i);
						sendPacket(&ap,false,i);
						std::cout<<"Assigning Client ID... (ID: "<<i<<")\n";
						break;
					}
				}
				if(!found)
					std::cout<<"SHIT! Something went wrong!\n";
			}
			else if(event.type==ENET_EVENT_TYPE_RECEIVE)
			{
				byte id = event.packet->data[0];
				if(id<3||id>5)
					recievePacket(event.packet);
				else
				{
					if(id==3)
					{
						IntroPacket ap(event.packet->data,event.packet->dataLength);
						std::cout<<"Client introduced: "<<ap.name<<" (ID: "
							<<static_cast<int>(ap.id)<<")\n";
						
						std::map<byte,String>::iterator iter = mClientNames.begin();
						for(iter;iter!=mClientNames.end();++iter)
						{
							sendPacket(&SpawnPacket(iter->second,iter->first),false,ap.id);
						}
						
						SpawnPacket sp(ap.name,ap.id);
						mClientNames[ap.id] = ap.name;
						sendPacket(&sp);
						for(uint i=0;i<mConnectCallbacks.size();++i)
						{
							mConnectCallbacks[i](ap.id);
						}
					}
				}
				enet_packet_destroy(event.packet);
			}
			else if(event.type==ENET_EVENT_TYPE_DISCONNECT)
			{
				std::map<byte,ENetPeer*>::iterator it = mClients.begin();
				for(it;it!=mClients.end();++it)
				{
					if(it->second==event.peer)
					{
						std::cout<<"Disconnected Client (ID: "<<static_cast<int>(it->first)<<")\n";
						mClientNames.erase(mClientNames.find(it->first));
						mClients.erase(it);
						sendPacket(&QuitPacket(it->first));// notify everyone
						break;
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------

	void Server::addCallback(packetCallback call)
	{
		mCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------
	
	void Server::addConnectCallback(clientCallback call)
	{
		mConnectCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------
	
	void Server::addDisconnectCallback(clientCallback call)
	{
		mDisconnectCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------
	
	void Server::sendPacket(Packet* pack,bool broadcast,byte id)
	{
		uint length = 0;
		byte* data = pack->getFormattedPacket(length);
		ENetPacket* packet = enet_packet_create(data,length,
			ENET_PACKET_FLAG_RELIABLE);
		if(broadcast)
			enet_host_broadcast(mServer,0,packet);
		else
			enet_peer_send(mClients[id],0,packet);
	}
	//-----------------------------------------------------------------------
	
	void Server::recievePacket(ENetPacket* packet)
	{
			for(uint i=0;i<mCallbacks.size();++i)
				mCallbacks[i](packet->data,packet->dataLength,static_cast<uint>(packet->data[0]));
	}
	//-----------------------------------------------------------------------
	
	String Server::getClientName(byte id)
	{
		if(mClientNames.find(id)!=mClientNames.end())
		{
			return mClientNames[id];
		}
		return "";
	}
	//-----------------------------------------------------------------------	
}

