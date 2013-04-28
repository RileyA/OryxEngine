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

#ifndef ORYX_OGRE_BILLBOARD_H
#define ORYX_OGRE_BILLBOARD_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"
#include "Material.h"

namespace Ogre
{
	class SceneNode;
	class Entity;
	class BillboardSet;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT BillboardSet : public SceneNode
	{
	public:

		BillboardSet(String name,Ogre::SceneNode* node,Ogre::BillboardSet* bs);
		virtual ~BillboardSet();

		String getMaterialName();
		Material getMaterial();
		void setMaterialName(String name);

    void addBillboard(Vector3 pos, Real w, Real h);

	protected:

		Ogre::BillboardSet* mBill;
	};
}

#endif
