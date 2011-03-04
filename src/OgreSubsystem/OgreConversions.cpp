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

#include "Oryx.h"
#include "OgreConversions.h"

namespace Oryx
{
	Ogre::Vector3 convertOgre(Vector3 v)
	{
		return Ogre::Vector3(v.x,v.y,v.z);
	}
	//-----------------------------------------------------------------------

	Vector3 convertOgre(Ogre::Vector3 v)
	{
		return Vector3(v.x,v.y,v.z);
	}
	//-----------------------------------------------------------------------

	Ogre::Quaternion convertOgre(Quaternion quat)
	{
		return Ogre::Quaternion(quat.w,quat.x,quat.y,quat.z);
	}
	//-----------------------------------------------------------------------
	
	Quaternion convertOgre(Ogre::Quaternion quat)
	{
		return Quaternion(quat.x,quat.y,quat.z,quat.w);
	}
	//-----------------------------------------------------------------------
	
	Colour convertOgre(Ogre::ColourValue c)
	{
		return Colour(c.r,c.g,c.b,c.a);
	}
	//-----------------------------------------------------------------------

	Ogre::ColourValue convertOgre(Colour c)
	{
		return Ogre::ColourValue(c.r,c.g,c.b,c.a);
	}
	//-----------------------------------------------------------------------
}
