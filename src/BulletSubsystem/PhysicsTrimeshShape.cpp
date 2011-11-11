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

#include "btBulletDynamicsCommon.h"
#include "PhysicsTrimeshShape.h"

namespace Oryx
{
	PhysicsTrimeshShape::PhysicsTrimeshShape(MeshData& d, String name)
		:PhysicsShape(name == "NULL",name)
	{
		btTriangleMesh *triMesh = new btTriangleMesh();
		/*for(int i=0;i+3<d.indices.size();i+=3)
		{
			btVector3 points[3];
			for(int j=0;j<3;++j)
				points[j] = btVector3(
					d.vertices[d.indices[i+j]*3],
					d.vertices[d.indices[i+j]*3+1],
					d.vertices[d.indices[i+j]*3+2]);
			triMesh->addTriangle(points[0],points[1],points[2]);
		}*/

		for(int i=0;i+8<d.vertices.size();i+=9)
		{
			btVector3 points[3];
			for(int j=0;j<3;++j)
				points[j] = btVector3(
					d.vertices[i + j*3],
					d.vertices[i + j*3+1],
					d.vertices[i + j*3+2]);
			triMesh->addTriangle(points[0],points[1],points[2]);
		}

		mShape = new btBvhTriangleMeshShape(triMesh,true);
	}

	PhysicsTrimeshShape::~PhysicsTrimeshShape()
	{
		// clear triangle data
		delete dynamic_cast<btTriangleMesh*>(
			dynamic_cast<btBvhTriangleMeshShape*>(mShape)->getMeshInterface());
	}
}
