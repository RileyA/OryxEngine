# Build file for the GUI Subsystem
include_directories("${OYSTER_INCLUDE_DIR}")

set(SOURCE_FILES
	GUIBatch.cpp
	GUIButton.cpp
	GUICaption.cpp
	GUIdllmain.cpp
	GUIElement.cpp
	GUIEmpty.cpp
	GUIPanel.cpp
	GUISubsystem.cpp
	)

set(HEADER_FILES
	GUIBatch.h
	GUIButton.h
	GUICaption.h
	GUIdllmain.h
	GUIElement.h
	GUIEmpty.h
	GUIPanel.h
	GUISubsystem.h
	)

add_library(GUISubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(GUISubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (GUISubsystem ${ORYX_LIB})

install(TARGETS GUISubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
