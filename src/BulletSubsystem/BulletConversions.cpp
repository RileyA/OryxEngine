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

#include "BulletConversions.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	Vector3 convertBullet(btVector3 v)
	{
		return Vector3(v.getX(),v.getY(),v.getZ());
	}

	btVector3 convertBullet(Vector3 v)
	{
		return btVector3(v.x,v.y,v.z);
	}

	Quaternion convertBullet(btQuaternion q)
	{
		return Quaternion(q.getAxis().getX(),q.getAxis().getY(),q.getAxis().getZ(),q.getAngle());
	}

	btQuaternion convertBullet(Quaternion q)
	{
		return btQuaternion(q.x,q.y,q.z,q.w);
	}
}
