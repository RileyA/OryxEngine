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
	/** This class basically hides away the Chaiscript header, so that client apps 
	 *	don't need to include it and the horrendous compiled times that go with it */
	class ORYX_CHAI_EXPORT ChaiWrapper
	{
	public:

		ChaiWrapper()
			:mChai(){}

		~ChaiWrapper(){}

		/** Returns the Chaiscript subsystem */
		chaiscript::ChaiScript* getChai()
		{
			return &mChai;
		}

		/** Registers a named function with the Chaiscript subsystem 
		 *		@param t A pointer to the function 
		 *		@param name The name to use for it in scripts */
		template<typename T> void registerFunction(T t,String name)
		{
			mChai.add(chaiscript::fun(t),name);
		}
		
		/** Registers a constructor for a class
		 *		@tparam T The constructor's signature 
		 *		@param name The name to use to refer to it */
		template<typename T> void registerConstructor(String name)
		{
			mChai.add(chaiscript::constructor<T>(),name);
		}

		/** Registers a type with Chaiscript
		 *		@tparam T The type to register
		 *		@param name The name to use in the scripting system */
		template<typename T> void registerType(String name)
		{
			mChai.add(chaiscript::user_type<T>(), name);
		}

	protected:

		chaiscript::ChaiScript mChai;

	};
}

#endif
