//---------------------------------------------------------------------------
//(C) Copyright Riley Adams 2011

//This file is part of Oryx Engine.

// Oryx Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the license, or
// (at your option) any later version.

// Oryx Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTEE; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have recieved a copy of the GNU General Public License
// along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
//---------------------------------------------------------------------------

#ifndef PHYSICS_COMPOUND_SHAPE_H
#define PHYSICS_COMPOUND_SHAPE_H

#include "PhysicsShape.h"
#include "Bulletdllmain.h"

class btCompoundShape;

namespace Oryx
{
	class ORYX_BULLET_EXPORT PhysicsCompoundShape : public PhysicsShape
	{
	public:

		PhysicsCompoundShape();
		virtual ~PhysicsCompoundShape();

		PhysicsShape* getShape(size_t index);

		void addShape(PhysicsShape* shape, Vector3 pos=Vector3::ZERO, 
			Quaternion orientation = Quaternion::IDENTITY);
		void removeShape(PhysicsShape* shape);
		void removeShapeByIndex(size_t shape);
		void removeAllShapes();

		btCompoundShape* getCompound();

		PhysicsShapeType getType(){return PST_COMPOUND;}

	protected:

		std::vector<PhysicsShape*> mShapes;
	};
}

#endif

