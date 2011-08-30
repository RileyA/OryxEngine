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

#ifndef ORYXLOGGER_H
#define ORYXLOGGER_H

#include "Oryx.h"

namespace Oryx
{
	/** Very simple singleton class for logging game events */
	class ORYX_EXPORT Logger : public EventHandler
	{
	public:

		/** Gets a pointer to the Logger */
		static Logger* getPtr();

		/** Writes a message to the console and log file. 
		 *		@param message The message to write (no need for a newline) */
		void logMessage(String message, bool newline = true, bool timestamp = true);

		/** Tells the Logger to stop outputting all messages */
		void suppressOutput();

		/** Tells the Logger to stop outputting to the Oryx.log file */
		void suppressFileOutput();

	private:

		Logger();
		~Logger();
		Logger(Logger const&);
		Logger& operator=(Logger const&);

		std::ofstream mLogFile;
		bool mActive;
	};
}

#endif
