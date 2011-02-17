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

#include "Oryx.h"
#include "Decal.h"
#include "Oryx3DMath.h"
#include "Ogre.h"
#include "OgreConversions.h"

namespace Oryx
{
	Decal::Decal(String name,Ogre::SceneNode* node,Mesh* target)
		:SceneNode(name,node),mTarget(target)
	{
		recalculate();	
	}

	Decal::~Decal()
	{
		for(uint i=0;i<mDecals.size();++i)
		{
			mNode->getCreator()->destroyEntity(mDecals[i]);
		}
	}

	void Decal::recalculate()
	{
		
	}

	//void Decal::generateMesh()
	//{
	//	
	//}
}
