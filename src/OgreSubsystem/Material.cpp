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

#include "Material.h"
#include "OgreConversions.h"

namespace Oryx
{
	Material::Material(String name)
		:mName(name)
	{
		mMaterial = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingletonPtr()->getByName(name)).getPointer();
		if(!mMaterial)
		{
			// TODO create a material
		}
	}
	//-----------------------------------------------------------------------

	void Material::setTexture(size_t index, String name)
	{
		mMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(index)->setTextureName(name);
	}
	//-----------------------------------------------------------------------

	void Material::setTexture(size_t index, Color colour)
	{
		mMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(index)->setColourOperationEx(
			Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_CURRENT,convertOgre(colour));
	}
	//-----------------------------------------------------------------------

	String Material::cloneMe()
	{
		int i = 0;
		while(1)
		{
			if(!Ogre::MaterialManager::getSingletonPtr()->resourceExists(
				mName+StringUtils::toString(i)))
				break;
			++i;
		}

		mMaterial->clone(mName+StringUtils::toString(i));
		return mName+StringUtils::toString(i);
	}
	//-----------------------------------------------------------------------
}
