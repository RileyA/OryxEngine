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

#include "ScreenMesh.h"
#include "CustomMesh.h"

namespace Oryx
{
	ScreenMesh::ScreenMesh(String material)
	{
		mMesh = new CustomMesh(material);
		createSlot("update", this, &ScreenMesh::updateSlot);
	}
	//-----------------------------------------------------------------------

	ScreenMesh::~ScreenMesh()
	{
		delete mMesh;
	}
	//-----------------------------------------------------------------------

	/** Builds the whole thing */
	void ScreenMesh::buildMesh(size_t vertexCount, size_t faceCount, float* pos, 
		float* tex, float* colors, unsigned short* indices)
	{
		mMesh->buildMesh(vertexCount,faceCount,pos,tex,colors,indices);
	}
	//-----------------------------------------------------------------------

	/** rebuilds the whole thing */
	void ScreenMesh::rebuildMesh(size_t vertexCount, size_t faceCount, float* pos,
		float* tex, float* colors, unsigned short* indices)
	{
		mMesh->rebuildMesh(vertexCount,faceCount,pos,tex,colors,indices);
	}
	//-----------------------------------------------------------------------

	/** Updates vertex positions */
	void ScreenMesh::updatePositions(float* pos)
	{
		mMesh->updatePositions(pos);
	}
	//-----------------------------------------------------------------------

	/** Updates texcoords */
	void ScreenMesh::updateTexcoords(float* tex)
	{
		mMesh->updateTexcoords(tex);
	}
	//-----------------------------------------------------------------------

	/** Updates vertex colors */
	void ScreenMesh::updateColors(float* colors)
	{
		mMesh->updateColors(colors);
	}
	//-----------------------------------------------------------------------

	void ScreenMesh::updateSlot(const Message& m)
	{
		// no RTTI, just assume it's getting passed the right thing...
		MeshUpdate* mu = &((static_cast<const MessageAny<MeshUpdate&>*>(&m))->data);

		if(mu->flags & 1<<3)
		{
			rebuildMesh(mu->vertexCount, mu->faceCount, mu->vertices, mu->texcoords,
				mu->diffuse, mu->indices);
		}
		else
		{
			if(mu->flags & 1)
				updatePositions(mu->vertices);
			if(mu->flags & 1 << 1)
				updateTexcoords(mu->texcoords);
			if(mu->flags & 1 << 2)
				updateColors(mu->diffuse);
		}
	}
	//-----------------------------------------------------------------------

	void ScreenMesh::setHidden(bool h)
	{
		mMesh->mHide = h;
	}
}
