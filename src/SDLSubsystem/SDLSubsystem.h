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

#ifndef ORYX_SDL_SUBSYSTEM_H
#define ORYX_SDL_SUBSYSTEM_H

#include "Oryx.h"
#include "SDLdllmain.h"
#include "OryxEngineSubsystem.h"
#include "OryxColor.h"

struct SDL_Surface;

namespace Oryx
{
	class ORYX_SDL_EXPORT SDLSubsystem : public EngineSubsystem
	{
	public:

		SDLSubsystem(int width=640,int height=480);
		~SDLSubsystem();

		virtual void _init();
		virtual void _deinit();
		virtual void _update(Real delta);
		virtual void _endState();
		virtual String getName();

		void lock();
		void unlock();
		void flip();
		void drawPixel(int x,int y,Color colour);
		void drawPixel(int x,int y,byte r, byte g, byte b);
		void setManual(bool manual);
		bool getManual();
		void setBackgroundColor(Color col);
		Color getBackgroundColor();

		void drawRaw(byte* data, int x=0, int y=0);

	protected:

		bool mInitialized;

		SDL_Surface* mSurface;
		Color mBackgroundColor;

		int mWidth;
		int mHeight;

		bool mManual;

	};
}

#endif
