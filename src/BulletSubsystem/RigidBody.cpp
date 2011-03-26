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

#include "RigidBody.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	RigidBody::RigidBody(btDynamicsWorld* world, btRigidBody* body, PhysicsShape* shape)
		:CollisionObject(world,body,shape)
	{
		mBody = body;
	}
	//-----------------------------------------------------------------------

	void RigidBody::update(bool frame, Real interpolation, Vector3 gravity = Vector3::ZERO)
	{
		mInterpolation = interpolation;

		/*if(gravity!=Vector3::ZERO)
		{
			mBody->activate();
			mBody->setGravity(convertBullet(gravity));
		}*/

		mPosition[1] = mPosition[0];
		mPosition[0] = convertBullet(mBody->getCenterOfMassPosition());

		mOrientation[1] = mOrientation[0];
		mOrientation[0] = convertBullet(mBody->getOrientation());
	}
	//-----------------------------------------------------------------------

	Vector3 RigidBody::getPosition()
	{
		return mPosition[0] * mInterpolation + mPosition[1] * (1-mInterpolation);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setPosition(Vector3 position)
	{
		btTransform trans = mBody->getCenterOfMassTransform();
		trans.setOrigin(convertBullet(position));
		mBody->setCenterOfMassTransform(trans);
		mPosition[0] = position;
		mPosition[1] = position;
	}
	//-----------------------------------------------------------------------
	
	Quaternion RigidBody::getOrientation()
	{
		return mOrientation[0];// TODO: Slerp!
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setOrientation(Quaternion orientation)
	{
		btTransform trans = mBody->getCenterOfMassTransform();
		trans.setRotation(convertBullet(orientation));
		mBody->setCenterOfMassTransform(trans);
		mOrientation[0] = orientation;
		mOrientation[1] = orientation;
	}
	//-----------------------------------------------------------------------
	
	btRigidBody* RigidBody::getRigidBody()
	{
		return mBody;
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::addForce(Vector3 force,Vector3 pos)
	{
		mBody->applyForce(convertBullet(force),convertBullet(pos));
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::addImpulse(Vector3 impulse,Vector3 pos)
	{
		mBody->applyImpulse(convertBullet(impulse),convertBullet(pos));
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setVelocity(Vector3 velocity)
	{
		mBody->setLinearVelocity(convertBullet(velocity));
	}
	//-----------------------------------------------------------------------
	
	Vector3 RigidBody::getVelocity()
	{
		return convertBullet(mBody->getLinearVelocity());
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setMass(float mass)
	{
		removeFromSimulation();
		btVector3 localInertia(0,0,0);
		mBody->getCollisionShape()->calculateLocalInertia(mass,localInertia);
		mBody->setMassProps(mass,localInertia);
		addToSimulation();
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::wakeup()
	{
		mBody->setActivationState(ACTIVE_TAG);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::toSleep()
	{
		mBody->setActivationState(ISLAND_SLEEPING);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setSleepingEnabled(bool enabled)
	{
		if(enabled)
			if(mBody->getActivationState() == DISABLE_DEACTIVATION)
				wakeup();
		else
			mBody->setActivationState(DISABLE_DEACTIVATION);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setLinearFactor(Vector3 factor)
	{
		mBody->setLinearFactor(convertBullet(factor));
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setAngularFactor(Vector3 factor)
	{
		mBody->setAngularFactor(convertBullet(factor));
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::setKinematic(bool kinematic)
	{
		removeFromSimulation();
		if(kinematic)
		{
			mBody->setMassProps(0.f,btVector3(0,0,0));
			mBody->setCollisionFlags(mBody->getCollisionFlags() | 
				btCollisionObject::CF_KINEMATIC_OBJECT);			
		}
		else
		{
			btVector3 localInertia(0,0,0);
			// TODO save mass somewhere..
			mBody->getCollisionShape()->calculateLocalInertia(10.f,localInertia);
			mBody->setMassProps(10.f,localInertia);
			mBody->setCollisionFlags(mBody->getCollisionFlags() ^ 
				btCollisionObject::CF_KINEMATIC_OBJECT);	
		}
		addToSimulation();
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::removeFromSimulation()
	{
		mDynamicsWorld->removeRigidBody(mBody);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::addToSimulation()
	{
		mDynamicsWorld->addRigidBody(mBody);
	}
	//-----------------------------------------------------------------------
	
	void RigidBody::destroyObject()
	{
		removeFromSimulation();
	}
	//-----------------------------------------------------------------------
}
