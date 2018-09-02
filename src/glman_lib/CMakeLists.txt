file( GLOB SOURCES
	./*.cpp
#	./UT/*.cpp
#	./Parameters/*.cpp
#	./OP/*.cpp
#	./GEO/*.cpp
)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# find boost libs
find_package( Boost COMPONENTS log REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )

add_library( glman_lib SHARED ${SOURCES} )
target_link_libraries( glman_lib ${OpenCL_LIBRARY} ${Boost_LIBRARIES} dl)
set_target_properties(glman_lib PROPERTIES OUTPUT_NAME "glman")

install(TARGETS glman_lib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if (APPLE)
	add_custom_command(
		TARGET glman_lib
		POST_BUILD
		COMMAND rsync
		ARGS -r
	    	"${CMAKE_CURRENT_SOURCE_DIR}/../../bin/macos/*"
	    	"${CMAKE_INSTALL_PREFIX}/bin"
		COMMENT "Copying mac binaries"
	)
endif (APPLE)

add_custom_command(
	TARGET glman_lib
	POST_BUILD
	COMMAND mkdir
	ARGS ${CMAKE_INSTALL_PREFIX}/tests
)

add_custom_command(
	TARGET glman_lib
	POST_BUILD
	COMMAND rsync
	ARGS -r
    	"${CMAKE_CURRENT_SOURCE_DIR}/../../tests/*"
    	"${CMAKE_INSTALL_PREFIX}/tests"
	COMMENT "Copying test files"
)