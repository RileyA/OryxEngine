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
#ifndef OGRECONVERSIONS_H
#define OGRECONVERSIONS_H

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "OryxColour.h"
#include "Ogre.h"

namespace Oryx
{
	// ogre -> oryx and vice/versa conversions
	Ogre::Vector3 convertOgre(Vector3 v);
	Vector3 convertOgre(Ogre::Vector3 v);

	Ogre::Quaternion convertOgre(Quaternion quat);
	Quaternion convertOgre(Ogre::Quaternion quat);

	Colour convertOgre(Ogre::ColourValue c);
	Ogre::ColourValue convertOgre(Colour c);
}

#endif
