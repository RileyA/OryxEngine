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

#ifndef ORYX_VECTOR3_H
#define ORYX_VECTOR3_H

#include "Oryx.h"

namespace Oryx
{
	class Quaternion;

	/** A 3d Vector; borrows heavily from Ogre3d's implementation */
	class ORYX_EXPORT Vector3
	{
	public:
		Vector3()
			:x(0),
			 y(0),
			 z(0)
		{
		}

		Vector3(const float _x,const float _y,const float _z)
			:x(_x),y(_y),z(_z)
		{
		}

		Vector3(float coords[3])
			:x(coords[0]),y(coords[1]),z(coords[2])
		{
		}

		bool operator==(const Vector3 vect)
		{
			return(x==vect.x&&y==vect.y&&z==vect.z);
		}

		bool operator!=(const Vector3 vect)
		{
			return(x!=vect.x||y!=vect.y||z!=vect.z);
		}

		Vector3& operator=(const Vector3 vect)
		{
			x = vect.x;
			y = vect.y;
			z = vect.z;
			return *this;
		}

		Vector3 operator+(const Vector3 vect) const
		{
			return Vector3(x+vect.x,y+vect.y,z+vect.z);
		}

		Vector3 operator-(const Vector3 vect) const
		{
			return Vector3(x-vect.x,y-vect.y,z-vect.z);
		}

		Vector3 operator*(const Vector3 vect) const
		{
			return Vector3(x*vect.x,y*vect.y,z*vect.z);
		}

		Vector3 operator*(const float scalar) const
		{
			return Vector3(x*scalar,y*scalar,z*scalar);
		}

		Vector3 operator/(const Vector3 vect) const
		{
			return Vector3(x/vect.x,y/vect.y,z/vect.z);
		}

		Vector3 operator/(const float scalar) const
		{
			return Vector3(x/scalar,y/scalar,z/scalar);
		}

		Vector3& operator+=(const Vector3 vect)
		{
			x+=vect.x;
			y+=vect.y;
			z+=vect.z;
			return *this;
		}

		Vector3& operator-=(const Vector3 vect)
		{
			x-=vect.x;
			y-=vect.y;
			z-=vect.z;
			return *this;
		}

		Vector3& operator*=(const Vector3 vect)
		{
			x*=vect.x;
			y*=vect.y;
			z*=vect.z;
			return *this;
		}

		Vector3& operator*=(const float scalar)
		{
			x*=scalar;
			y*=scalar;
			z*=scalar;
			return *this;
		}

		Vector3& operator/=(const Vector3 vect)
		{
			x/=vect.x;
			y/=vect.y;
			z/=vect.z;
			return *this;
		}

		Vector3& operator/=(const float scalar)
		{
			if(scalar==0)
			{
				// an exception should probably be thrown here, once the exception handling stuff is set up...
				return *this;
			}
			float invScalar = 1/scalar;
			x/=invScalar;
			y/=invScalar;
			z/=invScalar;
			return *this;
		}

		float& operator [] ( const size_t i )
        {
            return *(&x+i);
        }

		const float& operator [] ( const size_t i ) const
        {
            return *(&x+i);
        }

		inline bool directionEquals(const Vector3& rhs,
				const Real& tolerance)
		{
				Real dot = dotProduct(rhs);
				Real angle = acos(dot);
				return abs(angle) <= (3.14159f/180.f) * tolerance;
		}

		/** Normalize the vector, (make it unit length). Returns the previous length. */
		float normalize()
		{
			float fLength = sqrt( x * x + y * y + z * z );

            if ( fLength > 1e-08 )
            {
                float fInvLength = 1.0f / fLength;
                x *= fInvLength;
                y *= fInvLength;
                z *= fInvLength;
            }

            return fLength;
		}

		float length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		float squaredLength()
		{
			return float(x * x + y * y + z * z);
		}

		Vector3 crossProduct(const Vector3& vect) const
		{
			return Vector3( y * vect.z - z * vect.y,
							z * vect.x - x * vect.z,
							x * vect.y - y * vect.x);
		}

		float distance(const Vector3& vect) const
        {
            return (*this - vect).length();
        }

		float dotProduct(const Vector3 vect)
		{
			return x*vect.x + y*vect.y + z*vect.z;
		}

		float angleBetween( Vector3 dest)
		{
			Real lenProduct = length() * dest.length();

			// Divide by zero check
			if(lenProduct < 1e-6f)
				lenProduct = 1e-6f;

			Real f = dotProduct(dest) / lenProduct;

			if(f>1.f)
			{
				f = 1.f;
			}
			if(f<-1.f)
			{
				f = -1.f;
			}
			return (180.f/3.14159265f)*(acos(f));

		}

		bool isZeroLength()
		{
			Real sqlen = (x * x) + (y * y) + (z * z);
            return (sqlen < (1e-06 * 1e-06));
		}

        Quaternion getRotationTo(const Vector3& dest) const;

		// the coords
		float x;
		float y;
		float z;

		static const Vector3 ZERO;
        static const Vector3 UNIT_X;
        static const Vector3 UNIT_Y;
        static const Vector3 UNIT_Z;
        static const Vector3 NEGATIVE_UNIT_X;
        static const Vector3 NEGATIVE_UNIT_Y;
        static const Vector3 NEGATIVE_UNIT_Z;
        static const Vector3 UNIT_SCALE;
	};
}

#endif
