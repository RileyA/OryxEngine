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

#ifndef BULLET_PHYSICSOBJECT_H
#define BULLET_PHYSICSOBJECT_H

#include "Oryx.h"
#include "Oryx3DMath.h"

class btDynamicsWorld;

namespace Oryx
{
	/** An abstract representation of a physics object */
	class PhysicsObject
	{
	public:

		/** Constructor */
		PhysicsObject(btDynamicsWorld* world);

		virtual ~PhysicsObject(){};

		/** Updates this object
		 *		@param frame Whether or not this is a new frame 
		 *		@param interpolation The interpolation value 
		 *		@param gravity The current gravity */
		virtual void update(bool frame, Real interpolation, Vector3 gravity) = 0;

		/** Returns whether or not this object is ready to be deleted */
		bool readyForDelete();

		/** Gets this objects position
		 *		@remarks This will probably be an interpolated position, due to 
		 *			fixed timestepping */
		virtual Vector3 getPosition() = 0;

		/** Get the orientation of this object
		 *		@remarks This will probably be an interpolated position, due to 
		 *			fixed timestepping */	
		virtual Quaternion getOrientation() = 0;

		/** Makes this object ready for deletion by the BulletSubsystem */
		void _kill();
		
	protected:
		
		/** Pointer to the physics world */
		btDynamicsWorld* mDynamicsWorld;

	private:

		/** Whether or not this object is ready for deletion */
		bool mReadyForDelete;

	};
}

#endif
