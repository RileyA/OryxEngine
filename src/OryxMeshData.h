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
	/** Simple struct representing a 3d mesh (meant for interchange between subsystems etc..) */
	struct ORYX_EXPORT MeshData
	{
		/** Add a vertex to this mesh
		 *		@remarks Since I'm lazy, indices are just an incrementing list...
		 *		@param v The vertex position 
		 *		@param n The normal 
		 *		@param t The texcoords 
		 *		@param d The vertex color (optional) */
		void vertex(Vector3 v,Vector3 n,Vector2 t,Vector3 d=Vector3(-1,-1,-1))
		{
			vertices.push_back(v.x);
			vertices.push_back(v.y);
			vertices.push_back(v.z);
			normals.push_back(n.x);
			normals.push_back(n.y);
			normals.push_back(n.z);
			texcoords[0].push_back(t.x);
			texcoords[0].push_back(t.y);
			if(d.x>-0.5f)// sorta ugly way of doing this, but ahh well...
			{
				diffuse.push_back(d.x);
				diffuse.push_back(d.y);
				diffuse.push_back(d.z);
			}
			indices.push_back(indices.size());// in order for now...
		}
		
		void vertex(Vector3 v,Vector2 t)
		{
			vertices.push_back(v.x);
			vertices.push_back(v.y);
			vertices.push_back(v.z);
			texcoords[0].push_back(t.x);
			texcoords[0].push_back(t.y);
			indices.push_back(indices.size());// in order for now...
		}

		/** Returns the array of vertices */
		float* getVertices() const
		{
			return const_cast<float*>(&vertices[0]);
		}

		/** Returns the array of normals */
		float* getNormals() const
		{
			if(!normals.empty())
				return const_cast<float*>(&normals[0]);
			return 0;
		}

		/** Returns the array of texcoords */
		float* getTexcoords(int set=0) const
		{
			return const_cast<float*>(&texcoords[set][0]);
		}

		/** Returns the array of vertex color */
		float* getDiffuse() const
		{
			if(!diffuse.empty())
				return const_cast<float*>(&diffuse[0]);
			return 0;
		}

		/** Returns the array of indices */
		unsigned short* getIndices() const
		{
			return const_cast<unsigned short*>(&indices[0]);
		}

		void addTexcoordSet()
		{
			texcoords.push_back(std::vector<float>());
		}

		void loadObj(String filename)
		{
			addTexcoordSet();
			std::ifstream file(filename.c_str());
			if(file.is_open())
			{
				String line = "";
				std::getline(file,line);
				while(file.good())
				{
					std::stringstream ss;
					ss<<line;
					String type;
					ss>>type;
					if(type == "v")
					{
						float x, y, z;
						ss>>x;
						ss>>y;
						ss>>z;
						vertices.push_back(x);
						vertices.push_back(y);
						vertices.push_back(z);
					}
					else if(type == "vt")
					{
						float u,v;
						ss>>u;
						ss>>v;
						texcoords[0].push_back(u);
						texcoords[0].push_back(v);
					}
					else if(type == "f")
					{
						String v1, v2, v3;
						ss>>v1;
						ss>>v2;
						ss>>v3;
						indices.push_back(static_cast<short>(atoi(v1.c_str()))-1);
						indices.push_back(static_cast<short>(atoi(v2.c_str()))-1);
						indices.push_back(static_cast<short>(atoi(v3.c_str()))-1);
					}
					// else - we don't care

					std::getline(file,line);;
				}
				file.close();
			}
		}

		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<std::vector<float> > texcoords;
		std::vector<float> diffuse;
		std::vector<unsigned short> indices;
	};
}

#endif
