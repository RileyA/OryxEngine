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
#include "ChaiscriptSubsystem.h"
#include "ChaiWrapper.h"
#include "OryxLogger.h"
#include "OryxTimeManager.h"

#include "OryxEngine.h"
#include "OryxState.h"
#include "OryxGameState.h"
#include "OryxEngineSubsystem.h"

#include "OryxColor.h"
#include "Oryx3DMath.h"

#ifdef ORYX_CHAI_REGISTER_OPENAL
	#include "ALSubsystem/ALSubsystem.h"
#endif
#ifdef ORYX_CHAI_REGISTER_OGRE
	#include "OgreSubsystem/OgreSubsystem.h"
#endif
#ifdef ORYX_CHAI_REGISTER_OIS

#endif

namespace Oryx
{
	#ifdef ORYX_CHAI_REGISTER_OGRE
	OgreSubsystem* getOgre()
	{
		return Engine::getPtr()->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();
	}
	#endif
	#ifdef ORYX_CHAI_REGISTER_OPENAL
	ALSubsystem* getAL()
	{
		return Engine::getPtr()->getSubsystem("ALSubsystem")->castType<ALSubsystem>();
	}
	#endif

	ChaiscriptSubsystem::ChaiscriptSubsystem()
		:EngineSubsystem(),mInitialized(0),mChai(0){}
	//-----------------------------------------------------------------------

	ChaiscriptSubsystem::~ChaiscriptSubsystem()
	{
		if(mChai)
			delete mChai;
		mChai = 0;
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::_init()
	{
		if(!mInitialized)
		{
			mChai = new ChaiWrapper();
			_registerBasicTypes();

			mInitialized = true;
			Logger::getPtr()->logMessage("Chaiscript Subsystem Initialized.");
		}
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::_deinit()
	{
		if(mInitialized)
		{
			if(mChai)
				delete mChai;
			mChai = 0;
			mInitialized = false;
			Logger::getPtr()->logMessage("Chaiscript Subsystem Deinitialized.");
		}
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::_update(Real delta)
	{
		// nothing to do here.
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::_endState()
	{

	}
	//-----------------------------------------------------------------------

	String ChaiscriptSubsystem::getName()
	{
		return String("ChaiscriptSubsystem");
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::runScript(String filename)
	{
		try
		{
			mChai->getChai()->eval_file(filename);
		}
		catch(chaiscript::Eval_Error e)
		{
			Logger::getPtr()->logMessage(String("Script Error: ")+e.what());
		}
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::runString(String script)
	{
		try
		{
			mChai->getChai()->eval(script);
		}
		catch(chaiscript::Eval_Error e)
		{
			Logger::getPtr()->logMessage(String("Script Error: ")+e.what());
		}
	}
	//-----------------------------------------------------------------------

	ChaiWrapper* ChaiscriptSubsystem::getWrapper()
	{
		return mChai;
	}
	//-----------------------------------------------------------------------

	void ChaiscriptSubsystem::_registerBasicTypes()
	{
		// game state stuff
		mChai->registerType<State>("State");
		mChai->registerType<GameState>("GameState");

		// subsystem
		mChai->registerType<EngineSubsystem>("EngineSubsystem");
		mChai->registerFunction(&EngineSubsystem::getName, "getName");

		// The engine object itself
		mChai->registerType<Engine>("Engine");
		mChai->registerConstructor<Engine (void)>("Engine");
		mChai->registerFunction(&Engine::init, "init");
		mChai->registerFunction(&Engine::start, "start");
		mChai->registerFunction(&Engine::getPtr, "getEngine");
		mChai->registerFunction(&Engine::getSubsystem, "getSubsystem");
		mChai->registerFunction(&Engine::shutdown, "shutdown");
		mChai->registerFunction(&Engine::endCurrentState, "endCurrentState");

		// the logger system
		mChai->registerType<Logger>("Logger");
		mChai->registerFunction(&Logger::logMessage, "logMessage");
		mChai->registerFunction(&Logger::getPtr, "getLog");

		// the time manager
		mChai->registerType<TimeManager>("TimeManager");
		mChai->registerFunction(&TimeManager::getTimeSpeed, "getTimeSpeed");
		mChai->registerFunction(&TimeManager::setTimeSpeed, "setTimeSpeed");
		mChai->registerFunction(&TimeManager::getPtr, "getTimer");

		// register the script system (so scripts can run other scripts, etc)
		mChai->registerType<ChaiscriptSubsystem>("ChaiscriptSubsystem");
		mChai->registerFunction(&ChaiscriptSubsystem::runString, "runString");
		mChai->registerFunction(&ChaiscriptSubsystem::runString, "runScript");

		mChai->registerType<Color>("Color");
		mChai->registerFunction(&Color::r, "r");
		mChai->registerFunction(&Color::g, "g");
		mChai->registerFunction(&Color::b, "b");
		mChai->registerFunction(&Color::a, "a");

		mChai->registerType<Vector3>("Vector3");
		mChai->registerFunction(&Vector3::x, "x");
		mChai->registerFunction(&Vector3::y, "y");
		mChai->registerFunction(&Vector3::z, "z");

		// fun( static_cast<bool (Vector3::*)(const Vector3)>(&...)
		//Vector3 (Vector3::*)(const Vector3)

		// register subsystems
		#ifdef ORYX_CHAI_REGISTER_OPENAL
		mChai->registerFunction(&getAL,"getAL");

		mChai->registerType<ALSubsystem>("ALSubsystem");
		mChai->registerType<SoundPtr>("SoundPtr");
		mChai->registerType<ActiveSound>("ActiveSound");
		mChai->registerType<BufferedSound>("BufferedSound");

		mChai->registerFunction(&ALSubsystem::play2D, "play2D");
		mChai->registerFunction(&ALSubsystem::loadSound, "loadSound");
		mChai->registerFunction(&ALSubsystem::bufferSound, "bufferSound");
		mChai->registerFunction(&ALSubsystem::setDefaultVolume, "setVolume");
		mChai->registerFunction(&ALSubsystem::setDefaultVolumeOgg, "setVolumeOgg");
		#endif
		
		#ifdef ORYX_CHAI_REGISTER_OGRE

		mChai->registerFunction(&getOgre,"getOgre");

		mChai->registerType<OgreSubsystem>("OgreSubsystem");
		mChai->registerType<OgreSubsystem>("SceneNode");
		mChai->registerType<OgreSubsystem>("Mesh");
		mChai->registerType<OgreSubsystem>("Camera");
		mChai->registerType<OgreSubsystem>("Light");

		mChai->registerFunction(&OgreSubsystem::createCamera,"createCamera");
		//mChai->registerFunction(&OgreSubsystem::createMesh,"createMesh");
		mChai->registerFunction(&OgreSubsystem::createSceneNode,"createSceneNode");
		mChai->registerFunction(&OgreSubsystem::createLight,"createLight");
		mChai->registerFunction(&OgreSubsystem::setBackgroundColor,"setBackgroundColor");
		mChai->registerFunction(&OgreSubsystem::getBackgroundColor,"getBackgroundColor");
		mChai->registerFunction(&OgreSubsystem::getActiveCamera,"getActiveCamera");
		mChai->registerFunction(&OgreSubsystem::getDefaultCamera,"getDefaultCamera");
		mChai->registerFunction(&OgreSubsystem::getRootSceneNode,"getRootSceneNode");
		mChai->registerFunction(&OgreSubsystem::renderFrame,"renderFrame");
		mChai->registerFunction(&OgreSubsystem::restart,"restart");
		mChai->registerFunction(&OgreSubsystem::getScreenHeight,"getScreenHeight");
		mChai->registerFunction(&OgreSubsystem::getScreenWidth,"getScreenWidth");
		mChai->registerFunction(&OgreSubsystem::isFullscreen,"isFullscreen");
		mChai->registerFunction(&OgreSubsystem::getGfxParameter,"getGfxParameter");
		mChai->registerFunction(&OgreSubsystem::setActiveCamera,"setActiveCamera");
		mChai->registerFunction(&OgreSubsystem::setFullscreen,"setFullscreen");
		mChai->registerFunction(&OgreSubsystem::setGfxParameter,"setGfxParameter");
		mChai->registerFunction(&OgreSubsystem::setScreenHeight,"setScreenHeight");
		mChai->registerFunction(&OgreSubsystem::setScreenWidth,"setScreenWidth");

		mChai->registerFunction(&SceneNode::setPosition,"setPosition");
		mChai->registerFunction(&SceneNode::getPosition,"getPosition");
		mChai->registerFunction(&SceneNode::addChild,"addChild");
		mChai->registerFunction(&SceneNode::getChild,"getChild");
		mChai->registerFunction(&SceneNode::getChildCount,"getChildCount");
		mChai->registerFunction(&SceneNode::getName,"getName");
		mChai->registerFunction(&SceneNode::getParent,"getParent");
		mChai->registerFunction(&SceneNode::removeAllChildren,"removeAllChildren");
		mChai->registerFunction(static_cast<void (SceneNode::*)(String)>(&SceneNode::removeChild),"removeChild");
		mChai->registerFunction(static_cast<void (SceneNode::*)(SceneNode*)>(&SceneNode::removeChild),"removeChild");

		// since chai apparently doesn't like inheritance...
		mChai->registerFunction(&Mesh::setPosition,"setPosition");
		mChai->registerFunction(&Mesh::getPosition,"getPosition");
		mChai->registerFunction(&Mesh::addChild,"addChild");
		mChai->registerFunction(&Mesh::getChild,"getChild");
		mChai->registerFunction(&Mesh::getChildCount,"getChildCount");
		mChai->registerFunction(&Mesh::getName,"getName");
		mChai->registerFunction(&Mesh::getParent,"getParent");
		mChai->registerFunction(static_cast<void (SceneNode::*)(String)>(&SceneNode::removeChild),"removeChild");
		mChai->registerFunction(static_cast<void (SceneNode::*)(SceneNode*)>(&SceneNode::removeChild),"removeChild");

		mChai->registerFunction(&Camera::setPosition,"setPosition");
		mChai->registerFunction(&Camera::getPosition,"getPosition");
		mChai->registerFunction(&Camera::addChild,"addChild");
		mChai->registerFunction(&Camera::getChild,"getChild");
		mChai->registerFunction(&Camera::getChildCount,"getChildCount");
		mChai->registerFunction(&Camera::getName,"getName");
		mChai->registerFunction(&Camera::getParent,"getParent");
		mChai->registerFunction(&Camera::removeAllChildren,"removeAllChildren");
		mChai->registerFunction(&Camera::setFOV,"setFOV");
		mChai->registerFunction(&Camera::setNearClip,"setNearClip");
		mChai->registerFunction(&Camera::setFarClip,"setFarClip");
		mChai->registerFunction(static_cast<void (Camera::*)(String)>(&Camera::removeChild),"removeChild");
		mChai->registerFunction(static_cast<void (Camera::*)(SceneNode*)>(&Camera::removeChild),"removeChild");

		mChai->registerFunction(&Light::setPosition,"setPosition");
		mChai->registerFunction(&Light::getPosition,"getPosition");
		mChai->registerFunction(&Light::addChild,"addChild");
		mChai->registerFunction(&Light::getChild,"getChild");
		mChai->registerFunction(&Light::getChildCount,"getChildCount");
		mChai->registerFunction(&Light::getName,"getName");
		mChai->registerFunction(&Light::getParent,"getParent");
		mChai->registerFunction(static_cast<void (Light::*)(String)>(&Light::removeChild),"removeChild");
		mChai->registerFunction(static_cast<void (Light::*)(SceneNode*)>(&Light::removeChild),"removeChild");

		
		#endif
		#ifdef ORYX_CHAI_REGISTER_OIS

		#endif
	}
	//-----------------------------------------------------------------------
}
