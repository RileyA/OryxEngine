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

#ifndef ORYX_STATE
#define ORYX_STATE

#include "Oryx.h"
#include "OryxEventHandler.h"

namespace Oryx
{
    class ORYX_EXPORT State : public EventHandler
    {
    public:

        virtual void init()=0;
        virtual void update(Real delta)=0;
        virtual void deinit()=0;

        bool isDone(){return mDone;}

    protected:

        bool mDone;

    };
}

#endif
