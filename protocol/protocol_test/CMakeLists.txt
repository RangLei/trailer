# CMakeLists for src directory
PROJECT(protocol_test)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++0x")

include(CTest)
enable_testing()

#confirm TOOLKITS if define or not
if(EXISTS $ENV{TOOLKITS} )
message("1. TOOLKITS is $ENV{TOOLKITS}...")
else()
message(FATAL_ERROR "-1. Please Define TOOLKITS!")
endif()
set(TOOLKITS_DIR $ENV{TOOLKITS})
#end confirm TOOLKITS

#confirm ACE
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH $ENV{TOOLKITS}/share/cmake)

find_package(ACE REQUIRED)
if(ACE_FOUND)
message("3. ACE_INCLUDE_DIR is ${ACE_INCLUDE_DIR}...")
message("4. ACE_LIBRARY is ${ACE_LIBRARY}...")
else(ACE_FOUND)
message(FATAL_ERROR "-2. ACE find Error!")
endif(ACE_FOUND)

include_directories(${ACE_INCLUDE_DIR})
link_directories(${ACE_INCLUDE_DIR}/../lib)
#end confirm ACE


aux_source_directory (. DISPATCH_SRCS)

include_directories(
  ${PROJECT_SOURCE_DIR}/../
)
link_directories(
${CMAKE_BINARY_DIR}/lib
)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# executable file
ADD_EXECUTABLE(protocol_test ${DISPATCH_SRCS})
TARGET_LINK_LIBRARIES(protocol_test protocol ACE)
add_dependencies(protocol_test protocol)

# Add a simple test     
set_property(TARGET protocol_test PROPERTY LABELS protocol)

ADD_TEST(protocol_get_default_route_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 1)
ADD_TEST(protocol_dotini_open_right_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 2)
ADD_TEST(protocol_dotini_open_err_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 3)
ADD_TEST(protocol_init_sendsock_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 4) 
ADD_TEST(protocol_init_recvsock_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 5) 
ADD_TEST(protocol_create_port_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 6) 
ADD_TEST(protocol_get_local_ipaddr_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 7) 
ADD_TEST(protocol_is_addr_local_no_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 8) 
ADD_TEST(protocol_select_localaddr_for_remote_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 9) 
ADD_TEST(protocol_Transfer_Registe_Param_assign_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 10) 
ADD_TEST(protocol_Transfer_Registe_Param_cmp_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 11) 
ADD_TEST(protocol_Transfer_Registe_Param_cmp_not_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 12) 
ADD_TEST(protocol_Protocol_Head_assign_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 13) 
ADD_TEST(protocol_dotini_close_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 14) 
ADD_TEST(protocol_ACE_Protocol_Client_init_err_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 15) 
ADD_TEST(protocol_ACE_Protocol_Client_release_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 16)
ADD_TEST(protocol_ACE_Protocol_Client_operator_connect_success_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 17) 
ADD_TEST(protocol_ACE_Protocol_Client_operator_param_fail_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 18)
ADD_TEST(protocol_ACE_Protocol_Client_receive_test ${EXECUTABLE_OUTPUT_PATH}/protocol_test 19)

set_property(TEST
		protocol_get_default_route_test
		protocol_init_sendsock_test
		protocol_init_recvsock_test
		protocol_create_port_test
		protocol_get_local_ipaddr_test
		protocol_is_addr_local_no_test
		protocol_select_localaddr_for_remote_test
		protocol_Transfer_Registe_Param_assign_test
		protocol_Transfer_Registe_Param_cmp_test
		protocol_Transfer_Registe_Param_cmp_not_test	
		protocol_dotini_open_right_test
		protocol_dotini_open_err_test	
		protocol_Protocol_Head_assign_test	
		protocol_dotini_close_test
		protocol_ACE_Protocol_Client_init_err_test	
		protocol_ACE_Protocol_Client_release_test
		protocol_ACE_Protocol_Client_operator_connect_success_test
		protocol_ACE_Protocol_Client_operator_param_fail_test
		protocol_ACE_Protocol_Client_receive_test
PROPERTY LABELS protocol)



