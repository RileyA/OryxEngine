# Build file for the Lua Subsystem
include_directories("${LUA_INCLUDE_DIR}")
include_directories("${LUABIND_INCLUDE_DIR}")

set(SOURCE_FILES
	Luadllmain.cpp
	LuaSubsystem.cpp
	)

set(HEADER_FILES
	Luadllmain.h
	LuaSubsystem.h
	LuaWrapper.h
	)

add_library(LuaSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(LuaSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (LuaSubsystem ${ORYX_LIB} ${LUA_LIB} 
	${LUABIND_LIB})

install(TARGETS LuaSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
