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

#ifndef BULLET_COLLISIONOBJECT_H
#define BULLET_COLLISIONOBJECT_H

#include "Oryx.h"
#include "PhysicsShape.h"
#include "PhysicsObject.h"
#include "Bulletdllmain.h"
#include "BulletConversions.h"

class btCollisionObject;
class btDynamicsWorld;

namespace Oryx
{
	class ORYX_BULLET_EXPORT CollisionObject : public PhysicsObject
	{
		public:

			/** */
			CollisionObject(btDynamicsWorld* world, btCollisionObject* obj,
				PhysicsShape* shape);
			virtual ~CollisionObject();
			
			/** Updates this object */
			virtual void update(bool frame, Real interpolation, Vector3 gravity);

			/** Gets this object's position in world space 
			 *		@return This object's world-space position */
			virtual Vector3 getPosition();

			/** Sets this object's position in world-space
			 *		@param, position The desired position */
			virtual void setPosition(Vector3 position);

			/** Gets this object's orientation
			 *		@return The orientation as a Quaternion */
			virtual Quaternion getOrientation();

			/** Sets this object's orientation
			 *		@param orientation The desired orientation */
			virtual void setOrientation(Quaternion orientation);

			/** Gets the bullet collision object */
			btCollisionObject* getCollisionObject();

			/** Gets this object's shape */
			PhysicsShape* getShape();

			/** Sets the object's collision group (determines which objects will collide with it)
				@param mask The collision group */
			void setCollisionGroup(short group);

			/** Sets the object's collision mask (what collision groups it will collide with)
				@param mask The collision mask */
			void setCollisionMask(short mask);

			/** Pulls this object out of the simulation world */
			virtual void removeFromSimulation();

			/** Adds this object back into the physics world */
			virtual void addToSimulation();

			/** Sets the user data that will be associated with the bullet object
			 *		TODO: Make this wrap it up in something... */
			void setUserData(void* data);

			/** Gets this object's user data */
			void* getUserData();

			/** Cleans this object up */
			virtual void destroyObject();

		protected:

			btCollisionObject* mObject;
			PhysicsShape* mShape;
			Real mInterpolation;

		private:

	};
}

#endif
