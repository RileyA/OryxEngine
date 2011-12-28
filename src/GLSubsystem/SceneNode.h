#ifndef ORYX_SceneNode_H
#define ORYX_SceneNode_H

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "OryxMatrix4.h"

namespace Oryx
{
	class GLSubsystem;

	class SceneNode
	{
	public:

		SceneNode();
		~SceneNode();

		void setPosition(Vector3 position);
		Vector3 getPosition();

		Vector3 getAbsolutePosition();
		Quaternion getAbsoluteOrientation();

		void rotate(Quaternion q);

		void yaw(Real angle);
		void pitch(Real angle);
		void roll(Real angle);

		Matrix4 getTransform();

		void addChild(SceneNode* node);
		bool hasChild(SceneNode* node);
		void removeChild(SceneNode* node);
		void removeAllChildren();

		void _render(GLSubsystem* gl);
		virtual void _draw();


	private:

		std::list<SceneNode*> mChildren;
		SceneNode* mParent;

		Vector3 mPosition;
		Quaternion mOrientation;
	};
}

#endif

