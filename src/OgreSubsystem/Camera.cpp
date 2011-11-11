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
#include "Camera.h"
#include "Oryx3DMath.h"
#include "Ogre.h"
#include "OgreConversions.h"

#include "OgreSubsystem.h"
#include "OryxEngine.h"

namespace Oryx
{
	Camera::Camera(String name,Ogre::SceneNode* node,Ogre::Camera* cam)
		:SceneNode(name,node),mCamera(cam)
	{
		mCamera->setPolygonMode(Ogre::PM_SOLID);
	}
	//-----------------------------------------------------------------------

	Camera::~Camera()
	{
		mNode->getCreator()->destroyCamera(mCamera);
	}
	//-----------------------------------------------------------------------

	Ogre::Camera* Camera::getCamera()
	{
		return mCamera;
	}
	//-----------------------------------------------------------------------

	Vector2 Camera::getScreenCoords(Vector3 worldPos)
	{
		Vector3 hcsPosition = convertOgre(mCamera->getProjectionMatrix() * 
			mCamera->getViewMatrix() * convertOgre(worldPos));
		return Vector2(hcsPosition.x,hcsPosition.y);
	}
	//-----------------------------------------------------------------------

	void Camera::setFarClip(Real clip)
	{
		mCamera->setFarClipDistance(clip);
	}
	//-----------------------------------------------------------------------

	Real Camera::getFarClip()
	{
		return mCamera->getFarClipDistance();
	}
	//-----------------------------------------------------------------------

	void Camera::setNearClip(Real clip)
	{
		mCamera->setNearClipDistance(clip);
	}
	//-----------------------------------------------------------------------
	
	Real Camera::getNearClip()
	{
		return mCamera->getNearClipDistance();
	}
	//-----------------------------------------------------------------------

	void Camera::setCustomNearClipPlane(Plane p)
	{
		mCamera->enableCustomNearClipPlane(Ogre::Plane(convertOgre(p.n), p.d));
	}
	//-----------------------------------------------------------------------

	void Camera::setFOV(Real fov)
	{
		mCamera->setFOVy(Ogre::Degree(fov));
	}
	//-----------------------------------------------------------------------

	Real Camera::getFOV()
	{
		return mCamera->getFOVy().valueDegrees();
	}
	//-----------------------------------------------------------------------

	void Camera::setAspectRatio(Real ratio)
	{
		mCamera->setAspectRatio(ratio);
	}
	//-----------------------------------------------------------------------
	
	Real Camera::getAspectRatio()
	{
		return mCamera->getAspectRatio();
	}
	//-----------------------------------------------------------------------

	Vector3 Camera::getAbsoluteDirection()
	{
		return convertOgre(mCamera->getDerivedDirection());	
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getDirection()
	{
		return convertOgre(mCamera->getDirection());
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getAbsoluteRight()
	{
		return convertOgre(mCamera->getDerivedRight());
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getRight()
	{
		return convertOgre(mCamera->getRight());
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getAbsoluteLeft()
	{
		return getAbsoluteRight()*-1.f;
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getLeft()
	{
		return getRight()*-1.f;
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getAbsoluteUp()
	{
		return convertOgre(mCamera->getDerivedUp());
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getUp()
	{
		return convertOgre(mCamera->getUp());
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getAbsoluteDown()
	{
		return getAbsoluteUp()*-1.f;
	}
	//-----------------------------------------------------------------------
	
	Vector3 Camera::getDown()
	{
		return getUp()*-1.f;
	}
	//-----------------------------------------------------------------------	

	void Camera::setDirection(Vector3 dir)
	{
		mCamera->setDirection(convertOgre(dir));
	}
	//-----------------------------------------------------------------------
	
	Quaternion Camera::getCameraAbsoluteOrientation()
	{
		return convertOgre(mCamera->getDerivedOrientation());
	}
	//-----------------------------------------------------------------------	
	
	Quaternion Camera::getCameraOrientation()
	{
		return convertOgre(mCamera->getOrientation());
	}
	//-----------------------------------------------------------------------	

	/*void Camera::setCamOrientation(Quaternion q)
	{
		mCamera->setOrientation(convertOgre(q));
	}
	//-----------------------------------------------------------------------	

	Vector3 Camera::getCamPosition()
	{
		return convertOgre(mCamera->getPosition());
	}
	//-----------------------------------------------------------------------	

	void Camera::setCamPosition(Vector3 p)
	{
		mCamera->setPosition(convertOgre(p));
	}
	//-----------------------------------------------------------------------	
*/
}
