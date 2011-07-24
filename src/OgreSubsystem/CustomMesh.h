//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the license, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTEE; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have recieved a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#ifndef ORYX_CUSTOMMESH_H
#define ORYX_CUSTOMMESH_H

#include "Oryx.h"
#include "Ogredllmain.h"
#include "Oryx3DMath.h"
#include "Ogre.h"

namespace Ogre
{
	class Entity;
	class SceneNode;
}

namespace Oryx
{
	class CustomMesh : public Ogre::RenderQueueListener
	{
	public:
		
		CustomMesh(String material)
			:mVisible(false)
		{
			mMaterial = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingletonPtr()->
				getByName(material)).getPointer();
			Ogre::Root::getSingletonPtr()->getSceneManager("mSceneManager")->addRenderQueueListener(this);
			mRenderOp.vertexData = 0;
			mRenderOp.indexData = 0;
		}

		virtual ~CustomMesh();

		/** Builds the whole thing */
		void buildMesh(size_t vertexCount, size_t faceCount, float* pos, float* tex, float* colors, unsigned short* indices);

		/** rebuilds the whole thing */
		void rebuildMesh(size_t vertexCount, size_t faceCount, float* pos, float* tex, float* colors, unsigned short* indices);

		/** Updates vertex positions */
		void updatePositions(float* pos);

		/** Updates texcoords */
		void updateTexcoords(float* tex);

		/** Updates vertex colors */
		void updateColors(float* colors);

		/** Empty implementations... */
		void preRenderQueues(){}
		void postRenderQueues(){}
		void renderQueueStarted(Ogre::uint8 id, const Ogre::String& invocation, bool& repeat){}
		
		/** Manually render it here. */
		void renderQueueEnded(Ogre::uint8 id, const Ogre::String& invocation, bool& repeat);

	protected:

		Ogre::Material* mMaterial;
		Ogre::RenderOperation mRenderOp;
		size_t mVertexCount;

		bool mVisible;

	};
}

#endif
