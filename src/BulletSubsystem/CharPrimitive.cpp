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

#include "CharPrimitive.h"
#include "BulletSubsystem.h"

namespace Oryx
{

	CharPrimitive::CharPrimitive(BulletSubsystem* bull,Vector3 pos)
		:mBullet(bull),mPosition(pos)
	{
		mSphere = mBullet->createSphereShape(RADIUS);
	}
	//-----------------------------------------------------------------------
	
	Vector3 CharPrimitive::move(Vector3 direction, Real distance, int maxDepth)
	{
		if(maxDepth <= 0)
			return Vector3::ZERO;
		
		Real castLength = distance + SKIN_WIDTH;
		SweepReport s = mBullet->sweep(mSphere, mPosition, direction, castLength,
			COLLISION_GROUP_3,COLLISION_GROUP_3);
		
		if(!s.hit)
			return direction * distance;
		else
		{
			Real travel = std::max(distance - (castLength - castLength * s.hitFraction),0.f);

			Vector3 slide = direction + s.normal * direction.dotProduct(s.normal * -1);
			// TODO: get rid of this?
			Plane pl = Plane(Vector3(0,1,0),0);
			slide = pl.projectVector(slide);

			return direction * travel + move(slide, distance - travel, maxDepth -1);
		}
	}
	//-----------------------------------------------------------------------
	
	void CharPrimitive::translate(Vector3 v)
	{
		mPosition += v;
	}
	//-----------------------------------------------------------------------
	
	Vector3 CharPrimitive::getPosition()
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
}
