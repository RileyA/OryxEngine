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

#ifndef LUAWRAPPER_H
#define LUAWRAPPER_H

#include "Oryx.h"
#include "Luadllmain.h"

extern "C"
{
	#include "lua.h"
}

#include <luabind/luabind.hpp>

void print(Oryx::String out);
void println(Oryx::String out);

namespace Oryx
{
	class ORYX_LUA_EXPORT LuaWrapper
	{
	public:

		LuaWrapper()
		{
			mLua = lua_open();
			luabind::open(mLua);
			registerFunction(&print,"print");
			registerFunction(&println,"println");
		}

		~LuaWrapper()
		{
			lua_close(mLua);
		}

		/** Returns the lua subsystem */
		lua_State* getLua()
		{
			return mLua;
		}

		/** Registers a named function with the lua subsystem 
		 *		@param t A pointer to the function 
		 *		@param name The name to use for it in scripts */
		template<typename T> void registerFunction(T t,String name, String nspace = "_default")
		{
			if(nspace != "_default")
			{
				luabind::module(mLua, nspace.c_str())
				[
					luabind::def(name.c_str(), t)
				];
			}
			else
			{
				luabind::module(mLua)
				[
					luabind::def(name.c_str(), t)
				];
			}
		}
		
		/** Registers a constructor for a class
		 *		@tparam T The constructor's signature 
		 *		@param name The name to use to refer to it */
		//template<typename T> void registerConstructor(String name)
		//{
		//    mChai.add(chaiscript::constructor<T>(),name);
		//}

		/** Registers a type with Chaiscript
		 *		@tparam T The type to register
		 *		@param name The name to use in the scripting system */
		//template<typename T> void registerType(String name)
		//{
		//	mChai.add(chaiscript::user_type<T>(), name);
		//}

	protected:

		lua_State* mLua;

	};
}

void print(Oryx::String out)
{
	std::cout<<out;
}

void println(Oryx::String out)
{
	std::cout<<out<<std::endl;
}

#endif
