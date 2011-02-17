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

#ifndef ORYX_MESHDATA_H
#define ORYX_MESHDATA_H

#include "Oryx.h"
#include "OryxVector3.h"
#include "OryxVector2.h"

namespace Oryx
{
	struct MeshData
	{
		void vertex(Vector3 v,Vector3 n,Vector2 t,Vector3 d=Vector3(-1,-1,-1))
		{
			vertices.push_back(v.x);
			vertices.push_back(v.y);
			vertices.push_back(v.z);
			normals.push_back(n.x);
			normals.push_back(n.y);
			normals.push_back(n.z);
			texcoords.push_back(t.x);
			texcoords.push_back(t.y);
			if(d.x>-0.5f)// sorta ugly way of doing this, but ahh well...
			{
				diffuse.push_back(d.x);
				diffuse.push_back(d.y);
				diffuse.push_back(d.z);
			}
			indices.push_back(indices.size());// in order for now...
		}

		float* getVertices() const
		{
			return const_cast<float*>(&vertices[0]);
		}

		float* getNormals() const
		{
			return const_cast<float*>(&normals[0]);
		}

		float* getTexcoords() const
		{
			return const_cast<float*>(&texcoords[0]);
		}

		float* getDiffuse() const
		{
			if(!diffuse.empty())
				return const_cast<float*>(&diffuse[0]);
			return 0;
		}

		unsigned short* getIndices() const
		{
			return const_cast<unsigned short*>(&indices[0]);
		}

		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> texcoords;
		std::vector<float> diffuse;
		std::vector<unsigned short> indices;
	};
}

#endif
