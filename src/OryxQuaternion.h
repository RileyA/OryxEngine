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

		static const Quaternion IDENTITY;
		static const Quaternion ZERO;

		Real x;
		Real y;
		Real z;
		Real w;

		Quaternion() : x(0),y(0),z(0),w(0) {}
		Quaternion(Real x_,Real y_,Real z_,Real w_) : x(x_),y(y_),z(z_),w(w_) {}

		Quaternion(const Matrix3& mat)
		{
			this->FromRotationMatrix(mat);
		}

		/** Performs spherical linear interpolation between two Quaternions 
		 *		@param fT The interpolation factor 
		 *		@param rkP The first Quaternion 
		 *		@param rkQ The second Quaternion
		 *		@param shortestPath Whether or not to use the shortest path */
		static Quaternion Slerp(Real fT, const Quaternion& rkP,
			const Quaternion& rkQ, bool shortestPath = true);

		/** Dots this Quaternion with another
		 *		@param rkQ The Quaternion to dot with 
		 *		@return The dot product */
		Real dotProduct(const Quaternion& rkQ) const;

		/** Normalizes the Quaternion
		 *		@return The original length */
		Real normalize(void); 

		/** Constructs a quaternion from an angle and an axis
		 *		@param angle The angle
		 *		@param kAxis The axis */
		void FromAngleAxis(const Real& angle,const Vector3& kAxis);

		/** Constructs a quaternion from a 3x3 matrix
		 *		@param kRot The matrix to use */
		void FromRotationMatrix(const Matrix3& kRot);

		/** Returns a matrix representation of this rotation
		 *		@param kRot The matrix to output to */
		void ToRotationMatrix(Matrix3& kRot) const;

		void fromAxes(const Vector3& xA, const Vector3& yA, const Vector3& zA);

		/** Computes and returns the inverse of this Quaternion 
		 *		@returns The inverse Quaternion */
		Quaternion inverse() const;

		Vector3 operator*(Vector3 vect);
		Quaternion operator-(const Quaternion& rkQ) const;
		Quaternion operator+(const Quaternion& rkQ) const;
		Quaternion operator*(const Quaternion& rkQ) const;
		Quaternion operator*(Real fScalar) const;
		Quaternion operator-() const;
		friend Quaternion operator*(Real fScalar, const Quaternion& rkQ);

	};
}

#endif
