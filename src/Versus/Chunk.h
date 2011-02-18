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

#ifndef VERSUS_CHUNK_H
#define VERSUS_CHUNK_H

#include "Oryx.h"
#include "OryxEngine.h"
#include "OryxObject.h"
#include "OgreSubsystem/OgreSubsystem.h"
#include "OISSubsystem/OISSubsystem.h"
#include "BulletSubsystem/BulletSubsystem.h"

#include "ChunkCoords.h"
#include "PhysicsBlock.h"

namespace Oryx
{
	class ChunkManager;

	class Chunk
	{
	public:

		Chunk(Vector3 position,ChunkManager* parent);
		virtual ~Chunk();

		void update(Real delta);

		void build(bool physics = false);

		//void rebuild();

		/** Destroys all blocks in a given radius */
		void killBlocks(Vector3 p,float radius);

		/** Destroys a block based on raycast data */
		void killBlock(Vector3 p,Vector3 n);

		/** Adds a block based on raycast data */
		void addBlock(Vector3 p,Vector3 n,byte tp=1);

		/** Does a full physics rebuild */
		void rebuildPhysics();

		void notifyNeighbors();

		void localLighting();
		void secondaryLighting();
		void clearLighting();

		byte getBlock(Chunk* c, int x,int y,int z);
		void setBlock(Chunk* c, int x,int y,int z,byte type);

		void getLighting(ChunkCoords c,int light);
		
		static Vector3 getBlockFaceNormal(int bn)
		{
			Vector3 out = Vector3::ZERO;
			out[bn/2] = ((bn & 1) == 0) ? 1 : -1;
			return out;
		}

		static ChunkCoords getChunkCoords(const ChunkCoords& c,int bn)
		{
			ChunkCoords out = c;
			out[bn/2] += ((bn & 1) == 0) ? -1 : 1;
			return out;
		}

		static int validateCoords(ChunkCoords& coords)
		{
			for(int i=0;i<3;++i)
			{
				if(coords[i]<0)
				{
					coords[i]+=16;
					return i*2;	
				}
				else if(coords[i]>15)
				{
					coords[i]-=16;
					return i*2+1;
				}
			}
			return -1;
		}

		static void correctNeighbor(Chunk** c, ChunkCoords& coords)
		{
			int n = 0;
			while(n!=-1&&(*c))
			{
				n = validateCoords(coords);
				if(n!=-1)
					(*c) = (*c)->neighbors[n];
			}
		}
		
		static void setBlock(Chunk* c, ChunkCoords coords, byte type)
		{
			correctNeighbor(&c,coords);
			if(c && c->blocked[coords.x][coords.y][coords.z]!=type)
			{
				c->blocked[coords.x][coords.y][coords.z] = type;
				c->markDirty();
			}
		}
		
		static byte getBlock(Chunk* c, ChunkCoords coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->blocked[coords.x][coords.y][coords.z] : 0;
		}
			
		static byte getLight(Chunk* c, ChunkCoords coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->light[coords.x][coords.y][coords.z] : 15;
		}	
		
		bool setLight(const ChunkCoords& coords,byte lit)
		{
			if(light[coords.x][coords.y][coords.z]<lit)
			{
				light[coords.x][coords.y][coords.z] = lit;
				return true;
			}
			return false;
		}

		byte getBlockState(const ChunkCoords& c)
		{
			return blocked[c.x][c.y][c.z];
		}

		byte getLightState(const ChunkCoords& c) const
		{
			return light[c.x][c.y][c.z];
		}

		bool isSolid(const ChunkCoords& c)
		{
			return getBlockState(c);
		}

		bool needsUpdate()
		{
			return mDirty;
		}

		void markDirty()
		{
			mDirty = true;
		}

		// The graphics object
		Mesh* mChunk;
	
		// The states of the voxels
		byte blocked[16][16][16];
		byte light[16][16][16];
	
		// Physics objects
		
		// Neightboring blocks
		Chunk* neighbors[6];


		bool lit;
		bool lightingDirty;
		static const Vector3 mNormals[6];
		static const Colour mLightValues[16];

	private:

		ChunkManager* mParent;
		bool mDirty;
		OgreSubsystem* mOgre;
		Vector3 mPosition;
		PhysicsBlock* mBlocks[4][4][4];
	};
}

#endif	
