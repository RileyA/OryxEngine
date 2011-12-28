#ifndef ORYX_GLXPlatformContext_H
#define ORYX_GLXPlatformContext_H

#include "GLPlatformContext.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace Oryx
{
	class GLXPlatformContext : public GLPlatformContext
	{
	public:

		GLXPlatformContext();
		~GLXPlatformContext();

		virtual void init(size_t h, size_t w, bool fullscreen);
		virtual void deinit();
		virtual void update();
		virtual void swapBuffers();
		virtual long getWindowHandle();

	private:

		Display* mDisplay;
		Window mRoot;
		XVisualInfo* mVisual;
		Colormap mColormap;
		XSetWindowAttributes mSetWindowAttributes;
		Window mWindow;
		GLXContext mContext;
		XWindowAttributes mWindowAttributes;
		Atom mDeleteMessage;
		bool mInitialized;

	};
}

#endif

