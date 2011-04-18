//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010-2011

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
#include "LuaSubsystem.h"
#include "LuaWrapper.h"
#include "OryxLogger.h"
#include "OryxTimeManager.h"

#include "OryxEngine.h"
#include "OryxState.h"
#include "OryxGameState.h"
#include "OryxEngineSubsystem.h"

#include "OryxColour.h"
#include "Oryx3DMath.h"

#ifdef ORYX_LUA_REGISTER_OPENAL
	#include "ALSubsystem/ALSubsystem.h"
#endif
#ifdef ORYX_LUA_REGISTER_OGRE
	#include "OgreSubsystem/OgreSubsystem.h"
#endif
#ifdef ORYX_LUA_REGISTER_OIS

#endif

namespace Oryx
{
	#ifdef ORYX_LUA_REGISTER_OGRE
	OgreSubsystem* getOgre()
	{
		return Engine::getPtr()->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();
	}
	#endif
	#ifdef ORYX_LUA_REGISTER_OPENAL
	ALSubsystem* getAL()
	{
		return Engine::getPtr()->getSubsystem("ALSubsystem")->castType<ALSubsystem>();
	}
	#endif

    LuaSubsystem::LuaSubsystem()
        :ScriptingSubsystem(),mInitialized(0),mLua(0){}
    //-----------------------------------------------------------------------

    LuaSubsystem::~LuaSubsystem()
    {
        if(mLua)
            delete mLua;
        mLua = 0;
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::_init()
    {
        if(!mInitialized)
        {
            mLua = new LuaWrapper();
            _registerBasicTypes();

            mInitialized = true;
            Logger::getPtr()->logMessage("Chaiscript Subsystem Initialized.");
        }
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::_deinit()
    {
        if(mInitialized)
        {
            if(mLua)
                delete mLua;
            mLua = 0;
            mInitialized = false;
            Logger::getPtr()->logMessage("Chaiscript Subsystem Deinitialized.");
        }
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::_update(Real delta)
    {
        // nothing to do here.
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::_endState()
    {

    }
    //-----------------------------------------------------------------------

    String LuaSubsystem::getName()
    {
        return String("LuaSubsystem");
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::runScript(String filename)
    {
    }
    //-----------------------------------------------------------------------

    void LuaSubsystem::runString(String script)
    {
		luaL_dostring(mLua->getLua(), script.c_str());
    }
    //-----------------------------------------------------------------------

    LuaWrapper* LuaSubsystem::getWrapper()
    {
        return mLua;
    }
    //-----------------------------------------------------------------------

	void LuaSubsystem::_registerBasicTypes()
	{
		
	}
	//-----------------------------------------------------------------------
}
