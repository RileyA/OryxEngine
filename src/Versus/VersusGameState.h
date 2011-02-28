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

#ifndef VERSUS_GAMESTATE
#define VERSUS_GAMESTATE

#include "Oryx.h"
#include "OryxEngine.h"
#include "OryxGameState.h"
#include "FPSCamera.h"
#include "ExplosionManager.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "VersusPeer.h"
#include "OryxMessageAny.h"
#include "OryxEventHandler.h"

#include "ENetSubsystem/ENetSubsystem.h"
#include "ENetSubsystem/Server.h"
#include "ENetSubsystem/Client.h"
#include "BulletSubsystem/BulletSubsystem.h"

// uuuuugly playpen code

namespace Oryx
{

	// this is obviously the scientific nomenclature
	class CharacterThingy
	{
	public:

		static const Real SKIN_WIDTH=0.075f;
		static const Real TIMESTEP = 1.f/60.f;// update 60 times/s

		
		CharacterThingy(BulletSubsystem* bs,OgreSubsystem* ogre)
		{
			mBullet = bs;
			mOgre = ogre;
			mSphere = mBullet->createSphereShape(0.375f);
			mSpeed = 5.f;// 2 m/s?
			mPosition = Vector3(0,0,0);
			debug = mOgre->createMesh("DBGSPHERE.mesh");
			mOgre->getRootSceneNode()->addChild(debug);

			debug->setVisible(false);
			for(int i=0;i<10;++i)
			{
				pastFrames.push_back(mOgre->createMesh("DBGSPHERE.mesh"));
				mOgre->getRootSceneNode()->addChild(pastFrames.back());
				poses.push_back(Vector3(0,0,0));
				pastFrames.back()->setVisible(false);
				pastFrames[i]->setScale(Vector3(0.1+i/10.f,0.1+i/10.f,0.1f+i/10.f));
			}

			frm = 0;

			acc = 0.f;

		}

		void update(Real delta,Vector3 motion)
		{
			acc+=delta;
			while(acc>TIMESTEP)
			{
				move(Vector3(0,-1,0),10.f,11);

				if(motion.length()>0.001f)
					move(motion);

				acc-=TIMESTEP;
			}
		}

		void move(Vector3 direction,Real speed = 0.f,int gg=0,float offset=0.f)
		{
			if(speed==0.f)
				speed = mSpeed;
			
			direction.normalize();
			float step;

			step = (!gg||gg==11) ? TIMESTEP*speed : offset;

			float originalStep = step;
			Real castLen = step + SKIN_WIDTH;
			SweepReport swept = mBullet->sweep(mSphere,mPosition,direction,castLen,
					COLLISION_GROUP_3,COLLISION_GROUP_3);
			Real hitDist = castLen * swept.hitFraction;

			if(!swept.hit)
				mPosition += direction*step;
			else
			{
				step = std::max(step - (castLen - hitDist),0.f);
				mPosition += direction*step;

				if(gg<10)
				{
					
					Vector3 slide = direction + swept.normal * direction.dotProduct(swept.normal*-1);
					Plane pl = Plane(Vector3(0,1,0),0);
					slide = pl.projectVector(slide);
					if(slide.squaredLength()>0)
					{
						slide.normalize();
						move(slide,0.f,gg+1,originalStep-step);
					}
				}
			}


			/*if(!gg)
			{
				debug->setPosition(mPosition);
				poses.push_back(mPosition);
				poses.erase(poses.begin());
					for(int i=0;i<pastFrames.size();++i)
						pastFrames[i]->setPosition(poses[i]);
			}*/
		}

		Vector3 getPos()
		{
			return mPosition;
		}

		PhysicsShape* mSphere;
		BulletSubsystem* mBullet;
		OgreSubsystem* mOgre;
		Real mSpeed;
		Vector3 mPosition;
		Real acc;

		Mesh* debug;
		std::vector<Mesh*> pastFrames;
		std::vector<Vector3> poses;
		int frm;

	};

	class VersusGameState : public GameState
	{
	public:

		VersusGameState();
		
		void init();
		void update(Real delta);
		void deinit();

		QuantaController* qcc;

		void processPackets(byte* data,size_t length,size_t id);
		void addPeer(byte id,String name);
		void removePeer(byte id);
		void mouse(const Message& msg);
		StaticText* txt; 
		std::map<byte,TestPeer*> mPeers;
		Client* mClient;
		FPSCamera* mCam;
		Real mTimer;
		GUIRectangle* curse;
		Chunk* c;
		bool toggle;
		bool toggle2;
		PhysicsObject* box;
		ExplosionManager* mgr;
		ChunkManager* cmgr;
		int currentMat;

		CharacterThingy* ct;
	};
}

#endif
