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

#include "Oryx.h"
#include "OryxBucket.h"
#include "OryxObject.h"

namespace Oryx
{
	Bucket::Bucket(String name)
		:mName(name),mTemporary(true)
	{
		
	}
	//-----------------------------------------------------------------------

	Bucket::~Bucket()
	{
		std::map<OryxID,Object*>::iterator it = mObjects.begin();
		for(it;it!=mObjects.end();++it)
			delete it->second;
		mObjects.clear();
	}
	//----------------------------------------------------------------------
	
	void Bucket::update(Real delta)
	{
		std::map<OryxID,Object*>::iterator it = mObjects.begin();
		for(it;it!=mObjects.end();++it)
		{
			it->second->update(delta);	
		}
	}
	//-----------------------------------------------------------------------

	void Bucket::addObject(Object* obj)
	{
		mObjects[obj->getID()] = obj;
	}
	//-----------------------------------------------------------------------

	Object* Bucket::getObject(String name)
	{
		std::map<OryxID,Object*>::iterator it = mObjects.begin();
		for(it;it!=mObjects.end();++it)
		{
			if(it->second->getName()==name)
				return it->second;
		}
		return 0;
	}
	//-----------------------------------------------------------------------
	
	Object* Bucket::getObject(OryxID id)
	{
		if(mObjects.find(id)!=mObjects.end())
			return mObjects[id];
		return 0;
	}
	//-----------------------------------------------------------------------

	bool Bucket::hasObject(String name) const
	{
		std::map<OryxID,Object*>::const_iterator it = mObjects.begin();
		for(it;it!=mObjects.end();++it)
		{
			if(it->second->getName()==name)
				return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------
	
	bool Bucket::hasObject(OryxID id) const
	{
		return mObjects.find(id)!=mObjects.end() ? true : false;
	}
	//-----------------------------------------------------------------------

	bool Bucket::killObject(String name)
	{
		std::map<OryxID,Object*>::iterator it = mObjects.begin();
		for(it;it!=mObjects.end();++it)
		{
			if(it->second->getName()==name) {
        delete it->second;
        mObjects.erase(it);
				return true;
      }
		}
		return false;
	}
	//-----------------------------------------------------------------------

	bool Bucket::killObject(OryxID id)
	{
		if(mObjects.find(id)!=mObjects.end()) {
      delete mObjects.find(id)->second;
			mObjects.erase(mObjects.find(id));
      return true;
    }
    return false;
	}
 
	bool Bucket::isTemporary() const
	{
		return mTemporary;
	}
	//-----------------------------------------------------------------------

	void Bucket::setTemporary(bool temp)
	{
		mTemporary = temp;
	}
	//-----------------------------------------------------------------------
}
