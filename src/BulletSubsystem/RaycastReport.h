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
#include "Oryx3DMath.h"

namespace Oryx
{
	/** A simple struct representing the results fo a raycast test */
	struct RaycastReport
	{
		/** Whether or not this raycast hit anything, if not everything else 
		 *		will be uninitialized	 */
		bool hit;

		/** The normal of the impact point */
		Vector3 normal;

		/** The impact point */
		Vector3 position;

		/** The collision group of the hit object */
		short group;

		/** The userdata pointer of the hit object */
		void* userData;
		
		RaycastReport()
		{
			hit = false;
		}

		RaycastReport(Vector3 n, Vector3 p, short hitGroup=0, void* _userData=0)
		{
			hit = true;
			normal = n;
			position = p;
			group = hitGroup;
			userData = _userData;
		}
	};

	/** Gives info on the result of a convex sweep test */
	struct SweepReport
	{
		/** Whether or not this sweep hit anything, if not everything else 
		 *		will be uninitialized	 */
		bool hit;

		/** The normal of the impact point */
		Vector3 normal;

		/** The impact point */
		Vector3 position;

		/** The collision group of the hit object */
		short group;

		/** The userdata pointer of the hit object */
		void* userData;

		/** The fraction of the desired move reached */
		float hitFraction;

		SweepReport()
		{
			hit = false;
		}

		SweepReport(Vector3 n, Vector3 p, float moveFraction, short hitGroup=0, void* _userData=0)
		{
			hit = true;
			normal = n;
			position = p;
			group = hitGroup;
			hitFraction = moveFraction;
			userData = _userData;
		}	
	};
}
