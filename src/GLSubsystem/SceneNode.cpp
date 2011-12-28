#include "SceneNode.h"
#include "GLSubsystem.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace Oryx
{
	SceneNode::SceneNode()
	{
		mPosition = Vector3::ZERO;
		mOrientation = Quaternion::IDENTITY;
		mParent = 0;
	}
	//--------------------------------------------------------------------------

	SceneNode::~SceneNode()
	{
		for(std::list<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
			delete (*it);
	}
	//--------------------------------------------------------------------------

	void SceneNode::setPosition(Vector3 position)
	{
		mPosition = position;
	}
	//--------------------------------------------------------------------------

	Vector3 SceneNode::getPosition()
	{
		return mPosition;
	}
	//--------------------------------------------------------------------------

	Vector3 SceneNode::getAbsolutePosition()
	{
		return mPosition + (mParent ? mParent->getAbsolutePosition() : Vector3::ZERO);
	}
	//--------------------------------------------------------------------------

	Quaternion SceneNode::getAbsoluteOrientation()
	{
		return mOrientation;
	}
	//--------------------------------------------------------------------------

	void SceneNode::rotate(Quaternion q)
	{
		q.normalize();
		mOrientation = mOrientation * q;
	}
	//--------------------------------------------------------------------------

	void SceneNode::yaw(Real angle)
	{
		Quaternion rot;
		rot.FromAngleAxis(angle * 3.14159/180.f, Vector3::UNIT_Y);
		rotate(rot);
	}
	//--------------------------------------------------------------------------

	void SceneNode::pitch(Real angle)
	{
		Quaternion rot;
		rot.FromAngleAxis(angle * 3.14159/180.f, Vector3::UNIT_X);
		rotate(rot);
	}
	//--------------------------------------------------------------------------

	void SceneNode::roll(Real angle)
	{
		Quaternion rot;
		rot.FromAngleAxis(angle * 3.14159/180.f, Vector3::UNIT_Z);
		rotate(rot);
	}
	//--------------------------------------------------------------------------

	Matrix4 SceneNode::getTransform()
	{
		Matrix4 transform(mOrientation);
		transform.setTrans(mPosition);
		return transform;
	}
	//--------------------------------------------------------------------------
	
	void SceneNode::addChild(SceneNode* node)
	{
		if(node && !node->mParent)
		{
			node->mParent = this;
			mChildren.push_back(node);
		}
	}
	//--------------------------------------------------------------------------

	bool SceneNode::hasChild(SceneNode* node)
	{
		for(std::list<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
			if(*it == node)
				return true;
		return false;
	}
	//--------------------------------------------------------------------------
	
	void SceneNode::removeChild(SceneNode* node)
	{
		for(std::list<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
		{
			if(*it == node)
			{
				node->mParent = 0;
				mChildren.erase(it);
				break;
			}
		}
	}
	//--------------------------------------------------------------------------
	
	void SceneNode::removeAllChildren()
	{
		for(std::list<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
			(*it)->mParent = 0;
		mChildren.clear();
	}
	//--------------------------------------------------------------------------
	
	void SceneNode::_render(GLSubsystem* gl)
	{
		// save previous state
		Matrix4 original = gl->getWorldMatrix();

		// transform
		gl->setWorldMatrix(gl->getWorldMatrix() * getTransform());

		// draw this object
		_draw();
		
		// render children
		for(std::list<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
			(*it)->_render(gl);

		// restore prior state
		gl->setWorldMatrix(original);
	}
	//--------------------------------------------------------------------------
	
	void SceneNode::_draw()
	{
		// just a triangle...
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 1.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-1.f, -1.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.f, -1.f, 0.f);
		glEnd();
	}
	//--------------------------------------------------------------------------
}

