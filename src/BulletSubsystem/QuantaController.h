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

#ifndef QUANTA_CONTROLLER_H
#define QUANTA_CONTROLLER_H

#include "Oryx.h"
#include "CharacterController.h"
#include "CharPrimitive.h"
#include "Bulletdllmain.h"

class btPairCachingGhostObject;
class btKinematicCharacterController;

namespace Oryx
{
	class ORYX_BULLET_EXPORT QuantaController : public CharacterController
	{
	public:

		QuantaController(BulletSubsystem* bullet,Vector3 startPos);
		virtual ~QuantaController();

		virtual Vector3 getPosition();
		virtual Quaternion getOrientation();

		virtual void update(bool frame, Real interpolation, Vector3 gravity);
		virtual void jump(Real strength);

		void move(Vector3 d, Real dist, bool slide = false);
	private:


		Real mGravityFactor;
		std::vector<CharPrimitive*> mComponents;
		Real mInterpolation;

		Vector3 mPosition[2];// 0 is last frame, 1 is next frame

    btPairCachingGhostObject* mGhostObject;
    btKinematicCharacterController* mCharacter;
    BulletSubsystem* mBullet;

		//static const int NUM_SPHERES = 4;
	};
}


#endif
