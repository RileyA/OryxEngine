# Build file for the OIS Subsystem
include_directories("${SDL_INCLUDE_DIR}")

set(SOURCE_FILES
	SDLdllmain.cpp
	SDLSubsystem.cpp
	)

set(HEADER_FILES
	SDLdllmain.h
	SDLSubsystem.h
	)

add_library(SDLSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(SDLSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (SDLSubsystem ${ORYX_LIB} ${SDL_LIB})

install(TARGETS SDLSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
