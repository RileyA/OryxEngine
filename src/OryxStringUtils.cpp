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

#include "OryxStringUtils.h"

namespace Oryx
{
	String StringUtils::toString(long long val)
	{
		std::stringstream stream;
        stream.precision(6);
        stream.width(0);
        stream.fill(' ');
        stream<<val;
        return stream.str();
	}
	//-----------------------------------------------------------------------

	String StringUtils::toString(int val)
	{
		std::stringstream stream;
        stream.precision(6);
        stream.width(0);
        stream.fill(' ');
        stream<<val;
        return stream.str();
	}
	//-----------------------------------------------------------------------

	String StringUtils::toString(unsigned int val)
	{
		std::stringstream stream;
        stream.precision(6);
        stream.width(0);
        stream.fill(' ');
        stream<<val;
        return stream.str();
	}
	//-----------------------------------------------------------------------

	String StringUtils::toString(Real val)
	{
		std::stringstream stream;
        stream.precision(6);
        stream.width(0);
        stream.fill(' ');
        stream<<val;
        return stream.str();
	}
	//-----------------------------------------------------------------------

	String StringUtils::toString(double val)
	{
		std::stringstream stream;
        stream.precision(6);
        stream.width(0);
        stream.fill(' ');
        stream<<val;
        return stream.str();
	}
	//-----------------------------------------------------------------------
}
