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

#include "PhysicsCompoundShape.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	PhysicsCompoundShape::PhysicsCompoundShape()
		:PhysicsShape(false,"NULL")
	{
		mShape = new btCompoundShape();
	}
	//-----------------------------------------------------------------------

	PhysicsCompoundShape::~PhysicsCompoundShape()
	{
		for(std::vector<PhysicsShape*>::iterator it = mShapes.begin();
			it!=mShapes.end(); ++it)
		{
			(*it)->removeUser();
		}
		mShapes.clear();
	}
	//-----------------------------------------------------------------------

	btCompoundShape* PhysicsCompoundShape::getCompound()
	{
		return dynamic_cast<btCompoundShape*>(mShape);
	}
	//-----------------------------------------------------------------------

	PhysicsShape* PhysicsCompoundShape::getShape(size_t index)
	{
		return index < mShapes.size() ? mShapes[index] : 0;
	}
	//-----------------------------------------------------------------------

	void PhysicsCompoundShape::addShape(PhysicsShape* shape, Vector3 pos,Quaternion orientation)
	{
		mShapes.push_back(shape);
		mShapes.back()->addUser();
		getCompound()->addChildShape(btTransform(convertBullet(orientation),
			convertBullet(pos)),shape->getBtShape());
	}
	//-----------------------------------------------------------------------
	
	void PhysicsCompoundShape::removeShape(PhysicsShape* shape)
	{
		getCompound()->removeChildShape(shape->getBtShape());

		for(std::vector<PhysicsShape*>::iterator it = mShapes.begin();
			it!=mShapes.end(); ++it)
		{
			if(shape==(*it))
			{
				(*it)->removeUser();
				it = mShapes.erase(it);
			}
		}
	}
	//-----------------------------------------------------------------------
	
	void PhysicsCompoundShape::removeShapeByIndex(size_t shape)
	{
		getCompound()->removeChildShapeByIndex(shape);
		mShapes[shape]->removeUser();
		if(mShapes[shape]->isTemporary() && mShapes[shape]->getNumUsers() <= 0)
			delete mShapes[shape];
		mShapes.erase(mShapes.begin()+shape);
	}
	//-----------------------------------------------------------------------
	
	void PhysicsCompoundShape::removeAllShapes()
	{
		while(getCompound()->getNumChildShapes() > 0)
			getCompound()->removeChildShapeByIndex(0);

		while(mShapes.size()>0)
		{
			mShapes.back()->removeUser();
			mShapes.pop_back();
		}
	}
	//-----------------------------------------------------------------------
}
