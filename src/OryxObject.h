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
	class Object : public EventHandler
	{
	public:

		Object(String bucket="Default",String name="AUTONAMEME");
		virtual ~Object();

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

		virtual void update(Real delta) = 0;

		String getName()
		{
			return mName;
		}

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
