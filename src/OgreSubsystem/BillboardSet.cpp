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

#include "Oryx.h"
#include "BillboardSet.h"
#include "Oryx3DMath.h"
#include "Ogre.h"
#include "OgreConversions.h"

namespace Oryx
{
  BillboardSet::BillboardSet(String name,Ogre::SceneNode* node,Ogre::BillboardSet* bs)
    :SceneNode(name, node) {
    mBill = bs;
  }
	//--------------------------------------------------------------------------

  BillboardSet::~BillboardSet()
  {
		mNode->getCreator()->destroyBillboardSet(mBill);
  }
	//--------------------------------------------------------------------------
	
	void BillboardSet::setMaterialName(String name)
	{
    mBill->setMaterialName(name);
	}
	//-----------------------------------------------------------------------

	String BillboardSet::getMaterialName()
	{
		return mBill->getMaterialName();
	}
	//-----------------------------------------------------------------------

	Material BillboardSet::getMaterial()
	{
		return Material(getMaterialName());
	}
	//-----------------------------------------------------------------------

  void BillboardSet::addBillboard(Vector3 pos, Real w, Real h) {
    Ogre::Billboard* b = mBill->createBillboard(convertOgre(pos));
    b->setDimensions(w, h);
  }
	//-----------------------------------------------------------------------
}
