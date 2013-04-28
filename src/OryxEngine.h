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

#ifndef ORYXENGINE_H
#define ORYXENGINE_H

#include "Oryx.h"
#include "OryxGameState.h"
#include "OryxEngineSubsystem.h"
#include "OryxEventHandler.h"

namespace Oryx
{
	class Bucket;
	class Object;

	/** The main Engine class for the whole thing.
		Everything starts here. */
	class ORYX_EXPORT Engine : public EventHandler
	{
	public:
		
		/** Constructor */
		Engine();
		/** Destructor */
		~Engine();

		/** Adds a subsystem to the engine
		 *		@param system The system to be added
		 *		@remarks Note that the system will not be init-ed until
		 *			Engine::init() is called*/
		void addSubsystem(EngineSubsystem* system);

		/** Adds a game state to the stack
		 *		@param Pointer to the state */
		void addState(GameState* state);

		/** Initializes the engine and all added subsystems
		 *		@returns Whether or not all systems init-ed sucessfully */
		bool init();

		/** Starts the engine. It will run until it runs out of states
		 *		@returns Whether or not the run was sucessful */
		bool start();

		/** Forces a shutdown */
		void shutdown();

		/** Forces the current state to end */
		void endCurrentState();

		/** Gets an engine subsystem by name */
		EngineSubsystem* getSubsystem(String name);

		/** Creates a new Object Bucket
		 *		@param name What to name the bucket (must be unique)
		 *		@return The created object */
		Bucket* createBucket(String name);

		/** Retrieves a pointer to a named bucket
		 *		@param name The bucket to look for 
		 *		@return A pointer to the bucket (or 0 if non-extant) */
		Bucket* getBucket(String name);

		/** Adds an object to a bucket
		 *		@param obj The object to add 
		 *		@param bucket The name of the bucke to add to
		 *		@remarks A client app shouldn't need to use this, objects will
		 *			automagically add themselves to their buckets upon creation */
		void _addObject(Object* obj, String bucket);

		/** Gets an object by name (this searches all buckets) 
		 *		@param name The name of the object to find and return
		 *		@return A pointer to the object (or 0 if non existent) */
		Object* getObject(String name);

    void killObject(String name);
    void killObject(OryxID id);

		/** Gets an object by ID (this searches all buckets)
		 *		@param id The id to search for 
		 *		@return A pointer to the object */
		Object* getObject(OryxID id);

		virtual void recieveMessage(const Message& message,EventHandler* sender);

		/** INTERNAL: deinitializes all subsystems */
		void _deinit();

		/** Get a pointer to the engine from anywhere
		 *		@remarks The engine must have been created explicitly
		 *			before this will work */
		static Engine* getPtr()
		{
			return msInstance;
		}

		/** Get a reference to the engine from anywhere
		 *		@remarks The engine must have been created explicitly
		 *			before this will work */
		static Engine& getRef()
		{
			assert(msInstance);
			return *msInstance;
		}

	private:

		// The states
		std::deque<GameState*> mStates;
		std::map<String,EngineSubsystem*> mSubsystems;

		std::map<String,Bucket*> mBuckets;

		bool mInitialized;
		bool mKill;
		bool mKillState;

		Logger* mLogger;
		TimeManager* mTimeManager;

		static Engine* msInstance;

		// don't allow these, 'tis a singleton
		Engine(const Engine &);
		Engine& operator=(const Engine &);

	};
}

#endif
