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

#ifndef ORYX_COLOUR_H
#define ORYX_COLOUR_H

#include "Oryx.h"

namespace Oryx
{
	/** A color value (in British spelling, since I was feeling different...
	 *		this will be corected eventually). Partially based on Ogre3D's
	 *		ColourValue (Ogre is under the MIT license) */
	class ORYX_EXPORT Colour
	{
	public:

		// Some preset constant values
		static const Colour ZERO;
		static const Colour Red;
		static const Colour Green;
		static const Colour Blue;
		static const Colour Black;
		static const Colour White;

		Real r;
		Real g;
		Real b;
		Real a;

		explicit Colour()
			: r(1.f), g(1.f), b(1.f), a(1.f)
		{}

		explicit Colour(float red, float green, float blue, float alpha = 1.f)
			: r(red), g(green), b(blue), a(alpha)
		{}

		explicit Colour(uint32_t color)
			: r((color >> 24) / 255.f), g(((color >> 16) & 0xff) / 255.f), b(((color >> 8) & 0xff) / 255.f), a((color & 0xff) / 255.f)
		{}

		bool operator==(const Colour& col) const;
		bool operator!=(const Colour& col) const;

		/** Clamps this color to [0,1] range in all channels */
		void saturate()
		{
			if(r>1)
				r=1.f;
			else if(r<0)
				r=0.f;

			if(g>1)
				g=1.f;
			else if(g<0)
				g=0.f;

			if(b>1)
				b=1.f;
			else if(b<0)
				b=0.f;

			if(a>1)
				a=1.f;
			else if(a<0)
				a=0.f;
		}

		/** Returns a saturated copy of this Colour
		 *		@return A saturated copy*/
		Colour saturateCopy() const
		{
			Colour copy = *this;
			copy.saturate();

			return copy;
		}

		Colour operator + (const Colour& col) const
		{
			Colour out;

			out.r = r + col.r;
			out.g = g + col.g;
			out.b = b + col.b;
			out.a = a + col.a;

			return out;
		}

		Colour& operator += (const Colour& col)
		{
			r += col.r;
			g += col.g;
			b += col.b;
			a += col.a;

			return *this;
		}

		Colour operator - (const Colour& col) const
		{
			Colour out;

			out.r = r - col.r;
			out.g = g - col.g;
			out.b = b - col.b;
			out.a = a - col.a;

			return out;
		}

		Colour& operator -= (const Colour& col)
		{
			r -= col.r;
			g -= col.g;
			b -= col.b;
			a -= col.a;

			return *this;
		}

		Colour operator * (const float scalar) const
		{
			Colour out;

			out.r = r * scalar;
			out.g = g * scalar;
			out.b = b * scalar;
			out.a = a * scalar;

			return out;
		}

		Colour& operator *= (const float scalar)
		{
			r *= scalar;
			g *= scalar;
			b *= scalar;
			a *= scalar;

			return *this;
		}

		Colour operator / (const float scalar) const
		{
			Colour out;

			out.r = r / scalar;
			out.g = g / scalar;
			out.b = b / scalar;
			out.a = a / scalar;

			return out;
		}

		Colour& operator /= (const float scalar)
		{
			r /= scalar;
			g /= scalar;
			b /= scalar;
			a /= scalar;

			return *this;
		}

		/** Returns 8-bit 0-255 value of the R channel */
		byte getR8()
		{
			return static_cast<byte>(floor(r*255.f));
		}

		/** Returns 8-bit 0-255 value of the G channel */
		byte getG8()
		{
			return static_cast<byte>(floor(g*255.f));
		}

		/** Returns 8-bit 0-255 value of the B channel */
		byte getB8()
		{
			return static_cast<byte>(floor(b*255.f));
		}

		/** Returns 8-bit 0-255 value of the A channel */
		byte getA8()
		{
			return static_cast<byte>(floor(a*255.f));
		}
	};
}

#endif
