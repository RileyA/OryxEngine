//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "ENetSubsystem.h"
#include "OryxEngine.h"
#include "Server.h"
#include "Client.h"

namespace Oryx
{
	ENetSubsystem::ENetSubsystem()
		:EngineSubsystem(),mInitialized(0){}
	//-----------------------------------------------------------------------

	ENetSubsystem::~ENetSubsystem()
	{
	}
	//-----------------------------------------------------------------------

	void ENetSubsystem::_init()
	{
		if(!mInitialized)
		{
			mInitialized = true;
			Logger::getPtr()->logMessage("ENet Subsystem Initialized.");
		}
	}
	//-----------------------------------------------------------------------

	void ENetSubsystem::_deinit()
	{
		if(mInitialized)
		{
			mInitialized = false;
			for(int i=0;i<mClients.size();++i)
			{
				delete mClients[i];
				mClients[i] = 0;
			}

			for(int i=0;i<mServers.size();++i)
			{
				delete mServers[i];
				mServers[i] = 0;
			}

			mClients.clear();
			mServers.clear();

			Logger::getPtr()->logMessage("ENet Subsystem Deinitialized.");
		}
	}
	//-----------------------------------------------------------------------

	void ENetSubsystem::_update(Real delta)
	{
		for(int i=0;i<mServers.size();++i)
			mServers[i]->pollEvents();

		for(int i=0;i<mClients.size();++i)
			mClients[i]->pollEvents();
	}
	//-----------------------------------------------------------------------

	void ENetSubsystem::_endState()
	{
		
	}
	//-----------------------------------------------------------------------

	String ENetSubsystem::getName()
	{
		return String("ENetSubsystem");
	}
	//-----------------------------------------------------------------------
	
	Client* ENetSubsystem::createClient()
	{
		mClients.push_back(new Client());
		mClients.back()->init(2);
		return mClients.back();
	}
	//-----------------------------------------------------------------------	

	Server* ENetSubsystem::createServer(int port)
	{
		mServers.push_back(new Server());
		mServers.back()->init(port,2);
		return mServers.back();
	}
	//-----------------------------------------------------------------------	
}
