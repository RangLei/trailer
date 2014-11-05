#include "auto_test.h"
#include "local_addr.h"
#include "dotini_parser.h"
#include <iostream>
#include <string>
#include <cstring>
#include "udp_socket.h"
#include "machine_param.h"
#include "protocol_head.h"
#include "ace_protocol_client.h"

using namespace std;

AUTO_TEST::AUTO_TEST()
{
}

AUTO_TEST::~AUTO_TEST()
{
}

int AUTO_TEST::protocol_get_default_route_test()
{
    int ret = util::get_default_route();
    if(1 == ret)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_dotini_open_right_test()
{
    return dotini_open("dispatch.ini");
}

int AUTO_TEST::protocol_dotini_open_err_test()
{
    int ret = dotini_open("file.ini");
    if(-1 == ret)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_init_sendsock_test()
{
    UDP_Socket udp_socket;
    if( -1 != udp_socket.init_sendsock() )
        return 0;
    return -1;
}

int AUTO_TEST::protocol_init_recvsock_test()
{
    UDP_Socket udp_socket;
    if( -1 != udp_socket.init_recvsock(1234) )
        return 0;
    return -1;
}

int AUTO_TEST::protocol_create_port_test()
{
    UDP_Socket udp_socket;
    int tmp = -1;
    int &port = tmp;
    int &fd = tmp;
    udp_socket.create_port(port, fd);
    if(port > -1 && fd > -1)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_get_local_ipaddr_test()
{
    int ret = util::get_local_ipaddr();
    if(1 == ret)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_is_addr_local_no_test()
{
    in_addr tmp;
    tmp.s_addr = 123;
    util::get_default_route();
    util::get_local_ipaddr();

    return util::is_addr_local(&tmp);
}

int AUTO_TEST::protocol_select_localaddr_for_remote_test()
{
    util::get_default_route();
    util::get_local_ipaddr();
    u_int32_t localip = util::select_localaddr_for_remote(12345672);
    if(localip > 0)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_Transfer_Registe_Param_assign_test()
{
    Transfer_Registe_Param transfer_registe_param;
    strcpy(transfer_registe_param._id ,"transfer_param");
    transfer_registe_param._ip = 1231548;

    Transfer_Registe_Param dispatch_registe_param(transfer_registe_param);
    if(strcmp(dispatch_registe_param._id, transfer_registe_param._id) == 0
            && dispatch_registe_param._ip == transfer_registe_param._ip)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_Transfer_Registe_Param_cmp_test()
{
    Transfer_Registe_Param transfer_registe_param;
    strcpy(transfer_registe_param._id ,"transfer_param");
    transfer_registe_param._ip = 1231548;

    Transfer_Registe_Param dispatch_registe_param;
    strcpy(dispatch_registe_param._id ,"transfer_param");
    dispatch_registe_param._ip = 1231548;

    if( transfer_registe_param == dispatch_registe_param )
        return 0;
    return -1;
}

int AUTO_TEST::protocol_Transfer_Registe_Param_cmp_not_test()
{
    Transfer_Registe_Param transfer_registe_param;
    strcpy(transfer_registe_param._id ,"transfer_param");
    transfer_registe_param._ip = 1231548;

    Transfer_Registe_Param dispatch_registe_param;
    strcpy(dispatch_registe_param._id ,"dispatch_param");
    dispatch_registe_param._ip = 1231545;

    if( transfer_registe_param == dispatch_registe_param )
        return -1;
    return 0;

}

int AUTO_TEST::protocol_Protocol_Head_assign_test()
{
    Protocol_Head protocol_head;
    protocol_head._pkg_len = 123;
    protocol_head._protocol_type = _TYPE_HEART;
    strcpy( protocol_head._reserve,"hello world" );
    protocol_head._version = 132;

    Protocol_Head protocol_tail(protocol_head);
    if(protocol_head._pkg_len == protocol_tail._pkg_len &&
            protocol_head._protocol_type == protocol_tail._protocol_type &&
            strcmp(protocol_head._reserve, protocol_tail._reserve) == 0 &&
            protocol_head._version == protocol_tail._version)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_dotini_close_test()
{
    dotini_open("dispatch.ini");
    dotini_close();
    return 0;
}

int AUTO_TEST::protocol_ACE_Protocol_Client_init_err_test()
{
    ACE_Protocol_Client ace_protocol_client;
    if( true == ace_protocol_client.init("localhost",1234) )
        return -1;
    return 0;
}

int AUTO_TEST::protocol_ACE_Protocol_Client_release_test()
{
    ACE_Protocol_Client ace_protocol_client;
    ace_protocol_client.init("localhost",1234);
    ace_protocol_client.release();
    return 0;
}

int AUTO_TEST::protocol_ACE_Protocol_Client_operator_connect_success_test()
{
    unsigned char send_buf[] = "hello world";
    int len = strlen("hello world");
    time_t time_out = 1;
    ACE_Protocol_Client ace_protocol_client;
    ace_protocol_client.init("localhost",1234);
    bool ret = true;
    ret == ace_protocol_client(send_buf, len, time_out);
    ace_protocol_client.release();
    if(true == ret)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_ACE_Protocol_Client_operator_param_fail_test()
{
    unsigned char *send_buf = NULL;
    int len = 0;
    time_t time_out = 1;
    ACE_Protocol_Client ace_protocol_client;
    ace_protocol_client.init("localhost",1234);
    bool ret = true;
    ret == ace_protocol_client(send_buf, len, time_out);
//    ace_protocol_client.release();
    if(true == ret)
        return 0;
    return -1;
}

int AUTO_TEST::protocol_ACE_Protocol_Client_receive_test()
{
    char buf[] = "hello world";
    int length;
    time_t time_out = 1;
    ACE_Protocol_Client ace_protocol_client;
    ace_protocol_client.init("localhost",1234);
    if( false == ace_protocol_client.receive(buf, &length, time_out) ){
        ace_protocol_client.release();
        return 0;
    }
    ace_protocol_client.release();
    return -1;
}
