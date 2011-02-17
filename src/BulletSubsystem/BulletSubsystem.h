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

#ifndef ORYX_BULLET_SUBSYSTEM
#define ORYX_BULLET_SUBSYSTEM

#include "Oryx.h"
#include "Bulletdllmain.h"
#include "BulletConversions.h"
#include "OryxEngineSubsystem.h"
#include "Oryx3DMath.h"
#include "PhysicsObject.h"
#include "RaycastReport.h"

// bullet forward declarations
class btDynamicsWorld;
class btRigidBody;
class btCollisionShape;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
struct btDbvtBroadphase;
class btSequentialImpulseConstraintSolver;

namespace Oryx
{
    class ORYX_BULLET_EXPORT BulletSubsystem : public EngineSubsystem
    {
    public:

        BulletSubsystem();
        ~BulletSubsystem();

        virtual void _init();
        virtual void _deinit();
        virtual void _update(Real delta);
        virtual void _endState();
        virtual String getName();

		void startSimulation();
		void stopSimulation();

		float getInterpolation();
		Vector3 getGravity();

		RaycastReport raycast(Vector3 origin,Vector3 direction,
			float length=10000.f,short group=0,short mask=0);

		PhysicsObject* createStaticTrimesh(MeshData& d,Vector3 pos,String name="NULL");
		PhysicsObject* createConvexHull(MeshData& d,Vector3 pos,float mass=10.f,String name="NULL");
		PhysicsObject* createSphere(float radius,Vector3 pos,float mass=10.f);
		PhysicsObject* createCube(Vector3 scale,Vector3 pos,float mass=10.f);
		PhysicsObject* createCompound(Vector3 pos);

		btCollisionShape* getShape(String name);
		btCollisionShape* createBoxShape(Vector3 extents);
		btCollisionShape* createSphereShape(Real radius);
		btCollisionShape* createConvexShape(MeshData& points, String name="NULL");
		btCollisionShape* createTrimeshShape(MeshData& triangles,String name="NULL");
		btCollisionShape* createCompoundShape(const std::vector<btCollisionShape*>& shapes,
			const std::vector<Vector3>& positions);

		PhysicsObject* createObject(btCollisionShape* shape, Vector3 position, float mass);
		PhysicsObject* createRigidBody(btCollisionShape* shape, Vector3 position, float mass);
		PhysicsObject* createStatic(btCollisionShape* shape, Vector3 position);

        static const size_t mDependencyCount;
        static const String mDependencies[];

    protected:

        bool mInitialized;
		float mAccumulation;
		float mInterpolation;
		float mTimeStep;

		btDynamicsWorld* mDynamicsWorld;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btDbvtBroadphase* mBroadphase;
		btSequentialImpulseConstraintSolver* mSolver;
		
		bool mStarted;
		std::vector<PhysicsObject*> mObjects;
		std::map<std::string,btCollisionShape*> mShapes;

		Vector3 mGravity;
    };

	#define BIT(x) (1<<(x))
	enum CollisionTypes 
	{
		COLLISION_GROUP_0 = 0,
		COLLISION_GROUP_1 = BIT(1),
		COLLISION_GROUP_2 = BIT(2),
		COLLISION_GROUP_3 = BIT(3),
		COLLISION_GROUP_4 = BIT(4),
		COLLISION_GROUP_5 = BIT(5),
		COLLISION_GROUP_6 = BIT(6),
		COLLISION_GROUP_7 = BIT(7),
		COLLISION_GROUP_8 = BIT(8),
		COLLISION_GROUP_9 = BIT(9),
		COLLISION_GROUP_10 = BIT(10),
		COLLISION_GROUP_11 = BIT(11),
		COLLISION_GROUP_12 = BIT(12),
		COLLISION_GROUP_13 = BIT(13),
		COLLISION_GROUP_14 = BIT(14),
		COLLISION_GROUP_15 = BIT(15)
	};
}

#endif
