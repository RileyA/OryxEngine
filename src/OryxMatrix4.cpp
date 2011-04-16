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
#include "OryxMatrix4.h"

namespace Oryx
{
    const Matrix4 Matrix4::ZERO(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 );

    const Matrix4 Matrix4::IDENTITY(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );

    const Matrix4 Matrix4::CLIPSPACE2DTOIMAGESPACE(
        0.5,    0,  0, 0.5, 
          0, -0.5,  0, 0.5, 
          0,    0,  1,   0,
          0,    0,  0,   1);
    //-----------------------------------------------------------------------

    Matrix4 Matrix4::inverse() const
    {
        Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
        Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
        Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
        Real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

        Real v0 = m20 * m31 - m21 * m30;
        Real v1 = m20 * m32 - m22 * m30;
        Real v2 = m20 * m33 - m23 * m30;
        Real v3 = m21 * m32 - m22 * m31;
        Real v4 = m21 * m33 - m23 * m31;
        Real v5 = m22 * m33 - m23 * m32;

        Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
        Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
        Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
        Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

        Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        Real d00 = t00 * invDet;
        Real d10 = t10 * invDet;
        Real d20 = t20 * invDet;
        Real d30 = t30 * invDet;

        Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        return Matrix4(
            d00, d01, d02, d03,
            d10, d11, d12, d13,
            d20, d21, d22, d23,
            d30, d31, d32, d33);
    }
    //-----------------------------------------------------------------------

    void Matrix4::makeTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation)
    {
        // Ordering:
        //    1. Scale
        //    2. Rotate
        //    3. Translate

        Matrix3 rot3x3;
        orientation.ToRotationMatrix(rot3x3);

        // Set up final matrix with scale, rotation and translation
        m[0][0] = scale.x * rot3x3[0][0]; m[0][1] = scale.y * rot3x3[0][1]; m[0][2] = scale.z * rot3x3[0][2]; m[0][3] = position.x;
        m[1][0] = scale.x * rot3x3[1][0]; m[1][1] = scale.y * rot3x3[1][1]; m[1][2] = scale.z * rot3x3[1][2]; m[1][3] = position.y;
        m[2][0] = scale.x * rot3x3[2][0]; m[2][1] = scale.y * rot3x3[2][1]; m[2][2] = scale.z * rot3x3[2][2]; m[2][3] = position.z;

        // No projection term
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
    //-----------------------------------------------------------------------

    void Matrix4::makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation)
    {
        // Invert the parameters
        Vector3 invTranslate = Vector3(-position.x,-position.y,-position.z);
        Vector3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
        Quaternion invRot = orientation.inverse();

        // Because we're inverting, order is translation, rotation, scale
        // So make translation relative to scale & rotation
        invTranslate = invRot * invTranslate; // rotate
        invTranslate *= invScale; // scale

        // Next, make a 3x3 rotation matrix
        Matrix3 rot3x3;
        invRot.ToRotationMatrix(rot3x3);

        // Set up final matrix with scale, rotation and translation
        m[0][0] = invScale.x * rot3x3[0][0]; m[0][1] = invScale.x * rot3x3[0][1]; m[0][2] = invScale.x * rot3x3[0][2]; m[0][3] = invTranslate.x;
        m[1][0] = invScale.y * rot3x3[1][0]; m[1][1] = invScale.y * rot3x3[1][1]; m[1][2] = invScale.y * rot3x3[1][2]; m[1][3] = invTranslate.y;
        m[2][0] = invScale.z * rot3x3[2][0]; m[2][1] = invScale.z * rot3x3[2][1]; m[2][2] = invScale.z * rot3x3[2][2]; m[2][3] = invTranslate.z;		

        // No projection term
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }
	//-----------------------------------------------------------------------
}
