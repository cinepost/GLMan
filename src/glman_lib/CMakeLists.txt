file( GLOB SOURCES
	./*.cpp
	./interfaces/*.cpp
	./loaders/*.cpp
	./renderer/*.cpp
)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# find OpenGL libs
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIR} )

# find GLM libs
find_package( glm REQUIRED )
include_directories( ${glm_INCLUDE_DIRS} )

# find ASSIMP libs
find_package( assimp REQUIRED)
include_directories( ${assimp_INCLUDE_DIRS} )

# find boost libs
find_package( Boost COMPONENTS log REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )

IF(APPLE)
   	INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   	FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
   	MARK_AS_ADVANCED (COCOA_LIBRARY
                     OpenGL_LIBRARY)
   	SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY})

   	set(CMAKE_CXX_COMPILER "clang++")
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
ENDIF (APPLE)

add_library( glman_lib SHARED ${SOURCES} )
target_link_libraries( glman_lib ${OpenCL_LIBRARY} ${Boost_LIBRARIES} ${glm_LIBRARIES} ${assimp_LIBRARIES} ${OPENGL_LIBRARIES} ${EXTRA_LIBS} dl)
set_target_properties(glman_lib PROPERTIES 
	CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
	OUTPUT_NAME "glman"
)

install(TARGETS glman_lib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if (UNIX)
	if (APPLE)
		set(DIST_DIR ${PROJECT_DIR}/dist/macos)
	elseif (LINUX)
		set(DIST_DIR ${PROJECT_DIR}/dist/linux)
	endif ()
	add_custom_command(
		TARGET glman_lib
		POST_BUILD
		#COMMAND mkdir ARGS -p ${CMAKE_INSTALL_PREFIX}/etc
		COMMAND rsync ARGS -avr
	    	"${DIST_DIR}/*"
	    	"${CMAKE_INSTALL_PREFIX}"
		COMMENT "Copying distributed stuff"
	)
endif (UNIX)


add_custom_command(
	TARGET glman_lib
	POST_BUILD
	COMMAND mkdir ARGS -p ${CMAKE_INSTALL_PREFIX}/tests
	COMMAND rsync ARGS -avr
   		"${CMAKE_CURRENT_SOURCE_DIR}/../../tests/*"
    	"${CMAKE_INSTALL_PREFIX}/tests"
	COMMENT "Copying test files"
)