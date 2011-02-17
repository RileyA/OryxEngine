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
#include "PhysicsObject.h"
#include "Bulletdllmain.h"
#include "BulletConversions.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	PhysicsObject::PhysicsObject(btRigidBody* actor,btDynamicsWorld* dynWorld,bool c)
		:mReadyForDelete(0),mUnique(0),mCompound(c)
	{
		mDynamicsWorld = dynWorld;
		mActor = actor;
		mRigidBody = true;
		mPos[0] = Vector3(mActor->getWorldTransform().getOrigin().x(),
				mActor->getWorldTransform().getOrigin().y(),
				mActor->getWorldTransform().getOrigin().z());
		mPos[1] = mPos[0];
		mOrient[0] = Quaternion(1,0,0,0);
		mOrient[1] = Quaternion(1,0,0,0);
		gravLast = Vector3(0,0,0);
		setUserData(0);
	}

	//-----------------------------------------------------------------------
	PhysicsObject::PhysicsObject(btCollisionObject* actor,btDynamicsWorld* dynWorld,bool c)
		:mReadyForDelete(0),mUnique(0),mCompound(c)
	{
		mActor = 0;
		mDynamicsWorld = dynWorld;
		mActor = actor;
		mRigidBody = false;
		mPos[0] = Vector3(mActor->getWorldTransform().getOrigin().x(),
				mActor->getWorldTransform().getOrigin().y(),
				mActor->getWorldTransform().getOrigin().z());
		mPos[1] = mPos[0];
		mOrient[0] = Quaternion(1,0,0,0);
		mOrient[1] = Quaternion(1,0,0,0);
		setUserData(0);
	}

	//-----------------------------------------------------------------------
	PhysicsObject::~PhysicsObject()
	{
		if(mRigidBody)
		{
			mDynamicsWorld->removeRigidBody(dynamic_cast<btRigidBody*>(mActor));
		}
		else
		{
			mDynamicsWorld->removeCollisionObject(mActor);
		}

		if(mUnique)
		{
			btTriangleMesh* tr = 0;
			if(mActor->getCollisionShape()->getShapeType()==21)
			{
				tr = dynamic_cast<btTriangleMesh*>(dynamic_cast<btBvhTriangleMeshShape*>(
					mActor->getCollisionShape())->getMeshInterface());
			}
			delete mActor->getCollisionShape();
			if(tr)
				delete tr;// clear triangle data!
		}
		
		mActor = 0;
	}

	//-----------------------------------------------------------------------
	btRigidBody* PhysicsObject::getActor()
	{
		return dynamic_cast<btRigidBody*>(mActor);
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setPosition(Vector3 pos)
	{
		if(mRigidBody)
		{
			btTransform trans = dynamic_cast<btRigidBody*>(mActor)->getCenterOfMassTransform();
			trans.setOrigin(btVector3(pos.x,pos.y,pos.z));
			dynamic_cast<btRigidBody*>(mActor)->setCenterOfMassTransform(trans);
		}
		else
		{
			btTransform trans = mActor->getWorldTransform();
			trans.setOrigin(btVector3(pos.x,pos.y,pos.z));
			mActor->setWorldTransform(trans);
		}
		mPos[0] = pos;
		mPos[1] = pos;
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setOrientation(Quaternion ori)
	{
		if(mRigidBody)
		{
			btTransform trans = dynamic_cast<btRigidBody*>(mActor)->getCenterOfMassTransform();
			trans.setRotation(btQuaternion(ori.x,ori.y,ori.z,ori.w));
			dynamic_cast<btRigidBody*>(mActor)->setCenterOfMassTransform(trans);
		}
		else
		{
			btTransform trans = mActor->getWorldTransform();
			trans.setRotation(btQuaternion(ori.x,ori.y,ori.z,ori.w));
			mActor->setWorldTransform(trans);
		}
	}

	//-----------------------------------------------------------------------
	Vector3 PhysicsObject::getPosition()
	{
		// pos[0] is the 'current' pos, [1] is the previous
		return mPos[0]*mInterpolation+mPos[1]*(1-mInterpolation);
	}

	//-----------------------------------------------------------------------
	Quaternion PhysicsObject::getOrientation()
	{
		// TOBEFIXED add interpolation here (once slerp is implemented?)
		return mOrient[0];
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::addForce(Vector3 force,Vector3 pos)
	{
		dynamic_cast<btRigidBody*>(mActor)->applyForce(btVector3(force.x,force.y,force.z),btVector3(pos.x,pos.y,pos.z));
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::addImpulse(Vector3 impulse,Vector3 pos)
	{
		dynamic_cast<btRigidBody*>(mActor)->applyImpulse(btVector3(impulse.x,impulse.y,impulse.z),btVector3(pos.x,pos.y,pos.z));
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setVelocity(Vector3 velocity)
	{
		dynamic_cast<btRigidBody*>(mActor)->setLinearVelocity(btVector3(velocity.x,velocity.y,velocity.z));
	}

	//-----------------------------------------------------------------------
	Vector3 PhysicsObject::getVelocity()
	{
		return Vector3(dynamic_cast<btRigidBody*>(mActor)->getLinearVelocity().x(),
			dynamic_cast<btRigidBody*>(mActor)->getLinearVelocity().y(),
			dynamic_cast<btRigidBody*>(mActor)->getLinearVelocity().z());
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setMass(float mass)
	{
		if(mRigidBody)
		{
			// we have to remove it from the world and add it back:
			mDynamicsWorld->removeRigidBody(dynamic_cast<btRigidBody*>(mActor));
			btVector3 localInertia(0,0,0);
			mActor->getCollisionShape()->calculateLocalInertia(10.f,localInertia);
			dynamic_cast<btRigidBody*>(mActor)->setMassProps(10.f,localInertia);
			mDynamicsWorld->addRigidBody(dynamic_cast<btRigidBody*>(mActor));
		}
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::wakeup()
	{
		mActor->setActivationState(ACTIVE_TAG);
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::toSleep()
	{
		mActor->setActivationState(ISLAND_SLEEPING);
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setSleepingEnabled(bool enabled)
	{
		if(enabled)
		{
			// only set it is its disabled already
			if(mActor->getActivationState()==DISABLE_DEACTIVATION)
			{
				mActor->setActivationState(ACTIVE_TAG);
			}
		}
		else
		{
			mActor->setActivationState(DISABLE_DEACTIVATION);
		}
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setLinearFactor(Vector3 factor)
	{
		dynamic_cast<btRigidBody*>(mActor)->setLinearFactor(btVector3(factor.x,factor.y,factor.z));
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setAngularFactor(Vector3 factor)
	{
		dynamic_cast<btRigidBody*>(mActor)->setAngularFactor(btVector3(factor.x,factor.y,factor.z));
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setCollisionGroup(short group)
	{
		mActor->getBroadphaseHandle()->m_collisionFilterGroup = group;
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setCollisionMask(short mask)
	{
		mActor->getBroadphaseHandle()->m_collisionFilterMask = mask;
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setKinematic(bool kinematic)
	{
		if(mRigidBody)
		{
			if(kinematic)
			{
				mDynamicsWorld->removeRigidBody(dynamic_cast<btRigidBody*>(mActor));
				dynamic_cast<btRigidBody*>(mActor)->setMassProps(0,btVector3(0,0,0));
				mActor->setCollisionFlags(mActor->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
				mDynamicsWorld->addRigidBody(dynamic_cast<btRigidBody*>(mActor));
			}
			else
			{
				mDynamicsWorld->removeRigidBody(dynamic_cast<btRigidBody*>(mActor));
				btVector3 localInertia(0,0,0);
				dynamic_cast<btRigidBody*>(mActor)->getCollisionShape()->calculateLocalInertia(10.f,localInertia);
				dynamic_cast<btRigidBody*>(mActor)->setMassProps(10.f,localInertia);
				mActor->setCollisionFlags(mActor->getCollisionFlags() ^ btCollisionObject::CF_KINEMATIC_OBJECT);
				mDynamicsWorld->addRigidBody(dynamic_cast<btRigidBody*>(mActor));
			}
		}
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::update(bool frame,float interpolation,Vector3 gravity)
	{
		mInterpolation = interpolation;
		if(mRigidBody)
		{
			if(frame&&!mActor->isStaticObject())
			{
				// only set if gravity has changed (since it may keep the actor awake)
				if(gravLast!=gravity)
				{
					mActor->activate(true);
					dynamic_cast<btRigidBody*>(mActor)->setGravity(btVector3(gravity.x*1.75f,gravity.y*1.75f,gravity.z*1.75f));
				}
				
				gravLast = gravity;
				mPos[1] = mPos[0];
				mPos[0] = Vector3(dynamic_cast<btRigidBody*>(mActor)->getCenterOfMassPosition().x(),
					dynamic_cast<btRigidBody*>(mActor)->getCenterOfMassPosition().y(),
					dynamic_cast<btRigidBody*>(mActor)->getCenterOfMassPosition().z());
				mOrient[1] = mOrient[0];
				mOrient[0] = Quaternion(dynamic_cast<btRigidBody*>(mActor)->getOrientation().x(),
					dynamic_cast<btRigidBody*>(mActor)->getOrientation().y(),
					dynamic_cast<btRigidBody*>(mActor)->getOrientation().z(),
					dynamic_cast<btRigidBody*>(mActor)->getOrientation().w());
			}
		}
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::setUserData(void* data)
	{
		// pass it right along to bullet
		mActor->setUserPointer(data);
	}

	//-----------------------------------------------------------------------
	void* PhysicsObject::getUserData()
	{
		return mActor->getUserPointer();
	}

	//-----------------------------------------------------------------------
	bool PhysicsObject::readyForDelete()
	{
		return mReadyForDelete;
	}

	//-----------------------------------------------------------------------
	void PhysicsObject::_kill()
	{
		mReadyForDelete = true;
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::setUniqueCollisionShape(bool unique)
	{
		mUnique = unique;
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::setCompound(bool compound)
	{
		mCompound = compound;	
	}

	btCollisionShape* PhysicsObject::getShape(int index)
	{
		if(!mCompound)
			return mActor->getCollisionShape();
		else
		{
			btCompoundShape* cs = dynamic_cast<btCompoundShape*>(mActor->getCollisionShape());
			return cs->getChildShape(index);
		}
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::removeShape(btCollisionShape* shape)
	{
		if(mCompound)
			dynamic_cast<btCompoundShape*>(mActor->getCollisionShape())->removeChildShape(shape);
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::removeShapeByIndex(int shape)
	{
		if(mCompound)
			dynamic_cast<btCompoundShape*>(mActor->getCollisionShape())
				->removeChildShapeByIndex(shape);
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::removeAllShapes()
	{
		if(!mCompound)
			return;
		btCompoundShape* c = dynamic_cast<btCompoundShape*>(mActor->getCollisionShape());
		while(c->getNumChildShapes()>0)
			c->removeChildShapeByIndex(0);
	}
	//-----------------------------------------------------------------------	
	void PhysicsObject::remove()
	{
		mDynamicsWorld->removeCollisionObject(mActor);
	}
	void PhysicsObject::reset()
	{
		mDynamicsWorld->addCollisionObject(mActor);
	}
	//-----------------------------------------------------------------------
	
	void PhysicsObject::addShape(btCollisionShape* shape,Vector3 position,Quaternion orientation)
	{
		if(mCompound)
		{
			shape->setMargin(0.f);
			dynamic_cast<btCompoundShape*>(mActor->getCollisionShape())->addChildShape(
				btTransform(convertBullet(orientation),convertBullet(position)),shape);
		}
	}
}
