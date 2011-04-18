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

#ifndef ORYX_OGRE_MATERIAL_H
#define ORYX_OGRE_MATERIAL_H

#include "Oryx.h"
#include "OryxColour.h"

namespace Ogre
{
	class Material;
}

namespace Oryx
{
	/** A material for application to a 3d object */
	class Material
	{
	public:

		Material(String name);

		/** Sets the texture at the specified index
		 *		@param index The texture_unit to refer to 
		 *		@param name The name of the new texture file*/
		void setTexture(size_t index, String name);
		/** Sets the texture at the specified index
		 *		@param index The texture_unit to refer to 
		 *		@param colour The soliud color to use as a texture */
		void setTexture(size_t index, Colour colour);

		/** Clones this material
		 *		@return The name of the new material*/
		String cloneMe();

	private:

		String mName;
		Ogre::Material* mMaterial;

	};
}

#endif
