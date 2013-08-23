//-----------------------------------------------------------------------
// Copyright Riley Adams 2010

// This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Oryx Engine.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#include "Oryx.h"
#include "OryxColor.h"

namespace Oryx
{
	const Color Color::ZERO = Color(0.f,0.f,0.f,0.f);
	const Color Color::Red = Color(1.f,0.f,0.f);
	const Color Color::Green = Color(0.f,1.f,0.f);
	const Color Color::Blue = Color(0.f,0.f,1.f);
	const Color Color::Black = Color(0.f,0.f,0.f);
	const Color Color::White = Color(1.f,1.f,1.f);

	bool Color::operator==(const Color& col) const
	{
		return (r == col.r && g == col.g &&
			b == col.b && a == col.a);
	}
	//-----------------------------------------------------------------------
	

	bool Color::operator!=(const Color& col) const
	{
		return !(*this == col);
	}
	//-----------------------------------------------------------------------
}
