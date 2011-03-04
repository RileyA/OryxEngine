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

#ifndef ORYX_OBJECT_H
#define ORYX_OBJECT_H

#include "Oryx.h"
#include "OryxEventHandler.h"

namespace Oryx
{
	/** A game Object, just about anything that isn't a subsystem or state
	 *		(e.g. A tree, a soldier, a score handler, etc..) */
	class ORYX_EXPORT Object : public EventHandler
	{
	public:
		
		/** Constructor
		 *		@param bucket The bucket to place this object in 
		 *		@param name The name to use */
		Object(String bucket="Default",String name="AUTONAMEME");
		virtual ~Object();

		/** Generates a unique ID value */
		static OryxID generateID()
		{
			#ifdef ORYX_REUSE_OBJECT_IDS
			if(!msFreeIDs.empty())
			{
				OryxID temp = msFreeIDs.back();
				msFreeIDs.pop_back();
				return temp;
			}
			#endif
			
			++msIDCount;
			return msIDCount-1;
		}

		/** Pure virtual, should update the object
		 *		@param delta The time since last frame */
		virtual void update(Real delta) = 0;

		/** Gets the name of this object */
		String getName()
		{
			return mName;
		}

		/** Gets the ID of this object */
		OryxID getID();

	private:

		String mName;
		OryxID mID;

		static OryxID msIDCount;

		#ifdef ORYX_REUSE_OBJECT_IDS
		// if need be, this can store discarded ID's for reuse
		static std::vector<OryxID> msFreeIDs;
		#endif

	};
}

#endif
