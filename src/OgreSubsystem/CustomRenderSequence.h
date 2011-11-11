#ifndef CustomRenderSequence_H
#define CustomRenderSequence_H

#include "Oryx.h"

namespace Oryx
{
	/** A custom sequence of rendering iterations, this is mainly for the sake of 
	 * doing stencil stuffs. Sort of hacked in for Portal stuff, I'll tidy up later... */
	class CustomRenderSequence
	{
	public:

		CustomRenderSequence();

		struct CustomRenderIteration
		{
			// stencil settings per render queue
			std::map<int, StencilSetting> mStencilConfigs;

			// whether or not to clear the z buffer
			bool clearDepth;

			//CompareFunction compare;
			//uint32 mask;
			//uint32 ref;
			//StencilOperation failOp;
			//StencilOperation depthFailOp;
			//StencilOperation passOp;

			void addStencilConfig(int renderQueue, CompareFunction com,
				uint32 mask, uint32 ref, StencilOperation fail,
				StencilOperation depthFail, StencilOperation pass)
			{
				mStencilConfigs[renderQueue] = StencilConfig();
				StencilConfig* cfg = mStencilConfigs[renderQueue];
				cfg->compare = com;
				cfg->mask = mask;
				cfg->ref = ref;
				cfg->failOp = fail;
				cfg->depthFailOp = depthFail;
				cfg->passOp = pass;
			}
		};

		// sorta hack-tastic, copied from ogre...
		enum StencilOperation
		{
			SOP_KEEP,
			SOP_ZERO,
			SOP_REPLACE,
			SOP_INCREMENT,
			SOP_DECREMENT,
			SOP_INCREMENT_WRAP,
			SOP_DECREMENT_WRAP,
			SOP_INVERT
		};

		// sorta hack-tastic, copied from ogre... (this is the sort of thing that may
		// be best added as a general thing somewhere, but not right now...)
		enum CompareFunction
		{
			CMPF_ALWAYS_FAIL,
			CMPF_ALWAYS_PASS,
			CMPF_LESS,
			CMPF_LESS_EQUAL,
			CMPF_EQUAL,
			CMPF_NOT_EQUAL,
			CMPF_GREATER_EQUAL,
			CMPF_GREATER
		};

		CustomRenderIteration* addIteration();
		CustomRenderIteration* getRenderingIteration(size_t index);
		std::list<CustomRenderIteration*>::iterator getIterator();

	private:

		// A configuration for stencil stuff (this'll change in an individual iteration from
		// render queue to queue, so it gets its own struct).
		struct StencilConfig
		{
			CompareFunction compare;
			uint32 mask;
			uint32 ref;
			StencilOperation failOp;
			StencilOperation depthFailOp;
			StencilOperation passOp;
		};

		std::list<CustomRenderPass*> mIteration;

	};
};

#endif
