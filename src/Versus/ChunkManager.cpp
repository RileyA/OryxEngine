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

#include "Oryx.h"
#include "OryxStringUtils.h"
#include "ChunkManager.h"
#include <stack>

namespace Oryx
{
	ChunkManager::ChunkManager(Vector3 position)
		:radius(1),mLast(10,10,10)
	{
		generate(position);
	}
	//-----------------------------------------------------------------------

	ChunkManager::~ChunkManager()
	{
		std::map<ChunkCoords,Chunk*>::iterator it = mChunks.begin();
		while(it!=mChunks.end())
		{
			delete it->second;
			++it;
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::update(Real delta)
	{
		std::stack<Chunk*> updated;
		Real start = TimeManager::getPtr()->getTimeDecimal();

		int chunksRebuilt = 0;

		std::map<ChunkCoords,Chunk*>::iterator it = mChunks.begin();
		while(it!=mChunks.end())
		{
			it->second->update(delta);

			if(it->second->needsUpdate())
			{
				updated.push(it->second);
				it->second->localLighting();

				for(int i=0;i<6;++i)
				{
					// TODO update diagonals as well. optimize?
					if(it->second->neighbors[i])
					{
						updated.push(it->second->neighbors[i]);
						it->second->neighbors[i]->localLighting();
						it->second->neighbors[i]->secondaryLighting();
					}
				}
				it->second->secondaryLighting();
			}
			++it;
		}



		chunksRebuilt = updated.size();

		if(chunksRebuilt>0)
		{
			Logger::getPtr()->logMessage("Lighting Took: "+StringUtils::toString(
				TimeManager::getPtr()->getTimeDecimal()-start));
		}
		
		Real start2 = TimeManager::getPtr()->getTimeDecimal();

		while(!updated.empty())
		{
			updated.top()->build();
			updated.pop();
		}

		if(chunksRebuilt>0)
		{
;
			Logger::getPtr()->logMessage("Builds Took: "+StringUtils::toString(
				TimeManager::getPtr()->getTimeDecimal()-start2)+" "
				+StringUtils::toString(chunksRebuilt)+" Chunk Updates");
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::generate(Vector3 position)
	{
		int i = (position.x+CHUNK_SIZE_X/2)/CHUNK_SIZE_X;
		//int j = (position.y+CHUNK_SIZE_Y/2)/CHUNK_SIZE_Y;
		int k = (position.z+CHUNK_SIZE_Z/2)/CHUNK_SIZE_Z;

		if(mLast.x!=i||mLast.z!=k)//||mLast.y!=j)
		{			
			ChunkCoords c = (i-radius,0,k-radius);

			for(c.x = i-radius; c.x<=i+radius; ++c.x)
				//for(c.y = j-radius; c.y<=j+radius; ++c.y)
					for(c.z = k-radius; c.z<=k+radius; ++c.z)
					createChunk(c);
		}
		mLast = ChunkCoords(i,0,k);
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::killBlocks(Vector3 p,float radius)
	{

	}
	//-----------------------------------------------------------------------
	
	Chunk* ChunkManager::getChunk(ChunkCoords c)
	{
		if(mChunks.find(c)!=mChunks.end())
			return mChunks[c];
		return 0;
	}
	//-----------------------------------------------------------------------
	
	Chunk* ChunkManager::createChunk(ChunkCoords c)
	{
		if(getChunk(c))
			return 0;

		byte data[16][16][16];

		for(int i=0;i<16;++i)
			for(int j=0;j<16;++j)
				for(int k=0;k<16;++k)
		{
				data[i][j][k] = 0;
				if(j<5)
					data[i][j][k] = 2;
				else if(j<8)
					data[i][j][k] = 3;
				else if(j<9)
					data[i][j][k] = 4;
		}

		Chunk* ch = new Chunk(Vector3(c.x*CHUNK_SIZE_X-CHUNK_SIZE_X/2,c.y*CHUNK_SIZE_Y-CHUNK_SIZE_Y/2,
			c.z*CHUNK_SIZE_Z-CHUNK_SIZE_Z/2),this,&data[0][0][0]);

		for(int i=0;i<6;++i)
			ch->neighbors[i] = getChunk(c<<i);

		ch->markDirty();
		ch->notifyNeighbors();
		mChunks[c] = ch;
		return ch;
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::setMaterial(String material,size_t atlasDimensions)
	{
		std::map<ChunkCoords,Chunk*>::iterator it = mChunks.begin();

		while(it!=mChunks.end())
		{
			it->second->setMaterial(material,atlasDimensions);
			++it;
		}
	}
	//-----------------------------------------------------------------------
}
