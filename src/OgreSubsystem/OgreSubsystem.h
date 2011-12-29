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

#ifndef ORYX_OGRESUBSYSTEM_H
#define ORYX_OGRESUBSYSTEM_H

#include "Oryx.h"
#include "OgreSubsystem/Ogredllmain.h"
#include "OryxEngineSubsystem.h"
#include "OryxColour.h"
#include "OryxTimeManager.h"

#include "SceneNode.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Material.h"
#include "ScreenMesh.h"
#include "CustomRenderSequence.h"

namespace Ogre
{
	class Root;
	class RenderWindow;
	class Viewport;
	class Camera;
	class SceneManager;
}

namespace Oryx
{
	class CustomRenderSequenceListener;
	
	/** 3d graphics subsystem that wraps the Ogre3d engine */
	class ORYX_OGRE_EXPORT OgreSubsystem : public EngineSubsystem
	{
	public:

		OgreSubsystem(unsigned int resX=800,unsigned int resY=600,bool fullscreen=false,
			std::map<String,String> params=std::map<String,String>());
		virtual ~OgreSubsystem();

		/** INTERNAL: inits the system */
		virtual void _init();
		/** INTERNAL: deinits the system */
		virtual void _deinit();
		/** INTERNAL: updates the system */
		virtual void _update(Real delta);
		/** INTERNAL: called at the end of a state */
		virtual void _endState();
		/** Gets the name of the system 
			@return The name ("OgreSubsystem") */
		virtual String getName();

		/** render a single frame */
		void renderFrame();
		/** restart the render window and apply any pending changes */
		void restart();
		/** Sets the background color of the viewport
			@param bc The desired color*/
		void setBackgroundColor(Colour bc);
		/** Gets the background color of the vieport
			@return The color */
		Colour getBackgroundColor();

		/** Returns a pointer to the GUI system 
			@return A pointer to the GUI system */
		//GUI* getGUI();
		/** Returns a pointer to the main window's viewport
			@return The main window's viewport*/
		Ogre::Viewport* getMainViewport();

		/** Creates a SceneNode
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		SceneNode* createSceneNode(String name="AUTO_NAME_ME");
		/** Creates a Mesh
			@param mesh The mesh file to use
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		Mesh* createMesh(String mesh,String name="AUTO_NAME_ME");
		/** Creates a Mesh based on raw vertices
			@param mesh The mesh file to use
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		Mesh* createMesh(const MeshData& data,String name="AUTO_NAME_ME");/** Creates a Camera
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		Camera* createCamera(String name="AUTO_NAME_ME");
		/** Creates a Light
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		Light* createLight(String name="AUTO_NAME_ME");
		/** Creates a ParticleSystem
		 *	@param script the script to use
			@param name The name of the node "AUTO_NAME_ME" (the default) will make
				the subsystem assign a unique name automatically */
		ParticleSystem* createParticleSystem(String script,String name="AUTO_NAME_ME");
		
		/** Destroys a SceneNode
		 *	@param node The SceneNode (or any derivative object) to destroy */
		void destroySceneNode(SceneNode* node);

		/** Gets a pointer to the root scene node */
		SceneNode* getRootSceneNode();
		/** Gets a pointer to the default camera */
		Camera* getDefaultCamera();
		/** Gets a pointer to the active camera */
		Camera* getActiveCamera();
		/** Sets the active camera */
		void setActiveCamera(Camera* cam);

		/** Sets fog parameters */
		void setLinearFog(float start, float end, Colour color);

		/** Takes a screenshot */
		void takeScreenshot(String name = "OryxShot", String target="NULL");

		/** Returns the width of the rendering window
			@return Width of the current rendering window */
		unsigned int getScreenWidth();
		/** Returns the height of the rendering window
			@return Height of the current rendering window */
		unsigned int getScreenHeight();
		/** Returns whether or not the system is running fullscreen
			@return If the system is fullscreen */
		bool isFullscreen();
		/** Returns the current value of a rendering parameter
			@param param The parameter to get
			@return The value of the selected parameter */
		String getGfxParameter(String param);

		/** Set the render window's width
			@param resX The width 
			@remarks This won't take effect until the system is restarted */
		void setScreenWidth(unsigned int resX);
		/** Set the render window's height
			@param resY The height
			@remarks This won't take effect until the system is restarted */
		void setScreenHeight(unsigned int resY);
		/** Set whether or not the window should be fullscreen
			@param fs Whether or not to be fullscreen
			@remarks This won't take effect until the system is restarted */
		void setFullscreen(bool fs);
		/** Sets a rendersystem parameter
			@param param The parameter to set
			@param value The value to set the parameter to
			@remarks Depending on the param, this may not take effect until
					the system is restarted */
		void setGfxParameter(String param,String value);

		int getBatchCount();

		void enableCustomRenderSequence(CustomRenderSequence* seq);
		void disableCustomRenderSequence();

		bool isCustomRenderSequenceEnabled() {return mCustomRenderSequenceEnabled;}

		//void enablePortalHack(int depth);
		//bool mPortalHack;
		//int mPortalDepth;

		void add3dOverlay(String overlay, SceneNode* node);

		size_t getWindowHandle();

		ScreenMesh* createScreenMesh(String material);

		void setOverlayEnabled(String name, bool enabled);
		void setOverlayText(String element, String text);
		void setOverlayTextColour(String element, Colour color);
		void setOverlayTextColour(String element, Colour color, Colour color2);
		void loadFont(String name);

	protected:

		bool mInitialized;

		Ogre::Root* mRoot;
		Ogre::SceneManager* mSceneManager;
		Ogre::RenderWindow* mWindow;
		Ogre::Viewport* mViewport;

		Camera* mDefaultCamera;
		Camera* mActiveCamera;

		SceneNode* mRootSceneNode;
		std::vector<SceneNode*> mSceneNodes;

		// TODO clean this up...
		std::vector<ScreenMesh*> mScreenMeshes;

		unsigned int mResolutionX;
		unsigned int mResolutionY;
		bool mFullscreen;
		std::map<String,String> mCurrentParams;// current params of the running rendersystem
		std::map<String,String> mParams;// params to be set during the next restart of the system
		bool mNeedsRestart;// does it have options to set during the next reset?

		int mAutoNameIndex;

		CustomRenderSequenceListener* mSequenceListener;
		bool mCustomRenderSequenceEnabled;
		CustomRenderSequence* mRenderSequence;

	};
}

#endif
