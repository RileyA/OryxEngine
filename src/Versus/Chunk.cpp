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

#define COLORVAL(x) Colour(x,x,x)

namespace Oryx
{
	const Vector3 Chunk::mNormals[6] = {
		Vector3(1,0,0),
		Vector3(-1,0,0),
		Vector3(0,1,0),
		Vector3(0,-1,0),
		Vector3(0,0,1),
		Vector3(0,0,-1)};
	
	const Colour Chunk::mLightValues[16] = {
		COLORVAL(0.021475f),
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
		COLORVAL(1.f)
	};


	void quad(Vector3 pos,Vector3 normal,MeshData& d,short type,Colour diffuse);
	void getLighting(Chunk* c,int x,int y,int z,int light,bool origin = false);

	Chunk::Chunk(Vector3 position,ChunkManager* parent)
		:mPosition(position),mParent(parent)
	{	
		lightingDirty = true;
		mChunk = 0;
		mPosition = position;
		mOgre = Engine::getPtr()->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();

		memset(blocked,(byte)0,4096);
		memset(light,(byte)0,4096);
	
		// init all the blocks
		for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		{		
			if(j<8)
				blocked[i][j][k] = 4;
		}
		
		BulletSubsystem* b = Engine::getPtr()->getSubsystem("BulletSubsystem")->
			castType<BulletSubsystem>();

		// init the physics
		for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)
		{
			mBlocks[i][j][k] = new PhysicsBlock(i,j,k,
				b->createCompound(Vector3(-7.5,-7.5,-7.5)+Vector3(i,j,k)*4+mPosition),this);
		}

		for(int p=0;p<6;++p)
			neighbors[p] = 0;
	}
	//-----------------------------------------------------------------------
	
	Chunk::~Chunk()
	{
		for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)
			delete mBlocks[i][j][k];
	}

	void Chunk::update(Real delta)
	{
	}
	//-----------------------------------------------------------------------
	
	void Chunk::build(bool physics)
	{
		MeshData d;

		if(mDirty)
			physics = true;

		for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		{

			if(blocked[i][j][k])
			{ 	
				bool adjacents[6];

				// very ugly, but hard coding this all seems ~50% more efficient 
				// than my attempt at a cleaner version...
				adjacents[0] = (i>0&&!blocked[i-1][j][k]) || (i==0&&!neighbors[0]) ||
					(i==0&&neighbors[0]&&!neighbors[0]->blocked[15][j][k]);
				adjacents[1] = (i<15&&!blocked[i+1][j][k]) || (i==15&&!neighbors[1]) ||
					(i==15&&neighbors[1]&&!neighbors[1]->blocked[0][j][k]);
				adjacents[2] = (j>0&&!blocked[i][j-1][k]) || (j==0&&!neighbors[2]) ||
					(j==0&&neighbors[2]&&!neighbors[2]->blocked[i][15][k]);			
				adjacents[3] = (j<15&&!blocked[i][j+1][k]) || (j==15&&!neighbors[3]) ||
					(j==15&&neighbors[3]&&!neighbors[3]->blocked[i][0][k]);
				adjacents[4] = (k>0&&!blocked[i][j][k-1]) || (k==0&&!neighbors[4]) ||
					(k==0&&neighbors[4]&&!neighbors[4]->blocked[i][j][15]);
				adjacents[5] = (k<15&&!blocked[i][j][k+1]) || (k==15&&!neighbors[5]) ||
					(k==15&&neighbors[5]&&!neighbors[5]->blocked[i][j][0]);

				if(!adjacents[0]&&!adjacents[1]&&!adjacents[2]&&!adjacents[3]&&!adjacents[4]&&!adjacents[5])
					continue;

				byte type = blocked[i][j][k];
				ChunkCoords bc(i,j,k);
				
				for(int p=0;p<6;++p)
					if(adjacents[p])
						quad(Vector3(i,j,k),mNormals[p],d,type,mLightValues[getLight(this,getChunkCoords(bc,p))]);
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

	//-----------------------------------------------------------------------
	
	void Chunk::killBlock(Vector3 p,Vector3 n)
	{
		p+=Vector3(7.5,7.5,7.5);
		p-=mPosition;

		Vector3 pp = p-n*0.5f;

		int i = floor(pp.x+0.5);
		int j = floor(pp.y+0.5);
		int k = floor(pp.z+0.5);

		setBlock(this,ChunkCoords(i,j,k),0);
	}
	//-----------------------------------------------------------------------
	
	void Chunk::killBlocks(Vector3 p,float radius)
	{
		p+=Vector3(7.5,7.5,7.5);
		p-=mPosition;

		int i = floor(p.x+0.5);
		int j = floor(p.y+0.5);
		int k = floor(p.z+0.5);

		//for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		//	if(Vector3(i,j,k).distance(p)<=radius)
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
		p+=Vector3(7.5,7.5,7.5);
		p-=mPosition;
		float x = (n.x<0) ? -n.x : n.x;
		float y = (n.y<0) ? -n.y : n.y;
		float z = (n.z<0) ? -n.z : n.z;

		Vector3 pp = p+n*-0.4f;

		if(x>y&&x>z)
			n = Vector3(n.x,0,0);
		else if(y>x&&y>z)
			n = Vector3(0,n.y,0);
		else if(z>x&&z>y)
			n = Vector3(0,0,n.z);
		else
			return;

		pp+=n*0.6f;

		int i = floor(pp.x+0.5);
		int j = floor(pp.y+0.5);
		int k = floor(pp.z+0.5);

		setBlock(this,ChunkCoords(i,j,k),type);
	}
	//-----------------------------------------------------------------------


	
	void Chunk::rebuildPhysics()
	{
		for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)
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
		memset(light,(byte)0,4096);
	}
	//-----------------------------------------------------------------------

	void Chunk::secondaryLighting()
	{
		//return;
		for(int p=0;p<6;++p)
		{
			if(neighbors[p])
			{
				ChunkCoords c = ChunkCoords(0,0,0);

				// ugly, but theoretically more effiecient than my original solution...
				signed char* i, *j, *k;
				signed char opposite = 0;
				
				i = &(c[p<2?1:0]);
				j = &(c[p>3?1:2]);
				//k = &(c[p/2]);

				c[p/2] = ((p%2)==0) ? CHUNKSIZE[p/2]-1:0;
				if(c[p/2]==0)
					opposite = 15;
				else
					opposite = 0;
				//opposite = ((p%2)==0) ? CHUNKSIZE[p/2]-1:0;

				for((*i)=0;(*i)<16;++(*i))for((*j)=0;(*j)<16;++(*j))
				{
					byte value = neighbors[p]->getLightState(c);
					if(value>1)
					{
						c[p/2] = opposite;
						getLighting(c,value-1);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------

	void Chunk::localLighting()
	{
		lightingDirty = false;
		clearLighting();
		for(int i=0;i<16;++i)for(int k=0;k<16;++k)
		{
			int highest = 0;
			
			for(int y=0;y<16;++y)
				if(blocked[i][y][k])	
					highest = y;

			for(int p=highest+1;p<16;++p)
				light[i][p][k] = 15;
		}

		ChunkCoords c = ChunkCoords();

		// this seems sliiightly more efficient... I should probably dig 
		// through the disassembly and figure out for sure, but I'm lazy...
		signed char *i,*j,*k;
		i = &c.x;
		j = &c.y;
		k = &c.z;

		for((*i)=0;(*i)<16;++(*i))for((*j)=0;(*j)<16;++(*j))for((*k)=0;(*k)<16;++(*k))
		{
			if(getLightState(c)==15)
				getLighting(c,15);
		}
	}
	//-----------------------------------------------------------------------
	
	void Chunk::getLighting(ChunkCoords c,int light)
	{
		if(light>0&&c.inBounds()&&(light==15||!isSolid(c)))
		{
			if(light!=MAX_LIGHT&&!setLight(c,light))
				return;
				
			--light;

			// explore in each direction 
			for(int i=0;i<6;++i)
			{
				byte val = (i&1)==0 ? 1 : -1;

				// choose
				c[i/2] += val;

				// explore
				getLighting(c,light);

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

		pos-=Vector3(7.5f,7.5f,7.5f);

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

