cmake_minimum_required (VERSION 2.6)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Some lib stuff, probably unneeded, but I don't know cmake too well yet...
if (WIN32)
	set(LIB_PREFIX )
	set(LIB_POSTFIX .lib)
else ()
	set(LIB_PREFIX lib)
	set(LIB_POSTFIX .so)
endif ()

# Some options:
option(BUILD_OIS_SUBSYSTEM "Build OIS Subsystem." TRUE)
option(BUILD_OGRE_SUBSYSTEM "Build OGRE Subsystem." TRUE)
option(BUILD_SDL_SUBSYSTEM "Build SDL Subsystem." TRUE)

set(INSTALL_RUNTIMES_TO "/usr/bin" CACHE STRING "Where install executables.")
set(INSTALL_LIBS_TO "/usr/lib" CACHE STRING "Where to install libs.")

# ogre
set(OGRE_INCLUDE_DIR "/usr/include/OGRE" CACHE STRING "Where to look for ogre includes.")
set(OGRE_LIB_DIR "/usr/lib" CACHE STRING "Where to look for ogre libs.")

# SDL
set(SDL_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for sdl includes.")
set(SDL_LIB_DIR "/usr/lib" CACHE STRING "Where to look for sdl libs.")

# OIS
set(OIS_INCLUDE_DIR "/usr/include/OIS" CACHE STRING "Where to look for ois includes.")
set(OIS_LIB_DIR "/usr/lib" CACHE STRING "Where to look for ois libs.")

# boost
#set(BOOST_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for boost includes.")
#set(BOOST_LIB_DIR "/usr/lib" CACHE STRING "Where to look for boost libs.")

# common includes
include_directories("src")

# lib stuff, ugly, but gets the job done for now...
set(ORYX_LIB ${PROJECT_BINARY_DIR}/lib/${LIB_PREFIX}OryxEngine${LIB_POSTFIX})
# freenect and boost
set(OGRE_LIB ${OGRE_LIB_DIR}/${LIB_PREFIX}OgreMain${LIB_POSTFIX})
set(SDL_LIB ${SDL_LIB_DIR}/${LIB_PREFIX}SDL${LIB_POSTFIX})
set(OIS_LIB ${SDL_LIB_DIR}/${LIB_PREFIX}OIS${LIB_POSTFIX})
#set(BOOST_THREAD_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_thread-mt${LIB_POSTFIX})

# build the plain engine
add_subdirectory(src)

# subsystems
add_subdirectory(src/SDLSubsystem)
add_subdirectory(src/OISSubsystem)
add_subdirectory(src/OgreSubsystem)

