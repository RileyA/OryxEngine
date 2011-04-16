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
#include "OryxEngine.h"

#include "OryxBucket.h"
#include "OryxObject.h"

#include "OryxMessageAny.h"

namespace Oryx
{
	Engine* Engine::msInstance = 0;

	Engine::Engine()
		:mInitialized(0),mKill(0),mKillState(0)
	{
		assert(!msInstance);// if it already exists then abort
		msInstance = this;// singleton
		mTimeManager = TimeManager::getPtr();
		mTimeManager->start();
		mTimeManager->update();
		mLogger = Logger::getPtr();
		mLogger->logMessage("Oryx Engine Instance Created. Version "+String(ORYX_VERSION));
		EventHandler::registerDestination("Engine",this);
	}
	//-----------------------------------------------------------------------

	Engine::~Engine()
	{
		_deinit();
		msInstance = 0;
	}
	//-----------------------------------------------------------------------

	void Engine::addSubsystem(EngineSubsystem* system)
	{
		mSubsystems[system->getName()] = system;
	}
	//-----------------------------------------------------------------------

	void Engine::addState(GameState* state)
	{
		mStates.push_back(state);
	}
	//-----------------------------------------------------------------------

	bool Engine::init()
	{
		if(!mInitialized)
		{
			mLogger->logMessage("Oryx Engine v"+String(ORYX_VERSION)+" Initializing....");

			mLogger->logMessage("Reticulating Splines...");

			std::map<String,EngineSubsystem*>::iterator iter = mSubsystems.begin();
			for(;iter!=mSubsystems.end();++iter)
				iter->second->_init();
			
			mLogger->logMessage("Subsystems started up!");

			createBucket("Default");
			createBucket("DefaultPerma")->setTemporary(false);

			mLogger->logMessage("Default buckets allocated.");

			mLogger->logMessage("Oryx Engine v"+String(ORYX_VERSION)+" Initialized successfully.");
			mInitialized = true;
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------

	bool Engine::start()
	{
		mLogger->logMessage("Oryx Engine v"+String(ORYX_VERSION)+" Starting up....");

		while(!mStates.empty()&&!mKill)
		{
			mStates[0]->init();
			mKillState = false;

			while(!mKillState && !mStates.front()->isDone())
			{
				mTimeManager->update();
				Real delta = mTimeManager->getDeltaTime();
				
				// update buckets and objects
				std::map<String,Bucket*>::iterator ite = mBuckets.begin();
				for(ite;ite!=mBuckets.end();++ite)
					ite->second->update(delta);

				// update subsystems
				std::map<String,EngineSubsystem*>::iterator iter = mSubsystems.begin();
				for(;iter!=mSubsystems.end();++iter)
					iter->second->_update(delta);

				// update the state
				mStates.front()->update(delta);
			}

			mStates.front()->deinit();
			delete mStates.front();

			mStates.pop_front();

			std::map<String,Bucket*>::iterator it = mBuckets.begin();;

			while(it != mBuckets.end())
			{
				if(it->second->isTemporary())
				{
					std::map<String,Bucket*>::iterator toErase = it;
					++it;
					delete toErase->second;
					mBuckets.erase(toErase);
				}
				else
					++it;
			}

			std::map<String,EngineSubsystem*>::iterator iter = mSubsystems.begin();
			for(;iter!=mSubsystems.end();++iter)
				iter->second->_endState();

			createBucket("Default");// remake the default bucket
		}

		return true;
	}
	//-----------------------------------------------------------------------

	void Engine::shutdown()
	{
		endCurrentState();
		mKill = true;
	}
	//-----------------------------------------------------------------------

	void Engine::endCurrentState()
	{
		mKillState = true;
	}
	//-----------------------------------------------------------------------

	EngineSubsystem* Engine::getSubsystem(String name)
	{
		if(mSubsystems.find(name)!=mSubsystems.end())
			return mSubsystems[name];
		return 0;
	}
	//-----------------------------------------------------------------------

	Bucket* Engine::createBucket(String name)
	{
		mBuckets[name] = new Bucket(name);
		return mBuckets[name];
	}
	//-----------------------------------------------------------------------	

	Bucket* Engine::getBucket(String name)
	{
		if(mBuckets.find(name)!=mBuckets.end())
			return mBuckets[name];
		return 0;
	}
	//-----------------------------------------------------------------------	

	void Engine::_addObject(Object* obj,String bucket)
	{
		if(mBuckets.find(bucket)!=mBuckets.end())
			mBuckets[bucket]->addObject(obj);
		else
			mBuckets["Default"]->addObject(obj);
	}
	//-----------------------------------------------------------------------

	Object* Engine::getObject(String name)
	{
		std::map<String,Bucket*>::iterator it = mBuckets.begin();
		for(it;it!=mBuckets.end();++it)
		{
			Object* obj = it->second->getObject(name);
			if(obj)
				return obj;
		}
		return 0;	
	}
	//-----------------------------------------------------------------------	

	Object* Engine::getObject(OryxID id)
	{
		std::map<String,Bucket*>::iterator it = mBuckets.begin();
		for(it;it!=mBuckets.end();++it)
		{
			Object* obj = it->second->getObject(id);
			if(obj)
				return obj;
		}
		return 0;
	}
	//-----------------------------------------------------------------------	

	void Engine::recieveMessage(const Message& message,EventHandler* sender)
	{
		if(const MessageAny<String>* str = message_cast<String>(message))
		{
			if(str->data=="kill")
				shutdown();
			else if(str->data=="end state")
				endCurrentState();
		}
	}
	//-----------------------------------------------------------------------

	void Engine::_deinit()
	{
		if(mInitialized)
		{
			mLogger->logMessage("Oryx Engine v"+String(ORYX_VERSION)+" Shutting down....");
			
			// delete all buckets (and objects therein)
			std::map<String,Bucket*>::iterator it = mBuckets.begin();
			for(it;it!=mBuckets.end();++it)
				delete it->second;
			mBuckets.clear();

			// deinit all the subsystems
			std::map<String,EngineSubsystem*>::iterator iter = mSubsystems.begin();
			for(;iter!=mSubsystems.end();++iter)
				iter->second->_deinit();

			mLogger->logMessage("Oryx Engine v"+String(ORYX_VERSION)+" Shut down successfully.");
			mInitialized = false;
		}
	}
	//-----------------------------------------------------------------------
}
