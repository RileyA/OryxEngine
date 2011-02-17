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

#ifndef CHAIWRAPPER_H
#define CHAIWRAPPER_H

#include "Oryx.h"
#include "Chaidllmain.h"
#include <chaiscript/chaiscript.hpp>

namespace Oryx
{
	class ORYX_CHAI_EXPORT ChaiWrapper
	{
	public:
		ChaiWrapper():mChai(){}
		~ChaiWrapper(){}
		chaiscript::ChaiScript* getChai(){return &mChai;}
		template<typename T> void registerFunction(T t,String name)
		{
		    mChai.add(chaiscript::fun(t),name);
		}
		template<typename T> void registerType(String name)
		{
			mChai.add(chaiscript::user_type<T>(), name);
		}

	protected:
		chaiscript::ChaiScript mChai;
	};
}

#endif
