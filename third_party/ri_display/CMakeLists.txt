set (SOURCES 
	./d_houdini.C
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# find boost libs
find_package( Boost COMPONENTS log python27 REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} ${PROJECT_DIR}/include/prman )

# define wrapper library
add_library( d_houdini SHARED ${SOURCES} )
#target_include_directories ( d_houdini PUBLIC ${GLMAN_INCLUDE_DIRECTORY} )
target_link_libraries( d_houdini ${Boost_LIBRARIES} )

# don't prepend wrapper library name with lib
set_target_properties( d_houdini PROPERTIES PREFIX "" )

if (APPLE)
    set_target_properties( d_houdini PROPERTIES
    	SUFFIX ".so"
    )
endif (APPLE)
	
install(TARGETS d_houdini DESTINATION ${CMAKE_INSTALL_PREFIX}/etc)

#add_custom_command(
#  TARGET d_houdini
#  POST_BUILD
#  COMMAND mkdir ARGS -p ${CMAKE_INSTALL_PREFIX}/lib/python2.7libs
#  COMMAND rsync ARGS -r
#    "${PROJECT_DIR}/dist/python/d_houdini/prman.py"
#    "${CMAKE_INSTALL_PREFIX}/lib/python2.7libs"
#  COMMENT "Copying Bundle Stuff"
#)