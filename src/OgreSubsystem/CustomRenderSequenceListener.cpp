#include "CustomRenderSequenceListener.h"

namespace Oryx
{
	const unsigned CustomRenderSequenceListener::MASK_FULL = 0xFFFFFFFF;

	void CustomRenderSequenceListener::renderQueueStarted(Ogre::uint8 queueGroupId, 
		const Ogre::String& invocation, bool& skipThisInvocation) 
	{ 
		typedef std::map<int, StencilConfig>::iterator StencilConfigIterator;
		Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 

		StencilConfigIterator it = iteration->stencilConfigs.find(queueGroupId);

		if(it != iteration->stencilConfigs.end())
		{
			if(it->second.stencil)
			{
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(
					static_cast<Ogre::CompareFunction>(it->second.compare), 
					static_cast<Ogre::uint32>(it->second.mask),
					static_cast<Ogre::uint32>(it->second.ref),
					static_cast<Ogre::StencilOperation>(it->second.failOp),
					static_cast<Ogre::StencilOperation>(it->second.depthFailOp),
					static_cast<Ogre::StencilOperation>(it->second.passOp),
					false); 
			}
			else
			{
				//rendersys->setStencilCheckEnabled(false); 
			}
		}
		
		/*if(queueGroupId == 75)
		{
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 

			if(pass.first == 0)
			{
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
					1, MASK_FULL, 
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
			}
			else if(pass.first == 1)
			{
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_EQUAL,
					pass.second + 1, MASK_FULL, 
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_INCREMENT,false);       
			}
			//else
			//{
			//	rendersys->setStencilCheckEnabled(false); 
			//}
		}
		else if(queueGroupId == 76)
		{
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 

			if(pass.first == 0)
			{
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
					51, MASK_FULL, 
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
			}
			else if(pass.first == 2)
			{
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_EQUAL,
					51 + pass.second, MASK_FULL, 
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_INCREMENT,false);       
			}
			//else
			//{
			//	rendersys->setStencilCheckEnabled(false); 
			//}
		}*/
	} 
}

