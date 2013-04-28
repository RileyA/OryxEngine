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

#include "CharPrimitive.h"
#include "BulletSubsystem.h"
//#include "CCT_Primitive.h"
#include "btBulletDynamicsCommon.h"
#include <algorithm>

namespace Oryx
{

	CharPrimitive::CharPrimitive(BulletSubsystem* bull,Vector3 pos, Real radius, Real skinWidth)
		:mBullet(bull),mPosition(pos),mRadius(radius),mSkinWidth(skinWidth)
	{
		mSphere = mBullet->createSphereShape(mRadius);
	}
	//-----------------------------------------------------------------------
	
	Vector3 CharPrimitive::move(Vector3 direction, Real distance, int maxDepth)
	{

    std::cout<<"lenm: "<<distance<<"\n";

		if (distance < 0.f) {
			distance *= -1.f;
			direction *= -1.f;
		}

		if(maxDepth <= 0)
			return Vector3::ZERO;
		
		Real castLength = distance + mSkinWidth;
		SweepReport s = mBullet->sweep(mSphere, mPosition, direction, castLength,
			COLLISION_GROUP_3,COLLISION_GROUP_3);
		
		if(!s.hit)
    {
			return direction * distance;
		} 
		else
		{
			Real travel = castLength * s.hitFraction;


      Vector3 pd = direction.crossProduct(s.normal);
      Plane p;
      pd.normalize();
      std::cout<<"pd: "<<pd.x<<" "<<pd.y<<" "<<pd.z<<"\n";
      p.n = pd;
      p.d = 0.f;
      Vector3 n = p.projectVector(s.normal);
      Vector3 d = p.projectVector(direction);

      n.normalize();
      d.normalize();

      n *= -mSkinWidth;
      d *= travel;
      std::cout<<"n: "<<n.x<<" "<<n.y<<" "<<n.z<<" "<<n.length()<<"\n";
      std::cout<<"d: "<<d.x<<" "<<d.y<<" "<<d.z<<" "<<d.length()<<"\n";

      Vector3 e = n * (n.dotProduct(d) / (n.dotProduct(n)));
      std::cout<<"e: "<<e.x<<" "<<e.y<<" "<<e.z<<" "<<e.length()<<"\n";
      Real len = e.length();
      e /= len;
      e *= len - mSkinWidth;
      std::cout<<"e: "<<e.x<<" "<<e.y<<" "<<e.z<<" "<<e.length()<<"\n";

      Vector3 r = d * (d.dotProduct(e) / d.dotProduct(d));

      std::cout<<"r: "<<r.x<<" "<<r.y<<" "<<r.z<<" "<<r.length()<<"\n";


      std::cout<<"travel "<<travel<<"\n";

      // how much we'd penetrate the collided pt if we kept going
      /*Real lost = travel - castLength; 

      // offset by skinwidth
      Real actual_travel = travel - mSkinWidth;
      std::cout<<"travela "<<actual_travel<<"\n";

      if (actual_travel < 0.f) {
        actual_travel = 0.f;
      }

      */

      Real actual_travel = r.length();
      // how much slides could go for
      Real remaining_dist = distance - actual_travel;

      Vector3 slide = s.normal * direction.dotProduct(s.normal * -1);
      Vector3 motion = direction * actual_travel;

      std::cout<<"motion: "<<motion.x<<" "<<motion.y<<" "<<motion.z<<"\n";

      std::cout<<"direction: "<<direction.x<<" "<<direction.y<<" "<<direction.z<<"\n";
      std::cout<<"normal: "<<s.normal.x<<" "<<s.normal.y<<" "<<s.normal.z<<"\n";
      Real dot = direction.dotProduct(s.normal) * -1;
      std::cout<<"DOT: "<<dot<<"\n";

      //if (remaining_dist < 0.00001f || fabs(dot) > 0.9f)
      //{
      //  return motion;
      //}
      //else
      //{
        return motion + move(slide, (remaining_dist) * slide.length(), maxDepth -1,
               mPosition + motion);
      //}
		}
	}
	//-----------------------------------------------------------------------

	Vector3 CharPrimitive::move(Vector3 direction, Real distance, int maxDepth, Vector3 position)
	{
    //std::cout<<"direction_s: "<<direction.x<<" "<<direction.y<<" "<<direction.z<<" "<<maxDepth<<"\n";
    std::cout<<"lens: "<<distance<<"\n";
		if (distance < 0.f) {
			distance *= -1.f;
			direction *= -1.f;
		}
    direction.normalize();

		if(maxDepth <= 0)
			return Vector3::ZERO;
		
		Real castLength = distance + mSkinWidth;
		SweepReport s = mBullet->sweep(mSphere, position, direction, castLength,
			COLLISION_GROUP_3,COLLISION_GROUP_3);
		
		if(!s.hit) {
      Vector3 motion = direction * distance;
      std::cout<<"slided_unobstructed: "<<motion.x<<" "<<motion.y<<" "<<motion.z<<"\n";
			return direction * distance;
		} 
		else
		{
			Real travel = castLength * s.hitFraction;

      // how much we'd penetrate the collided pt if we kept going
      Real lost = travel - castLength; 

      // offset by skinwidth
      Real actual_travel = travel - mSkinWidth;

      // how much slides could go for
      Real remaining_dist = distance - actual_travel;

      Vector3 slide = s.normal * direction.dotProduct(s.normal * -1);
      Vector3 motion = direction * actual_travel;

      std::cout<<"slided: "<<motion.x<<" "<<motion.y<<" "<<motion.z<<"\n";

      if (remaining_dist < 0.00001f)
      {
        return motion;
      }
      else
      {
        return motion + move(slide, remaining_dist, maxDepth -1,
               mPosition + motion);
      }
		}
	}
	
	void CharPrimitive::translate(Vector3 v)
	{
		mPosition += v;
	}
	//-----------------------------------------------------------------------
	
	Vector3 CharPrimitive::getPosition()
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
}
