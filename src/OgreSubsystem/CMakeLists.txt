# Build file for the Ogre Subsystem
include_directories("${OGRE_INCLUDE_DIR}")

set(SOURCE_FILES
	Camera.cpp
	Decal.cpp
	#Gorilla.cpp
	#GUIButton.cpp
	#GUI.cpp
	#GUIElement.cpp
	#GUIEmpty.cpp
	#GUIRectangle.cpp
	#GUIScreen.cpp
	#GUIStaticText.cpp
	#GUIText.cpp
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
	)

set(HEADER_FILES
	Camera.h
	Decal.h
	#Gorilla.h
	#GUIButton.h
	#GUIElement.h
	#GUIEmpty.h
	#GUI.h
	#GUIRectangle.h
	#GUIScreen.h
	#GUIStaticText.h
	#GUIText.h
	Light.h
	ManualObjectData.h
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
	)

add_library(OgreSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(OgreSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (OgreSubsystem ${ORYX_LIB} ${BOOST_LIB} ${OGRE_LIB})


install(TARGETS OgreSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})

