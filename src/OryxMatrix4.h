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

#ifndef ORYX_MATRIX4_H
#define ORYX_MATRIX4_H

#include "Oryx.h"
#include "OryxMatrix3.h"

namespace Oryx
{
	/** a 4x4 matrix, adapted from Ogre3d's implementation (iself an 
	 *		adaptation of the Wild Magic 0.2 Matrix library 
	 *		(http://www.geometrictools.com/)) */
	class ORYX_EXPORT Matrix4
	{
	protected:

		union
		{
			Real m[4][4];
			Real _m[16];
		};

	public:

		Matrix4(){}
		Matrix4(
			Real m00, Real m01, Real m02, Real m03,
			Real m10, Real m11, Real m12, Real m13,
			Real m20, Real m21, Real m22, Real m23,
			Real m30, Real m31, Real m32, Real m33 )
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		/** Creates a standard 4x4 transformation matrix with a zero 
		 *	translation part from a rotation/scaling 3x3 matrix. 
		 *		@param m3x3 The rotation matrix to use */
		Matrix4(const Matrix3& m3x3)
		{
		  operator=(IDENTITY);
		  operator=(m3x3);
		}

		/** Creates a standard 4x4 transformation matrix with a zero translation part from a rotation/scaling Quaternion.*/
		Matrix4(const Quaternion& rot)
		{
		  Matrix3 m3x3;
		  rot.ToRotationMatrix(m3x3);
		  operator=(IDENTITY);
		  operator=(m3x3);
		}
		

		/** Exchange the contents of this matrix with another. 
		*/
		void swap(Matrix4& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[0][3], other.m[0][3]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[1][3], other.m[1][3]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
			std::swap(m[2][3], other.m[2][3]);
			std::swap(m[3][0], other.m[3][0]);
			std::swap(m[3][1], other.m[3][1]);
			std::swap(m[3][2], other.m[3][2]);
			std::swap(m[3][3], other.m[3][3]);
		}

		Real* operator [] ( size_t iRow )
		{
			return m[iRow];
		}

		const Real *operator [] ( size_t iRow ) const
		{
			return m[iRow];
		}

		Matrix4 concatenate(const Matrix4 &m2) const
		{
			Matrix4 r;
			r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0]
				+ m[0][3] * m2.m[3][0];
			r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1]
				+ m[0][3] * m2.m[3][1];
			r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2]
				+ m[0][3] * m2.m[3][2];
			r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3]
				+ m[0][3] * m2.m[3][3];

			r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0]
				+ m[1][3] * m2.m[3][0];
			r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1]
				+ m[1][3] * m2.m[3][1];
			r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2]
				+ m[1][3] * m2.m[3][2];
			r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3]
				+ m[1][3] * m2.m[3][3];

			r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0]
				+ m[2][3] * m2.m[3][0];
			r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1]
				+ m[2][3] * m2.m[3][1];
			r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2]
				+ m[2][3] * m2.m[3][2];
			r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3]
				+ m[2][3] * m2.m[3][3];

			r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0]
				+ m[3][3] * m2.m[3][0];
			r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1]
				+ m[3][3] * m2.m[3][1];
			r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2]
				+ m[3][3] * m2.m[3][2];
			r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3]
				+ m[3][3] * m2.m[3][3];

			return r;
		}

		/** Matrix concatenation using '*'.
		*/
		Matrix4 operator * ( const Matrix4 &m2 ) const
		{
			return concatenate( m2 );
		}

		/** Vector transformation using '*'.
			@remarks
				Transforms the given 3-D vector by the matrix, projecting the 
				result back into <i>w</i> = 1.
			@note
				This means that the initial <i>w</i> is considered to be 1.0,
				and then all the tree elements of the resulting 3-D vector are
				divided by the resulting <i>w</i>.
		*/
		Vector3 operator * ( const Vector3 &v ) const
		{
			Vector3 r;

			Real fInvW = 1.0f / ( m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] );

			r.x = ( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] ) * fInvW;
			r.y = ( m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] ) * fInvW;
			r.z = ( m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] ) * fInvW;

			return r;
		}

		/** Matrix addition.
		*/
		Matrix4 operator + ( const Matrix4 &m2 ) const
		{
			Matrix4 r;

			r.m[0][0] = m[0][0] + m2.m[0][0];
			r.m[0][1] = m[0][1] + m2.m[0][1];
			r.m[0][2] = m[0][2] + m2.m[0][2];
			r.m[0][3] = m[0][3] + m2.m[0][3];

			r.m[1][0] = m[1][0] + m2.m[1][0];
			r.m[1][1] = m[1][1] + m2.m[1][1];
			r.m[1][2] = m[1][2] + m2.m[1][2];
			r.m[1][3] = m[1][3] + m2.m[1][3];

			r.m[2][0] = m[2][0] + m2.m[2][0];
			r.m[2][1] = m[2][1] + m2.m[2][1];
			r.m[2][2] = m[2][2] + m2.m[2][2];
			r.m[2][3] = m[2][3] + m2.m[2][3];

			r.m[3][0] = m[3][0] + m2.m[3][0];
			r.m[3][1] = m[3][1] + m2.m[3][1];
			r.m[3][2] = m[3][2] + m2.m[3][2];
			r.m[3][3] = m[3][3] + m2.m[3][3];

			return r;
		}

		/** Matrix subtraction.
		*/
		Matrix4 operator - ( const Matrix4 &m2 ) const
		{
			Matrix4 r;
			r.m[0][0] = m[0][0] - m2.m[0][0];
			r.m[0][1] = m[0][1] - m2.m[0][1];
			r.m[0][2] = m[0][2] - m2.m[0][2];
			r.m[0][3] = m[0][3] - m2.m[0][3];

			r.m[1][0] = m[1][0] - m2.m[1][0];
			r.m[1][1] = m[1][1] - m2.m[1][1];
			r.m[1][2] = m[1][2] - m2.m[1][2];
			r.m[1][3] = m[1][3] - m2.m[1][3];

			r.m[2][0] = m[2][0] - m2.m[2][0];
			r.m[2][1] = m[2][1] - m2.m[2][1];
			r.m[2][2] = m[2][2] - m2.m[2][2];
			r.m[2][3] = m[2][3] - m2.m[2][3];

			r.m[3][0] = m[3][0] - m2.m[3][0];
			r.m[3][1] = m[3][1] - m2.m[3][1];
			r.m[3][2] = m[3][2] - m2.m[3][2];
			r.m[3][3] = m[3][3] - m2.m[3][3];

			return r;
		}

		/** Tests 2 matrices for equality.
		*/
		bool operator == ( const Matrix4& m2 ) const
		{
			if( 
				m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] 
					|| m[0][3] != m2.m[0][3] ||
				m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] 
					|| m[1][3] != m2.m[1][3] ||
				m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] 
					|| m[2][3] != m2.m[2][3] ||
				m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] 
					|| m[3][3] != m2.m[3][3] )
				return false;
			return true;
		}

		/** Tests 2 matrices for inequality.
		*/
		bool operator != ( const Matrix4& m2 ) const
		{
			if( 
				m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] 
					|| m[0][3] != m2.m[0][3] ||
				m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] 
					|| m[1][3] != m2.m[1][3] ||
				m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] 
					|| m[2][3] != m2.m[2][3] ||
				m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] 
					|| m[3][3] != m2.m[3][3] )
				return true;
			return false;
		}

		/** Assignment from 3x3 matrix.
		*/
		void operator = ( const Matrix3& mat3 )
		{
			m[0][0] = mat3.m[0][0]; m[0][1] = mat3.m[0][1]; m[0][2] = mat3.m[0][2];
			m[1][0] = mat3.m[1][0]; m[1][1] = mat3.m[1][1]; m[1][2] = mat3.m[1][2];
			m[2][0] = mat3.m[2][0]; m[2][1] = mat3.m[2][1]; m[2][2] = mat3.m[2][2];
		}

		Matrix4 transpose(void) const
		{
			return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
						   m[0][1], m[1][1], m[2][1], m[3][1],
						   m[0][2], m[1][2], m[2][2], m[3][2],
						   m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		/*
		-----------------------------------------------------------------------
		Translation Transformation
		-----------------------------------------------------------------------
		*/
		/** Sets the translation transformation part of the matrix.
		*/
		void setTrans( const Vector3& v )
		{
			m[0][3] = v.x;
			m[1][3] = v.y;
			m[2][3] = v.z;
		}

		/** Extracts the translation transformation part of the matrix.
		 */
		Vector3 getTrans() const
		{
		  return Vector3(m[0][3], m[1][3], m[2][3]);
		}
		

		/** Builds a translation matrix
		*/
		void makeTrans( const Vector3& v )
		{
			m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = v.x;
			m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = v.y;
			m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = v.z;
			m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
		}

		void makeTrans( Real tx, Real ty, Real tz )
		{
			m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = tx;
			m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = ty;
			m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = tz;
			m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
		}

		/** Gets a translation matrix.
		*/
		static Matrix4 getTrans( const Vector3& v )
		{
			Matrix4 r;

			r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = v.x;
			r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = v.y;
			r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = v.z;
			r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

			return r;
		}

		/** Gets a translation matrix - variation for not using a vector.
		*/
		static Matrix4 getTrans( Real t_x, Real t_y, Real t_z )
		{
			Matrix4 r;

			r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = t_x;
			r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = t_y;
			r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = t_z;
			r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

			return r;
		}

		/*
		-----------------------------------------------------------------------
		Scale Transformation
		-----------------------------------------------------------------------
		*/
		/** Sets the scale part of the matrix.
		*/
		void setScale( const Vector3& v )
		{
			m[0][0] = v.x;
			m[1][1] = v.y;
			m[2][2] = v.z;
		}

		/** Gets a scale matrix.
		*/
		static Matrix4 getScale( const Vector3& v )
		{
			Matrix4 r;
			r.m[0][0] = v.x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
			r.m[1][0] = 0.0; r.m[1][1] = v.y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
			r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = v.z; r.m[2][3] = 0.0;
			r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

			return r;
		}

		/** Gets a scale matrix - variation for not using a vector.
		*/
		static Matrix4 getScale( Real s_x, Real s_y, Real s_z )
		{
			Matrix4 r;
			r.m[0][0] = s_x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
			r.m[1][0] = 0.0; r.m[1][1] = s_y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
			r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = s_z; r.m[2][3] = 0.0;
			r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

			return r;
		}

		/** Extracts the rotation / scaling part of the Matrix as a 3x3 matrix. 
		@param m3x3 Destination Matrix3
		*/
		void extract3x3Matrix(Matrix3& m3x3) const
		{
			m3x3.m[0][0] = m[0][0];
			m3x3.m[0][1] = m[0][1];
			m3x3.m[0][2] = m[0][2];
			m3x3.m[1][0] = m[1][0];
			m3x3.m[1][1] = m[1][1];
			m3x3.m[1][2] = m[1][2];
			m3x3.m[2][0] = m[2][0];
			m3x3.m[2][1] = m[2][1];
			m3x3.m[2][2] = m[2][2];

		}

		/** Extracts the rotation / scaling part as a quaternion from the Matrix. */
		Quaternion extractQuaternion() const
		{
		  Matrix3 m3x3;
		  extract3x3Matrix(m3x3);
		  return Quaternion(m3x3);
		}

		static const Matrix4 ZERO;
		static const Matrix4 IDENTITY;

		/** Useful little matrix which takes 2D clipspace {-1, 1} to {0,1} and inverts the Y. */
		static const Matrix4 CLIPSPACE2DTOIMAGESPACE;

		Matrix4 operator*(Real scalar) const
		{
			return Matrix4(
				scalar*m[0][0], scalar*m[0][1], scalar*m[0][2], scalar*m[0][3],
				scalar*m[1][0], scalar*m[1][1], scalar*m[1][2], scalar*m[1][3],
				scalar*m[2][0], scalar*m[2][1], scalar*m[2][2], scalar*m[2][3],
				scalar*m[3][0], scalar*m[3][1], scalar*m[3][2], scalar*m[3][3]);
		}

		Matrix4 inverse() const;

		/** Building a Matrix4 from orientation / scale / position. */
		void makeTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation);

		/** Building an inverse Matrix4 from orientation / scale / position. */
		void makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation);
	};
}

#endif
