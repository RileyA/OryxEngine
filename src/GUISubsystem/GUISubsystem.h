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

#ifndef ORYXGUISUBSYSTEM
#define ORYXGUISUBSYSTEM

#include "Oryx.h"
#include "GUIdllmain.h"
#include "OryxEngineSubsystem.h"
#include "GUIBatch.h"

namespace Oryx
{
	class ORYX_GUI_EXPORT GUISubsystem : public EngineSubsystem
	{
	public:

		GUISubsystem(int width, int height);
		~GUISubsystem();

		virtual void _init();
		virtual void _deinit();
		virtual void _update(Real delta);
		virtual void _endState();
		virtual String getName();

		void setHeight(int w){mWidth = w;}
		void setWidth(int h){mHeight = h;}

		Batch* createBatch(String name, String atlas, int w = 0, int h = 0);

	protected:

		bool mInitialized;
		std::map<String, Batch*> mBatches;

		Oyster::Oyster* mOyster;

		// The screen width/height
		int mWidth;
		int mHeight;

	};
}

#endif
