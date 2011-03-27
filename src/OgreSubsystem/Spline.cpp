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

#include "OgreSimpleSpline.h"
#include "Spline.h"
#include "OgreConversions.h"

namespace Oryx
{
	Spline::Spline()
	{
		mSpline = new Ogre::SimpleSpline();
	}

	Spline::~Spline()
	{
		delete mSpline;
	}

	void Spline::addPoint(Vector3 p)
	{
		mSpline->addPoint(convertOgre(p));
	}

	Vector3 Spline::interpolate(Real t)
	{
		return convertOgre(mSpline->interpolate(t));
	}

	void Spline::setAutoCalc(bool calc)
	{
		mSpline->setAutoCalculate(calc);
	}

	void Spline::recalc()
	{
		mSpline->recalcTangents();
	}
}
