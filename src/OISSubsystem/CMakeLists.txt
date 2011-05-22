# Build file for the OIS Subsystem
include_directories("${OIS_INCLUDE_DIR}")

set(SOURCE_FILES
	OISdllmain.cpp
	OISListener.cpp
	OISSubsystem.cpp
	)

set(HEADER_FILES
	OISdllmain.h
	OISListener.h
	OISSubsystem.h
	)

add_library(OISSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(OISSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (OISSubsystem ${ORYX_LIB} ${OIS_LIB})

install(TARGETS OISSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})

