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
	// borrowed from Ogre3D, which is under the MIT license
	bool Intersect::intersects(const Ray& ray,const Box& box)
	{
		// Put line in box space	
		Matrix4 mat;
		mat.makeTransform(box.center,Vector3(1,1,1),box.orientation);
		Matrix4 imat = mat.inverse();
		Vector3 p1 = imat*ray.origin;
		Vector3 p2 = imat*(ray.origin+(ray.direction*ray.length));

		Vector3 mid = (p1+p2)*0.5f;
		Vector3 l = p1-mid;
		Vector3 lext = Vector3(fabs(l.x),fabs(l.y),fabs(l.z));

		// Use Separating Axis Test
		// Separation vector from box center to line center is LMid, since the line is in box space
		if ( fabs( mid.x ) > box.scale.x + lext.x ) return false;
		if ( fabs( mid.y ) > box.scale.y + lext.y ) return false;
		if ( fabs( mid.z ) > box.scale.z + lext.z ) return false;
		// Crossproducts of line and each axis
		if ( fabs( mid.y * l.z - mid.z * l.y)  >  (box.scale.y * lext.z + box.scale.z * lext.y) ) 
			return false;
		if ( fabs( mid.x * l.z - mid.z * l.x)  >  (box.scale.x * lext.z + box.scale.z * lext.x) ) 
			return false;
		if ( fabs( mid.x * l.y - mid.y * l.x)  >  (box.scale.x * lext.y + box.scale.y * lext.x) ) 
			return false;
		// No separating axis, the line intersects
		return true;
	}
}
