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
#include "Mesh.h"
#include "Oryx3DMath.h"
#include "Ogre.h"
#include "OgreConversions.h"

namespace Oryx
{
	Mesh::Mesh(String name,Ogre::SceneNode* node,Ogre::Entity* ent)
		:SceneNode(name,node),mEntity(ent){}
	//--------------------------------------------------------------------------

	Mesh::~Mesh()
	{
		Ogre::MeshPtr m = mEntity->getMesh();
		// TODO: improve this, as-is a manually loaded and reused mesh would cause a crash here
		if(m->isManuallyLoaded())
		{
			Ogre::MeshManager::getSingleton().unload(m->getName());
			Ogre::MeshManager::getSingleton().remove(m->getName());
		}
		mNode->getCreator()->destroyEntity(mEntity);
	}
	//--------------------------------------------------------------------------
	
	void Mesh::setMaterialName(String name, int submeshIndex)
	{
		if(submeshIndex == -1)
			mEntity->setMaterialName(name);
		else
			mEntity->getSubEntity(submeshIndex)->setMaterialName(name);
	}
	//-----------------------------------------------------------------------

	String Mesh::getMaterialName(size_t submeshIndex)
	{
		return mEntity->getSubEntity(submeshIndex)->getMaterialName();
	}
	//-----------------------------------------------------------------------

	Material Mesh::getMaterial(size_t submeshIndex)
	{
		return Material(getMaterialName(submeshIndex));
	}
	//-----------------------------------------------------------------------
	
	/** Copies this mesh's vertex/etc data into a MeshData object */
	void Mesh::getMeshData(MeshData& out, bool texcoords, bool normals,
		bool indices, bool vertices)
	{
		out.addTexcoordSet();
		size_t vertex_count = 0;
		size_t numTris = 0;
		size_t index_count = 0;

		bool added_shared = false;
		size_t current_offset = vertex_count;
		size_t shared_offset = vertex_count;
		size_t next_offset = vertex_count;
		size_t index_offset = index_count;
		size_t prev_vert = vertex_count;
		size_t prev_ind = index_count;

		Ogre::MeshPtr mesh = mEntity->getMesh();

		for(int i = 0;i < mesh->getNumSubMeshes();i++)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);

			if(submesh->useSharedVertices)
			{
				if(!added_shared)
				{
					Ogre::VertexData* vertex_data = mesh->sharedVertexData;
					vertex_count += vertex_data->vertexCount;
					added_shared = true;
				}
			}
			else
			{
				Ogre::VertexData* vertex_data = submesh->vertexData;
				vertex_count += vertex_data->vertexCount;
			}

			Ogre::IndexData* index_data = submesh->indexData;
			index_count += index_data->indexCount;
		}

		added_shared = false;

		for(int i = 0;i < mesh->getNumSubMeshes();i++)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);
			Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

			if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
			{
				if(submesh->useSharedVertices)
				{
					added_shared = true;
					shared_offset = current_offset;
				}

				const Ogre::VertexElement *posElem, *nElem, *tElem;
				Ogre::HardwareVertexBufferSharedPtr vbuf, nbuf, tbuf;
				unsigned char *vertex, *normal, *tex;
				Ogre::Real *pReal, *nReal, *tReal;

				if(vertices)
				{
					posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
					vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
					vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
				}
				if(normals)
				{
					nElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
					nbuf = vertex_data->vertexBufferBinding->getBuffer(nElem->getSource());
					normal = static_cast<unsigned char*>(nbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
				}
				if(texcoords)
				{
					tElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);
					tbuf = vertex_data->vertexBufferBinding->getBuffer(tElem->getSource());
					tex = static_cast<unsigned char*>(tbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
				}

				for(size_t j = 0; j < vertex_data->vertexCount; ++j)
				{
					if(vertices)
					{
						posElem->baseVertexPointerToElement(vertex, &pReal);
						out.vertices.push_back(*pReal++);
						out.vertices.push_back(*pReal++);
						out.vertices.push_back(*pReal++);
						//std::cout<<"v: "<<out.vertices[out.vertices.size()-1]<<" "<<
						//	out.vertices[out.vertices.size()-2]<<" "<<out.vertices[out.vertices.size()-3]<<"\n";
						vertex += vbuf->getVertexSize();
					}

					if(normals)
					{
						nElem->baseVertexPointerToElement(normal, &nReal);
						out.normals.push_back(*nReal++);
						out.normals.push_back(*nReal++);
						out.normals.push_back(*nReal++);
						normal+=nbuf->getVertexSize();
					}

					if(texcoords)
					{
						tElem->baseVertexPointerToElement(tex, &tReal);
						out.texcoords[0].push_back(*tReal++);
						out.texcoords[0].push_back(*tReal++);
						tex+=tbuf->getVertexSize();
					}
				}

				if(vertices)
					vbuf->unlock();
				if(normals)
					nbuf->unlock();
				if(texcoords)
					tbuf->unlock();

				next_offset += vertex_data->vertexCount;
			}

			if(indices)
			{
				Ogre::IndexData* index_data = submesh->indexData;

				numTris = index_data->indexCount / 3;
				unsigned short* pShort;
				unsigned int* pInt;
				Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
				bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

				if (use32bitindexes) 
					pInt = static_cast<unsigned int*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
				else 
					pShort = static_cast<unsigned short*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

				for(size_t k = 0; k < numTris; ++k)
				{
					size_t offset = (submesh->useSharedVertices)?shared_offset:current_offset;

					unsigned int vindex = use32bitindexes? *pInt++ : *pShort++;
					out.indices.push_back(vindex + offset);

					vindex = use32bitindexes? *pInt++ : *pShort++;
					out.indices.push_back(vindex + offset);

					vindex = use32bitindexes? *pInt++ : *pShort++;
					out.indices.push_back(vindex + offset);

					index_offset += 3;
				}
				ibuf->unlock();
			}
			current_offset = next_offset;
		}

		std::cout<<"Mesh Data output: v: "<<out.vertices.size()<<" i: "<<out.indices.size()<<"\n";
	}

	void Mesh::update(MeshData& data)
	{
		using namespace Ogre;

		bool hasVertexColor = data.getDiffuse();
		bool hasNormals = data.getNormals();
		
		int numFaces = data.indices.size()/3;
		int numVertices = data.vertices.size()/3;
		
		HardwareVertexBufferSharedPtr posVertexBuffer;
		HardwareVertexBufferSharedPtr normVertexBuffer;
		std::vector<HardwareVertexBufferSharedPtr> texcoordsVertexBuffer;
		HardwareVertexBufferSharedPtr diffuseVertexBuffer;
		HardwareIndexBufferSharedPtr indexBuffer;

		Ogre::SubMesh* sm = mEntity->getMesh()->getSubMesh(0);
		sm->vertexData->vertexStart = 0;
		sm->vertexData->vertexCount = data.vertices.size()/3;

		Ogre::VertexDeclaration* vdecl = sm->vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* vbind = sm->vertexData->vertexBufferBinding;

		size_t bufferCount = 0;

		vdecl->addElement(bufferCount, 0, VET_FLOAT3, VES_POSITION);

		if(hasNormals)
			vdecl->addElement(++bufferCount, 0, VET_FLOAT3, VES_NORMAL);
		
		if(hasVertexColor)
			vdecl->addElement(++bufferCount, 0, VET_FLOAT4, VES_DIFFUSE);
		
		for(int i=0;i<data.texcoords.size();++i)
			vdecl->addElement(++bufferCount, 0, VET_FLOAT2, VES_TEXTURE_COORDINATES,i);
		
		bufferCount = 0;

		// Positions
		posVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
			3*sizeof(float),numVertices,Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

		vbind->setBinding(bufferCount, posVertexBuffer);

		float* vertices = data.getVertices(); 
		float* normals = data.getNormals();
		float* diffuse = data.getDiffuse();
		unsigned short* indices = data.getIndices();

		posVertexBuffer->writeData(0,posVertexBuffer->getSizeInBytes(),vertices, true);

		// Normals
		if(hasNormals)
		{
			normVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
				3*sizeof(float),numVertices,HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

			vbind->setBinding(++bufferCount, normVertexBuffer);

			normVertexBuffer->writeData(0,normVertexBuffer->getSizeInBytes(),normals, true);
		}
		
		if(hasVertexColor)
		{
			diffuseVertexBuffer = HardwareBufferManager::getSingleton().createVertexBuffer(
				4*sizeof(float),numVertices,HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

			vbind->setBinding(++bufferCount, diffuseVertexBuffer);

			diffuseVertexBuffer->writeData(0,diffuseVertexBuffer->getSizeInBytes(), diffuse, true);
		}

		// Texcoords
		for(int i=0;i<data.texcoords.size();++i)
		{
			texcoordsVertexBuffer.push_back(HardwareBufferManager::getSingleton().createVertexBuffer(
				2*sizeof(float),numVertices,HardwareBuffer::HBU_STATIC_WRITE_ONLY));

			vbind->setBinding(++bufferCount, texcoordsVertexBuffer[i]);
			
			texcoordsVertexBuffer[i]->writeData(0,sizeof(float)*data.texcoords[i].size(),&data.texcoords[i][0], false);
		}

		// Prepare buffer for indices
		indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(
			HardwareIndexBuffer::IT_16BIT,3*numFaces,HardwareBuffer::HBU_STATIC, true);

		//unsigned short *faceVertexIndices = (unsigned short*)
		//indexBuffer->lock(0, numFaces*3*2, HardwareBuffer::HBL_DISCARD);

		// Set index buffer for this submesh
		sm->indexData->indexBuffer = indexBuffer;
		sm->indexData->indexStart = 0;
		sm->indexData->indexCount = 3*numFaces;

		indexBuffer->writeData(0,indexBuffer->getSizeInBytes(),indices,true);

		//vdecl->sort();

		mEntity->getMesh()->load();
		mEntity->getMesh()->touch();
	}
	//-----------------------------------------------------------------------
}
