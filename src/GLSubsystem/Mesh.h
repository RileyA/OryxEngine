#ifndef ORYX_Mesh_H
#define ORYX_Mesh_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Oryx3DMath.h"
#include "OryxMatrix4.h"

namespace Oryx
{
	class GLSubsystem;

	class Mesh : public SceneNode
	{
	public:

		Mesh();
		~Mesh();

		virtual void _draw();

	private:

	};
}

#endif

