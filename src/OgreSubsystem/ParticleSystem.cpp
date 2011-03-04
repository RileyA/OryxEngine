//-----------------------------------------------------------------------
// Copyright Riley Adams 2010

// This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#include "Oryx.h"
#include "ParticleSystem.h"
#include "Oryx3DMath.h"	
#include "Ogre.h"
#include "OgreConversions.h"

namespace Oryx
{
	ParticleSystem::ParticleSystem(String name,Ogre::SceneNode* node,Ogre::ParticleSystem* psys)
		:SceneNode(name,node),mParticleSystem(psys){}
	//--------------------------------------------------------------------------

	ParticleSystem::~ParticleSystem()
	{
		mNode->getCreator()->destroyParticleSystem(mParticleSystem);
	}
	//--------------------------------------------------------------------------
	
	void ParticleSystem::scale(Real scale)
	{
		//mNode->setScale(scale,scale,scale);

		mParticleSystem->setDefaultWidth(
			mParticleSystem->getDefaultWidth()*scale);

		mParticleSystem->setDefaultHeight(
			mParticleSystem->getDefaultHeight()*scale);


		for(int i=0;i<mParticleSystem->getNumEmitters();++i)
		{
			mParticleSystem->getEmitter(i)->setMinParticleVelocity(
				mParticleSystem->getEmitter(i)->getMinParticleVelocity()*scale);
			mParticleSystem->getEmitter(i)->setMaxParticleVelocity(
				mParticleSystem->getEmitter(i)->getMaxParticleVelocity()*scale);
		}
		for(int i=0;i<mParticleSystem->getNumAffectors();++i)
		{
			Ogre::ParticleAffector* a = mParticleSystem->getAffector(i);
			if(a->getType()=="LinearForce")
			{
				String f = a->getParameter("force_vector");
				std::stringstream ss;
				ss<<f;
				Real x,y,z;
				ss>>x;
				ss>>y;
				ss>>z;
				ss.clear();
				ss<<x*scale<<" "<<y*scale<<" "<<z*scale;
				String t;
				std::getline(ss,t);
				a->setParameter("force_vector",t);
			}
			else if(a->getType()=="Scaler")
			{
				a->setParameter("rate",Ogre::StringConverter::toString(atoi(
					a->getParameter("rate").c_str())*scale));
			}
		}
	}

	bool ParticleSystem::isDone()
	{
		for(int i=0;i<mParticleSystem->getNumEmitters();++i)
		{
			if(mParticleSystem->getEmitter(i)->getEnabled())
				return false;
			//mParticleSystem->getEmitter(i)->setEnabled(true);
		}		
		return mParticleSystem->getNumParticles()==0;
	}

	void ParticleSystem::restart()
	{
		//mParticleSystem->setEmitting(true);
		for(int i=0;i<mParticleSystem->getNumEmitters();++i)
		{
			mParticleSystem->getEmitter(i)->setEnabled(true);
			//mParticleSystem->getEmitter(i)->setStartTime(0.f);
		}
	}
}
