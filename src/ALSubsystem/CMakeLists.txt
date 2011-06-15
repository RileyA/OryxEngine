# Build file for the AL Subsystem
include_directories("${AL_INCLUDE_DIR}")
include_directories("${ALUT_INCLUDE_DIR}")
include_directories("${OGG_INCLUDE_DIR}")
include_directories("${VORBIS_INCLUDE_DIR}")

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
