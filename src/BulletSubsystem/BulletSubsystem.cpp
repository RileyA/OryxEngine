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

			std::map<String,btCollisionShape*>::iterator iter = mShapes.begin();
			while(iter!=mShapes.end())
			{
				btTriangleMesh* tr = 0;

				if(iter->second->getShapeType()==21)
					tr = dynamic_cast<btTriangleMesh*>(dynamic_cast<btBvhTriangleMeshShape*>(
						iter->second)->getMeshInterface());

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
		p->setUniqueCollisionShape(name=="NULL");
		return p;
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createConvexHull(MeshData& d,Vector3 pos,float mass,String name)
	{
		PhysicsObject* p = createObject(createConvexShape(d,name),pos,mass);
		p->setUniqueCollisionShape(name=="NULL");
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
		std::vector<btCollisionShape*> s;
		std::vector<Vector3> v;
		PhysicsObject* obj = createStatic(createCompoundShape(s,v),pos);
		obj->setCompound(true);
		return obj;
	}
	//-----------------------------------------------------------------------
	
	btCollisionShape* BulletSubsystem::getShape(String name)
	{
		if(mShapes.find(name)!=mShapes.end())
			return mShapes[name];
		return 0;
	}
	//-----------------------------------------------------------------------
	
	btCollisionShape* BulletSubsystem::createBoxShape(Vector3 extents)
	{
		String name = "BOX_"+StringUtils::toString(extents.x)+"_"+
			StringUtils::toString(extents.y)+"_"+
			StringUtils::toString(extents.z);
		btCollisionShape* s = getShape(name);
		if(!s)
		{
			s =  new btBoxShape(btVector3(extents.x,extents.y,extents.z));
			mShapes[name] = s;
		}
		return s;
	}
	//-----------------------------------------------------------------------
	
	btCollisionShape* BulletSubsystem::createSphereShape(Real radius)
	{
		String name = "SPHERE_"+StringUtils::toString(radius);
		btCollisionShape* s = getShape(name);
		if(!s)
		{
			s =  new btSphereShape(radius);
			mShapes[name] = s;
		}
		return s;
	}
	//-----------------------------------------------------------------------
	
	btCollisionShape* BulletSubsystem::createConvexShape(MeshData& points, String name)
	{
		btCollisionShape* s = 0;
		if(name!="NULL")
			s = getShape(name);
		if(!s)
		{
			s = new btConvexHullShape(static_cast<btScalar*>(points.getVertices()),
				points.vertices.size()/3,3*sizeof(btScalar));

			if(name!="NULL")
				mShapes[name] = s;
		}
		return s;
	}
	//-----------------------------------------------------------------------
	
	btCollisionShape* BulletSubsystem::createTrimeshShape(MeshData& d,String name)
	{
		btCollisionShape* s = 0;
		if(name!="NULL")
			s = getShape(name);
		if(!s)
		{
			btTriangleMesh *triMesh = new btTriangleMesh();
			for(int i=0;i+3<d.indices.size();i+=3)
			{
				btVector3 points[3];
				for(int j=0;j<3;++j)
					points[j] = btVector3(
						d.vertices[d.indices[i+j]*3],
						d.vertices[d.indices[i+j]*3+1],
						d.vertices[d.indices[i+j]*3+2]);
				triMesh->addTriangle(points[0],points[1],points[2]);
			}
			s = new btBvhTriangleMeshShape(triMesh,true);
			if(name!="NULL")
				mShapes[name] = s;
		}
		return s;
	}
	//-----------------------------------------------------------------------
	// TODO add orientation options
	btCollisionShape* BulletSubsystem::createCompoundShape(
		const std::vector<btCollisionShape*>& shapes,
		const std::vector<Vector3>& positions)
	{
		btCompoundShape* comp = new btCompoundShape();
		for(int i=0;i<shapes.size();++i)
			comp->addChildShape(btTransform(btQuaternion::getIdentity(),
				convertBullet(positions[i])),shapes[i]);
		return comp;
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createObject(btCollisionShape* shape,
		Vector3 position, Real mass)
	{
		if(mass<=0.f)
			return createStatic(shape,position);
		return createRigidBody(shape,position,mass);
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createRigidBody(btCollisionShape* shape, 
		Vector3 position, float mass)
	{
		btVector3 localInertia(0,0,0);
		shape->calculateLocalInertia(mass,localInertia);

		btRigidBody* actor = new btRigidBody(mass,0,shape,localInertia);	
		actor->setRestitution(0.3f);
		actor->setFriction(0.8f);
		actor->setAnisotropicFriction(btVector3(0.9f,0.9f,0.9f));
		actor->setWorldTransform(btTransform(btQuaternion::getIdentity(),
			btVector3(position.x,position.y,position.z)));

		dynamic_cast<btDiscreteDynamicsWorld*>(mDynamicsWorld)->addRigidBody(actor,
			COLLISION_GROUP_1,COLLISION_GROUP_1);

		mObjects.push_back(new PhysicsObject(actor,mDynamicsWorld));
		return mObjects.back();
	}
	//-----------------------------------------------------------------------
	
	PhysicsObject* BulletSubsystem::createStatic(btCollisionShape* shape, Vector3 position)
	{
		btCollisionObject* actor = new btCollisionObject();
		actor->setCollisionShape(shape);
		actor->setWorldTransform(btTransform(btQuaternion::getIdentity(),
			btVector3(position.x,position.y,position.z)));
		actor->setRestitution(0.3f);
		actor->setFriction(0.8f);

		mDynamicsWorld->addCollisionObject(actor,COLLISION_GROUP_1);
		mObjects.push_back(new PhysicsObject(actor,mDynamicsWorld));
		return mObjects.back();
	}
	//-----------------------------------------------------------------------
}


				/*btVector3 point1 = btVector3(
					d.vertices[d.indices[i+j]*3+0],
					d.vertices[d.indices[i+j]*3+1],
					d.vertices[d.indices[i+j]*3+2]
					);++j;
				btVector3 point2 = btVector3(
					d.vertices[d.indices[i+j]*3+0],
					d.vertices[d.indices[i+j]*3+1],
					d.vertices[d.indices[i+j]*3+2]
					);++j;		
				btVector3 point3 = btVector3(
					d.vertices[d.indices[i+j]*3+0],
					d.vertices[d.indices[i+j]*3+1],
					d.vertices[d.indices[i+j]*3+2]
					);
				mTriMesh->addTriangle(point1,point2,point3);*/
