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

namespace Oryx
{
	class Chunk;

	enum BlockNeighbor
	{
		// TODO: double check...
		BN_LEFT,
		BN_RIGHT,
		BN_DOWN,
		BN_UP,
		BN_BACK,
		BN_FRONT
	};



	struct ChunkBlock
	{
		PhysicsObject* block;
		Chunk* parent;

		int x;
		int y;
		int z;

		ChunkBlock(int i, int j, int k,PhysicsObject* bl,Chunk* par)
		{
			block = bl;
			x = i*4;
			y = j*4;
			z = k*4;
			parent = par;
			block->setUserData(parent);
			block->setCollisionMask(COLLISION_GROUP_15);
		}

		~ChunkBlock()
		{
			block->_kill();
		}

		void rebuild();
	};

	// a simple coordinate thingy, used for logging changes and the like
	struct BlockCoord
	{
		signed char x;
		signed char y;
		signed char z;

		BlockCoord(signed char _x=0,signed char _y=0,signed char _z=0)
			:x(_x),y(_y),z(_z)
		{

		}

		BlockCoord getPhysicsBlock()
		{
			return BlockCoord(x/4,y/4,z/4);
		}

		bool onEdge()
		{
			return x==15||x==0||y==15||y==0||z==15||z==0;
		}

		
		signed char& operator [] ( const size_t i )
        {
            return *(&x+i);
        }

		const signed char& operator [] ( const size_t i ) const
        {
            return *(&x+i);
        }
	};

	class Chunk// : public Object
	{
	public:

		Chunk(Vector3 position);
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

		static Vector3 getBlockFaceNormal(int bn)
		{
			Vector3 out = Vector3::ZERO;
			out[bn/2] = ((bn & 1) == 0) ? 1 : -1;
			return out;
		}

		static BlockCoord getBlockCoords(const BlockCoord& c,int bn)
		{
			int j = bn/2;
			BlockCoord out = c;
			out[bn/2] += ((bn & 1) == 0) ? -1 : 1;
			return out;
		}

		static int validateCoords(BlockCoord& coords)
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

		static void correctNeighbor(Chunk** c, BlockCoord& coords)
		{
			int n = 0;
			while(n!=-1&&(*c))
			{
				n = validateCoords(coords);
				if(n!=-1)
					(*c) = (*c)->neighbors[n];
			}
		}
		
		static void setBlock(Chunk* c, BlockCoord coords, byte type)
		{
			correctNeighbor(&c,coords);
			if(c && c->blocked[coords.x][coords.y][coords.z]!=type)
			{
				c->blocked[coords.x][coords.y][coords.z] = type;
				c->dirtyBlocks.push_back(coords);
			}
		}
		
		static byte getBlock(Chunk* c, BlockCoord coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->blocked[coords.x][coords.y][coords.z] : 0;
		}
			
		static byte getLight(Chunk* c, BlockCoord coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->light[coords.x][coords.y][coords.z] : 15;
		}	
		
		static bool setLight(Chunk* c, BlockCoord coords,byte lit)
		{
			//correctNeighbor(&c,coords);
			if(c->light[coords.x][coords.y][coords.z]<lit)
			{
				c->light[coords.x][coords.y][coords.z] = lit;
				return true;
			}
			return false;
		}

		byte getBlockState(BlockCoord c)
		{
			return blocked[c.x][c.y][c.z];
		}

		// The graphics object
		Mesh* mChunk;
	
		// The states of the voxels
		byte blocked[16][16][16];
		byte light[16][16][16];
	
		// Physics objects
		ChunkBlock* mBlocks[4][4][4];
		
		// Neightboring blocks
		Chunk* neighbors[6];

		std::vector<BlockCoord> dirtyBlocks;

		// this object's coords
		int xi;
		int yj;
		int zk;

		bool lit;
		bool lightingDirty;

	private:

		OgreSubsystem* mOgre;
		Vector3 mPosition;

	};
}

#endif	
