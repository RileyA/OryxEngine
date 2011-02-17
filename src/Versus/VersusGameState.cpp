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
#include "VersusGameState.h"
#include "Chunk.h"
#include "OryxStringUtils.h"
#include "OryxLogger.h"
#include "OgreSubsystem/GUIButton.h"

namespace Oryx
{

	VersusGameState::VersusGameState()
		:GameState()
	{
		toggle = false;
	}
	
	void VersusGameState::init()
	{
		OgreSubsystem* ogre = mEngine->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();
		BulletSubsystem* bts = mEngine->getSubsystem("BulletSubsystem")->castType<BulletSubsystem>();
		OISSubsystem* ois = mEngine->getSubsystem("OISSubsystem")->castType<OISSubsystem>();
		ois->initInput(ogre->getWindowHandle());
		ogre->setBackgroundColor(Colour(0.f,0.f,0.f));
		ogre->setLinearFog(30.f,45.f,Colour(0.f,0.f,0.f));
		mgr = new ExplosionManager();

		ENetSubsystem* enet = mEngine->getSubsystem("ENetSubsystem")->castType<ENetSubsystem>();
		mClient = enet->createClient();
		mClient->connect("127.0.0.1",1244);
		mClient->addCallback(fastdelegate::MakeDelegate(this,&VersusGameState::processPackets));
		mClient->addConnectCallback(fastdelegate::MakeDelegate(this,&VersusGameState::addPeer));
		mClient->addDisconnectCallback(fastdelegate::MakeDelegate(this,&VersusGameState::removePeer));
		createSlot("clk",fastdelegate::MakeDelegate(this,&VersusGameState::mouse));

		GUIScreen* scrn = ogre->getGUI()->createScreen(ogre->getMainViewport(),"TechDemo","Test");

		txt = new StaticText(scrn->getRootElement(0),
			"Text01",0,20,Vector2(10,10),Vector2(0.5,1.f/12.f),"Test!");
		txt->setColour(Colour(0.6,0.75,0.9));
		//txt->setAlign(GA_CENTER);
		//txt->getSignal("clicked")->addListener(getSlot("clk"));

		//GUIRectangle* rect = new GUIRectangle(txt,"Coloredrect01",Colour(1,0,0,0.5),
		//	Colour(0.3,0.6,0.9,0.8),4.0,0,Vector2(10,10),Vector2(0.1,0.1));

		//curse = new GUIRectangle(scrn->getRootElement(15),"cursor","SpriteTest",0,
		//	Vector2(10,10),Vector2(16/1024.f,23/768.f));

		//scrn->setCursor(curse);

		//GUIButton* bt = new GUIButton(scrn->getRootElement(0),0,"cursor");
		//bt->setScale(Vector2(16.f/1024,23.f/768));
		//bt->setPosition(Vector2(50,50));

		mCam = new FPSCamera();
		mTimer = 0.f;

		//ogre->createLight()->setPosition(0,30,0);

		//createSlot("mouse",fastelegate::MakeDelegate(this,&VersusGameState::mouse));
		EventHandler::getDestination("OISSubsystem")->getSignal("mouseMovedAbs")
			->addListener(scrn->getSlot("moveCursor"));

		EventHandler::getDestination("OISSubsystem")->getSignal("pressed_MB_Left")
			->addListener(scrn->getSlot("click"));
		EventHandler::getDestination("OISSubsystem")->getSignal("released_MB_Left")
			->addListener(scrn->getSlot("release"));	
		
		bts->startSimulation();
		cmgr = new ChunkManager(Vector3(0,-10,0));	
	}

	void VersusGameState::update(Real delta)
	{
		txt->setCaption("FPS: "+StringUtils::toString(1.f/delta));
		OISSubsystem* ois = mEngine->getSubsystem("OISSubsystem")->castType<OISSubsystem>();
		OgreSubsystem* ogre = mEngine->getSubsystem("OgreSubsystem")->castType<OgreSubsystem>();
		BulletSubsystem* bts = mEngine->getSubsystem("BulletSubsystem")->castType<BulletSubsystem>();
		
		if(ois->isKeyDown("KC_ESCAPE"))
			sendMessage(MessageAny<String>("kill"),"Engine");

		if(ois->isButtonDown("MB_Right")&&!toggle)
		{
			toggle = true;
			RaycastReport r = bts->raycast(mCam->getPosition(),mCam->getDirection());

			if(r.hit&&r.userData)
			{
				Chunk* xc = (Chunk*)r.userData;
				if(ois->isKeyDown("KC_G"))
				{
					xc->killBlocks(r.position,2);
					mgr->createExplosion(r.position);
				}
				else
					xc->killBlock(r.position,r.normal);
			}
		}
		else if(!ois->isButtonDown("MB_Right")&&toggle)
		{
			toggle = false;
		}

		if(ois->isButtonDown("MB_Left")&&!toggle2)
		{				
		
			RaycastReport r = bts->raycast(mCam->getPosition(),mCam->getDirection());
			toggle2 = true;

			if(r.hit&&r.userData)
			{
				float t1 = TimeManager::getPtr()->getTimeDecimal();
				Chunk* xc = (Chunk*)r.userData;
				xc->addBlock(r.position,r.normal,rand()%4+1);
			}
		}
		else if(!ois->isButtonDown("MB_Left")&&toggle2)
		{
			toggle2 = false;
		}


		mTimer+=delta*(float)rand()/(float)RAND_MAX;

		//if(mTimer>0.1f&&mClient->isConnected())// 10/s 
		//{
		//	mTimer = 0.f;
		//	mClient->sendPacket(&LocationPacket(mClient->getID(),
		//		mCam->mCamera->getAbsolutePosition(),mCam->mCamera->getAbsoluteOrientation()));
//
//		}
		/*
		if(mTimer>0.1f&&TimeManager::getPtr()->getTimeDecimal()>10.f)
		{
			for(int i=0;i<rand()%8+1;++i)
			{
				RaycastReport r = bts->raycast(Vector3(48*(float)rand()/(float)RAND_MAX-24,48*(float)rand()/(float)RAND_MAX-24,48*(float)rand()/(float)RAND_MAX-24),
					Vector3(0,-1,0));

				if(r.hit&&r.userData)
				{
					Chunk* xc = (Chunk*)r.userData;
					xc->killBlocks(r.position,2);
					mgr->createExplosion(r.position);
				}
			}

			mTimer = 0.f;
		}*/
		std::map<byte,TestPeer*>::iterator it = mPeers.begin();
		for(it;it!=mPeers.end();++it)
		{
			Vector2 pos = mCam->mCamera->getScreenCoords(it->second->m->getAbsolutePosition()+
				Vector3(0,0.25f,0));
			pos.x=((pos.x+1.f)/2.f)*1024-0.5f*it->second->txt->getScale().x*ogre->getGUI()->getScreen(
				"Test")->getWidth();
			pos.y=((1.f-pos.y)/2.f)*768;
			it->second->txt->setPosition(pos);
		}

		cmgr->generate(mCam->getPosition());

	//	mCam->mPosNode->setPosition(box->getPosition());

	}

	void VersusGameState::deinit()
	{
		mEngine->getSubsystem("BulletSubsystem")->castType<BulletSubsystem>()->stopSimulation();
		// do stuff
	}

	void VersusGameState::processPackets(byte* data,size_t length,size_t id)
	{
		switch(id)
		{
		case 1:
		{
			StringPacket p(data,length);
			String str = p.message;
			std::cout<<"String packet! "<<str<<"\n";
			break;
		}
		case 2:
		{
			Vector3Packet vp(data,length);
			std::cout<<"Vector: "<<vp.vector.x<<" "<<vp.vector.y<<" "<<vp.vector.z<<"\n";
			break;
		}
		case PI_LOCATION:
		{
			LocationPacket p(data,length);
			if(mPeers.find(p.pid)!=mPeers.end())
			{
				mPeers[p.pid]->m->setPosition(p.position);
				mPeers[p.pid]->m->setOrientation(p.orientation);
			}
		}
		}
	}

	void VersusGameState::addPeer(byte id,String name)
	{
		mPeers[id] = (new TestPeer(id,name));
	}

	void VersusGameState::removePeer(byte id)
	{
		delete mPeers[id];
		mPeers.erase(mPeers.find(id));
	}

	void VersusGameState::mouse(const Message& msg)
	{
		//if(const MessageAny<Vector2>* ms = message_cast<Vector2>(msg))
		//{
			//curse->setPosition(curse->getPosition()+ms->data);
			//mYawNode->yaw(ms->data.x*-0.15f);
			//mPitchNode->pitch(ms->data.y*-0.15f);
		//}
		std::cout<<"YAY!\n";
	}


}

