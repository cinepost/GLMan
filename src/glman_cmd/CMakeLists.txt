set (SOURCES 
	./glman_cmd.cpp
)

add_executable (glman_cmd ${SOURCES} ${MOC_SRCS} ${RES_SOURCES})
set_target_properties(glman_cmd PROPERTIES OUTPUT_NAME "glman")
 
target_link_libraries (glman_cmd glman_lib)

install(TARGETS glman_cmd DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)