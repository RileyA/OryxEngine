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
	struct RaycastReport
	{
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

		bool hit;
		Vector3 normal;
		Vector3 position;
		short group;
		void* userData;
	};
}
