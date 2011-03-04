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

#ifndef ORYX_PLANE_H
#define ORYX_PLANE_H

#include "Oryx.h"
#include "OryxMatrix3.h"
#include "OryxVector3.h"

namespace Oryx
{
	class ORYX_EXPORT Plane
	{
	public:
	
		Vector3 n;
		Real d;

		Plane()
			:n(Vector3::ZERO),d(0.f){}

		Plane(Vector3 normal, Real distance)
			:n(normal),d(distance){}

		Vector3 projectVector(const Vector3& p) const
		{
			// We know plane normal is unit length, so use simple method
			Matrix3 xform;
			xform[0][0] = 1.0f - n.x * n.x;
			xform[0][1] = -n.x * n.y;
			xform[0][2] = -n.x * n.z;
			xform[1][0] = -n.y * n.x;
			xform[1][1] = 1.0f - n.y * n.y;
			xform[1][2] = -n.y * n.z;
			xform[2][0] = -n.z * n.x;
			xform[2][1] = -n.z * n.y;
			xform[2][2] = 1.0f - n.z * n.z;
			return xform * p;
		}
	};
}

#endif
