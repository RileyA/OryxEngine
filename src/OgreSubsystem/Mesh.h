//-----------------------------------------------------------------------
// Copyright Riley Adams 2010

// This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#ifndef ORYX_OGRE_MESH_H
#define ORYX_OGRE_MESH_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"
#include "Material.h"

namespace Ogre
{
	class SceneNode;
	class Entity;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT Mesh : public SceneNode
	{
	public:

		Mesh(String name,Ogre::SceneNode* node,Ogre::Entity* ent);
		virtual ~Mesh();

		/** Copies this mesh's vertex/etc data into a MeshData object */
		void getMeshData(MeshData& out, bool texcoords = true, bool normals = true,
			bool indices = true, bool vertices = true);

		String getMaterialName(size_t submeshIndex = 0);
		Material getMaterial(size_t submeshIndex = 0);
		
		void setMaterialName(String name, int submeshIndex = -1);

		void update(MeshData& d);
		void updatePositions(MeshData& d);
		void updateNormals(MeshData& d);

		// TODO: materials, animation, etc

	protected:

		Ogre::Entity* mEntity;
	};
}

#endif
