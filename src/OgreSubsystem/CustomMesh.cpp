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

#include "CustomMesh.h"

namespace Oryx
{
	void CustomMesh::buildMesh(size_t vertexCount, size_t faceCount, float* pos, float* tex, float* colors, unsigned short* indices)
	{
		using namespace Ogre;
		
		mVisible = true;
		mHide = false;

		mRenderOp.vertexData = new Ogre::VertexData;
		mRenderOp.vertexData->vertexStart = 0;
		Ogre::VertexDeclaration* vdecl = mRenderOp.vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = mRenderOp.vertexData->vertexBufferBinding;
		size_t offset = 0;

		HardwareVertexBufferSharedPtr posVB;
		HardwareVertexBufferSharedPtr texcoordVB;
		HardwareVertexBufferSharedPtr colorVB;
		HardwareVertexBufferSharedPtr indexVB;

		mRenderOp.vertexData->vertexCount = vertexCount;
		
		size_t bufferCount = 0;
		vdecl->addElement(bufferCount, 0, VET_FLOAT3, VES_POSITION);
		vdecl->addElement(++bufferCount, 0, VET_FLOAT4, VES_DIFFUSE);
		vdecl->addElement(++bufferCount, 0, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		bufferCount = 0;

		// Positions
		posVB = HardwareBufferManager::getSingleton().createVertexBuffer(
			3*sizeof(float), vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
		vbind->setBinding(bufferCount, posVB);
		posVB->writeData(0,posVB->getSizeInBytes(), pos, true);

		// Vertex colors
		colorVB = HardwareBufferManager::getSingleton().createVertexBuffer(
			4*sizeof(float), vertexCount, HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
		vbind->setBinding(++bufferCount, colorVB);
		colorVB->writeData(0,colorVB->getSizeInBytes(), colors, true);

		// Texcoords
		texcoordVB = HardwareBufferManager::getSingleton().createVertexBuffer(
			2*sizeof(float), vertexCount,HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		vbind->setBinding(++bufferCount, texcoordVB);
		texcoordVB->writeData(0,sizeof(float) * 2 * vertexCount, tex, true);

		// Indices
		Ogre::HardwareIndexBufferSharedPtr indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(
			HardwareIndexBuffer::IT_16BIT,3*faceCount,HardwareBuffer::HBU_STATIC, true);
		indexBuffer->writeData(0,indexBuffer->getSizeInBytes(),indices,true);
		
		mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		mRenderOp.useIndexes = true;
		mRenderOp.indexData = new Ogre::IndexData;

		// Set index buffer for the render op
		mRenderOp.indexData->indexBuffer = indexBuffer;
		mRenderOp.indexData->indexStart = 0;
		mRenderOp.indexData->indexCount = 3 * faceCount;
	}
	//-----------------------------------------------------------------------

	CustomMesh::~CustomMesh()
	{
		if(mVisible)
		{
			// delete render operation data
			delete mRenderOp.vertexData;
			delete mRenderOp.indexData;
		}

		Ogre::Root::getSingletonPtr()->getSceneManager("mSceneManager")->removeRenderQueueListener(this);
	}
	//-----------------------------------------------------------------------

	void CustomMesh::rebuildMesh(size_t vertexCount, size_t faceCount, float* pos, float* tex, float* colors, unsigned short* indices)
	{
		// TODO do an actual update rather than a full delete and rebuild!
		delete mRenderOp.vertexData;
		delete mRenderOp.indexData;
		mRenderOp.vertexData = 0;
		mRenderOp.indexData = 0;
		buildMesh(vertexCount, faceCount, pos, tex, colors, indices);
	}
	//-----------------------------------------------------------------------

	void CustomMesh::updatePositions(float* pos)
	{
		Ogre::VertexDeclaration* vdecl = mRenderOp.vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = mRenderOp.vertexData->vertexBufferBinding;
		const Ogre::VertexElement* buf = vdecl->findElementBySemantic(Ogre::VES_POSITION);
		Ogre::HardwareVertexBufferSharedPtr buffer = vbind->getBuffer(buf->getSource());
		if(buf && !buffer.isNull())
		{
			buffer->writeData(0,buffer->getSizeInBytes(), pos, true);
		}
		else
		{
			Logger::getPtr()->logMessage("ERROR: Could not find vertex position buffer.");
		}
	}
	//-----------------------------------------------------------------------

	void CustomMesh::updateTexcoords(float* tex)
	{
		Ogre::VertexDeclaration* vdecl = mRenderOp.vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = mRenderOp.vertexData->vertexBufferBinding;
		const Ogre::VertexElement* pos = vdecl->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);
		Ogre::HardwareVertexBufferSharedPtr buffer = vbind->getBuffer(pos->getSource());
		if(pos && !buffer.isNull())
		{
			buffer->writeData(0,buffer->getSizeInBytes(),tex, true);
		}
		else
		{
			Logger::getPtr()->logMessage("ERROR: Could not find texcoord buffer.");
		}
	}
	//-----------------------------------------------------------------------
	
	void CustomMesh::updateColors(float* colors)
	{
		Ogre::VertexDeclaration* vdecl = mRenderOp.vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = mRenderOp.vertexData->vertexBufferBinding;
		const Ogre::VertexElement* pos = vdecl->findElementBySemantic(Ogre::VES_DIFFUSE);
		Ogre::HardwareVertexBufferSharedPtr buffer = vbind->getBuffer(pos->getSource());
		if(pos && !buffer.isNull())
		{
			buffer->writeData(0,buffer->getSizeInBytes(),colors, true);
		}
		else
		{
			Logger::getPtr()->logMessage("ERROR: Could not find vertex color buffer.");
		}
	}
	//-----------------------------------------------------------------------

	void CustomMesh::renderQueueEnded(Ogre::uint8 id, const Ogre::String& invocation, bool& repeat)
	{
		if (!mVisible || id != Ogre::RENDER_QUEUE_OVERLAY || !mHide)
			return;

		Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
		rendersys->setStencilCheckEnabled(false); 

		// setup uniform matrices
		Ogre::Root::getSingletonPtr()->getRenderSystem()->_setWorldMatrix( Ogre::Matrix4::IDENTITY );
		Ogre::Root::getSingletonPtr()->getRenderSystem()->_setProjectionMatrix( Ogre::Matrix4::IDENTITY );
		Ogre::Root::getSingletonPtr()->getRenderSystem()->_setViewMatrix( Ogre::Matrix4::IDENTITY );
	
		// set the material pass
		Ogre::Root::getSingletonPtr()->getSceneManager("mSceneManager")->_setPass(
			mMaterial->getTechnique(0)->getPass(0), false, false);
		
		// actually render the thing
		Ogre::Root::getSingletonPtr()->getRenderSystem()->_render(mRenderOp);
	}
	//-----------------------------------------------------------------------
}

