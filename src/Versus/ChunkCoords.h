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
//--------------------------------------------------------------------------

#ifndef CHUNKCOORDS_H
#define CHUNKCOORDS_H

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "OryxColour.h"

#define COLORVAL(x) Colour(x,x,x)
//#define ALLOW_BLOCK_TRANSPARENCY
//#define BLOCK_AO
//#define BLOCK_NORMALS

namespace Oryx
{
	// NOTE: As of right now changing these will probably cause a spectacular crash,
	// I'm working on generalizing everything though...
	// NOTE: These must be multiples of CHUNK_STEP 
	const byte CHUNK_STEP = 4;
	const byte CHUNK_SIZE_X = 16;
	const byte CHUNK_SIZE_Y = 16;
	const byte CHUNK_SIZE_Z = 16;

	const byte CHUNK_STEPS_X = CHUNK_SIZE_X/CHUNK_STEP;
	const byte CHUNK_STEPS_Y = CHUNK_SIZE_Y/CHUNK_STEP;
	const byte CHUNK_STEPS_Z = CHUNK_SIZE_Z/CHUNK_STEP;

	// For convenience:
	const byte CHUNKSIZE[3] = {CHUNK_SIZE_X,CHUNK_SIZE_Y,CHUNK_SIZE_Z};
	const byte CHUNKSTEPS[3] = {CHUNK_STEPS_X,CHUNK_STEPS_Y,CHUNK_STEPS_Z};
	const uint CHUNK_VOLUME = CHUNK_SIZE_X*CHUNK_SIZE_Y*CHUNK_SIZE_Z;

	// The maximum light value (defaults to 4 bits for save file purposes,
	// so max is (2^4)-1 = 15)
	const byte MAX_LIGHT = 15;

	// Offset used for roughly centering Chunks
	static const Vector3 OFFSET = Vector3((CHUNKSIZE[0]-1)/2.f,
			(CHUNKSIZE[1]-1)/2.f,(CHUNKSIZE[2]-1)/2.f);

	// Normals for the quads (more effiecient to store them here, than to calculate each time...
	const Vector3 QUADNORMALS[6] = {
		Vector3(1,0,0),
		Vector3(-1,0,0),
		Vector3(0,1,0),
		Vector3(0,-1,0),
		Vector3(0,0,1),
		Vector3(0,0,-1)};
	
	// The light values 0.8^(15-lightLevel), saves some pow()-ing to store these as consts
	const Colour LIGHTVALUES[16] = {
		COLORVAL(0.03518f),
		COLORVAL(0.04398f),
		COLORVAL(0.0549755f),
		COLORVAL(0.06871948f),
		COLORVAL(0.08589f),
		COLORVAL(0.10737f),
		COLORVAL(0.1342f),
		COLORVAL(0.16777f),
		COLORVAL(0.2097f),
		COLORVAL(0.262144f),
		COLORVAL(0.32768f),
		COLORVAL(0.4096f),
		COLORVAL(0.512f),
		COLORVAL(0.64f),
		COLORVAL(0.8f),
		COLORVAL(1.f)
	};

	const byte AXIS[6] = {0,0,1,1,2,2};
	const int8 AXIS_OFFSET[6] = {-1,1,-1,1,-1,1};

	typedef signed char ChunkCoordValue;// save a few bytes...
	//typedef short ChunkCoordValue; //required if coords are gonna be >127 in any dimension
	
	enum BlockDirection
	{
		BD_LEFT,  // -x
		BD_RIGHT, // +x
		BD_DOWN,  // -y
		BD_UP,    // +y
		BD_FRONT, // -z
		BD_BACK   // +z
	};

	/** A representation of a position in/around a Chunk object */
	class ChunkCoords
	{
	public:

		const static ChunkCoords ChunkOffsets[6];

		ChunkCoordValue x;
		ChunkCoordValue y;
		ChunkCoordValue z;

		ChunkCoords(const ChunkCoordValue _x=0, const ChunkCoordValue _y=0, const ChunkCoordValue _z=0)
			:x(_x),y(_y),z(_z)
		{}

		ChunkCoords getPhysicsBlock()
		{
			return ChunkCoords(x/4,y/4,z/4);
		}

		bool inBounds()
		{
			return x<CHUNK_SIZE_X && x>=0 && y<CHUNK_SIZE_Y && y>=0 && z<CHUNK_SIZE_Z && z>=0;
		}

		bool onEdge() const
		{
			return x==CHUNK_SIZE_X-1||x==0||y==CHUNK_SIZE_Y-1||y==0||z==CHUNK_SIZE_Z-1||z==0;
		}

		ChunkCoordValue& operator [] ( const size_t i )
        {
            return *(&x+i);
        }

		const ChunkCoordValue& operator [] ( const size_t i ) const
        {
            return *(&x+i);
        }

		ChunkCoords operator << (const char dir) const
		{
			return *this + ChunkOffsets[dir];
		}

		ChunkCoords operator + (const ChunkCoords& c) const
		{
			return ChunkCoords(x+c.x,y+c.y,z+c.z);
		}
		
		// So this can be used as a std::map key
		bool operator < (const ChunkCoords& c) const
		{
			return std::lexicographical_compare(&x,&z+1,&c.x,&c.z+1);
		}
	};

	#ifdef ALLOW_BLOCK_TRANSPARENCY
	const byte TRANSPARENT[6] = {1,0,0,0,0,0};
	#endif

	// map tex atlas positions to faces and block indices
	/*const byte MAPPINGS[5][6] = 
	{
		{1,1,1,1,1,1},
		{1,1,1,1,1,1},
		{2,2,2,2,2,2},
		{3,3,3,3,3,3},
		{4,4,4,4,4,4}
	};*/

	// hard-coded since it shouldn't ever change, and is faster than calculating it out each time
	const Vector3 BLOCK_VERTICES[6][6] =
	{
		{Vector3(-0.5f,0.5f,0.5f),Vector3(-0.5f,0.5f,-0.5f),Vector3(-0.5f,-0.5f,-0.5f),
			Vector3(-0.5f,0.5f,0.5f),Vector3(-0.5f,-0.5f,-0.5f),Vector3(-0.5f,-0.5f,0.5f)},
		{Vector3(0.5f,0.5f,-0.5f),Vector3(0.5f,0.5f,0.5f),Vector3(0.5f,-0.5f,0.5f),
			Vector3(0.5f,0.5f,-0.5f),Vector3(0.5f,-0.5f,0.5f),Vector3(0.5f,-0.5f,-0.5f)},
		{Vector3(0.5f,-0.5f,-0.5f),Vector3(0.5f,-0.5f,0.5f),Vector3(-0.5f,-0.5f,0.5f),
			Vector3(0.5f,-0.5f,-0.5f),Vector3(-0.5f,-0.5f,0.5f),Vector3(-0.5f,-0.5f,-0.5f)},
		{Vector3(0.5f,0.5f,0.5f),Vector3(0.5f,0.5f,-0.5f),Vector3(-0.5f,0.5f,-0.5f),
			Vector3(0.5f,0.5f,0.5f),Vector3(-0.5f,0.5f,-0.5f),Vector3(-0.5f,0.5f,0.5f)},
		{Vector3(0.5f,0.5f,-0.5f),Vector3(0.5f,-0.5f,-0.5f),Vector3(-0.5f,-0.5f,-0.5f),
			Vector3(0.5f,0.5f,-0.5f),Vector3(-0.5f,-0.5f,-0.5f),Vector3(-0.5f,0.5f,-0.5f)},
		{Vector3(0.5f,-0.5f,0.5f),Vector3(0.5f,0.5f,0.5f),Vector3(-0.5f,0.5f,0.5f),
			Vector3(0.5f,-0.5f,0.5f),Vector3(-0.5f,0.5f,0.5f),Vector3(-0.5f,-0.5f,0.5f)}
	};

	// DEPRECATED
	const Vector3 BLOCK_NORMALS[6] =
	{
		Vector3(-1,0,0),
		Vector3(1,0,0),
		Vector3(0,-1,0),
		Vector3(0,1,0),
		Vector3(0,0,-1),
		Vector3(0,0,1)	
	};

	// TODO: fix vertex windings and such above, so this isn't necessary
	const Vector2 BLOCK_TEXCOORDS[6][6] =
	{
		{Vector2(0,0),Vector2(1,0),Vector2(1,1),Vector2(0,0),Vector2(1,1),Vector2(0,1)},
		{Vector2(0,0),Vector2(1,0),Vector2(1,1),Vector2(0,0),Vector2(1,1),Vector2(0,1)},
		{Vector2(0,0),Vector2(1,0),Vector2(1,1),Vector2(0,0),Vector2(1,1),Vector2(0,1)},
		{Vector2(0,0),Vector2(1,0),Vector2(1,1),Vector2(0,0),Vector2(1,1),Vector2(0,1)},
		{Vector2(1,0),Vector2(1,1),Vector2(0,1),Vector2(1,0),Vector2(0,1),Vector2(0,0)},
		{Vector2(1,1),Vector2(1,0),Vector2(0,0),Vector2(1,1),Vector2(0,0),Vector2(0,1)}
	};

	// Test w/ Minecraft terrain.png
	const byte MAPPINGS[5][6] = {
		{1,1,1,1,1,1},
		{37,37,37,37,37,37},
		{2,2,2,2,2,2},
		{3,3,3,3,3,3},
		{4,4,3,1,4,4}
	};
}
#endif
