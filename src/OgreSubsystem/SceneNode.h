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

#ifndef SCENENODE_H
#define SCENENODE_H

#include "Oryx.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"

namespace Ogre
{
	class SceneNode;
}


namespace Oryx
{
	class ORYX_OGRE_EXPORT SceneNode
	{
	public:

		SceneNode(String name,Ogre::SceneNode* node);
		virtual ~SceneNode();

		String getName(){return mName;}

		void setPosition(Vector3 pos);
		Vector3 getPosition();
		Vector3 getAbsolutePosition();

		void setOrientation(Quaternion ori);
		Quaternion getOrientation();
		Quaternion getAbsoluteOrientation();

		void setDirectionHack(Vector3 dir);
		static Quaternion hack(Vector3 dir, bool* fallback = 0);

		virtual void setScale(Vector3 scale);

		void setVisible(bool v);

		void yaw(Real angle);
		void pitch(Real angle);
		void roll(Real angle);

		void rotate(Quaternion q);

		void addChild(SceneNode* child);
		void removeChild(SceneNode* child);
		void removeChild(String name);
		void removeAllChildren();

		Vector3 worldToLocalPosition(Vector3 pos);
		Quaternion worldToLocalOrientation(Quaternion quat);
		Vector3 localToWorldPosition(Vector3 pos);
		Quaternion localToWorldOrientation(Quaternion quat);

		SceneNode* getParent();
		SceneNode* getChild(String name);
		std::vector<SceneNode*> getChildren();
		int getChildCount();

		void setParent(SceneNode* parent);

		Ogre::SceneNode* getNode();

	protected:

		String mName;
		Ogre::SceneNode* mNode;

		std::vector<SceneNode*> mChildren;
		SceneNode* mParent;
	};
}

#endif
