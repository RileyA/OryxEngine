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

#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "BulletConversions.h"
#include "Bulletdllmain.h"

struct btCollisionShape;

namespace Oryx
{
	enum PhysicsShapeType
	{
		PST_BOX,
		PST_SPHERE,
		PST_CONVEX,
		PST_TRIMESH,
		PST_COMPOUND,
		PST_CAPSULE
	};
	//-----------------------------------------------------------------------

	/** Wrapper class for btCollisionShape */
	class ORYX_BULLET_EXPORT PhysicsShape
	{
	public:
		
		/** Constructor */
		PhysicsShape(bool temporary = false, String name="")
			:mTemporary(temporary),mShape(0),mUsers(0),mName(""){}

		/** Destructor, takes care of deleting the shape */
		virtual ~PhysicsShape();

		/** Notifies this shape that an object is using it */
		void addUser(){++mUsers;}

		/** Notifies this shape that an object has stopped using it */
		void removeUser();

		/** Gets how many objects are using this particular object */
		size_t getNumUsers(){return mUsers;}

		/** Gets whether or not this will be deleted as soon as it is no longer
		 *		in active use by any objects. */
		bool isTemporary(){return mTemporary;}

		/** Returns a pointer to the Bullet collision object */
		btCollisionShape* getBtShape(){return mShape;}

		String getName(){return mName;}

		virtual PhysicsShapeType getType() = 0;

	protected:
	
		btCollisionShape* mShape;

	private:

		bool mTemporary;
		size_t mUsers;
		String mName;

	};
}

#endif
