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

#include "Oryx.h"
#include "OryxIntersect.h"

namespace Oryx
{
	bool Intersect::intersects(const Ray& ray,const Box& box)
	{
		// Put line in box space	
		Matrix4 mat;
		mat.makeTransform(box.mCenter,Vector3(1,1,1),box.mOrientation);
		Matrix4 imat = mat.inverse();
		Vector3 p1 = imat*ray.origin;
		Vector3 p2 = imat*(ray.origin+(ray.direction*ray.length));

		Vector3 mid = (p1+p2)*0.5f;
		Vector3 l = p1-mid;
		Vector3 lext = Vector3(fabs(l.x),fabs(l.y),fabs(l.z));

		// Use Separating Axis Test
		// Separation vector from box center to line center is LMid, since the line is in box space
		if ( fabs( mid.x ) > box.mScale.x + lext.x ) return false;
		if ( fabs( mid.y ) > box.mScale.y + lext.y ) return false;
		if ( fabs( mid.z ) > box.mScale.z + lext.z ) return false;
		// Crossproducts of line and each axis
		if ( fabs( mid.y * l.z - mid.z * l.y)  >  (box.mScale.y * lext.z + box.mScale.z * lext.y) ) 
			return false;
		if ( fabs( mid.x * l.z - mid.z * l.x)  >  (box.mScale.x * lext.z + box.mScale.z * lext.x) ) 
			return false;
		if ( fabs( mid.x * l.y - mid.y * l.x)  >  (box.mScale.x * lext.y + box.mScale.y * lext.x) ) 
			return false;
		// No separating axis, the line intersects
		return true;
	}
}
