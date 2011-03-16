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

#include "BulletSubsystem.h"
#include "QuantaController.h"

namespace Oryx
{
	QuantaController::QuantaController(BulletSubsystem* bullet,Vector3 startPos)
		:CharacterController(bullet->getWorld())
	{
		for(int i = 0; i < NUM_SPHERES; ++i)
			mComponents.push_back(new CharPrimitive(bullet,startPos+Vector3(0,0.375*i,0)));
	}
	//-----------------------------------------------------------------------
	
	QuantaController::~QuantaController()
	{
		for(int i = 0; i < NUM_SPHERES; ++i)
			delete mComponents[i];
	}
	//-----------------------------------------------------------------------
	
	Vector3 QuantaController::getPosition()
	{
		return mPosition[1]*mInterpolation + mPosition[0]*(1-mInterpolation);
	}
	//-----------------------------------------------------------------------
	
	Quaternion QuantaController::getOrientation()
	{
		return Quaternion::IDENTITY;
	}
	//-----------------------------------------------------------------------
	
	void QuantaController::update(bool frame, Real interpolation, Vector3 gravity)
	{
		mInterpolation = interpolation;

		if(frame)
		{
			mPosition[0] = mPosition[1];
			move(Vector3(0,-1,0),0.1f);// gravity
			move(mMove,0.05f,true);    // motion
			mPosition[1] = mComponents[0]->getPosition();
		}
	}
	//-----------------------------------------------------------------------
	
	void QuantaController::move(Vector3 d, Real dist, bool slide)
	{
		Vector3 minMove = Vector3(100,100,100);
		for(int i = 0;i < NUM_SPHERES; ++i)
		{
			Vector3 delta = mComponents[i]->move(d,dist,slide?5:1);
			if(delta.squaredLength() < minMove.squaredLength())
				minMove = delta;
		}

		for(int i = 0;i < NUM_SPHERES; ++i)
			mComponents[i]->translate(minMove);
	}
}