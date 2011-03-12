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
#include "Client.h"
#include <enet/enet.h>
#include "OryxStringUtils.h"

namespace Oryx
{
	Client::Client()
	{
		mClient = 0;
		mConnected = false;
	}
	//-----------------------------------------------------------------------
	
	Client::~Client()
	{
		if(mConnected)
			disconnect();
		enet_host_destroy(mClient);
	}
	//-----------------------------------------------------------------------
	
	bool Client::init(int channels)
	{
		mClient = enet_host_create(0,1,channels,0,0);
		return mClient;
	}
	//-----------------------------------------------------------------------
	
	bool Client::connect(std::string ipaddress,int port)
	{
		if(mConnected)
			return false;

		ENetAddress address;
		ENetEvent event;
		ENetPeer *peer;

		enet_address_set_host (&address, ipaddress.c_str());
		address.port = port;

		peer = enet_host_connect(mClient, &address, 2, 0);
		
		if(!peer)
			return false;
		
		if (enet_host_service (mClient, &event, 2000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT)
		{
			mServer = peer;
			pollEvents();// poll once
			mConnected = true;
			return true;// success!
		}
		else
		{
			enet_peer_reset (peer);
			return false;// failure!
		}
	}
	//-----------------------------------------------------------------------
	
	void Client::disconnect()
	{
		if(!mConnected)
			return;

		ENetEvent event;
		enet_peer_disconnect (mServer, 0);

		while (enet_host_service (mClient, &event, 1000) > 0)
		{
			if(event.type==ENET_EVENT_TYPE_RECEIVE)
			{
				enet_packet_destroy(event.packet);
			}
			else if(event.type==ENET_EVENT_TYPE_DISCONNECT)
			{
				std::cout<<"Disconnected Successfully\n";
			}
		}
		enet_peer_reset (mServer);

		mConnected = false;
	}
	//-----------------------------------------------------------------------

	void Client::addCallback(packetCallback call)
	{
		mCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------

	void Client::addConnectCallback(clientAddCallback call)
	{
		mConnectCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------	
	
	void Client::addDisconnectCallback(clientCallback call)
	{
		mDisconnectCallbacks.push_back(call);
	}
	//-----------------------------------------------------------------------
	
	void Client::pollEvents()
	{
		ENetEvent event;
		if(enet_host_service (mClient, & event, 0) > 0)
		{
			if(event.type==ENET_EVENT_TYPE_CONNECT)
			{

			}
			else if(event.type==ENET_EVENT_TYPE_RECEIVE)
			{
				byte id = event.packet->data[0];
				if(id>2&&id<7)
				{
					if(id==4)
					{
						AssignPacket ap(event.packet->data,event.packet->dataLength);
						std::cout<<"My Assigned ID: "<<static_cast<int>(ap.id)<<"\n";
						mID = ap.id;// assign this here...
						IntroPacket ip("Praetor"+StringUtils::toString(ap.id),ap.id);
						sendPacket(&ip);
						std::cout<<"Sending username: "<<static_cast<int>(ip.id)<<" "<<ip.name<<"\n";
					}
					else if(id==5)
					{
						SpawnPacket sp(event.packet->data,event.packet->dataLength);
						std::cout<<"Recieved spawn packet!\n";
						if(sp.id!=mID)
							mPeers[sp.id] = sp.name;
						for(uint i=0;i<mConnectCallbacks.size();++i)
						{
							if(mID!=sp.id)
								mConnectCallbacks[i](sp.id,sp.name);
						}
						std::cout<<"Peer name: "<<mPeers[sp.id]<<" "<<static_cast<int>(sp.id)<<"\n";
					}
					else if(id==6)
					{
						QuitPacket qp = QuitPacket(event.packet->data,event.packet->dataLength);
						byte quitter = qp.id;
						std::cout<<"Client "<<static_cast<int>(quitter)<<" has quit\n";
						for(uint i=0;i<mDisconnectCallbacks.size();++i)
						{
							if(quitter!=mID)// if I'm quitting, I don't care
								mDisconnectCallbacks[i](quitter);
						}
					}
				}
				else
					recievePacket(event.packet);	
				enet_packet_destroy(event.packet);
			}
			else if(event.type==ENET_EVENT_TYPE_DISCONNECT)
			{
				event.peer->data = 0;
			}
		}
	}
	//-----------------------------------------------------------------------
	
	void Client::sendPacket(Packet* packet)
	{
		uint length = 0;
		byte* data = packet->getFormattedPacket(length);
		ENetPacket* pack = enet_packet_create(data,length,ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(mServer,0,pack);
	}
	//-----------------------------------------------------------------------
	
	void Client::recievePacket(ENetPacket* packet)
	{
		for(uint i=0;i<mCallbacks.size();++i)
			mCallbacks[i](packet->data,packet->dataLength,static_cast<uint>(packet->data[0]));
	}
	//-----------------------------------------------------------------------
}


