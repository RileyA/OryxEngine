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

#ifndef ORYX_SPHERE_H
#define ORYX_SPHERE_H

#include "OryxVector3.h"
#include "OryxRay.h"

namespace Oryx
{
	class Sphere
	{
	public:

		Real radius;
		Vector3 center;

		bool intersects(Ray& ray);
	
		Sphere(Real rad = 1.f, Vector3 cen = Vector3::ZERO)
		{
			radius = rad;
			center = cen;
		}
	};
}

#endif
