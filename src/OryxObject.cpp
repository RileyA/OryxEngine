
//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

#include "Oryx.h"
#include "OryxObject.h"
#include "OryxEngine.h"
#include "OryxBucket.h"

namespace Oryx
{
	OryxID Object::msIDCount = 0;

	Object::Object(String bucket,String name)
	{
		mID = generateID();
		mName = name;
		Engine::getPtr()->getBucket(bucket)->addObject(this);
	}
	//-----------------------------------------------------------------------	

	Object::~Object()
	{
		#ifdef ORYX_REUSE_OBJECT_IDS
		msFreeIDs.push_back(mID);
		#endif
	}
	//-----------------------------------------------------------------------

	OryxID Object::getID()
	{
		return mID;
	}
	//--------------------------------------------------------------------------
}
