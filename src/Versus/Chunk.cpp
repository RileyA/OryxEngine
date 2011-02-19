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
#include "Chunk.h"
#include "ChunkManager.h"
#include "OryxMessageAny.h"
#include "OryxEventHandler.h"
#include "OryxTimeManager.h"
#include "OgreSubsystem/OgreSubsystem.h"
#include "OgreSubsystem/Mesh.h"


namespace Oryx
{
	void quad(Vector3 pos,Vector3 normal,MeshData& d,short type,Colour diffuse);

	//-----------------------------------------------------------------------

	Chunk::Chunk(Vector3 position,ChunkManager* parent)
		:mPosition(position),mParent(parent)
	{	
		mChunk = 0;
		mPosition = position;
		mOgre = Engine::getPtr()->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();

		memset(blocked,(byte)0,CHUNK_VOLUME);
		memset(light,(byte)0,CHUNK_VOLUME);
	
		// Throw in some blocks
		for(int i=0;i<CHUNK_SIZE_X;++i)for(int j=0;j<CHUNK_SIZE_Y;++j)for(int k=0;k<CHUNK_SIZE_Z;++k)
			if(j<8)
				blocked[i][j][k] = 4;
		
		BulletSubsystem* b = Engine::getPtr()->getSubsystem("BulletSubsystem")->
			castType<BulletSubsystem>();

		for(int i=0;i<CHUNK_STEPS_X;++i)for(int j=0;j<CHUNK_STEPS_Y;++j)for(int k=0;k<CHUNK_STEPS_Z;++k)
			mBlocks[i][j][k] = new PhysicsBlock(i,j,k,
				b->createCompound(OFFSET*-1.f+Vector3(i,j,k)*CHUNK_STEP+mPosition),this);

		for(int p=0;p<6;++p)
			neighbors[p] = 0;
	}
	//-----------------------------------------------------------------------
	
	Chunk::~Chunk()
	{
		for(int i=0;i<CHUNK_STEPS_X;++i)
			for(int j=0;j<CHUNK_STEPS_Y;++j)
				for(int k=0;k<CHUNK_STEPS_Z;++k)
					delete mBlocks[i][j][k];
	}
	//-----------------------------------------------------------------------

	void Chunk::update(Real delta)
	{
	}
	//-----------------------------------------------------------------------
	
	void Chunk::build(bool physics)
	{
		MeshData d;
		physics = mDirty||physics;

		for(int i=0;i<CHUNK_SIZE_X;++i)for(int j=0;j<CHUNK_SIZE_Y;++j)for(int k=0;k<CHUNK_SIZE_Z;++k)
		{
			byte type = blocked[i][j][k];

			if(type)
			{ 	
				bool adjacents[6];

				// very ugly, but hard coding this all seems ~50% more efficient 
				// than my attempt at a cleaner version...
				adjacents[0] = (i>0&&!blocked[i-1][j][k]) || (i==0&&!neighbors[0]) ||
					(i==0&&neighbors[0]&&!neighbors[0]->blocked[CHUNK_SIZE_X-1][j][k]);
				adjacents[1] = (i<CHUNK_SIZE_X-1&&!blocked[i+1][j][k]) || (i==CHUNK_SIZE_X-1&&!neighbors[1]) 
					|| (i==CHUNK_SIZE_X-1&&neighbors[1]&&!neighbors[1]->blocked[0][j][k]);
				adjacents[2] = (j>0&&!blocked[i][j-1][k]) || (j==0&&!neighbors[2]) ||
					(j==0&&neighbors[2]&&!neighbors[2]->blocked[i][CHUNK_SIZE_Y-1][k]);	
				adjacents[3] = (j<CHUNK_SIZE_Y-1&&!blocked[i][j+1][k]) || (j==CHUNK_SIZE_Y-1&&!neighbors[3]) ||
					(j==CHUNK_SIZE_Y-1&&neighbors[3]&&!neighbors[3]->blocked[i][0][k]);
				adjacents[4] = (k>0&&!blocked[i][j][k-1]) || (k==0&&!neighbors[4]) ||
					(k==0&&neighbors[4]&&!neighbors[4]->blocked[i][j][CHUNK_SIZE_Z-1]);
				adjacents[5] = (k<CHUNK_SIZE_Z-1&&!blocked[i][j][k+1]) || (k==CHUNK_SIZE_Z-1&&!neighbors[5]) ||
					(k==CHUNK_SIZE_Z-1&&neighbors[5]&&!neighbors[5]->blocked[i][j][0]);

				if(!adjacents[0]&&!adjacents[1]&&!adjacents[2]&&!adjacents[3]&&!adjacents[4]&&!adjacents[5])
					continue;

				ChunkCoords bc(i,j,k);
				
				for(int p=0;p<6;++p)
					if(adjacents[p])
						quad(Vector3(i,j,k),QUADNORMALS[p],d,type,LIGHTVALUES[getLight(this,bc<<p)]);
			}
		}

		if(mChunk)
			mOgre->destroySceneNode(mChunk);

		mChunk = mOgre->createMesh(d);
		mOgre->getRootSceneNode()->addChild(mChunk);
		mChunk->setPosition(mPosition);

		if(physics)
			rebuildPhysics();

		mDirty = false;
	}
	//-----------------------------------------------------------------------
	
	void Chunk::killBlock(Vector3 p,Vector3 n)
	{
		p += OFFSET;
		p-=mPosition;

		Vector3 pn = p-n*0.5f;

		int i = floor(pn.x+0.5);
		int j = floor(pn.y+0.5);
		int k = floor(pn.z+0.5);

		setBlock(this,ChunkCoords(i,j,k),0);
	}
	//-----------------------------------------------------------------------
	
	void Chunk::killBlocks(Vector3 p,float radius)
	{
		p += OFFSET;
		p -= mPosition;

		int i = floor(p.x+0.5);
		int j = floor(p.y+0.5);
		int k = floor(p.z+0.5);

		for(int x=i-radius;x<radius+i;++x)
			for(int y=j-radius;y<radius+j;++y)
				for(int z=k-radius;z<radius+k;++z)
		{
			if(Vector3(x,y,z).distance(Vector3(i,j,k))<radius)
				setBlock(this,ChunkCoords(x,y,z),0);
		}
	}
	//-----------------------------------------------------------------------
	
	void Chunk::addBlock(Vector3 p,Vector3 n,byte type)
	{
		p += OFFSET;
		p-=mPosition;
		float x = (n.x<0) ? -n.x : n.x;
		float y = (n.y<0) ? -n.y : n.y;
		float z = (n.z<0) ? -n.z : n.z;

		Vector3 pn = p+n*-0.4f;

		if(x>y&&x>z)
			n = Vector3(n.x,0,0);
		else if(y>x&&y>z)
			n = Vector3(0,n.y,0);
		else if(z>x&&z>y)
			n = Vector3(0,0,n.z);
		else
			return;

		pn += n*0.6f;

		int i = floor(pn.x+0.5);
		int j = floor(pn.y+0.5);
		int k = floor(pn.z+0.5);

		setBlock(this,ChunkCoords(i,j,k),type);
	}
	//-----------------------------------------------------------------------

	void Chunk::rebuildPhysics()
	{
		for(int i=0;i<CHUNK_STEPS_X;++i)
			for(int j=0;j<CHUNK_STEPS_Y;++j)
				for(int k=0;k<CHUNK_STEPS_Z;++k)
					mBlocks[i][j][k]->rebuild();
	}
	//-----------------------------------------------------------------------

	void Chunk::notifyNeighbors()
	{
		for(int i=0;i<6;++i)
		{
			if(neighbors[i])
			{
				neighbors[i]->neighbors[(i&1)==0?i+1:i-1] = this;
				neighbors[i]->markDirty();
			}
		}
	}
	//-----------------------------------------------------------------------

	void Chunk::clearLighting()
	{	
		memset(light,(byte)0,CHUNK_VOLUME);
	}
	//-----------------------------------------------------------------------

	void Chunk::secondaryLighting()
	{
		for(int p=0;p<6;++p)
		{
			if(neighbors[p])
			{
				for(int i=0;i<16;++i)for(int j=0;j<16;++j)
				{
					byte value;
					ChunkCoords coords;
					// just pretend you didn't see this... the nice clean version was buggy
					// and I haven't had time to figure out why yet...
					switch(p)
					{
					case 0:
						value = neighbors[p]->light[15][i][j];
						coords = ChunkCoords(0,i,j);
						break;
					case 1:
						value = neighbors[p]->light[0][i][j];
						coords = ChunkCoords(15,i,j);
						break;
					case 2:
						value = neighbors[p]->light[i][15][j];
						coords = ChunkCoords(i,0,j);
						break;
					case 3:
						value = neighbors[p]->light[i][0][j];
						coords = ChunkCoords(i,15,j);
						break;
					case 4:
						value = neighbors[p]->light[i][j][15];
						coords = ChunkCoords(i,j,0);
						break;
					case 5:
						value = neighbors[p]->light[i][j][0];
						coords = ChunkCoords(i,j,15);
						break;
					};
					if(value>1)
						getLighting(coords,value-1);
				}
			}
		}
	}
	//-----------------------------------------------------------------------

	void Chunk::localLighting()
	{
		clearLighting();

		for(int i=0;i<CHUNK_SIZE_X;++i)for(int k=0;k<CHUNK_SIZE_Z;++k)
		{
			int highest = 0;
			
			for(int y=0;y<CHUNK_SIZE_Y;++y)
				if(blocked[i][y][k])	
					highest = y;

			for(int p=highest+1;p<CHUNK_SIZE_Y;++p)
				light[i][p][k] = MAX_LIGHT;
		}

		ChunkCoords c = ChunkCoords();

		// this seems sliiightly more efficient... I should probably dig 
		// through the disassembly and figure out for sure, but I'm lazy...
		signed char *i,*j,*k;
		i = &c.x;
		j = &c.y;
		k = &c.z;

		for((*i)=0;(*i)<CHUNK_SIZE_X;++(*i))
			for((*j)=0;(*j)<CHUNK_SIZE_Y;++(*j))
				for((*k)=0;(*k)<CHUNK_SIZE_Z;++(*k))
		{
			if(getLightState(c)==MAX_LIGHT)
				getLighting(c,MAX_LIGHT);
		}
	}
	//-----------------------------------------------------------------------
	
	void Chunk::getLighting(ChunkCoords& c,int light)
	{
		if(light>0 && c.inBounds() && !isSolid(c) &&
			!(light != MAX_LIGHT&&!setLight(c,light)))
		{
			// explore in each direction 
			for(int i=0;i<6;++i)
			{
				byte val = (i&1)==0 ? 1 : -1;

				// choose
				c[i/2] += val;

				// explore
				getLighting(c,light-1);

				// unchoose
				c[i/2] -= val;
			}
		}
	}
	//-----------------------------------------------------------------------

	void quad(Vector3 pos,Vector3 normal,MeshData& d,short type,Colour diffuse)
	{
		Vector2 offset;
		int dims = 2;
		int tp = type-1;
		float gridSize = 1.f/dims;

		offset = Vector2(tp%dims*gridSize,tp/dims*gridSize);

		Quaternion rot;

		float factor = 1.f;
		
		if(normal.y<=-0.8)
			rot = Quaternion::IDENTITY;
		else if(normal.y>=0.8)
			rot = Quaternion(0,0,1,0);
		else 
			rot = normal.getRotationTo(Vector3(0,1,0));

		pos -= OFFSET;

		d.vertex(pos+rot * Vector3(-1,1,-1)*0.5,normal,offset+Vector2(0,0)*gridSize);
		d.vertex(pos+rot * Vector3(-1,1,1)*0.5,normal,offset+Vector2(0,1)*gridSize);
		d.vertex(pos+rot * Vector3(1,1,-1)*0.5,normal,offset+Vector2(1,0)*gridSize);
		
		d.vertex(pos+rot * Vector3(-1,1,1)*0.5,normal,offset+Vector2(0,1)*gridSize);
		d.vertex(pos+rot * Vector3(1,1,1)*0.5,normal,offset+Vector2(1,1)*gridSize);
		d.vertex(pos+rot * Vector3(1,1,-1)*0.5,normal,offset+Vector2(1,0)*gridSize);
		
		for(int i=0;i<6;++i)
		{
			d.diffuse.push_back(diffuse.r);
			d.diffuse.push_back(diffuse.g);
			d.diffuse.push_back(diffuse.b);
		}
	}
	//-----------------------------------------------------------------------
}

