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

#include "PhysicsBoxShape.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	PhysicsBoxShape::PhysicsBoxShape(Vector3 extents)
		:PhysicsShape(false,"BOX_"+StringUtils::toString(extents.x)+"_"+
			StringUtils::toString(extents.y)+"_"+StringUtils::toString(extents.z))
	{
		mShape = new btBoxShape(convertBullet(extents));
	}
}
