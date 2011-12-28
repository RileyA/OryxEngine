#ifndef CustomRenderSequence_H
#define CustomRenderSequence_H

#include "Oryx.h"

namespace Oryx
{
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

	// A configuration for stencil stuff (this'll change in an individual iteration from
	// render queue to queue, so it gets its own struct).
	struct StencilConfig
	{
		bool stencil;
		CompareFunction compare;
		uint32_t mask;
		uint32_t ref;
		StencilOperation failOp;
		StencilOperation depthFailOp;
		StencilOperation passOp;
	};

	struct CustomRenderIteration
	{
		CustomRenderIteration()
		{
			clearDepth = false;
		}

		void addStencilConfig(int renderQueue, CompareFunction com,
			uint32_t mask, uint32_t ref, StencilOperation fail,
			StencilOperation depthFail, StencilOperation pass)
		{
			stencilConfigs[renderQueue] = StencilConfig();
			StencilConfig& cfg = stencilConfigs[renderQueue];
			cfg.stencil = true;
			cfg.compare = com;
			cfg.mask = mask;
			cfg.ref = ref;
			cfg.failOp = fail;
			cfg.depthFailOp = depthFail;
			cfg.passOp = pass;
		}

		// disable stencil check
		void addStencilConfig(int renderQueue)
		{
			stencilConfigs[renderQueue] = StencilConfig();
			StencilConfig& cfg = stencilConfigs[renderQueue];
			cfg.stencil = false;
		}

		// stencil settings per render queue
		std::map<int, StencilConfig> stencilConfigs;

		// whether or not to clear the z buffer
		bool clearDepth;
	};

	/** A custom sequence of rendering iterations, this is mainly for the sake of 
	 * doing tricky stencil stuffs. Sort of hacked in for Portal-y stuff, I'll tidy up later... */
	class CustomRenderSequence
	{
	public:


		CustomRenderSequence();
		CustomRenderIteration& addIteration();
		CustomRenderIteration& getRenderingIteration(size_t index);
		std::list<CustomRenderIteration>::iterator getIterator();
		std::list<CustomRenderIteration>::iterator getEnd();

	//private:

		std::list<CustomRenderIteration> mIterations;

	};
};

#endif
