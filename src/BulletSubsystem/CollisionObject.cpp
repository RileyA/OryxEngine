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

#include "CollisionObject.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	CollisionObject::CollisionObject(btDynamicsWorld* world, btCollisionObject* obj,
		PhysicsShape* shape)
		:PhysicsObject(world),mShape(shape),mObject(obj),mInterpolation(0.f)
	{
		setUserData(0);
		mShape->addUser();
	}
	//-----------------------------------------------------------------------
	
	CollisionObject::~CollisionObject()
	{
		destroyObject();
		mShape->removeUser();
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::update(bool frame, Real interpolation, Vector3 gravity)
	{
		mInterpolation = interpolation;
	}
	//-----------------------------------------------------------------------
	
	Vector3 CollisionObject::getPosition()
	{
		return convertBullet(mObject->getWorldTransform().getOrigin());
	}
	//-----------------------------------------------------------------------

	void CollisionObject::setPosition(Vector3 position)
	{
		btTransform trans = mObject->getWorldTransform();
		trans.setOrigin(convertBullet(position));
		mObject->setWorldTransform(trans);
	}
	//-----------------------------------------------------------------------
	
	Quaternion CollisionObject::getOrientation()
	{
		return convertBullet(mObject->getWorldTransform().getRotation());
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::setOrientation(Quaternion orientation)
	{
		btTransform trans = mObject->getWorldTransform();
		trans.setRotation(convertBullet(orientation));
		mObject->setWorldTransform(trans);
	}
	//-----------------------------------------------------------------------

	btCollisionObject* CollisionObject::getCollisionObject()
	{
		return mObject;
	}
	//-----------------------------------------------------------------------

	PhysicsShape* CollisionObject::getShape()
	{
		return mShape;
	}
	//-----------------------------------------------------------------------

	void CollisionObject::setCollisionGroup(short group)
	{
		mObject->getBroadphaseHandle()->m_collisionFilterGroup = group;
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::setCollisionMask(short mask)
	{
		mObject->getBroadphaseHandle()->m_collisionFilterMask = mask;
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::removeFromSimulation()
	{
		mDynamicsWorld->removeCollisionObject(mObject);
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::addToSimulation()
	{
		mDynamicsWorld->addCollisionObject(mObject);
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::setUserData(void* data)
	{
		mObject->setUserPointer(data);
	}
	//-----------------------------------------------------------------------
	
	void* CollisionObject::getUserData()
	{
		return mObject->getUserPointer();
	}
	//-----------------------------------------------------------------------
	
	void CollisionObject::destroyObject()
	{
		mDynamicsWorld->removeCollisionObject(mObject);
	}
	//-----------------------------------------------------------------------
}
