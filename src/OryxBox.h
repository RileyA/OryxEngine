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

#ifndef ORYX_BOX_H
#define ORYX_BOX_H

#include "Oryx.h"
#include "OryxQuaternion.h"
#include "OryxVector3.h"

namespace Oryx
{
	class Ray;

	/** A representation of an oriented 3d box */
	class Box
	{
	public:
		
		// Properties:
		Vector3 center;
		Vector3 scale;
		Quaternion orientation;

		/** Construct a box with scale, orientation and position */
		Box(Vector3 _center=Vector3(0,0,0), Vector3 _scale=Vector3(0,0,0),
			Quaternion _orientation=Quaternion::IDENTITY)
			:center(_center),scale(_scale),orientation(_orientation)
		{}

		/** Gets whether or not the passed ray intersects this box
		 *		@param Ray The ray to check with
		 *		@return Whether or not an intersection was found */
		bool intersects(const Ray& r) const;
	};
}

#endif
