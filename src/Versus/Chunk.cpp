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
#include "OryxMessageAny.h"
#include "OryxEventHandler.h"
#include "OryxTimeManager.h"
#include "OgreSubsystem/OgreSubsystem.h"
#include "OgreSubsystem/Mesh.h"

namespace Oryx
{
	void quad(Vector3 pos,Vector3 normal,MeshData& d,short type,Colour diffuse);
	void getLighting(Chunk* c,int x,int y,int z,int light,bool origin = false);

	Chunk::Chunk(Vector3 position)
	{	
		lightingDirty = true;
		mChunk = 0;
		mPosition = position;
		mOgre = Engine::getPtr()->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();

		// init all the blocks
		for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		{		
			blocked[i][j][k] = 0;
			light[i][j][k] = 0;
			//if(rand()%2==1)
			//{
				//if(j<4)
				//	blocked[i][j][k] = j+1;
				if(j<3||(Vector3(i,j,k)-Vector3(7,7,7)).length()>10)
				{
					blocked[i][j][k] = 4;
					if(j>8)
						blocked[i][j][k] = rand()%4+1;
				}
				if(j<8)
					blocked[i][j][k] = 4;
			//}
		}
		
		BulletSubsystem* b = Engine::getPtr()->getSubsystem("BulletSubsystem")->
			castType<BulletSubsystem>();

		// init the physics
		for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)
		{
			mBlocks[i][j][k] = new ChunkBlock(i,j,k,
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

		if(!dirtyBlocks.empty())
		{
			physics = true;
			dirtyBlocks.clear();
		}

		for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		{
			if(blocked[i][j][k])
			{ 	
				byte adjacents[6];

				BlockCoord bc(i,j,k);

				// very ugly, but hard coding this all seems ~50% more efficient 
				// than my attempt at cleaner version...
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
				
				byte tp = blocked[i][j][k];			
				Colour shade = Colour(1.f,1.f,1.f);

				for(int p=0;p<6;++p)
				{
					if(adjacents[p])
						quad(Vector3(i,j,k),getBlockFaceNormal(p),d,tp,shade*pow(
							0.75f,15-getLight(this,getBlockCoords(bc,p))));//(p%2==0)?p+1:p-1))));
				}
			}
		}

		if(mChunk)
			mOgre->destroySceneNode(mChunk);

		mChunk = mOgre->createMesh(d);
		mOgre->getRootSceneNode()->addChild(mChunk);
		mChunk->setPosition(mPosition);

		if(physics)
			rebuildPhysics();
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
	
	void Chunk::killBlock(Vector3 p,Vector3 n)
	{
		p+=Vector3(7.5,7.5,7.5);
		p-=mPosition;

		Vector3 pp = p-n*0.5f;

		int i = floor(pp.x+0.5);
		int j = floor(pp.y+0.5);
		int k = floor(pp.z+0.5);

		setBlock(this,BlockCoord(i,j,k),0);
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
				setBlock(this,BlockCoord(x,y,z),0);
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

		setBlock(this,BlockCoord(i,j,k),type);
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
				neighbors[i]->dirtyBlocks.push_back(BlockCoord());
			}
		}
	}
	//-----------------------------------------------------------------------
	
	void ChunkBlock::rebuild()
	{
		BulletSubsystem* b = Engine::getPtr()->getSubsystem("BulletSubsystem")->
			castType<BulletSubsystem>();

		block->removeAllShapes();
		for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)
		{
			bool Xp = x+i==15||!parent->blocked[x+i+1][y+j][z+k];
			bool Xn = x+i==0||!parent->blocked[x+i-1][y+j][z+k];
			bool Yp = y+j==15||!parent->blocked[x+i][y+j+1][z+k];
			bool Yn = y+j==0||!parent->blocked[x+i][y+j-1][z+k];					
			bool Zp = z+k==15||!parent->blocked[x+i][y+j][z+k+1];
			bool Zn = z+k==0||!parent->blocked[x+i][y+j][z+k-1];

			if(!Xp&&!Xn&&!Yn&&!Yp&&!Zp&&!Zn)
				continue;

			if(parent->blocked[x+i][y+j][z+k])
				block->addShape(b->createBoxShape(Vector3(0.5,0.5,0.5)),
					Vector3(i,j,k));
		}
	}

	void Chunk::clearLighting()
	{	
		memset(light,(byte)0,4096);
	}

	void Chunk::secondaryLighting()
	{
		for(int p=0;p<6;++p)
		{
			if(neighbors[p])
			{
				for(int i=0;i<16;++i)for(int j=0;j<16;++j)
				{
					byte value;
					switch(p)
					{
					case 0:
						value = neighbors[p]->light[15][i][j];
						if(value>0)
							getLighting(this,0,i,j,value-1);
						break;
					case 1:
						value = neighbors[p]->light[0][i][j];
						if(value>0)
							getLighting(this,15,i,j,value-1);
						break;
					case 2:
						value = neighbors[p]->light[i][15][j];
						if(value>0)
							getLighting(this,i,0,j,value-1);
						break;
					case 3:
						value = neighbors[p]->light[i][0][j];
						if(value>0)
							getLighting(this,i,15,j,value-1);
						break;
					case 4:
						value = neighbors[p]->light[i][j][15];
						if(value>0)
							getLighting(this,i,j,0,value-1);
						break;
					case 5:
						value = neighbors[p]->light[i][j][0];
						if(value>0)
							getLighting(this,i,j,15,value-1);
						break;
					};
				}
			}
		}
	}

	void Chunk::localLighting()
	{
		lightingDirty = false;
		clearLighting();
		for(int i=0;i<16;++i)for(int k=0;k<16;++k)
		{
			Chunk* c = this;
			int highest = 0;
			int ii = 0;
			int iterations = 0;
			while(c)
			{
				if(c->blocked[i][ii][k])	
				{
					highest = ii;
					if(iterations)
					{
						highest = 999;
						break;
					}
				}	
				++ii;
				if(ii>15)
				{
					++iterations;
					ii = 0;
					c = c->neighbors[2];// wrong???
				}
			}

			if(highest<16)
			{
				for(int p=0;p<16;++p)
				{
					if(p>highest)
						light[i][p][k] = 15;
				}
			}
		}

		for(int i=0;i<16;++i)for(int j=0;j<16;++j)for(int k=0;k<16;++k)
		{
			if(light[i][j][k]==15)
				getLighting(this,i,j,k,15,true);
			//else if(blocked[i][j][k]==1)
			//	getLighting(this,i,j,k,15,true);
		}
	}
	//-----------------------------------------------------------------------
	
	void getLighting(Chunk* c,int x,int y,int z,int light,bool origin)
	{
		if(light<=0||x>15||x<0||y>15||y<0||z>15||z<0||(c->blocked[x][y][z]&&!origin))
			return;
		
		if(!c)
			return;

		bool gogo = true;

		if(light!=15)
			gogo = Chunk::setLight(c,BlockCoord(x,y,z),light);	

		--light;

		if(!gogo) return;

		getLighting(c,x+1,y,z,light);
		getLighting(c,x-1,y,z,light);
		getLighting(c,x,y+1,z,light);
		getLighting(c,x,y-1,z,light);
		getLighting(c,x,y,z+1,light);
		getLighting(c,x,y,z-1,light);
	}
	//-----------------------------------------------------------------------
}

