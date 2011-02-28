//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "BulletSubsystem.h"
#include "OryxLogger.h"
#include "OryxTimeManager.h"

#include "OryxEngine.h"
#include "OryxState.h"
#include "OryxGameState.h"
#include "OryxEngineSubsystem.h"

#include "OryxColour.h"
#include "Oryx3DMath.h"
#include "OryxStringUtils.h"

#include "PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

namespace Oryx
{
    const size_t BulletSubsystem::mDependencyCount = 0;
	const String BulletSubsystem::mDependencies[1];// nothin'

    BulletSubsystem::BulletSubsystem()
        :EngineSubsystem(const_cast<String*>(mDependencies),mDependencyCount)
        ,mInitialized(0),mStarted(0){}
    //-----------------------------------------------------------------------

    BulletSubsystem::~BulletSubsystem()
    {
    }
    //-----------------------------------------------------------------------

    void BulletSubsystem::_init()
    {
        if(!mInitialized)
        {
			mInitialized = true;
            Logger::getPtr()->logMessage("Bullet Subsystem Initialized.");
        }
    }
    //-----------------------------------------------------------------------

    void BulletSubsystem::_deinit()
    {
        if(mInitialized)
        {
			if(mStarted)
				stopSimulation();
            mInitialized = false;
            Logger::getPtr()->logMessage("Bullet Subsystem Deinitialized.");
        }
    }
    //-----------------------------------------------------------------------

    void BulletSubsystem::_update(Real delta)
	{
		if(mStarted)
		{
			mAccumulation += delta;

			while(mAccumulation>=mTimeStep)
			{
				mDynamicsWorld->stepSimulation(mTimeStep,0);
				for(unsigned int i=0;i<mObjects.size();++i)
				{
					if(!mObjects[i]->readyForDelete())
						mObjects[i]->update(true,0,mGravity);
					else
					{
						delete mObjects[i];
						mObjects.erase(mObjects.begin()+i);
						--i;
					}
				}
				mAccumulation -= mTimeStep;
			}
			mInterpolation = mAccumulation/mTimeStep;
			for(unsigned int i=0;i<mObjects.size();++i)
				mObjects[i]->update(false,mInterpolation,mGravity);
		}
    }
    //-----------------------------------------------------------------------

    void BulletSubsystem::_endState()
    {

    }
    //-----------------------------------------------------------------------

    String BulletSubsystem::getName()
    {
        return String("BulletSubsystem");
    }
    //-----------------------------------------------------------------------

	Vector3 BulletSubsystem::getGravity()
	{
		return mGravity;
	}
	//-----------------------------------------------------------------------

	void BulletSubsystem::setGravity(Vector3 g)
	{
		mGravity = g;
	}
	//-----------------------------------------------------------------------
	
	void BulletSubsystem::startSimulation()
	{
		if(!mStarted)
		{
			mCollisionConfiguration = new btDefaultCollisionConfiguration();
			mDispatcher = new	btCollisionDispatcher(mCollisionConfiguration);
			mBroadphase = new btDbvtBroadphase();
			mSolver = new btSequentialImpulseConstraintSolver;
			mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher,mBroadphase,
				mSolver,mCollisionConfiguration);

			mDynamicsWorld->setGravity(btVector3(0,-1,0));
			mGravity = Vector3(0,-1,0);

			mTimeStep = 1.f/100.f;
			mAccumulation = 0.f;
			mInterpolation = 0.f;
			mStarted = true;
		}
	}
	//-----------------------------------------------------------------------	
	
	void BulletSubsystem::stopSimulation()
	{
		if(mStarted)
		{
			for(unsigned int i=0;i<mObjects.size();++i)
				delete mObjects[i];

			mObjects.clear();

			for (int i=mDynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
			{
				btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
					delete body->getMotionState();
				mDynamicsWorld->removeCollisionObject(obj);
				delete obj;
			}

			std::map<String,PhysicsShape*>::iterator iter = mShapes.begin();
			while(iter != mShapes.end())
			{
				btTriangleMesh* tr = 0;

				// TODO put this in trimesh's dtor...
				if(iter->second->getType() == PST_TRIMESH)
					tr = dynamic_cast<btTriangleMesh*>(dynamic_cast<btBvhTriangleMeshShape*>(
						iter->second->getBtShape())->getMeshInterface());

				if(tr)
					delete tr;// clear triangle data!

				delete iter->second;
				++iter;
			}

			mShapes.clear();

			delete mDynamicsWorld;
			delete mSolver;
			delete mBroadphase;
			delete mDispatcher;
			delete mCollisionConfiguration;	
			mStarted = false;
		}
	}
	//-----------------------------------------------------------------------

	RaycastReport BulletSubsystem::raycast(Vector3 origin,Vector3 direction,
			float length,short group,short mask)
	{
		direction.normalize();
		direction *= length;

		btCollisionWorld::ClosestRayResultCallback cb(convertBullet(origin), 
			convertBullet(origin+direction));
		
		cb.m_collisionFilterGroup = 65535^group;
		cb.m_collisionFilterMask = 65535^mask;

		mDynamicsWorld->rayTest(convertBullet(origin),
			convertBullet(origin+direction),cb);
		
		if(cb.hasHit())
		{
			return RaycastReport(convertBullet(cb.m_hitNormalWorld),
				convertBullet(cb.m_hitPointWorld),
				cb.m_collisionObject->getBroadphaseHandle()->m_collisionFilterGroup,
				cb.m_collisionObject->getUserPointer());
		}
		else
		{
			return RaycastReport();
		}	
	}
	//-----------------------------------------------------------------------

	PhysicsObject* BulletSubsystem::createStaticTrimesh(MeshData& d,Vector3 pos,String name)
	{
		PhysicsObject* p = createStatic(createTrimeshShape(d,name),pos);
		return p;
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createConvexHull(MeshData& d,Vector3 pos,float mass,String name)
	{
		PhysicsObject* p = createObject(createConvexShape(d,name),pos,mass);
		return p;
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createSphere(float radius,Vector3 pos,float mass)
	{
		return createObject(createSphereShape(radius),pos,mass);
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createCube(Vector3 scale,Vector3 pos,float mass)
	{
		return createObject(createBoxShape(scale),pos,mass);
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createCompound(Vector3 pos)
	{
		std::vector<PhysicsShape*> s;
		std::vector<Vector3> v;
		PhysicsObject* obj = createStatic(createCompoundShape(s,v),pos);
		return obj;
	}
	//-----------------------------------------------------------------------
	
	PhysicsShape* BulletSubsystem::getShape(String name)
	{
		if(mShapes.find(name) != mShapes.end())
			return mShapes[name];
		return 0;
	}
	//-----------------------------------------------------------------------
	
	PhysicsBoxShape* BulletSubsystem::createBoxShape(Vector3 extents)
	{
		PhysicsBoxShape* box = 0;
		String name = "BOX_"+StringUtils::toString(extents.x)+"_"+
			StringUtils::toString(extents.y)+"_"+StringUtils::toString(extents.z);
		
		if(name!="NULL")
		{
			PhysicsShape* shape = getShape(name);
			if(!shape)
			{
				box = new PhysicsBoxShape(extents);
				mShapes[name] = box;
			}
			else
			{
				if(shape->getType() != PST_BOX)
					throw NonUniqueNameException(name);
				box = static_cast<PhysicsBoxShape*>(shape);
			}
		}
		else
			box = new PhysicsBoxShape(extents);

		return box;
	}
	//-----------------------------------------------------------------------
	
	PhysicsSphereShape* BulletSubsystem::createSphereShape(Real radius)
	{
		PhysicsSphereShape* sphere;
		String name = "SPHERE_"+StringUtils::toString(radius);
		
		if(name!="NULL")
		{
			PhysicsShape* shape = getShape(name);
			if(!shape)
			{
				sphere = new PhysicsSphereShape(radius);
				mShapes[name] = sphere;
			}
			else
			{
				if(shape->getType() != PST_SPHERE)
					throw NonUniqueNameException(name);
				sphere = static_cast<PhysicsSphereShape*>(shape);
			}
		}
		else
			sphere = new PhysicsSphereShape(radius);

		return sphere;
	}
	//-----------------------------------------------------------------------
	
	PhysicsConvexShape* BulletSubsystem::createConvexShape(MeshData& points, String name)
	{
		PhysicsConvexShape* con;
		
		if(name!="NULL")
		{
			PhysicsShape* shape = getShape(name);
			if(!shape)
			{
				con = new PhysicsConvexShape(points,name);
				mShapes[name] = con;
			}
			else
			{
				if(shape->getType() != PST_CONVEX)
					throw NonUniqueNameException(name);
				con = static_cast<PhysicsConvexShape*>(shape);
			}
		}
		else
			con = new PhysicsConvexShape(points,name);

		return con;
	}
	//-----------------------------------------------------------------------
	
	PhysicsTrimeshShape* BulletSubsystem::createTrimeshShape(MeshData& triangles,String name)
	{
		PhysicsTrimeshShape* tri;
		
		if(name!="NULL")
		{
			PhysicsShape* shape = getShape(name);
			if(!shape)
			{
				tri = new PhysicsTrimeshShape(triangles,name);
				mShapes[name] = tri;
			}
			else
			{
				if(shape->getType() != PST_TRIMESH)
					throw NonUniqueNameException(name);
				tri = static_cast<PhysicsTrimeshShape*>(shape);
			}
		}
		else
			tri = new PhysicsTrimeshShape(triangles,name);

		return tri;
	}
	//-----------------------------------------------------------------------
	// TODO add orientation options
	PhysicsCompoundShape* BulletSubsystem::createCompoundShape(
		const std::vector<PhysicsShape*>& shapes,
		const std::vector<Vector3>& positions)
	{
		PhysicsCompoundShape* comp = new PhysicsCompoundShape();
		for(int i=0;i<shapes.size();++i)
			comp->addShape(shapes[i],positions[i]);
		return comp;
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createObject(PhysicsShape* shape,
		Vector3 position, Real mass)
	{
		if(mass<=0.f)
			return createStatic(shape,position);
		return createRigidBody(shape,position,mass);
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createObject(PhysicsShape* shape, Vector3 position)
	{
		return createStatic(shape,position);
	}
	//-----------------------------------------------------------------------

	RigidBody* BulletSubsystem::createRigidBody(PhysicsShape* shape, 
		Vector3 position, float mass)
	{
		btVector3 localInertia(0,0,0);
		shape->getBtShape()->calculateLocalInertia(mass,localInertia);

		btRigidBody* actor = new btRigidBody(mass,0,shape->getBtShape(),localInertia);	
		actor->setRestitution(0.3f);
		actor->setFriction(0.8f);
		actor->setAnisotropicFriction(btVector3(0.9f,0.9f,0.9f));
		actor->setWorldTransform(btTransform(btQuaternion::getIdentity(),
			btVector3(position.x,position.y,position.z)));

		dynamic_cast<btDiscreteDynamicsWorld*>(mDynamicsWorld)->addRigidBody(actor,
			COLLISION_GROUP_1,COLLISION_GROUP_1);
		
		RigidBody* body = new RigidBody(mDynamicsWorld,actor,shape);
		mObjects.push_back(body);
		return body;
	}
	//-----------------------------------------------------------------------
	
	CollisionObject* BulletSubsystem::createStatic(PhysicsShape* shape, Vector3 position)
	{
		btCollisionObject* actor = new btCollisionObject();
		actor->setCollisionShape(shape->getBtShape());
		actor->setWorldTransform(btTransform(btQuaternion::getIdentity(),convertBullet(position)));
		actor->setRestitution(0.3f);
		actor->setFriction(0.8f);

		mDynamicsWorld->addCollisionObject(actor,COLLISION_GROUP_1);
		CollisionObject* obj = new CollisionObject(mDynamicsWorld,actor,shape);
		mObjects.push_back(obj);
		return obj;
	}
	//-----------------------------------------------------------------------

	QuantaController* BulletSubsystem::createQuantaCCT(Vector3 pos)
	{
		mObjects.push_back(new QuantaController(this,pos));
		return static_cast<QuantaController*>(mObjects.back());
	}
	//-----------------------------------------------------------------------
}
