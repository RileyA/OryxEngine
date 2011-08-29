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

#include "Oryx.h"

namespace Oryx
{
	/** A reference-counted shared pointer implementation. */
	template <typename T> class SharedPtr
	{
	public:

		SharedPtr()
			:ptr(0),refCount(0)
		{}

		explicit SharedPtr(T* p)
			:ptr(0),refCount(0)
		{
			bind(p);
		}

		~SharedPtr()
		{
			release();
		}

		SharedPtr(const SharedPtr<T>& rhs)
			:ptr(0),refCount(0)
		{
			ptr = rhs.getPointer();
			refCount = rhs.getRefCountPtr();
			if(refCount)
				++(*refCount);
		}

		SharedPtr& operator=(const SharedPtr<T>& rhs)
		{
			SharedPtr<T> temp(rhs);
			swap(temp);
			return *this;
		}

		void bind(T* p)
		{
			ptr = p;
			refCount = new unsigned int(1);
		}

		void release()
		{
			--(*refCount);
			if((*refCount) == 0)
			{
				delete ptr;
				delete refCount;
				std::cout<<"deleted!\n";
			}
		}

		inline T* getPointer() const
		{
			return ptr;
		}

		inline unsigned int* getRefCountPtr() const
		{
			return refCount;
		}

		inline unsigned int getRefCount() const
		{
			return *refCount;
		}

		inline T& operator*() const {return *ptr;}
		inline T& operator->() const {return ptr;}

	protected:

		void swap(SharedPtr<T>& other)
		{
			std::swap(ptr, other.ptr);
			std::swap(refCount, other.refCount);
		}

		unsigned int* refCount;
		T* ptr;
		
	};
}
