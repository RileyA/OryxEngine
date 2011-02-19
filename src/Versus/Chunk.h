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

	/** A 16x16x16 Chunk of voxels, represented as cubes (a.k.a. Minecraft-style rendering) */
	class Chunk
	{
	public:

		/** Constructor
		 *		@remarks There should be no need to manually construct Chunks if
		 *			you're using a ChunkManager.
		 *		@param position The position of this chunk
		 *		@param parent The ChunkManager this Chunk belongs to */
		Chunk(Vector3 position,ChunkManager* parent = 0);

		/** Destructor, cleans up physics and mesh data */
		virtual ~Chunk();

		/** Updates this Chunk
		 *		@param delta The time passed since the last frame (in seconds) */
		void update(Real delta);

		/** Rebuilds the graphical mesh of this object
		 *		@param physics Whether or not to update the physics 
		 *			representation as well*/
		void build(bool physics = false);

		/** Destroys all blocks in a given radius (useful for explosions, etc)
		 *		@param p The origin position 
		 *		@param radius The radius in which to destroy blocks */
		void killBlocks(Vector3 p,float radius);

		/** Destroys a block based on raycast data
		 *		@remarks Since you'll often wind up with a pos/normal pair from
		 *			a raycast, but no idea which block it is, this simplifies things
		 *		@param p The position of the raycast hit 
		 *		@param n The surface normal at the impact point */
		void killBlock(Vector3 p,Vector3 n);

		/** Adds a block based on raycast data 
		 *		@remarks Since you'll often wind up with a pos/normal pair from
		 *			a raycast, but no idea which block it is, this simplifies things
		 *		@param p The position of the raycast hit 
		 *		@param n The surface normal at the impact point */
		void addBlock(Vector3 p,Vector3 n,byte tp=1);

		/** Does a full physics rebuild 
		 *		@remarks This should get called appropriately by build(), but you
		 *			can force a manual rebuild if you so please. */
		void rebuildPhysics();

		/** Gives this Chunk's neighbors a pointer to this Chunk
		 *		@remarks This should only need to be called by the ChunkManager
		 *			on creation of chunks, but there may be some need to do so
		 *			manually (alternate Chunkmanager implementation, etc...) */
		void notifyNeighbors();

		/** Calculates lighting local to this chunk */
		void localLighting();

		/** Calculates light that "bleeds over" from neighboring chunks */
		void secondaryLighting();

		/** memsets all the lighting values to zero (used when recalculating lighting) */
		void clearLighting();

		//byte getBlock(Chunk* c, int x,int y,int z);
		//void setBlock(Chunk* c, int x,int y,int z,byte type);

		/** Static helper for checking if a set of coords is in bounds of a chunk.
		 *		@remarks This may need to be called multiple times to truly 'validate'
		 *			the coords.
		 *		@param coords The coordinates to validate 
		 *		@return An integer index representing the direction the coords
		 *			were move in, or -1 if the coords are valid */
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

		/** Takes a pointer to a pointer to a Chunk and a set of coords
		 *		and corrects the pointer to point at the appropriate chunk
		 *		based on those coords.
		 *		@param c A pointer to a pointer to a chunk 
		 *		@param coords Reference to the coordinates*/
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
		
		/** Sets a given block to a given state
		 *		@param c The Chunk to start in
		 *		@param coords The coordinates to use 
		 *		@param type The type to make this block (0 is nothing) */
		static void setBlock(Chunk* c, ChunkCoords coords, byte type)
		{
			correctNeighbor(&c,coords);
			if(c && c->blocked[coords.x][coords.y][coords.z]!=type)
			{
				c->blocked[coords.x][coords.y][coords.z] = type;
				c->markDirty();
			}
		}
		
		/** Gets the state of a block, given a chunk pointer and coordinates */
		static byte getBlock(Chunk* c, ChunkCoords coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->blocked[coords.x][coords.y][coords.z] : 0;
		}
			
		/** Gets the lighting value of a set block
		 *		@param Chunk c The Chunk of origin
		 *		@param coords The coordinates to look at */
		static byte getLight(Chunk* c, ChunkCoords coords)
		{
			correctNeighbor(&c,coords);
			return c ? c->light[coords.x][coords.y][coords.z] : 15;
		}	
		
		/** Sets the light at a given coordinate
		 *		@param coords The coordinates (MUST be in chunk bounds, 
		 *			this will segfault otherwise) 
		 *		@return Whether or not the lighting value was set (this function 
		 *			only brightens) */
		bool setLight(const ChunkCoords& coords,byte lit)
		{
			if(light[coords.x][coords.y][coords.z]<lit)
			{
				light[coords.x][coords.y][coords.z] = lit;
				return true;
			}
			return false;
		}

		/** Returns the state of a block using a ChunkCoords object
		 *		@param c The coords (must be in bounds) */
		byte getBlockState(const ChunkCoords& c)
		{
			return blocked[c.x][c.y][c.z];
		}

		/** Returns the lighting state of a block using a ChunkCoords object
		 *		@param c The coords (must be in bounds) */
		byte getLightState(const ChunkCoords& c) const
		{
			return light[c.x][c.y][c.z];
		}

		/** Gets whether or not the block at this point is solid
		 *		@remarks At the moment, this doesn't really do anything,
		 *			however, when transparent blocks are added, this will matter*/
		bool isSolid(const ChunkCoords& c)
		{
			return getBlockState(c);
		}

		/** Gets whether or not this Chunk needs to be updated
		 *		@remarks This should only be true if a block was directly
		 *			added or removed in this chunk or on its border.
		 *		@return Whether or not this chunk needs to be updates*/
		bool needsUpdate()
		{
			return mDirty;
		}

		/** Marks this block as needing an update */
		void markDirty()
		{
			mDirty = true;
		}

	
		// The states of the voxels
		byte blocked[16][16][16];
		byte light[16][16][16];
		
		// Neightboring blocks
		Chunk* neighbors[6];


		//bool lit;
		//bool lightingDirty;

	private:

		/** Recursive lighting function, traverses the chunk from light sources
		 *		stepping the light down one notch each move 
		 *		@param c The coordinates to light from 
		 *		@param light The light value at this point */
		void getLighting(ChunkCoords& c,int light);
		
		// The graphics object
		Mesh* mChunk;

		// The parent ChunkManager, used to get info about block types etc
		ChunkManager* mParent;

		// does this Chunk need an update?
		bool mDirty;

		// Pointer to the graphics Subsystem
		OgreSubsystem* mOgre;

		// This Chunk's poition in world-space
		Vector3 mPosition;

		// The physics objects (4x4x4 compounds of up to 4x4x4 Box primitives each)
		PhysicsBlock* mBlocks[4][4][4];
	};
}

#endif	
