//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2010

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

#ifndef ORYX_SUBSYSTEM_H
#define ORYX_SUBSYSTEM_H

#include "Oryx.h"
#include "OryxEventHandler.h"

namespace Oryx
{
    class ORYX_EXPORT EngineSubsystem : public EventHandler
    {
    public:

        EngineSubsystem(String* deps,size_t count)
        {
            for(size_t i=0;i<count;++i)
                mDependencies[deps[i]] = 0;
        }

        virtual void _init() = 0;
        virtual void _deinit() = 0;
        virtual void _endState() = 0;
        virtual void _update(Real delta) = 0;
        virtual String getName() = 0;

        template<typename T> T* castType(){return dynamic_cast<T*>(this);}

        std::map<String,EngineSubsystem*>& getDependencies(){return mDependencies;}

    protected:

        std::map<String,EngineSubsystem*> mDependencies;

    };
}

#endif
