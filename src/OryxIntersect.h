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

#ifndef ORYX_INTERSECT_H
#define ORYX_INTERSECT_H

#include "Oryx.h"
#include "OryxMatrix4.h"
#include "OryxRay.h"
#include "OryxVector3.h"
#include "OryxBox.h"

namespace Oryx
{
	/** Utility class for finding simple shape intersections */
	class Intersect
	{
	public:

		//static bool intersects(const Sphere& sph1,const Sphere& sph2);

		/** Gets whether or not a Ray and Box intersect
		 *		@param ray The Ray
		 *		@param Box The Box 
		 *		@return Whether or not they intersect */
		static bool intersects(const Ray& ray,const Box& box);

		//static bool intersects(const Ray& ray,const AxisAlignedBox& aabox);
	};
}

#endif
