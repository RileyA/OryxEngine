#include "CustomRenderSequence.h"

namespace Oryx
{
	CustomRenderSequence::CustomRenderSequence()
	{

	}
	//---------------------------------------------------------------------------

	CustomRenderIteration& CustomRenderSequence::addIteration()
	{
		mIterations.push_back(CustomRenderIteration());
		return mIterations.back();
	}
	//---------------------------------------------------------------------------

	CustomRenderIteration& CustomRenderSequence::getRenderingIteration(size_t index)
	{
		std::list<CustomRenderIteration>::iterator it;
		for(index; index > 0; --index) ++it;
		return *it;
	}
	//---------------------------------------------------------------------------

	std::list<CustomRenderIteration>::iterator CustomRenderSequence::getIterator()
	{
		return mIterations.begin();
	}
	//---------------------------------------------------------------------------

	std::list<CustomRenderIteration>::iterator CustomRenderSequence::getEnd()
	{
		return mIterations.end();
	}
	//---------------------------------------------------------------------------
}
