# Build file for the Ogre Subsystem
include_directories("${OGRE_INCLUDE_DIR}")
include_directories("${BOOST_INCLUDE_DIR}")

set(SOURCE_FILES
	Camera.cpp
	Decal.cpp
	Light.cpp
	Material.cpp
	Mesh.cpp
	OgreConversions.cpp
	Ogredllmain.cpp
	OgreSubsystem.cpp
	ParticleSystem.cpp
	SceneNode.cpp
	Spline.cpp
	CustomMesh.cpp
	ScreenMesh.cpp
	CustomRenderSequence.cpp
	CustomRenderSequenceListener.cpp
	)

set(HEADER_FILES
	Camera.h
	Decal.h
	Light.h
	Material.h
	Mesh.h
	OgreConversions.h
	Ogredllmain.h
	OgreSubsystem.h
	ParticleSystem.h
	SceneNode.h
	Spline.h
	CustomMesh.h
	ScreenMesh.h
	CustomRenderSequence.h
	CustomRenderSequenceListener.h
	)

add_library(OgreSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(OgreSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (OgreSubsystem ${ORYX_LIB} ${BOOST_THREAD_LIB} ${BOOST_TIME_LIB} ${OGRE_LIB})


install(TARGETS OgreSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})

