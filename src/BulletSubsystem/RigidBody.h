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

#ifndef RIGID_BODY_H
#define RIGID_BODY_H
  
#include "Oryx.h"
#include "CollisionObject.h"
#include "Bulletdllmain.h"

class btDynamicsWorld;
struct btRigidBody;
struct btCollisionObject;
struct btCollisionShape;

namespace Oryx
{
	class ORYX_BULLET_EXPORT RigidBody : public CollisionObject
	{
	public:

		RigidBody(btDynamicsWorld* world, btRigidBody* body, PhysicsShape* shape);

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
		btRigidBody* getRigidBody();

		/** Adds a force at a position on the body
			@param dir the force 
			@param pos relative position on the body to apply the force to */
		void addForce(Vector3 force,Vector3 pos=Vector3(0,0,0));

		/** Adds an impulse at a position on the body
			@param dir the impulse 
			@param impulse relative position on the body to apply the impulse to */
		void addImpulse(Vector3 impulse,Vector3 pos=Vector3(0,0,0));

		/** Sets this object's velocity 
			@param velocity the velocity */
		void setVelocity(Vector3 velocity);

		/** Gets this object's velocity
			@returns the object's velocity */
		Vector3 getVelocity();

		/** Sets the object's mass 
			@param mass the desired mass */
		void setMass(float mass);

		/** Forces the object to wake up from a sleep state */
		void wakeup();

		/** Forces the object into a sleep state */
		void toSleep();

		/** Sets whether this object will be able to fall asleep due to inactivity
			@param enabled whether or not sleeping is enabled */
		void setSleepingEnabled(bool enabled);

		/** Sets the linear factor (0 disables motion on an axis entirely)
			@param factor The factor in the form of a vector */
		void setLinearFactor(Vector3 factor);

		/** Sets the angular factor (0 disables rotation on an axis entirely)
			@param factor The factor in the form of a vector */
		void setAngularFactor(Vector3 factor);

		/** Sets whether or not the body is kinematic
			@param kinematic whether or not the body is to be kinematic */
		void setKinematic(bool kinematic);	

		/** Pulls this object out of the simulation world */
		virtual void removeFromSimulation();

		/** Adds this object back into the physics world */
		virtual void addToSimulation();

		/** Cleans this object up */
		virtual void destroyObject();

	private:

		btRigidBody* mBody;
		Vector3 mPosition[2];
		Quaternion mOrientation[2];

	};
}

#endif
