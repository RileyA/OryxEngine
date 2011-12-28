# --------------------------------------------------------------------------
#(C) Copyright Riley Adams 2011
#
#This file is part of Oryx Engine.
#
# Oryx Engine is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the license, or
# (at your option) any later version.
#
# Oryx Engine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTEE; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have recieved a copy of the GNU General Public License
# along with Oryx Engine. If not, see <http://www.gnu.org/licenses/>
# --------------------------------------------------------------------------

# GL itself
set(GL_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for AL includes.")
set(GL_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for AL libs.")

# GL Utility lib
set(GLU_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for AL includes.")
set(GLU_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for AL libs.")

set(GL_LIB ${AL_LIB_DIR}/${LIB_PREFIX}GL${LIB_POSTFIX})
set(GLU_LIB ${AL_LIB_DIR}/${LIB_PREFIX}GLU${LIB_POSTFIX})

include_directories("${GL_INCLUDE_DIR}")
include_directories("${GLU_INCLUDE_DIR}")

if (WIN32)
	# TODO
else () # assume everything else uses X11 for now...
	# X11
	set(X11_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for AL includes.")
	set(X11_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for AL libs.")
	set(X11_LIB ${AL_LIB_DIR}/${LIB_PREFIX}X11${LIB_POSTFIX})
	include_directories("${X11_INCLUDE_DIR}")
endif ()

set(SOURCE_FILES
	GLdllmain.cpp
	GLSubsystem.cpp
	GLXPlatformContext.cpp
	SceneNode.cpp
	Mesh.cpp
	Camera.cpp
	)

set(HEADER_FILES
	GLdllmain.h
	GLPlatformContext.h
	GLSubsystem.h
	GLXPlatformContext.h
	SceneNode.h
	Mesh.h
	Camera.h
	)

add_library(GLSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(GLSubsystem PROPERTIES LINKER_LANGUAGE CXX)

if (WIN32)
	# TODO
else ()
	target_link_libraries (GLSubsystem ${ORYX_LIB}
		${GL_LIB} ${GLU_LIB} ${X11_LIB})
endif ()

install(TARGETS GLSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
