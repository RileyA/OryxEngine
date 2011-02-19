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
#ifndef ORYX_BUCKET_H
#define ORYX_BUCKET_H

#include "Oryx.h"

namespace Oryx
{
	class Object;

	/** A "Bucket" of game Objects, essentially a batch of objects to be updated,
	 *		allows objects with interdependencies to be placed in different 
	 *		batches to prevent problems. Objects in a bucket may potentially
	 *		be updated in parallel */
	class Bucket
	{
	public:

		/** Constructor
		 *		@param name The name the bucket will be referred to as (should be unique) */
		Bucket(String name);
		/** Destructor - deletes all contained objects */
		~Bucket();
		
		/** Updates the bucket and its contents */
		void update(Real delta);

		/** Adds an object to this bucket
		 *		@param obj The object to add */
		void addObject(Object* obj);

		/** Retrieves an Object from this bucket
		 *		@param name The name of the desired object
		 *		@return The object (or NULL if not found) */
		Object* getObject(String name);
		/** Retrieves an Object by its integer ID 
		 *		@param id The ID to search for 
		 *		@return The Object, or NULL if not found */
		Object* getObject(OryxID id);

		/** Gets whether or not a named Object is in this Bucket
		 *		@param name The name of the object to look for 
		 *		@return Whether or not it was found */
		bool hasObject(String name) const;
		/** Gets whether  or not an object is in this Bucket, by ID
		 *		@param id The objects unique integer ID value
		 *		@return Whether or not the object was found */
		bool hasObject(OryxID id) const;

		/** Gets whether or not this bucket will automagically be
		 *		deleted at the end of the current GameState */
		bool isTemporary() const;

		/** Sets whether or not this Bucket is temporary
		 *		@param temp Whether or not the objectshould be deleted
		 *			at the end of the current GameState */
		void setTemporary(bool temp);

	private:

		// The objects
		std::map<OryxID,Object*> mObjects;
		// This bucket's name
		String mName;
		// Whether or not it is temporary
		bool mTemporary;
	};
}

#endif
