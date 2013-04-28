//-----------------------------------------------------------------------
// Copyright Riley Adams 2010

// This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#include "Oryx.h"
#include "OryxVector3.h"
#include "OryxQuaternion.h"

namespace Oryx
{
	const Vector3 Vector3::ZERO( 0, 0, 0 );
	const Vector3 Vector3::UNIT_X( 1, 0, 0 );
	const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
	const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
	const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
	const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
	const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
	const Vector3 Vector3::UNIT_SCALE(1, 1, 1);
	//-----------------------------------------------------------------------

	Quaternion Vector3::getRotationTo(const Vector3& dest, const Vector3& fallback) const
	{
		// Based on Stan Melax's article in Game Programming Gems
		Vector3 fallbackAxis = fallback;
		Quaternion q;
		Vector3 v0 = *this;
		Vector3 v1 = dest;
		v0.normalize();
		v1.normalize();

		Real d = v0.dotProduct(v1);

		// If dot == 1, vectors are the same
		if(d >= 1.0f)
		{
			return Quaternion::IDENTITY;
		}

		if(d < (1e-6f - 1.0f))
		{
			if(fallbackAxis != Vector3::ZERO)
			{
				// rotate 180 degrees about the fallback axis
				q.FromAngleAxis(3.141592, fallbackAxis);
			}
			else
			{
				// Generate an axis
				Vector3 axis = Vector3::UNIT_X.crossProduct(*this);

				if(axis.isZeroLength()) // pick another if colinear
				{
					axis = Vector3::UNIT_Y.crossProduct(*this);
					axis.normalize();
					q.FromAngleAxis(3.141592, axis);
				}
			}
		}
		else
		{
			Real s = sqrt( (1+d)*2 );
				Real invs = 1 / s;
			Vector3 c = v0.crossProduct(v1);
			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;
			q.normalize();
		}
		return q;
	}
	//-----------------------------------------------------------------------

  Vector3 Vector3::randomDeviant(
      const Real& angle,
      const Vector3& up) const
  {
      Vector3 newUp;

      newUp = up;

      // Rotate up vector by random amount around this
      Quaternion q;
      q.FromAngleAxis(3.1415926 * 2.f * Rand::get().genFloat(0.f, 1.f), *this );
      newUp = q * newUp;

      // Finally rotate this by given angle around randomised up
      q.FromAngleAxis( angle, newUp );
      return q * (*this);
  }
}
