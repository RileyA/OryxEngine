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

	class Box
	{
	public:

		Box()
			:mCenter(0,0,0),mScale(0,0,0),mOrientation(0,0,0,1)
		{}
		Box(Vector3 center, Vector3 scale, Quaternion orientation)
			:mCenter(center),mScale(scale),mOrientation(orientation)
		{}

		bool intersects(Ray r);

	//protected:

		Vector3 mCenter;
		Vector3 mScale;
		Quaternion mOrientation;

	};
}

#endif
