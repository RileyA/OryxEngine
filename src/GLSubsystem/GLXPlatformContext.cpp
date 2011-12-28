#include "GLXPlatformContext.h"

namespace Oryx
{
	GLXPlatformContext::GLXPlatformContext()
	{
		mInitialized = false;
		mDisplay = 0;
		mVisual = 0;
		createSignal("WindowResized");
		createSignal("WindowClosed");
	}
	//-----------------------------------------------------------------------

	GLXPlatformContext::~GLXPlatformContext()
	{
		deinit();
	}
	//-----------------------------------------------------------------------

	void GLXPlatformContext::init(size_t w, size_t h, bool fullscreen)
	{
		if(!mInitialized)
		{
			// open local display
			mDisplay = XOpenDisplay(0);

			if(!mDisplay)
				return;

			mRoot = DefaultRootWindow(mDisplay);

			GLint attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
			mVisual = glXChooseVisual(mDisplay, 0, attributes);

			if(!mVisual)
				return;

			mColormap = XCreateColormap(mDisplay, mRoot, mVisual->visual, AllocNone);

			mSetWindowAttributes.event_mask = StructureNotifyMask;
			mSetWindowAttributes.colormap = mColormap;

			mWindow = XCreateWindow(mDisplay, mRoot, 0, 0, w, h, 0, mVisual->depth,
				InputOutput, mVisual->visual, CWColormap | CWEventMask, &mSetWindowAttributes);

			// register interest in the delete window message
			mDeleteMessage = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
			XSetWMProtocols(mDisplay, mWindow, &mDeleteMessage, 1);

			XMapWindow(mDisplay, mWindow);
			XStoreName(mDisplay, mWindow, "Test");

			mContext = glXCreateContext(mDisplay, mVisual, 0, GL_TRUE);
			glXMakeCurrent(mDisplay, mWindow, mContext);

			// the window and context are now all initialized, yay!
			mInitialized = true;
		}
	}
	//-----------------------------------------------------------------------

	void GLXPlatformContext::deinit()
	{
		if(mInitialized)
		{
			glXMakeCurrent(mDisplay, None, 0);
			glXDestroyContext(mDisplay, mContext);
			XDestroyWindow(mDisplay, mWindow);
			XCloseDisplay(mDisplay);
			mInitialized = false;
		}
	}
	//-----------------------------------------------------------------------

	void GLXPlatformContext::update()
	{
		XEvent xev;

		while(XCheckMaskEvent(mDisplay, StructureNotifyMask, &xev))
		{
			switch(xev.type)
			{
				case ConfigureNotify:

					if(xev.xconfigure.width != mWidth || xev.xconfigure.height != mHeight)
					{
						mWidth = xev.xconfigure.width;
						mHeight = xev.xconfigure.height;
						std::pair<size_t, size_t> report = std::make_pair(mWidth, mHeight);
						getSignal("WindowResized")->send(report);
					}

					break;

				case ClientMessage:

					if(xev.xclient.data.l[0] == mDeleteMessage)
					{
						getSignal("WindowClosed")->send(xev.xclient.data.l[0]);
					}

					break;
			}
		}
	}
	//-----------------------------------------------------------------------

	void GLXPlatformContext::swapBuffers()
	{
		glXSwapBuffers(mDisplay, mWindow); 
	}
	//-----------------------------------------------------------------------

	long GLXPlatformContext::getWindowHandle()
	{
		return mWindow;
	}
	//-----------------------------------------------------------------------
}
