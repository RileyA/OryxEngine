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

namespace Ogre
{
	class SimpleSpline;
}

namespace Oryx
{
	class Spline
	{
	public:

		Spline();
		~Spline();

		void addPoint(Vector3 p);
		Vector3 interpolate(Real t);

		void setAutoCalc(bool calc);
		void recalc();

	private:
	
		Ogre::SimpleSpline* mSpline;

	};
}
