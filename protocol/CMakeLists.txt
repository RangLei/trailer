# CMakeLists for src directory
project(protocol)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
aux_source_directory (. PROTOCOL_SRCS)
 
# shared library
add_library(protocol SHARED ${PROTOCOL_SRCS})
set_target_properties(protocol PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})

install(TARGETS protocol
		LIBRARY DESTINATION ${SUYUN_SDK_DIR}/lib)

#add_subdirectory(protocol_test)
