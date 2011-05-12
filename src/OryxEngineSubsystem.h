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
	/** An abstract representation of an Engine Subsystem 
	 *		The dependency system is really wonky right now... */
	class ORYX_EXPORT EngineSubsystem : public EventHandler
	{
	public:

		/** Constructor */
		EngineSubsystem(){}

		// should initialize the subsystem
		virtual void _init() = 0;

		// should deinit and clean up
		virtual void _deinit() = 0;

		// callback for when a GameState ends
		virtual void _endState() = 0;

		/** Should update this state
		 *		@param delta The time since the last frame */
		virtual void _update(Real delta) = 0;

		/** Gets the name of this subsystem */
		virtual String getName(){return "UnnamedSubsystem";}

		// Helper for casting to a derived type
		template<typename T> T* castType(){return dynamic_cast<T*>(this);}
	};
}

#endif
