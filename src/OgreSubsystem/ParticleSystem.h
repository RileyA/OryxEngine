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

#ifndef ORYX_OGRE_PARTICLESYSTEM_H
#define ORYX_OGRE_PARTICLESYSTEM_H

#include "Oryx.h"
#include "SceneNode.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"

namespace Ogre
{
	class SceneNode;
	class ParticleSystem;
}

namespace Oryx
{
	class ORYX_OGRE_EXPORT ParticleSystem : public SceneNode
	{
	public:

		ParticleSystem(String name,Ogre::SceneNode* node,Ogre::ParticleSystem* light);
		virtual ~ParticleSystem();

		void scale(Real scale);

		bool isDone();
		void restart();

		// TODO: materials, animation, etc

	protected:

		Ogre::ParticleSystem* mParticleSystem;

	};
}

#endif
