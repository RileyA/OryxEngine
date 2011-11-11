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

		Real x;
		Real y;
		Real z;

		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;

		Vector3() : x(0), y(0),z(0){}
		Vector3(Real coords[3]) : x(coords[0]),y(coords[1]),z(coords[2]){}
		Vector3(const Real _x,const Real _y,const Real _z) 
			:x(_x),y(_y),z(_z) {}

		/** Tests if this vector's direction equals that of another
		 *		@param vect The vector to test with 
		 *		@param tolerance The angle of tolerance (degrees) */
		bool directionEquals(const Vector3& vect, const Real& tolerance)
		{
				Real dot = dotProduct(vect);
				Real angle = acos(dot);
				return abs(angle) <= (3.14159f/180.f) * tolerance;
		}

		/** Normalize the vector, (make it unit length). Returns the previous length. */
		Real normalize()
		{
			Real fLength = sqrt( x * x + y * y + z * z );

			if ( fLength > 1e-08 )
			{
				Real fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return fLength;
		}

		/** Gets the length of this vector
		 *		@return The length 
		 *		@remarks When possible use squaredLength(), as this requires a costly
		 *			sqrt() operation. */
		Real length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		/** Gets the squared length of this vector
		 *		@return The squared length */
		Real squaredLength()
		{
			return Real(x * x + y * y + z * z);
		}

		/** Gets the cross product of this vector with another
		 *		@param vect The vector to cross with
		 *		@returns The result of the cross product */
		Vector3 crossProduct(const Vector3& vect) const
		{
			return Vector3( y * vect.z - z * vect.y,
							z * vect.x - x * vect.z,
							x * vect.y - y * vect.x);
		}

		/** Gets the distance between this vector and another
		 *		@param The vector to compare with 
		 *		@return The distance 
		 *		@remarks The */
		Real distance(const Vector3& vect) const
		{
			return (*this - vect).length();
		}

		/** Gets the squared distance between this vector and another
		 *		@param vect The vector to get the dist to
		 *		@return The squared distance */
		Real squaredDistance(const Vector3& vect) const
		{
			return (*this - vect).length();
		}

		/** Computes the dot (scalar) product of this vector with another 
		 *		@param vect The vector to dot with 
		 *		@return The scalar product */
		Real dotProduct(const Vector3 vect)
		{
			return x*vect.x + y*vect.y + z*vect.z;
		}

		/** Get the angle between this vector and another
		 *		@param dest The vector to get the angle to */
		Real angleBetween( Vector3 dest)
		{
			Real lenProduct = length() * dest.length();

			// Divide by zero check
			if(lenProduct < 1e-6f)
				lenProduct = 1e-6f;

			Real f = dotProduct(dest) / lenProduct;

			if(f>1.f)
				f = 1.f;
			if(f<-1.f)
				f = -1.f;
			return (180.f/3.14159265f)*(acos(f));
		}

		/** Gets whether or not this Vector has a length of zero
		 *		@param Whether it's zero or not */
		bool isZeroLength()
		{
			Real sqlen = (x * x) + (y * y) + (z * z);
			return (sqlen < (1e-06 * 1e-06));
		}

		/** Gets the Quaternion required to rotate this vector to another
		 *		@param dest The destination vector 
		 *		@return The rotation (as a Quaternion) */
		Quaternion getRotationTo(const Vector3& dest, const Vector3& fallback = Vector3::ZERO) const;

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

		Vector3 operator*(const Real scalar) const
		{
			return Vector3(x*scalar,y*scalar,z*scalar);
		}

		Vector3 operator/(const Vector3 vect) const
		{
			return Vector3(x/vect.x,y/vect.y,z/vect.z);
		}

		Vector3 operator/(const Real scalar) const
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

		Vector3& operator*=(const Real scalar)
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

		Vector3& operator/=(const Real scalar)
		{
			if(scalar==0)
			{
				// TODO: throw an exception here...
				return *this;
			}
			Real invScalar = 1/scalar;
			x/=invScalar;
			y/=invScalar;
			z/=invScalar;
			return *this;
		}

		Real& operator [] ( const size_t i )
		{
			return *(&x+i);
		}

		const Real& operator [] ( const size_t i ) const
		{
			return *(&x+i);
		}

	};
}

#endif
