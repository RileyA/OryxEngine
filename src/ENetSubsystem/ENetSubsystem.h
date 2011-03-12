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

#ifndef ORYXENETSUBSYSTEM
#define ORYXENETSUBSYSTEM

#include "Oryx.h"
#include "OryxEngineSubsystem.h"

namespace Oryx
{
	class Client;
	class Server;

    class ENetSubsystem : public EngineSubsystem
    {
    public:

        ENetSubsystem();
        virtual ~ENetSubsystem();

        virtual void _init();
        virtual void _deinit();
        virtual void _update(Real delta);
        virtual void _endState();
        virtual String getName();

		Client* createClient();
		Server* createServer(int port);


        static const size_t mDependencyCount;
        static const String mDependencies[];

    protected:

        bool mInitialized;

		std::vector<Client*> mClients;
		std::vector<Server*> mServers;

    };
}

#endif
