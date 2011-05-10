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

#ifndef JOINT_H
#define JOINT_H

#include "Oryx.h"
#include "CollisionObject.h"

class btTypedConstraint;

namespace Oryx
{
	class Joint
	{
	public:
		
		Joint(btTypedConstraint* joint, CollisionObject* obj1, CollisionObject* obj2)
			:mJoint(joint),mObject1(obj1),mObject2(obj2){}

		virtual ~Joint();

		CollisionObject* getObject1(){return mObject1;}
		CollisionObject* getObject2(){return mObject2;}

	private:

		btTypedConstraint* mJoint;
		CollisionObject* mObject1;
		CollisionObject* mObject2;

	};
}

#endif
