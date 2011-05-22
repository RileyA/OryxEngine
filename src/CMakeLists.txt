set(SOURCE_FILES
	OryxBox.cpp
	OryxBucket.cpp
	OryxColour.cpp
	Oryxdllmain.cpp
	OryxEngine.cpp
	OryxEventHandler.cpp
	OryxGameState.cpp
	OryxIntersect.cpp
	OryxLogger.cpp
	OryxMatrix3.cpp
	OryxMatrix4.cpp
	OryxObject.cpp
	OryxPlane.cpp
	OryxQuaternion.cpp
	OryxRand.cpp
	OryxRay.cpp
	OryxSignal.cpp
	OryxSlot.cpp
	OryxSphere.cpp
	OryxStringUtils.cpp
	OryxTimeManager.cpp
	OryxVector2.cpp
	OryxVector3.cpp
	)

set(HEADER_FILES
	FastDelegate.h
	Oryx3DMath.h
	OryxBox.h
	OryxBucket.h
	OryxColour.h
	OryxEngine.h
	OryxEngineSubsystem.h
	OryxEventHandler.h
	OryxException.h
	OryxGameState.h
	Oryx.h
	OryxIntersect.h
	OryxLogger.h
	OryxMatrix3.h
	OryxMatrix4.h
	OryxMeshData.h
	OryxMessageAny.h
	OryxMessage.h
	OryxObject.h
	OryxPlane.h
	OryxQuaternion.h
	OryxRand.h
	OryxRay.h
	OryxScriptingSubsystem.h
	OryxSignal.h
	OryxSlot.h
	OryxSphere.h
	OryxState.h
	OryxStringUtils.h
	OryxTimeManager.h
	OryxVector2.h
	OryxVector3.h
	VersusPackets.h
	)

add_library(OryxEngine SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(OryxEngine PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS OryxEngine
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
