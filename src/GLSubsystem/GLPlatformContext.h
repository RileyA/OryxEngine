#ifndef ORYX_GLPlatformContext_H
#define ORYX_GLPlatformContext_H

#include "Oryx.h"
#include "OryxEventHandler.h"

namespace Oryx
{
	/** Interface to be implemented by platform-specific GL context 
	 *		stuffs (i.e. Xlib/GLX in Linux). */
	class GLPlatformContext : public EventHandler
	{
	public:

		virtual void init(size_t h, size_t w, bool fullscreen) = 0;
		virtual void deinit() = 0;
		virtual void update() = 0;
		virtual void swapBuffers() = 0;
		virtual long getWindowHandle() = 0;

		size_t getHeight() {return mHeight;}
		size_t getWidth() {return mWidth;}

	protected:

		size_t mWidth, mHeight;

	};
}

#endif

