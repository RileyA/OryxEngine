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

#ifndef ORYX_RAY_H
#define ORYX_RAY_H

#include "Oryx.h"
#include "OryxVector3.h"

namespace Oryx
{
	/** Representation of a 3D Ray */
	class ORYX_EXPORT Ray
	{
	public:	

		Vector3 origin;
		Vector3 direction;
		Real length;		
		
		/** Constructor from a point to a direction
		 *		@param */
		Ray(Vector3 origin_=Vector3(0,0,0), Vector3 direction_=Vector3(0,0,0), float length_=0.f)
			:origin(origin_),direction(direction_),length(length_)
		{
			direction.normalize();
		}

		/** Makes the ray a finite line from p1 to p2
		 *		@param p1 the first point
		 *		@param p2 the second point */
		void line(Vector3 p1,Vector3 p2)
		{
			origin = p1;
			direction = p2-p1;
			length = direction.normalize();
		}
	};
}

#endif
