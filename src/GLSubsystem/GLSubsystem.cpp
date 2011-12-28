#include "GLSubsystem.h"
#include "GLXPlatformContext.h"

namespace Oryx
{
	GLSubsystem::GLSubsystem(size_t w, size_t h, bool fullscreen)
	{
		mContext = new GLXPlatformContext(); mWidth = w;
		mHeight = h;
		mFullscreen = fullscreen;
		createSlot("Resize", this, &GLSubsystem::handleResize);
	}
	//-----------------------------------------------------------------------

	GLSubsystem::~GLSubsystem()
	{
		delete mContext;
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::_init()
	{
		mContext->init(mWidth, mHeight, mFullscreen);
		mContext->getSignal("WindowResized")->addListener(getSlot("Resize"));
		updateView();

		mWorldMatrix = Matrix4::IDENTITY;
		mViewMatrix = Matrix4::IDENTITY;
		mProjectionMatrix = Matrix4::IDENTITY;

		glShadeModel(GL_SMOOTH);
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClearDepth(1.f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		mActiveCamera = new Camera();

		mActiveCamera->setPosition(Vector3(0,0,0));
		//mActiveCamera->yaw(0.f);

		mRoot = new SceneNode();
		mRoot->setPosition(Vector3(-1.5f,0,-10));
		//mRoot->roll(5.f);

		SceneNode* node2 = new SceneNode();
		node2->setPosition(Vector3(3.f, 0.f, 0.f));
		node2->roll(90.f);
		mRoot->addChild(node2);
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::_deinit()
	{
		delete mRoot;
		mRoot = 0;
		mContext->deinit();
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::_update(float delta)
	{
		mContext->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// setup view
		setViewMatrix(mActiveCamera->getTransform().inverse());	

		// render everything
		mRoot->_render(this);

		mContext->swapBuffers();
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::_endState()
	{
		delete mRoot;
		mRoot = new SceneNode();
	}
	//-----------------------------------------------------------------------

	long GLSubsystem::getWindowHandle()
	{
		return mContext->getWindowHandle();
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::updateView()
	{
		glViewport(0, 0, mWidth, mHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(GLfloat)mWidth/(GLfloat)mHeight,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::handleResize(const Message& m)
	{
		if(const std::pair<size_t, size_t>* dims = unpackMsg<std::pair<size_t, size_t> >(m))
		{
			mWidth = dims->first;
			mHeight = dims->second;
			updateView();
		}
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::setViewMatrix(const Matrix4& m)
	{
		GLfloat mat[16];
		mViewMatrix = m;
		convertGLMatrix(mat, mViewMatrix * mWorldMatrix );
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(mat);
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::setWorldMatrix(const Matrix4& m)
	{
		GLfloat mat[16];
		mWorldMatrix = m;
		convertGLMatrix(mat, mViewMatrix * mWorldMatrix );
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(mat);
	}
	//-----------------------------------------------------------------------

	void GLSubsystem::setProjectionMatrix(const Matrix4& m)
	{
		GLfloat mat[16];
		mProjectionMatrix = m;
		convertGLMatrix(mat, mProjectionMatrix);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(mat);
		glMatrixMode(GL_MODELVIEW);
	}
	//-----------------------------------------------------------------------
}

