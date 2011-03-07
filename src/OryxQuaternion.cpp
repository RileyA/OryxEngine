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
#include "OryxQuaternion.h"
#include "OryxMatrix4.h"
#include "OryxMatrix3.h"

namespace Oryx
{
	const Quaternion Quaternion::ZERO(0,0,0,0);
    const Quaternion Quaternion::IDENTITY(0,0,0,1);

    void Quaternion::FromAngleAxis (const Real& rfAngle,
        const Vector3& rkAxis)
    {
        float fHalfAngle ( 0.5*rfAngle );
        Real fSin = sin(fHalfAngle);
        w = cos(fHalfAngle);
        x = fSin*rkAxis.x;
        y = fSin*rkAxis.y;
        z = fSin*rkAxis.z;
    }

	Vector3 Quaternion::operator* (Vector3 v)
    {
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = qvec.crossProduct(v);
		uuv = qvec.crossProduct(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;
		return v + uv + uuv;
    }
    //-----------------------------------------------------------------------
	Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
    {
        return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
    }
    //----------------------------------------------------------------------
    Quaternion Quaternion::operator- (const Quaternion& rkQ) const
    {
        return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
    }
    //-----------------------------------------------------------------------
	
    Quaternion Quaternion::operator* (const Quaternion& rkQ) const
    {
        // NOTE:  Multiplication is not generally commutative, so in most
        // cases p*q != q*p.

        return Quaternion
        (
            w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
            w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
            w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
            w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
        );
    }
    //-----------------------------------------------------------------------
	
    Quaternion Quaternion::operator* (Real fScalar) const
    {
        return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
    }
	//-----------------------------------------------------------------------

    Quaternion Quaternion::operator- () const
    {
        return Quaternion(-w,-x,-y,-z);
    }
	//-----------------------------------------------------------------------

    Quaternion operator* (Real fScalar, const Quaternion& rkQ)
    {
        return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
            fScalar*rkQ.z);
    }
	//-----------------------------------------------------------------------
	
	void Quaternion::FromRotationMatrix (const Matrix3& kRot)
    {
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "Quaternion Calculus and Fast Animation".

        Real fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
        Real fRoot;

        if ( fTrace > 0.0 )
        {
            // |w| > 1/2, may as well choose w > 1/2
            fRoot = sqrt(fTrace + 1.0f);  // 2w
            w = 0.5f*fRoot;
            fRoot = 0.5f/fRoot;  // 1/(4w)
            x = (kRot[2][1]-kRot[1][2])*fRoot;
            y = (kRot[0][2]-kRot[2][0])*fRoot;
            z = (kRot[1][0]-kRot[0][1])*fRoot;
        }
        else
        {
            // |w| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if ( kRot[1][1] > kRot[0][0] )
                i = 1;
            if ( kRot[2][2] > kRot[i][i] )
                i = 2;
            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
            Real* apkQuat[3] = { &x, &y, &z };
            *apkQuat[i] = 0.5f*fRoot;
            fRoot = 0.5f/fRoot;
            w = (kRot[k][j]-kRot[j][k])*fRoot;
            *apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
            *apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
        }
    }

	void Quaternion::ToRotationMatrix (Matrix3& kRot) const
    {
        Real fTx  = x+x;
        Real fTy  = y+y;
        Real fTz  = z+z;
        Real fTwx = fTx*w;
        Real fTwy = fTy*w;
        Real fTwz = fTz*w;
        Real fTxx = fTx*x;
        Real fTxy = fTy*x;
        Real fTxz = fTz*x;
        Real fTyy = fTy*y;
        Real fTyz = fTz*y;
        Real fTzz = fTz*z;

        kRot[0][0] = 1.0f-(fTyy+fTzz);
        kRot[0][1] = fTxy-fTwz;
        kRot[0][2] = fTxz+fTwy;
        kRot[1][0] = fTxy+fTwz;
        kRot[1][1] = 1.0f-(fTxx+fTzz);
        kRot[1][2] = fTyz-fTwx;
        kRot[2][0] = fTxz-fTwy;
        kRot[2][1] = fTyz+fTwx;
        kRot[2][2] = 1.0f-(fTxx+fTyy);
    }

    //-----------------------------------------------------------------------
    Real Quaternion::normalize(void)
    {
        Real len = w*w+x*x+y*y+z*z;
        Real factor = 1.0f / sqrt(len);
        *this = *this * factor;
        return len;
    }
	//-----------------------------------------------------------------------
	
    Real Quaternion::Dot (const Quaternion& rkQ) const
    {
        return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
    }
	//-----------------------------------------------------------------------
	
    Quaternion Quaternion::Inverse () const
    {
        Real fNorm = w*w+x*x+y*y+z*z;
        if ( fNorm > 0.0 )
        {
            Real fInvNorm = 1.0f/fNorm;
            return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
        }
        else
        {
            // return an invalid result to flag the error
            return Quaternion(0,0,0,0);
        }
    }
	//-----------------------------------------------------------------------
	
    Quaternion Quaternion::Slerp (Real fT, const Quaternion& rkP,
        const Quaternion& rkQ, bool shortestPath)
    {
        Real fCos = rkP.Dot(rkQ);
        Quaternion rkT;

        // Do we need to invert rotation?
        if (fCos < 0.0f && shortestPath)
        {
            fCos = -fCos;
            rkT = -rkQ;
        }
        else
        {
            rkT = rkQ;
        }

        if (abs(fCos) < 1 - 1e-03)
        {
            // Standard case (slerp)
            Real fSin = sqrt(1 - fCos*fCos);
            Real fAngle = atan2(fSin, fCos);
            Real fInvSin = 1.0f / fSin;
            Real fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
            Real fCoeff1 = sin(fT * fAngle) * fInvSin;
            return fCoeff0 * rkP + fCoeff1 * rkT;
        }
        else
        {
            // There are two situations:
            // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
            //    interpolation safely.
            // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
            //    are an infinite number of possibilities interpolation. but we haven't
            //    have method to fix this case, so just use linear interpolation here.
            Quaternion t = (1.0f - fT) * rkP + fT * rkT;
            // taking the complement requires renormalisation
            t.normalize();
            return t;
        }
    }
}
