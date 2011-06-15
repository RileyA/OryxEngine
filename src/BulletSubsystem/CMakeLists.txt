# Build file for the Bullet Subsystem
include_directories("${BT_INCLUDE_DIR}")

set(SOURCE_FILES
	BulletConversions.cpp
	Bulletdllmain.cpp
	BulletSubsystem.cpp
	CCT_Compound.cpp
	CCT_Primitive.cpp
	CharPrimitive.cpp
	CollisionObject.cpp
	#Hinge.cpp
	#Joint.cpp
	PhysicsBoxShape.cpp
	PhysicsCapsuleShape.cpp
	PhysicsCompoundShape.cpp
	PhysicsConvexShape.cpp
	PhysicsObject.cpp
	PhysicsShape.cpp
	PhysicsSphereShape.cpp
	PhysicsTrimeshShape.cpp
	QCharacterController.cpp
	QuantaController.cpp
	RigidBody.cpp
	)

set(HEADER_FILES
	BulletConversions.h
	Bulletdllmain.h
	BulletSubsystem.h
	CCT_Compound.h
	CCT_Primitive.h
	CharacterController.h
	CharPrimitive.h
	CollisionObject.h
	#Hinge.h
	#Joint.h
	PhysicsBoxShape.h
	PhysicsCapsuleShape.h
	PhysicsCompoundShape.h
	PhysicsConvexShape.h
	PhysicsObject.h
	PhysicsShape.h
	PhysicsSphereShape.h
	PhysicsTrimeshShape.h
	QCharacterController.h
	QuantaController.h
	RaycastReport.h
	RigidBody.h
	)

add_library(BulletSubsystem SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(BulletSubsystem PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (BulletSubsystem ${ORYX_LIB} ${BT_MATH_LIB} 
	${BT_C_LIB} ${BT_D_LIB})

install(TARGETS BulletSubsystem
	RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
	LIBRARY DESTINATION ${INSTALL_LIBS_TO}
	ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
