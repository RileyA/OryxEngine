//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010-2011

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
#include "PhysicsShape.h"
#include "PhysicsBoxShape.h"
#include "PhysicsSphereShape.h"
#include "PhysicsCapsuleShape.h"
#include "PhysicsConvexShape.h"
#include "PhysicsCompoundShape.h"
#include "PhysicsTrimeshShape.h"
#include "CollisionObject.h"
#include "RigidBody.h"
#include "QuantaController.h"

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
	/** Bullet physics subsystem, does 3d physics simulation */
	class ORYX_BULLET_EXPORT BulletSubsystem : public EngineSubsystem
	{
	public:

		/** Constructor */
		BulletSubsystem();

		/** Destructor */
		~BulletSubsystem();

		/** Starts the subsystem up 
		 *		@remarks Note that this doesn't start the physics simulation 
		 *			but rather just preps it, individual states must tell the
		 *			actual simulation to begin with startSimulation() */
		virtual void _init();

		/** Shuts the physics system down */
		virtual void _deinit();

		/** Updates the physics
		 *		@remarks This is based on a fixed timestep, using an accumulator,
		 *			so any goven frame might not actually advance the simulation.
		 *			interpolation with the previous frame is used to keep things 
		 *			smooth between timesteps */
		virtual void _update(Real delta);

		/** Called upon ending the state, this shuts the simulation down entirely */
		virtual void _endState();

		/** Returns the name of this subsystem */
		virtual String getName();

		/** Starts the physics simulation */
		void startSimulation();
		/** Shts down and cleans up after the simulation */
		void stopSimulation();

		/** Get the current accumulation factor */
		float getInterpolation();

		/** Get the current direction and magnitude of gravity 
		 *		@return The gravity vector */
		Vector3 getGravity();
		/** Sets gravity
		 *		@param g The gravity value */
		void setGravity(Vector3 g);

		/** Performs a simple raycast and returns the results
		 *		@param origin Where to fire the ray from
		 *		@param direction The direction in which to fire the ray 
		 *		@param length The max distance to raycast out to (default:  10k meters)*/
		RaycastReport raycast(Vector3 origin,Vector3 direction,
			float length=10000.f,short group=0,short mask=0);
		/** Performs a sweep test and returns the results
		 *		@param shape The shae to sweep (or 'cast' with
		 *		@param origin Where to fire the ray from
		 *		@param direction The direction in which to fire the ray 
		 *		@param length The max distance to raycast out to (default:  10k meters)*/
		SweepReport sweep(PhysicsShape* shape, Vector3 origin,Vector3 direction,
			float length=10000.f,short group=0,short mask=0);

		/** Creates a static trimesh based on a standard MeshData object
		 *		@param d The mesh to base the physics object off of
		 *		@param pos The position to place the created object 
		 *		@param name A name for the mesh, so that identical objects may be 
		 *			cached and reused (optional) 
		 *		@returns a pointer to the PhysicsObject*/
		PhysicsObject* createStaticTrimesh(MeshData& d,Vector3 pos,String name="NULL");
		/** Creates a convex hull based on a standard MeshData object
		 *		@param d The mesh to base the physics object off of (only needs to be a point cloud
		 *			indices, normals, etc are not necessary)
		 *		@param pos The position to place the created object 
		 *		@param mass The mass of the new object (recommended unit: kg), 0 is static
		 *		@param name A name for the mesh, so that identical objects may be 
		 *			cached and reused (optional)
		 *		@returns a pointer to the PhysicsObject */
		PhysicsObject* createConvexHull(MeshData& d,Vector3 pos,float mass=10.f,String name="NULL");
		/** Creates a sphere primitive, with a given radius
		 *		@param radius The radius of the sphere to create 
		 *		@param pos Where to place the new object 
		 *		@param mass The desired mass, 0 makes a static object
		 *		@returns a pointer to the PhysicsObject */
		PhysicsObject* createSphere(float radius,Vector3 pos,float mass=10.f);
		/** Creates a capsule primitive object, with a given radius
		 *		@param radius The radius
		 *		@param height The desired height
		 *		@param pos Where to place the new object 
		 *		@param mass The desired mass, 0 makes a static object
		 *		@returns a pointer to the PhysicsObject */
		PhysicsObject* createCapsule(float radius, float height,Vector3 pos,float mass=10.f);
		/** Creates a cube primitive, with a given radius
		 *		@param scale The extents of the box to create
		 *		@param pos Where to place the new object 
		 *		@param mass The desired mass, 0 makes a static object
		 *		@returns a pointer to the PhysicsObject */
		PhysicsObject* createCube(Vector3 scale,Vector3 pos,float mass=10.f);
		/** Creates an empty compound object
		 *		@param pos The position to create the object at 
		 *		@returns a pointer to the PhysicsObject */
		PhysicsObject* createCompound(Vector3 pos);

		/** Gets a cached shape
		 *		@param name The name of the shape to loop for
		 *		@return The shape, or 0 if not found */
		PhysicsShape* getShape(String name);
		/** Creates a primitive box shape
		 *		@param extents The extents of the box to create
		 *		@return The created object */
		PhysicsBoxShape* createBoxShape(Vector3 extents);
		/** Creates a primitive sphere shape
		 *		@param radius The desired radius
		 *		@return The created shape */
		PhysicsSphereShape* createSphereShape(Real radius);
		/** Creates a primitive capsule shape
		 *		@param radius The desired radius
		 *		@param height The height of the capsule
		 *		@return The created shape */
		PhysicsCapsuleShape* createCapsuleShape(Real radius, Real height);
		/** Creates a convex hull primitive from a point cloud 
		 *		@param points The points, stored in a MeshData object 
		 *		@param name The name of the mesh (so if it already exists, we can reuse)
		 *		@return The created shape */
		PhysicsConvexShape* createConvexShape(MeshData& points, String name="NULL");
		/** Creates a triange mesh shape based on a MeshData object 
		 *		@param triangles The MeshData to use 
		 *		@param name The name, for caching purposes */
		PhysicsTrimeshShape* createTrimeshShape(MeshData& triangles,String name="NULL");
		/** Creates a compound object based on vectors of primitives and positions
		 *		@param shapes The shapes to use 
		 *		@param positions The positions to place the shapes within this compound */
		PhysicsCompoundShape* createCompoundShape(const std::vector<PhysicsShape*>& shapes,
			const std::vector<Vector3>& positions);

		/** Creates a single-shape physics object
		 *		@param shape The physics shape to be used
		 *		@param position Where to spawn the physics object 
		 *		@param mass The desired mass (0 if a static object) */
		PhysicsObject* createObject(PhysicsShape* shape, Vector3 position, float mass);
		/** Creates a single-shape static physics object
		 *		@param shape The physics shape to be used
		 *		@param position Where to spawn the physics object */
		PhysicsObject* createObject(PhysicsShape* shape, Vector3 position);

		/** Creates a dynamic rigid body object
		 *		@param shape The desired shape 
		 *		@param position Where to spawn the object 
		 *		@param mass The desired mass to use */
		RigidBody* createRigidBody(PhysicsShape* shape, Vector3 position, float mass);
		/** Creates a static physics object
		 *		@param shape The shape to be used
		 *		@param position Where to place the object */
		CollisionObject* createStatic(PhysicsShape* shape, Vector3 position);

		/** Creates an experimental character controller
		 *		@param pos The start position */
		QuantaController* createQuantaCCT(Vector3 pos);

		/** Gets a pointer to the bullet world itself */
		btDynamicsWorld* getWorld(){return mDynamicsWorld;}

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
		std::map<std::string,PhysicsShape*> mShapes;

		Vector3 mGravity;
	};

	#define BIT(x) (1<<(x))
	/** Collision group defines (bt uses 16-bit bitmasks for this) */
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
