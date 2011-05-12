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

#include "Oryx.h"
#include "OryxMatrix3.h"

namespace Oryx
{
	const Matrix3 Matrix3::ZERO(0,0,0,0,0,0,0,0,0);
	const Matrix3 Matrix3::IDENTITY(1,0,0,0,1,0,0,0,1);

	//-----------------------------------------------------------------------
	void Matrix3::SetColumn(size_t iCol, const Vector3& vec)
	{
		//assert( 0 <= iCol && iCol < 3 );
		m[0][iCol] = vec.x;
		m[1][iCol] = vec.y;
		m[2][iCol] = vec.z;
	}

	//-----------------------------------------------------------------------
	void Matrix3::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		SetColumn(0,xAxis);
		SetColumn(1,yAxis);
		SetColumn(2,zAxis);
	}

	//-----------------------------------------------------------------------
	Vector3 Matrix3::operator* (const Vector3& rkPoint) const
	{
		Vector3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				m[iRow][0]*rkPoint[0] +
				m[iRow][1]*rkPoint[1] +
				m[iRow][2]*rkPoint[2];
		}
		return kProd;
	}

	//-----------------------------------------------------------------------
	Vector3 operator* (const Vector3& rkPoint, const Matrix3& rkMatrix)
	{
		Vector3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				rkPoint[0]*rkMatrix.m[0][iRow] +
				rkPoint[1]*rkMatrix.m[1][iRow] +
				rkPoint[2]*rkMatrix.m[2][iRow];
		}
		return kProd;
	}

	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator* (Real fScalar) const
	{
		Matrix3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kProd[iRow][iCol] = fScalar*m[iRow][iCol];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Matrix3 operator* (Real fScalar, const Matrix3& rkMatrix)
	{
		Matrix3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kProd[iRow][iCol] = fScalar*rkMatrix.m[iRow][iCol];
		}
		return kProd;
	}

	//-----------------------------------------------------------------------
	Matrix3 Matrix3::Transpose () const
	{
		Matrix3 kTranspose;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kTranspose[iRow][iCol] = m[iCol][iRow];
		}
		return kTranspose;
	}

	//-----------------------------------------------------------------------
	Matrix3 Matrix3::Inverse (Real fTolerance) const
	{
		Matrix3 kInverse = Matrix3::ZERO;
		Inverse(kInverse,fTolerance);
		return kInverse;
	}

	//--------------------------------------------------------------------------
	bool Matrix3::Inverse (Matrix3& rkInverse, Real fTolerance) const
	{
		// Invert a 3x3 using cofactors.  This is about 8 times faster than
		// the Numerical Recipes code which uses Gaussian elimination.
		rkInverse[0][0] = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		rkInverse[0][1] = m[0][2]*m[2][1] -
			m[0][1]*m[2][2];
		rkInverse[0][2] = m[0][1]*m[1][2] -
			m[0][2]*m[1][1];
		rkInverse[1][0] = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		rkInverse[1][1] = m[0][0]*m[2][2] -
			m[0][2]*m[2][0];
		rkInverse[1][2] = m[0][2]*m[1][0] -
			m[0][0]*m[1][2];
		rkInverse[2][0] = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];
		rkInverse[2][1] = m[0][1]*m[2][0] -
			m[0][0]*m[2][1];
		rkInverse[2][2] = m[0][0]*m[1][1] -
			m[0][1]*m[1][0];

		Real fDet =
			m[0][0]*rkInverse[0][0] +
			m[0][1]*rkInverse[1][0]+
			m[0][2]*rkInverse[2][0];

		if ( abs(fDet) <= fTolerance )
			return false;

		Real fInvDet = 1.0f/fDet;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				rkInverse[iRow][iCol] *= fInvDet;
		}

		return true;
	}	
}
