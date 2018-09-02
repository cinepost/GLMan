file( GLOB SOURCES
	./*.cpp
)

# find python libs
find_package( PythonLibs 2.7 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# find boost libs
find_package( Boost COMPONENTS log python27 REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )

# define wrapper library
add_library( glman_for_python SHARED ${SOURCES} )
target_include_directories ( glman_for_python PUBLIC ${GLMAN_INCLUDE_DIRECTORY} )
target_link_libraries( glman_for_python ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} glman_lib )

# don't prepend wrapper library name with lib
set_target_properties( glman_for_python PROPERTIES PREFIX "" )

if (APPLE)
    set_target_properties( glman_for_python PROPERTIES
    	SUFFIX ".so"
    )
endif (APPLE)
	
install(TARGETS glman_for_python DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python2.7libs)

add_custom_command(
  TARGET glman_for_python
  POST_BUILD
  COMMAND rsync
  ARGS -r
    "${CMAKE_CURRENT_SOURCE_DIR}/../../python/glman_for_python/prman.py"
    "${CMAKE_INSTALL_PREFIX}/lib/python2.7libs"
  COMMENT "Copying Bundle Stuff"
)