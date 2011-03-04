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
		Vector2()
			:x(0),
			 y(0)
		{
		}

		Vector2(const float _x,const float _y)
			:x(_x),y(_y)
		{
		}

		Vector2(float coords[2])
			:x(coords[0]),y(coords[1])
		{
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

		/** Normalize the vector, (make it unit length). Returns the previous length. */
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

		float length() const
		{
			return sqrt(x * x + y * y);
		}

		float squaredLength()
		{
			return float(x * x + y * y);
		}

		float distance(const Vector2& vect) const
        {
            return (*this - vect).length();
        }

		// the coords
		Real x;
		Real y;
	};
}

#endif
