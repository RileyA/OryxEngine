#ifndef ORYX_GLSubsystem_H
#define ORYX_GLSubsystem_H

#include "Oryx.h"
#include "Oryx3DMath.h"
#include "OryxMatrix4.h"
#include "OryxEngineSubsystem.h"
#include "GLdllmain.h"
#include "GLPlatformContext.h"
#include "SceneNode.h"
#include "Camera.h"

namespace Oryx
{
	class ORYX_GL_EXPORT GLSubsystem : public EngineSubsystem
	{
	public:

		GLSubsystem(size_t w, size_t h, bool fullscreen);
		~GLSubsystem();

		void _init();
		void _deinit();
		void _update(float update);
		void _endState();
		String getName() {return "GLSubsystem";}

		long getWindowHandle();
		void updateView();

		void handleResize(const Message& m);

		void setWorldMatrix(const Matrix4& m);
		void setViewMatrix(const Matrix4& m);
		void setProjectionMatrix(const Matrix4& m);

		inline void convertGLMatrix(float* out, const Matrix4& in)
		{
			size_t x = 0;
			for (size_t i = 0; i < 4; i++)
				for (size_t j = 0; j < 4; j++)
					out[x++] = in[j][i];
		}

		const Matrix4& getWorldMatrix() const {return mWorldMatrix;}
		const Matrix4& getViewMatrix() const {return mViewMatrix;}
		const Matrix4& getProjectionMatrix() const {return mProjectionMatrix;}

	private:

		GLPlatformContext* mContext;
		size_t mWidth, mHeight;
		bool mFullscreen;
		Matrix4 mWorldMatrix, mViewMatrix, mProjectionMatrix;
		SceneNode* mRoot;

		Camera* mActiveCamera;

	};
}

#endif

