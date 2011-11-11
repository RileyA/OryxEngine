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
#include "SceneNode.h"
#include "Oryx3DMath.h"
#include "Ogre.h"
#include "OgreConversions.h"

namespace Oryx
{
	SceneNode::SceneNode(String name,Ogre::SceneNode* node)
		:mName(name),mNode(node){}

	SceneNode::~SceneNode()
	{
		mNode->getCreator()->destroySceneNode(mNode);
	}
	//-----------------------------------------------------------------------
	void SceneNode::setPosition(Vector3 pos)
	{
		mNode->setPosition(convertOgre(pos));
	}

	//-----------------------------------------------------------------------
	Vector3 SceneNode::getPosition()
	{
		return convertOgre(mNode->getPosition());
	}
	//-----------------------------------------------------------------------
	
	Vector3 SceneNode::getAbsolutePosition()
	{
		return convertOgre(mNode->_getDerivedPosition());
	}
	//-----------------------------------------------------------------------	
	
	void SceneNode::setOrientation(Quaternion ori)
	{
		mNode->setOrientation(convertOgre(ori));	
	}
	//-----------------------------------------------------------------------
	
	Quaternion SceneNode::getOrientation()
	{
		return convertOgre(mNode->getOrientation());
	}
	//-----------------------------------------------------------------------
	
	Quaternion SceneNode::getAbsoluteOrientation()
	{
		return convertOgre(mNode->_getDerivedOrientation());
	}
	//-----------------------------------------------------------------------
	
	void SceneNode::setScale(Vector3 scale)
	{
		mNode->setScale(convertOgre(scale));
	}
	//-----------------------------------------------------------------------
	
	void SceneNode::setVisible(bool v)
	{
		mNode->setVisible(v);
	}
	//-----------------------------------------------------------------------
	
//	bool SceneNode::isVisible()
//	{
//		return mNode->isVisible();
//	}
	//-----------------------------------------------------------------------
	
	void SceneNode::roll(Real angle)
	{
		mNode->roll(Ogre::Radian(Ogre::Degree(angle)));
	}
	//-----------------------------------------------------------------------

	void SceneNode::yaw(Real angle)
	{
		mNode->yaw(Ogre::Radian(Ogre::Degree(angle)));
	}
	//-----------------------------------------------------------------------

	void SceneNode::pitch(Real angle)
	{
		mNode->pitch(Ogre::Radian(Ogre::Degree(angle)));
	}
	//-----------------------------------------------------------------------	

	void SceneNode::rotate(Quaternion q)
	{
		mNode->rotate(convertOgre(q));
	}
	//-----------------------------------------------------------------------

	void SceneNode::addChild(SceneNode* child)
	{
		mNode->addChild(child->getNode());
		mChildren.push_back(child);
		child->setParent(this);
	}
	//-----------------------------------------------------------------------

	void SceneNode::removeChild(SceneNode* child)
	{
		std::vector<SceneNode*>::iterator i = mChildren.begin();
		for(i;i!=mChildren.end();++i)
		{
			if((*i)==child)
			{
				mNode->removeChild((*i)->getName());
				(*i)->setParent(0);
				mChildren.erase(i);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------

	void SceneNode::removeChild(String name)
	{
		std::vector<SceneNode*>::iterator i = mChildren.begin();
		for(i;i!=mChildren.end();++i)
		{
			if((*i)->getName()==name)
			{
				mNode->removeChild((*i)->getName());
				(*i)->setParent(0);
				mChildren.erase(i);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------

	void SceneNode::removeAllChildren()
	{
		std::vector<SceneNode*>::iterator i = mChildren.begin();
		for(i;i!=mChildren.end();++i)
			(*i)->setParent(0);
		mChildren.clear();
		mNode->removeAllChildren();
	}
	//-----------------------------------------------------------------------

	SceneNode* SceneNode::getParent()
	{
		return mParent;
	}
	//-----------------------------------------------------------------------

	SceneNode* SceneNode::getChild(String name)
	{
		std::vector<SceneNode*>::iterator i = mChildren.begin();
		for(i;i!=mChildren.end();++i)
		{
			if((*i)->getName()==name)
				return (*i);
		}
		return 0;
	}
	//-----------------------------------------------------------------------

	std::vector<SceneNode*> SceneNode::getChildren()
	{
		return mChildren;// a copy of the whole thing
	}
	//-----------------------------------------------------------------------

	int SceneNode::getChildCount()
	{
		return mChildren.size();
	}
	//-----------------------------------------------------------------------

	void SceneNode::setParent(SceneNode* parent)
	{
		mParent = parent;
	}
	//-----------------------------------------------------------------------

	Ogre::SceneNode* SceneNode::getNode()
	{
		return mNode;
	}
	//--------------------------------------------------------------------------
	
	Vector3 SceneNode::worldToLocalPosition(Vector3 pos)
	{
		return convertOgre(mNode->convertWorldToLocalPosition(convertOgre(pos)));
	}
	//-----------------------------------------------------------------------

	Quaternion SceneNode::worldToLocalOrientation(Quaternion quat)
	{
		return convertOgre(mNode->convertWorldToLocalOrientation(convertOgre(quat)));
	}
	//-----------------------------------------------------------------------

	Vector3 SceneNode::localToWorldPosition(Vector3 pos)
	{
		return convertOgre(mNode->convertLocalToWorldPosition(convertOgre(pos)));
	}
	//-----------------------------------------------------------------------

	Quaternion SceneNode::localToWorldOrientation(Quaternion quat)
	{
		return convertOgre(mNode->convertLocalToWorldOrientation(convertOgre(quat)));
	}
	//-----------------------------------------------------------------------
}
