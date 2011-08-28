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

# whether or not to do ogg support
option(AL_OGG_SUPPORT "Enable .ogg playback." TRUE)

# AL itself
set(AL_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for AL includes.")
set(AL_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for AL libs.")

# ALUT
set(ALUT_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for ALUT includes.")
set(ALUT_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for ALUT libs.")

# Ogg and vorbis
if (AL_OGG_SUPPORT)
	set(OGG_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for Ogg includes.")
	set(OGG_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for Ogg libs.")
	set(VORBIS_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for Vorbis includes.")
	set(VORBIS_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for Vorbis libs.")
endif (AL_OGG_SUPPORT)

# locate everything
set(AL_LIB ${AL_LIB_DIR}/${LIB_PREFIX}openal${LIB_POSTFIX})
set(ALUT_LIB ${ALUT_LIB_DIR}/${LIB_PREFIX}alut${LIB_POSTFIX})

if (AL_OGG_SUPPORT)
	set(OGG_LIB ${OGG_LIB_DIR}/libogg${LIB_POSTFIX})
	set(VORBIS_LIB ${VORBIS_LIB_DIR}/libvorbis${LIB_POSTFIX})
	if (UNIX)
		set(VORBISENC_LIB ${VORBIS_LIB_DIR}/libvorbisenc${LIB_POSTFIX})
	else (UNIX)
		set(VORBISENC_LIB ${VORBIS_LIB_DIR}/libvorbisenc${LIB_POSTFIX})
	endif (UNIX)
	set(VORBISFILE_LIB ${VORBIS_LIB_DIR}/libvorbisfile${LIB_POSTFIX})
endif (AL_OGG_SUPPORT)

# Build file for the AL Subsystem
include_directories("${AL_INCLUDE_DIR}")
include_directories("${ALUT_INCLUDE_DIR}")

if (AL_OGG_SUPPORT)
	include_directories("${OGG_INCLUDE_DIR}")
	include_directories("${VORBIS_INCLUDE_DIR}")
endif (AL_OGG_SUPPORT)

set(SOURCE_FILES
	ActiveSound.cpp
	ALdllmain.cpp
	ALSubsystem.cpp
	BufferedSound.cpp
	OggStream.cpp
	SoundPtr.cpp
	)

set(HEADER_FILES
	ActiveSound.h
	ALdllmain.h
	ALSubsystem.h
	BufferedSound.h
	OggStream.h
	SoundPtr.h
	)

add_library(ALSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(ALSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (ALSubsystem ${ORYX_LIB} ${AL_LIB} 
	${ALUT_LIB} ${OGG_LIB} ${VORBIS_LIB} ${VORBISFILE_LIB} ${VORBISENC_LIB})

install(TARGETS ALSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
