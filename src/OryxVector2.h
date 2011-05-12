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

#ifndef ORYX_VECTOR2_H
#define ORYX_VECTOR2_H

#include "Oryx.h"

namespace Oryx
{
	/** A 2d Vector; borrows heavily from Ogre3d's implementation */
	class ORYX_EXPORT Vector2
	{
	public:
		
		Real x;
		Real y;

		Vector2() : x(0),y(0) {}
		Vector2(const float _x,const float _y) : x(_x),y(_y){}
		Vector2(float coords[2]) : x(coords[0]),y(coords[1]){}

		/** Normalize the vector, (make it unit length).
		 *		@return The length prior to normalizing */
		float normalize()
		{
			float fLength = sqrt( x * x + y * y );

			if ( fLength > 1e-08 )
			{
				float fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
			}

			return fLength;
		}

		/** Gets the length of the vector
		 *		@return The length 
		 *		@remarks This requires a costly sqrt, so use squaredLength() when possible */
		float length() const
		{
			return sqrt(x * x + y * y);
		}

		/** Gets the squared length of a vector
		 *		@returns The length */
		float squaredLength()
		{
			return float(x * x + y * y);
		}

		/** Gets the distance between this vector and another
		 *		@param vect The vector to test against 
		 *		@return The distance */
		float distance(const Vector2& vect) const
		{
			return (*this - vect).length();
		}
		
		bool operator==(const Vector2 vect)
		{
			return(x==vect.x&&y==vect.y);
		}

		bool operator!=(const Vector2 vect)
		{
			return(x!=vect.x||y!=vect.y);
		}

		Vector2& operator=(const Vector2 vect)
		{
			x = vect.x;
			y = vect.y;
			return *this;
		}

		Vector2 operator+(const Vector2 vect) const
		{
			return Vector2(x+vect.x,y+vect.y);
		}

		Vector2 operator-(const Vector2 vect) const
		{
			return Vector2(x-vect.x,y-vect.y);
		}

		Vector2 operator*(const Vector2 vect) const
		{
			return Vector2(x*vect.x,y*vect.y);
		}

		Vector2 operator*(const float scalar) const
		{
			return Vector2(x*scalar,y*scalar);
		}

		Vector2 operator/(const Vector2 vect) const
		{
			return Vector2(x/vect.x,y/vect.y);
		}

		Vector2 operator/(const float scalar) const
		{
			return Vector2(x/scalar,y/scalar);
		}

		Vector2& operator+=(const Vector2 vect)
		{
			x+=vect.x;
			y+=vect.y;
			return *this;
		}

		Vector2& operator-=(const Vector2 vect)
		{
			x-=vect.x;
			y-=vect.y;
			return *this;
		}

		Vector2& operator*=(const Vector2 vect)
		{
			x*=vect.x;
			y*=vect.y;
			return *this;
		}

		Vector2& operator*=(const float scalar)
		{
			x*=scalar;
			y*=scalar;
			return *this;
		}

		Vector2& operator/=(const Vector2 vect)
		{
			x/=vect.x;
			y/=vect.y;
			return *this;
		}

		Vector2& operator/=(const float scalar)
		{
			if(scalar==0)
				return *this;
			float invScalar = 1/scalar;
			x/=invScalar;
			y/=invScalar;
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
	};
}

#endif
