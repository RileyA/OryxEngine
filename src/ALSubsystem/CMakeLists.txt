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

# AL itself
set(AL_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for AL includes.")
set(AL_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for AL libs.")

# Ogg and vorbis
set(OGG_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for Ogg includes.")
set(OGG_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for Ogg libs.")
set(VORBIS_INCLUDE_DIR "/usr/include" CACHE FILEPATH "Where to look for Vorbis includes.")
set(VORBIS_LIB_DIR "/usr/lib" CACHE FILEPATH "Where to look for Vorbis libs.")

# locate everything
set(AL_LIB ${AL_LIB_DIR}/${LIB_PREFIX}openal${LIB_POSTFIX})
set(ALUT_LIB ${ALUT_LIB_DIR}/${LIB_PREFIX}alut${LIB_POSTFIX})
set(OGG_LIB ${OGG_LIB_DIR}/libogg${LIB_POSTFIX})
set(VORBIS_LIB ${VORBIS_LIB_DIR}/libvorbis${LIB_POSTFIX})
set(VORBISFILE_LIB ${VORBIS_LIB_DIR}/libvorbisfile${LIB_POSTFIX})

include_directories("${AL_INCLUDE_DIR}")
include_directories("${OGG_INCLUDE_DIR}")
include_directories("${VORBIS_INCLUDE_DIR}")

set(SOURCE_FILES
	ALdllmain.cpp
	ALSubsystem.cpp
	Sound.cpp
	BufferedSound.cpp
	StreamedSound.cpp
	WavLoader.cpp
	WavStream.cpp
	OggLoader.cpp
	)

set(HEADER_FILES
	ALdllmain.h
	ALSubsystem.h
	Sound.h
	BufferedSound.h
	StreamedSound.h
	AudioLoader.h
	AudioStream.h
	WavLoader.h
	WavStream.h
	OggLoader.h
	)

add_library(ALSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(ALSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (ALSubsystem ${ORYX_LIB} ${AL_LIB}
	${OGG_LIB} ${VORBIS_LIB} ${VORBISFILE_LIB})

install(TARGETS ALSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
