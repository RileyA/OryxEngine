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

#ifndef CHARACTER_PRIMITIVE
#define CHARACTER_PRIMITIVE

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "Bulletdllmain.h"

namespace Oryx
{
	class PhysicsShape;
	class BulletSubsystem;

	/** A simple spherical collision casting object,
	 *		does no collision or interaction with other objects
	 *		but serves as a good basis for a more complex character 
	 *		control system*/
	class ORYX_BULLET_EXPORT CharPrimitive
	{
	public:

		static const Real SKIN_WIDTH = 0.075f;
		static const Real RADIUS     = 0.375f;

		CharPrimitive(BulletSubsystem* bull, Vector3 pos = Vector3::ZERO);

		/** Moves this sphere by set distance in a given direction
		 *		@param direction The desired direction
		 *		@param distance The distance (NOTE this works best with
		 *			a fixed timestep
		 *		@param depth The max number of recursions to perform for sliding */
		Vector3 move(Vector3 direction, Real distance, int maxDepth = 1);

		void translate(Vector3 v);
		Vector3 getPosition();
		bool overlapCheck(Vector3 position);

	private:

		BulletSubsystem* mBullet;
		PhysicsShape* mSphere;
		Vector3 mPosition;

	};
}

#endif
