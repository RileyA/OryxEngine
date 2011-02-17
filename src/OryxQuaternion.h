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


#ifndef ORYX_QUATERNION_H 
#define ORYX_QUATERNION_H 

#include "OryxVector3.h"
#include "Oryx.h"

namespace Oryx
{
	class Matrix3;

	/** A quaternion, for representing rotations! */
	class Quaternion
	{
	public:

		Real x;
		Real y;
		Real z;
		Real w;

		Quaternion()
			:x(0),y(0),z(0),w(0)
		{
		}

		Quaternion(Real x_,Real y_,Real z_,Real w_)
			:x(x_),y(y_),z(z_),w(w_)
		{
		}

		Quaternion(const Matrix3& mat)
		{
			this->FromRotationMatrix(mat);
		}

		Vector3 operator*(Vector3 vect);


		Real normalize()
        {
			Real len = w*w+x*x+y*y+z*z;
			Real factor = 1.0f / sqrt(len);
			x*=factor;
			y*=factor;
			z*=factor;
			w*=factor;
			//*this = *this * factor;
			return len;
        }

		

		//Real normalize(); 
		//Real Quaternion::Norm ();
		void FromAngleAxis(const Real& angle,const Vector3& kAxis);
		void FromRotationMatrix (const Matrix3& kRot);
		void ToRotationMatrix (Matrix3& kRot) const;

        Quaternion Inverse () const;  // apply to non-zero quaternion

		static const Quaternion IDENTITY;
		static const Quaternion ZERO;
	};
}

#endif
