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

#include "OryxColor.h"
#include "Oryx3DMath.h"
#include "OryxBucket.h"
#include "OryxObject.h"
#include "OryxEventHandler.h"

#ifdef ORYX_LUA_REGISTER_OPENAL
	#include "ALSubsystem/ALSubsystem.h"
#endif
#ifdef ORYX_LUA_REGISTER_OGRE
	#include "OgreSubsystem/OgreSubsystem.h"
#endif
#ifdef ORYX_LUA_REGISTER_OIS

#endif

Oryx::Engine* getEngine();
Oryx::Logger* getLogger();

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
			Logger::getPtr()->logMessage("Lua Subsystem Initialized.");
      runString("print(2)");
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
			Logger::getPtr()->logMessage("Lua Subsystem Deinitialized.");
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
		luaL_dofile(mLua->getLua(), filename.c_str());
	}
	//-----------------------------------------------------------------------

	void LuaSubsystem::runString(String script)
	{
		luaL_dostring(mLua->getLua(), (script+"\n").c_str());
	}
	//-----------------------------------------------------------------------

	LuaWrapper* LuaSubsystem::getWrapper()
	{
		return mLua;
	}
	//-----------------------------------------------------------------------

	void LuaSubsystem::_registerBasicTypes()
	{
		luabind::module(mLua->getLua()) 
		[
			// Signals
			luabind::class_<Signal>("Signal")
				.def("addListener", &Signal::addListener)
				.def("removeListener", &Signal::removeListener)
				.def("removeAllListeners", &Signal::removeAllListeners),
			// Slots
			luabind::class_<Slot>("Slot")
				.def("listenTo", &Slot::listenTo)
				.def("stopListeningTo", &Slot::stopListeningTo)
				.def("stopAllListening", &Slot::stopAllListening),
			// EventHandler
			luabind::class_<EventHandler>("EventHandler")
				.def("createSignal", &EventHandler::createSignal)
				.def("hasSignal", &EventHandler::hasSignal)
				.def("getSignal", &EventHandler::getSignal)
				.def("hasSlot", &EventHandler::hasSlot)
				.def("getSlot", &EventHandler::getSlot),
			// State (abstract)
			luabind::class_<State, EventHandler>("State")
				.def("init", &State::init)
				.def("deinit", &State::deinit)
				.def("isDone", &State::isDone)
				.def("update", &State::update),
			// GameState
			luabind::class_<GameState, State>("GameState"),
			// Buckets
			luabind::class_<Bucket>("Bucket")
				.def("update", &Bucket::update)
				.def("addObject", &Bucket::addObject)
				.def("isTemporary", &Bucket::isTemporary)
				.def("setTemporary", &Bucket::setTemporary)
				.def("getObject", (Object* (Bucket::*)(String))&Bucket::getObject)
				.def("getObject", (Object* (Bucket::*)(OryxID))&Bucket::getObject)
				.def("hasObject", (bool (Bucket::*)(String) const)&Bucket::hasObject)
				.def("hasObject", (bool (Bucket::*)(OryxID) const)&Bucket::hasObject),
			// Objects
			luabind::class_<Object>("Object"),
			// The Engine itself
			luabind::class_<Engine>("Engine"),
			// The TimeManager
			luabind::class_<TimeManager>("TimeManager"),
			// The Logger
			luabind::class_<Logger>("Logger")
				.def("logMessage", &Logger::logMessage)
				.def("suppressOutput", &Logger::suppressOutput)
				.def("suppressFileOutput", &Logger::suppressFileOutput)
		];

		mLua->registerFunction(&EventHandler::registerDestination,"registerDestination");
		mLua->registerFunction(&EventHandler::getDestination,"getDestination");

		mLua->registerFunction(&Logger::getPtr,"getLogger");
		mLua->registerFunction(&Engine::getPtr,"getEngine");
	}
	//-----------------------------------------------------------------------
}
