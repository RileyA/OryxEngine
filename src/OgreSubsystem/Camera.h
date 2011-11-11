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

#ifndef ORYX_OGRE_CAMERA_H
#define ORYX_OGRE_CAMERA_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"

namespace Ogre
{
	class SceneNode;
	class Camera;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT Camera : public SceneNode
	{
	public:

		Camera(String name,Ogre::SceneNode* node,Ogre::Camera* cam);
		virtual ~Camera();

		Ogre::Camera* getCamera();

		Vector2 getScreenCoords(Vector3 worldPos);

		void setFarClip(Real clip);
		Real getFarClip();

		void setNearClip(Real clip);
		Real getNearClip();

		void setCustomNearClipPlane(Plane p);

		void setFOV(Real fov);
		Real getFOV();

		void setAspectRatio(Real ratio);
		Real getAspectRatio();

		Vector3 getAbsoluteDirection();
		Vector3 getDirection();

		Vector3 getAbsoluteRight();
		Vector3 getRight();

		Vector3 getAbsoluteLeft();
		Vector3 getLeft();

		Vector3 getAbsoluteUp();
		Vector3 getUp();

		Vector3 getAbsoluteDown();
		Vector3 getDown();

		void setDirection(Vector3 dir);

		Quaternion getCameraAbsoluteOrientation();
		Quaternion getCameraOrientation();

		// TODO: lots...

	protected:

		Ogre::Camera* mCamera;

	};
}

#endif
