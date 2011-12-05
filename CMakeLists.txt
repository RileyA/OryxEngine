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

cmake_minimum_required (VERSION 2.6)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

enable_testing()

# Some lib stuff, probably unneeded, but I don't know cmake too well yet...
if (WIN32)
	set(LIB_PREFIX )
	set(LIB_POSTFIX .lib)
else ()
	set(LIB_PREFIX lib)
	set(LIB_POSTFIX .so)
endif ()

# Some options:
option(BUILD_AL_SUBSYSTEM "Build AL Subsystem." TRUE)
option(BUILD_BULLET_SUBSYSTEM "Build bullet Subsystem." TRUE)
option(BUILD_LUA_SUBSYSTEM "Build lua Subsystem." TRUE)
option(BUILD_OGRE_SUBSYSTEM "Build OGRE Subsystem." TRUE)
option(BUILD_OIS_SUBSYSTEM "Build OIS Subsystem." TRUE)
option(BUILD_SDL_SUBSYSTEM "Build SDL Subsystem." TRUE)
option(BUILD_GUI_SUBSYSTEM "Build GUI Subsystem." TRUE)
option(BUILD_UNIT_TESTS "Build Unit Tests." TRUE)

set(INSTALL_RUNTIMES_TO "/usr/bin" CACHE FILEPATH "Where install executables.")
set(INSTALL_LIBS_TO "/usr/lib" CACHE FILEPATH "Where to install libs.")

# ogre
set(OGRE_INCLUDE_DIR "/usr/local/include/OGRE" CACHE FILEPATH "Where to look for ogre includes.")
set(OGRE_LIB_DIR "/usr/local/lib" CACHE FILEPATH "Where to look for ogre libs.")

# SDL
set(SDL_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for sdl includes.")
set(SDL_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for sdl libs.")

# OIS
set(OIS_INCLUDE_DIR "/usr/local/include/OIS" CACHE FILEPATH "Where to look for ois includes.")
set(OIS_LIB_DIR "/usr/local/lib" CACHE FILEPATH "Where to look for ois libs.")

# Bullet
set(BT_INCLUDE_DIR "/usr/include/bullet" CACHE FILEPATH "Where to look for bullet includes.")
set(BT_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for bullet libs.")

# Oyster
set(OYSTER_INCLUDE_DIR "/home/riley/Desktop/Projects/Oyster/include" CACHE FILEPATH "Where to look for oyster includes.")

# lua/luabind
set(LUA_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for lua includes.")
set(LUA_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for lua libs.")
set(LUABIND_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for luabind includes.")
set(LUABIND_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for luabind libs.")

# boost
set(BOOST_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for boost includes.")
set(BOOST_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for boost libs.")

# common includes
include_directories("src")

# lib stuff, ugly, but gets the job done for now...
set(ORYX_LIB ${PROJECT_BINARY_DIR}/lib/${LIB_PREFIX}OryxEngine${LIB_POSTFIX})
# Ogre
set(OGRE_LIB ${OGRE_LIB_DIR}/${LIB_PREFIX}OgreMain${LIB_POSTFIX})
# SDL
set(SDL_LIB ${SDL_LIB_DIR}/${LIB_PREFIX}SDL${LIB_POSTFIX})
# OIS
set(OIS_LIB ${OIS_LIB_DIR}/${LIB_PREFIX}OIS${LIB_POSTFIX})
# bullet
set(BT_C_LIB ${BT_LIB_DIR}/${LIB_PREFIX}BulletCollision${LIB_POSTFIX})
set(BT_D_LIB ${BT_LIB_DIR}/${LIB_PREFIX}BulletDynamics${LIB_POSTFIX})
set(BT_MATH_LIB ${BT_LIB_DIR}/${LIB_PREFIX}LinearMath${LIB_POSTFIX})
# boost
#set(BOOST_THREAD_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_thread-mt${LIB_POSTFIX})
set(BOOST_THREAD_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_thread${LIB_POSTFIX})
set(BOOST_TEST_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_unit_test_framework${LIB_POSTFIX})
# lua stuff
set(LUA_LIB ${LUA_LIB_DIR}/${LIB_PREFIX}lua${LIB_POSTFIX})
set(LUABIND_LIB ${LUABIND_LIB_DIR}/${LIB_PREFIX}luabind${LIB_POSTFIX})

# build the plain engine
add_subdirectory(src)

# subsystems
if (BUILD_SDL_SUBSYSTEM)
	add_subdirectory(src/SDLSubsystem)
endif ()
if (BUILD_OIS_SUBSYSTEM)
	add_subdirectory(src/OISSubsystem)
endif ()
if (BUILD_OGRE_SUBSYSTEM)
	add_subdirectory(src/OgreSubsystem)
endif ()
if (BUILD_BULLET_SUBSYSTEM)
	add_subdirectory(src/BulletSubsystem)
endif ()
if (BUILD_GUI_SUBSYSTEM)
	add_subdirectory(src/GUISubsystem)
endif ()
if (BUILD_AL_SUBSYSTEM)
	add_subdirectory(src/ALSubsystem)
endif ()
if (BUILD_LUA_SUBSYSTEM)
	add_subdirectory(src/LuaSubsystem)
endif ()
if (BUILD_UNIT_TESTS)
	add_subdirectory(src/UnitTests)
endif ()
