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

#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "PhysicsObject.h"

namespace Oryx
{
	class ORYX_BULLET_EXPORT CharacterController : public PhysicsObject
	{
	public:

		CharacterController(btDynamicsWorld* w)
			:PhysicsObject(w){}
		
		virtual void update(bool frame, Real interpolation, Vector3 gravity) = 0;
		virtual Vector3 getPosition() = 0;
		virtual Quaternion getOrientation() = 0;

		virtual void jump(Real strength) = 0;

		virtual void setMoveVector(Vector3 move){mMove = move;}
		virtual void setMaxSpeed(Real max){mMaxSpeed = max;}
		virtual void setMinSpeed(Real min){mMinSpeed = min;}
		virtual void setAcceleration(Real acc){mAcceleration = acc;}

		virtual Real getMaxSpeed(){return mMaxSpeed;}
		virtual Real getMinSpeed(){return mMinSpeed;}
		virtual Real getAcceleration(){return mAcceleration;}
		virtual Vector3 getMoveVector(){return mMove;}

	protected:

		Real mMaxSpeed;
		Real mMinSpeed;
		Real mAcceleration; 
		Vector3 mMove;

	private:

	};
}

#endif
