#include "CustomRenderSequence.h"

namespace Oryx
{
	CustomRenderIteration* CustomRenderSequence::addIteration()
	{
		mIterations.push_back();
		return mIteration.back();
	}
	//---------------------------------------------------------------------------

	CustomRenderIteration* CustomRenderSequence::getRenderingIteration(size_t index)
	{
		return *(mIterations.begin() + index);
	}
	//---------------------------------------------------------------------------

	std::list<CustomRenderIteration*>::iterator CustomRenderSequence::getIterator()
	{
		return mIterations.begin();
	}
	//---------------------------------------------------------------------------
}
