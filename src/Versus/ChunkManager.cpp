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
#include "ChunkManager.h"
#include <set>

namespace Oryx
{
	ChunkManager::ChunkManager(Vector3 position)
		:radius(2)
	{
		generate(position);
	}
	//-----------------------------------------------------------------------

	ChunkManager::~ChunkManager()
	{
		std::map<int,std::map<int,std::map<int,Chunk*> > >::iterator it = mChunks.begin();
		while(it!=mChunks.end())
		{
			std::map<int,std::map<int,Chunk*> >::iterator ite = it->second.begin();
			while(ite!=it->second.end())
			{
				std::map<int,Chunk*>::iterator iter = ite->second.begin();
				while(iter!=ite->second.end())
				{
					delete iter->second;
					++iter;
				}
				++ite;
			}
			++it;
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::update(Real delta)
	{
		std::map<Chunk*,bool> updaters;
		std::map<int,std::map<int,std::map<int,Chunk*> > >::iterator it = mChunks.begin();
		while(it!=mChunks.end())
		{
			std::map<int,std::map<int,Chunk*> >::iterator ite = it->second.begin();
			while(ite!=it->second.end())
			{
				std::map<int,Chunk*>::iterator iter = ite->second.begin();
				while(iter!=ite->second.end())
				{
					iter->second->update(delta);
					if(!iter->second->dirtyBlocks.empty())
					{
						updaters[iter->second] = true;
						for(int i=0;i<6;++i)
						{
							if(iter->second->neighbors[i]&&updaters.find(iter->second->neighbors[i])
								==updaters.end())
								updaters[iter->second->neighbors[i]] = false;
						}
					}
					++iter;
				}
				++ite;
			}
			++it;
		}

		float start;
		if(updaters.size()>0)
		{
			start = TimeManager::getPtr()->getTimeDecimal();
		}

		std::map<Chunk*,bool>::iterator itera = updaters.begin();
		while(itera!=updaters.end())
		{
			if(itera->second)
				itera->first->localLighting();
			++itera;
		}

		itera = updaters.begin();
		while(itera!=updaters.end())
		{
			if(!itera->second)
			{
				itera->first->localLighting();
				itera->first->secondaryLighting();
			}
			++itera;
		}

		itera = updaters.begin();
		while(itera!=updaters.end())
		{
			if(itera->second)
				itera->first->secondaryLighting();
			++itera;
		}

		itera = updaters.begin();
		while(itera!=updaters.end())
		{
			itera->first->build();
			++itera;
		}	

		if(updaters.size()>0)
		{
			std::cout<<"Update Took: "<<TimeManager::getPtr()->getTimeDecimal()-start<<"\n";
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::generate(Vector3 position)
	{
		// get position as a grid spot
		int i = (position.x+8)/16;
		int j = (position.y+8)/16;
		int k = (position.z+8)/16;
		
		int _j = 0;
		//int _k = k;
		for(int _i = -radius+i; _i <= radius+i; ++_i)
			for(int _k = -radius+k; _k <= radius+k; ++_k)
		{
			if(!getChunk(_i,_j,_k))
				createChunk(_i,_j,_k);
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkManager::killBlocks(Vector3 p,float radius)
	{

	}
	//-----------------------------------------------------------------------
	
	Chunk* ChunkManager::getChunk(int x,int y,int z)
	{
		if(mChunks.find(x) != mChunks.end() && mChunks[x].find(y) != mChunks[x].end()
			&& mChunks[x][y].find(z) != mChunks[x][y].end())
			return mChunks[x][y][z];
		return 0;
	}
	//-----------------------------------------------------------------------
	
	Chunk* ChunkManager::createChunk(int x,int y,int z)
	{
		if(getChunk(x,y,z))
			return 0;

		mChunks[x][y][z] = new Chunk(Vector3(x*16-8,y*16-8,z*16-8));
		
		// set neighbors
		mChunks[x][y][z]->neighbors[1] = getChunk(x+1,y,z);
		mChunks[x][y][z]->neighbors[0] = getChunk(x-1,y,z);
		mChunks[x][y][z]->neighbors[3] = getChunk(x,y+1,z);
		mChunks[x][y][z]->neighbors[2] = getChunk(x,y-1,z);
		mChunks[x][y][z]->neighbors[5] = getChunk(x,y,z+1);
		mChunks[x][y][z]->neighbors[4] = getChunk(x,y,z-1);

		mChunks[x][y][z]->build();
		mChunks[x][y][z]->rebuildPhysics();
		mChunks[x][y][z]->notifyNeighbors();

		return mChunks[x][y][z];
	}
}
