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

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Oryx.h"
#include "Oryx3DMath.h"

class btDynamicsWorld;
class btRigidBody;
class btCollisionObject;
class btCollisionShape;

namespace Oryx
{
	/** A physics object (either a static or a rigid body)
		this class functions as a wrapper for bullet functions 
		and does automatic interpolation. */
	class PhysicsObject
	{
	public:

		PhysicsObject(btRigidBody* actor,btDynamicsWorld* dynWorld,bool compound=false);
		PhysicsObject(btCollisionObject* actor,btDynamicsWorld* dynWorld,bool compound=false);
		~PhysicsObject();

		/** Returns a pointer the bullet rigid body 
			@returns a pointer to the bullet rigid body */
		btRigidBody* getActor();

		/** Sets the object's position
			@param pos the desired position */
		void setPosition(Vector3 pos);

		/** Sets the object's orientation
			@param pos the desired orientation */
		void setOrientation(Quaternion ori);

		/** Gets the object's position
			@returns the object's position */
		Vector3 getPosition();

		/** Gets the object's orientation
			@returns the object's orientation */
		Quaternion getOrientation();

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

		/** Sets the object's collision group (determines which objects will collide with it)
			@param mask The collision group */
		void setCollisionGroup(short group);

		/** Sets the object's collision mask (what collision groups it will collide with)
			@param mask The collision mask */
		void setCollisionMask(short mask);

		/** Sets whether or not the body is kinematic
			@param kinematic whether or not the body is to be kinematic */
		void setKinematic(bool kinematic);

		/** Internal update function
			@param frame Is it a new simulation frame 
			@param interpolation The current interpolation factor 
			@param gravity The current simulation gravity */
		void update(bool frame,float interpolation,Vector3 gravity);

		/** Sets the user pointer, which can be retrieved with getUserData()
			@param data some data in the form of a void pointer */
		void setUserData(void* data);

		/** Gets the user pointer
			@returns void pointer to user data */
		void* getUserData();

		/** Returns whether or not the object will be deleted next frame */
		bool readyForDelete();

		/** Internal function for killing a physics object
			@remarks This actually just tells the manager to delete it at the next available frame,
						rather than immediately deleting it. */
		void _kill();

		/** Tells this object that it's collision shape is unique, and should be deleted
		 *		upon its destruction to save memory */
		void setUniqueCollisionShape(bool unique);
		void setCompound(bool compound);

		btCollisionShape* getShape(int index=0);

		void removeShape(btCollisionShape* shape);
		void removeShapeByIndex(int shape);
		void removeAllShapes();

		void remove();
		void reset();

		void addShape(btCollisionShape* shape,Vector3 position=Vector3::ZERO,
			Quaternion orientation=Quaternion::IDENTITY);

	protected:

		// A pointer to the dynamics world this object belongs to
		btDynamicsWorld* mDynamicsWorld;

		// The Bullet Object (may be a rigid body or a plain collision object)
		btCollisionObject* mActor;

		// Whether this actor is a rigid body or a plain collision object
		bool mRigidBody;

		// The last recorded interpolation factor
		float mInterpolation;

		// Position data (1 prior frame is cached for interpolation purposes)
		Vector3 mPos[2];

		// Orientation data (1 prior frame is cached for interpolation purposes)
		Quaternion mOrient[2];

		// Whether or not this object is ready to be deleted by the PhysicsManager
		bool mReadyForDelete;

		// The last frames gravity (to avoid redundant setting of the object's gravity value)
		Vector3 gravLast;

		// Is this a unique object (should the collision shape remain cached, or be deleted
		// with this object?)
		bool mUnique;

		// Whether or not this is a compind shape (can have multiple shapes)
		bool mCompound;

	};
}

#endif
