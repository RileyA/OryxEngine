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

#ifndef ORYX_DECAL_H
#define ORYX_DECAL_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace Oryx
{
	class Mesh;

	class ORYX_OGRE_EXPORT Decal : public SceneNode
	{
	public:

		Decal(String name,Ogre::SceneNode* node,Mesh* target = 0);
		~Decal();

		void recalculate();

	protected:

		// one per affected mesh...
		Mesh* mTarget;// if we're affecting a single mesh (e.g. for a wound decal on a character)
		std::vector<Ogre::Entity*> mDecals;

	};
}

#endif
