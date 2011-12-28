#ifndef ORYX_CustomRenderSequenceListener_H
#define ORYX_CustomRenderSequenceListener_H

#include "Oryx.h"
#include "Ogre.h"
#include "CustomRenderSequence.h"

namespace Oryx
{
	class CustomRenderSequenceListener : public Ogre::RenderQueueListener
	{
	public:
		
		const static unsigned MASK_FULL;

		CustomRenderSequenceListener() :iteration(0) {}

		virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation,
			bool& skipThisInvocation) ;

		virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, 
			bool& repeatThisInvocation) {}

		CustomRenderIteration* iteration;
	};
}

#endif
