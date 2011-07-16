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
option(BUILD_AL_SUBSYSTEM "Build AL Subsystem." TRUE)
option(BUILD_BULLET_SUBSYSTEM "Build bullet Subsystem." TRUE)
option(BUILD_LUA_SUBSYSTEM "Build lua Subsystem." TRUE)
option(BUILD_OGRE_SUBSYSTEM "Build OGRE Subsystem." TRUE)
option(BUILD_OIS_SUBSYSTEM "Build OIS Subsystem." TRUE)
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

# Bullet
set(BT_INCLUDE_DIR "/usr/include/bullet" CACHE STRING "Where to look for bullet includes.")
set(BT_LIB_DIR "/usr/lib" CACHE STRING "Where to look for bullet libs.")

# lua/luabind
set(LUA_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for lua includes.")
set(LUA_LIB_DIR "/usr/lib" CACHE STRING "Where to look for lua libs.")
set(LUABIND_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for luabind includes.")
set(LUABIND_LIB_DIR "/usr/lib" CACHE STRING "Where to look for luabind libs.")

# Chaiscript

# AL
set(AL_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for AL includes.")
set(AL_LIB_DIR "/usr/lib" CACHE STRING "Where to look for AL libs.")
set(ALUT_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for ALUT includes.")
set(ALUT_LIB_DIR "/usr/lib" CACHE STRING "Where to look for ALUT libs.")
set(OGG_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for Ogg includes.")
set(OGG_LIB_DIR "/usr/lib" CACHE STRING "Where to look for Ogg libs.")
set(VORBIS_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for Vorbis includes.")
set(VORBIS_LIB_DIR "/usr/lib" CACHE STRING "Where to look for Vorbis libs.")

# ENet

# boost
set(BOOST_INCLUDE_DIR "/usr/include" CACHE STRING "Where to look for boost includes.")
set(BOOST_LIB_DIR "/usr/lib" CACHE STRING "Where to look for boost libs.")

# common includes
include_directories("src")

# lib stuff, ugly, but gets the job done for now...
set(ORYX_LIB ${PROJECT_BINARY_DIR}/lib/${LIB_PREFIX}OryxEngine${LIB_POSTFIX})
# Ogre
set(OGRE_LIB ${OGRE_LIB_DIR}/${LIB_PREFIX}OgreMain${LIB_POSTFIX})
# SDL
set(SDL_LIB ${SDL_LIB_DIR}/${LIB_PREFIX}SDL${LIB_POSTFIX})
# OIS
set(OIS_LIB ${SDL_LIB_DIR}/${LIB_PREFIX}OIS${LIB_POSTFIX})
# bullet
set(BT_C_LIB ${BT_LIB_DIR}/${LIB_PREFIX}BulletCollision${LIB_POSTFIX})
set(BT_D_LIB ${BT_LIB_DIR}/${LIB_PREFIX}BulletDynamics${LIB_POSTFIX})
set(BT_MATH_LIB ${BT_LIB_DIR}/${LIB_PREFIX}LinearMath${LIB_POSTFIX})
# boost
#set(BOOST_THREAD_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_thread-mt${LIB_POSTFIX})
set(BOOST_THREAD_LIB ${BOOST_LIB_DIR}/${LIB_PREFIX}boost_thread${LIB_POSTFIX})
# OpenAl Stuff
set(AL_LIB ${AL_LIB_DIR}/${LIB_PREFIX}openal${LIB_POSTFIX})
set(ALUT_LIB ${ALUT_LIB_DIR}/${LIB_PREFIX}alut${LIB_POSTFIX})
set(OGG_LIB ${OGG_LIB_DIR}/${LIB_PREFIX}ogg${LIB_POSTFIX})
set(VORBIS_LIB ${VORBIS_LIB_DIR}/${LIB_PREFIX}vorbis${LIB_POSTFIX})
set(VORBISENC_LIB ${VORBIS_LIB_DIR}/${LIB_PREFIX}vorbisenc${LIB_POSTFIX})
set(VORBISFILE_LIB ${VORBIS_LIB_DIR}/${LIB_PREFIX}vorbisfile${LIB_POSTFIX})
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
if (BUILD_AL_SUBSYSTEM)
	add_subdirectory(src/ALSubsystem)
endif ()
if (BUILD_LUA_SUBSYSTEM)
	add_subdirectory(src/LuaSubsystem)
endif ()

