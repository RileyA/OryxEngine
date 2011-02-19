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

// This is a the start of the vs game

#include "Oryx.h"
#include "OryxStringUtils.h"
#include "OryxEngine.h"

#include "ChaiscriptSubsystem/ChaiscriptSubsystem.h"
#include "ALSubsystem/ALSubsystem.h"
#include "OISSubsystem/OISSubsystem.h"
#include "ENetSubsystem/ENetSubsystem.h"
#include "BulletSubsystem/BulletSubsystem.h"

#include "VersusGameState.h"

using namespace Oryx;

int main()
{
    Logger::getPtr();
    TimeManager::getPtr();

    // create subsystems:
    ChaiscriptSubsystem chaiSys = ChaiscriptSubsystem();
    ALSubsystem aSys = ALSubsystem();
	OgreSubsystem ogre = OgreSubsystem(1024,768,false);
	OISSubsystem ois = OISSubsystem();
	ENetSubsystem enet = ENetSubsystem();
	BulletSubsystem bull = BulletSubsystem();

    // allocate engine and add subsystems
    Engine* eng = new Engine();
    eng->addSubsystem(&chaiSys);
    eng->addSubsystem(&aSys);
	eng->addSubsystem(&bull);
    eng->addSubsystem(&ogre);
	eng->addSubsystem(&ois);
	eng->addSubsystem(&enet);

    // initialize the engine
    eng->init();

	// add the testing state to the stack
	eng->addState(new VersusGameState());

	// start up the engine
	eng->start();

    // delete the engine object
    delete eng;

    return 0;
}