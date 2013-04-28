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
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "btBulletDynamicsCommon.h"

namespace Oryx
{
	QuantaController::QuantaController(BulletSubsystem* bullet,Vector3 startPos)
		:CharacterController(bullet->getWorld()),mGravityFactor(1.f)
	{
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(convertBullet(startPos));

    mGhostObject = new btPairCachingGhostObject();
    mGhostObject->setWorldTransform(startTransform);
    btScalar characterHeight = 1.5;
    btScalar characterWidth  = 0.35;
    btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
    mGhostObject->setCollisionShape(capsule);
    mGhostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

    btScalar stepHeight = btScalar(0.35);
    mCharacter = new btKinematicCharacterController(mGhostObject, capsule, stepHeight);

    bullet->getWorld()->addCollisionObject(mGhostObject);
      //btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
    bullet->getWorld()->addAction(mCharacter);
    mGhostObject->getBroadphaseHandle()->m_collisionFilterGroup = 0x1;
    mGhostObject->getBroadphaseHandle()->m_collisionFilterMask = 0xffff;
    mBullet = bullet;
    //mCharacter->setUpAxis(1);
    //mCharacter->setMaxSlope(60.f * (3.141592/180.f));
    mCharacter->setUseGhostSweepTest(true);
    //mCharacter->setFallSpeed(0.0);
	}
	//-----------------------------------------------------------------------
	
	QuantaController::~QuantaController()
	{
    mBullet->getWorld()->removeCollisionObject(mGhostObject);
	}
	//-----------------------------------------------------------------------
	
	Vector3 QuantaController::getPosition()
	{
    Vector3 out = convertBullet(mGhostObject->getWorldTransform().getOrigin());
    //std::cout<<out.x<<" "<<out.y<<" "<<out.z<<"\n";
    return out;
	}
	//-----------------------------------------------------------------------
	
	Quaternion QuantaController::getOrientation()
	{
    return Quaternion::IDENTITY;
	}
	//-----------------------------------------------------------------------
	
	void QuantaController::update(bool frame, Real interpolation, Vector3 gravity)
	{
    // ...
	}
	//-----------------------------------------------------------------------
	
	void QuantaController::jump(Real strength)
	{
    //mCharacter->jump(strength);
    mCharacter->setMaxJumpHeight(5.f);
    mCharacter->setJumpSpeed(strength);
    if (mCharacter->canJump()) {
      mCharacter->jump();
    }
	}
	//-----------------------------------------------------------------------

	void QuantaController::move(Vector3 d, Real dist, bool slide)
	{
    mCharacter->setVelocityForTimeInterval(convertBullet(d * dist), 1.f);
    //mCharacter->setWalkDirection(convertBullet(d * dist));

	}
}
