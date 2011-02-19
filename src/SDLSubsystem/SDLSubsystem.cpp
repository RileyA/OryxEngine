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

#include "SDLdllmain.h"
#include "SDLSubsystem.h"
#include "OryxLogger.h"
#include "OryxStringUtils.h"

#include "SDL.h"

namespace Oryx
{
    const size_t SDLSubsystem::mDependencyCount = 0;
    const String SDLSubsystem::mDependencies[1];// nothin'

    SDLSubsystem::SDLSubsystem(int width,int height)
        :EngineSubsystem(const_cast<String*>(mDependencies),mDependencyCount),
            mInitialized(0),
            mWidth(width),
            mHeight(height),
            mManual(0) {}
    //-----------------------------------------------------------------------

    SDLSubsystem::~SDLSubsystem()
    {
        _deinit();
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::_init()
    {
        if(SDL_Init(SDL_INIT_VIDEO)<0)
            Logger::getPtr()->logMessage("Unable to init SDL: " + String(SDL_GetError()));

        mSurface = SDL_SetVideoMode(mWidth,mHeight,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

        if(!mSurface)
            Logger::getPtr()->logMessage("SDL surface creation failed!");
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::_deinit()
    {
        SDL_Quit();
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::_update(Real delta)
    {
        if(!mManual)
        {
            lock();

            for(int x=0;x<mWidth;++x)
            {
                for(int y=0;y<mHeight;++y)
                {
                    drawPixel(x,y,mBackgroundColour);
                }
            }

            unlock();
            SDL_Flip(mSurface);
        }
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::_endState()
    {

    }
    //-----------------------------------------------------------------------

    String SDLSubsystem::getName()
    {
        return "SDLSubsystem";
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::lock()
    {
        if(SDL_MUSTLOCK(mSurface))
        {
            if(SDL_LockSurface(mSurface)<0)
                return;
        }
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::unlock()
    {
        if(SDL_MUSTLOCK(mSurface))
            SDL_UnlockSurface(mSurface);
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::flip()
    {
        SDL_Flip(mSurface);
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::drawPixel(int x,int y,Colour colour)
    {
        unsigned int col = SDL_MapRGB(mSurface->format, colour.getR8(), colour.getG8(), colour.getB8());

        switch (mSurface->format->BytesPerPixel)
        {
            case 1: // Assuming 8-bpp
            {
                Uint8 *bufp;
                bufp = (Uint8 *)mSurface->pixels + y*mSurface->pitch + x;
                *bufp = col;
            }
            break;
            case 2: // Probably 15-bpp or 16-bpp
            {
                Uint16 *bufp;
                bufp = (Uint16 *)mSurface->pixels + y*mSurface->pitch/2 + x;
                *bufp = col;
            }
            break;
            case 3: // Slow 24-bpp mode, usually not used
            {
                Uint8 *bufp;
                bufp = (Uint8 *)mSurface->pixels + y*mSurface->pitch + x * 3;
                if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
                {
                    bufp[0] = col;
                    bufp[1] = col >> 8;
                    bufp[2] = col >> 16;
                }
                else
                {
                    bufp[2] = col;
                    bufp[1] = col >> 8;
                    bufp[0] = col >> 16;
                }
            }
            break;
            case 4: // Probably 32-bpp
            {
                Uint32 *bufp;
                bufp = (Uint32 *)mSurface->pixels + y*mSurface->pitch/4 + x;
                *bufp = col;
            }
            break;
        }
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::setManual(bool manual)
    {
        mManual = manual;
    }
    //-----------------------------------------------------------------------

    bool SDLSubsystem::getManual()
    {
        return mManual;
    }
    //-----------------------------------------------------------------------

    void SDLSubsystem::setBackgroundColour(Colour col)
    {
        mBackgroundColour = col;
    }
    //-----------------------------------------------------------------------

    Colour SDLSubsystem::getBackgroundColour()
    {
        return mBackgroundColour;
    }
    //-----------------------------------------------------------------------
}