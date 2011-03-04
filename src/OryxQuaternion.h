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

// note: This class borrows a good deal from Ogre3d's quat implementation
// Ogre is open source under the MIT license

namespace Oryx
{
	class Matrix3;

	/** A quaternion, for representing rotations!*/
	class ORYX_EXPORT Quaternion
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
		Quaternion operator- (const Quaternion& rkQ) const;
		Quaternion operator+ (const Quaternion& rkQ) const;
		Quaternion operator* (const Quaternion& rkQ) const;
		Quaternion operator* (Real fScalar) const;
		Quaternion operator- () const;

		friend Quaternion operator* (Real fScalar,
            const Quaternion& rkQ);

		// performs spherical linear interpolation between two Quaternions
		static Quaternion Slerp (Real fT, const Quaternion& rkP,
			const Quaternion& rkQ, bool shortestPath = true);

        Real Dot (const Quaternion& rkQ) const;  // dot product
        Real normalize(void); 

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
