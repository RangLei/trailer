#include <iostream>
#include <cstdlib>
#include "auto_test.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
        return 0;

    AUTO_TEST auto_test;
    int option = atoi(argv[1]);

    switch(option)
    {
    case 1:
        return auto_test.protocol_get_default_route_test();
    case 2:
        return auto_test.protocol_dotini_open_right_test();
    case 3:
        return auto_test.protocol_dotini_open_err_test();
    case 4:
        return auto_test.protocol_init_sendsock_test();
    case 5:
        return auto_test.protocol_init_recvsock_test();
    case 6:
        return auto_test.protocol_create_port_test();
    case 7:
        return auto_test.protocol_get_local_ipaddr_test();
    case 8:
        return auto_test.protocol_is_addr_local_no_test();
    case 9:
        return auto_test.protocol_select_localaddr_for_remote_test();
    case 10:
        return auto_test.protocol_Transfer_Registe_Param_assign_test();
    case 11:
        return auto_test.protocol_Transfer_Registe_Param_cmp_test();
    case 12:
        return auto_test.protocol_Transfer_Registe_Param_cmp_not_test();
    case 13:
        return auto_test.protocol_Protocol_Head_assign_test();
    case 14:
        return auto_test.protocol_dotini_close_test();
    case 15:
        return auto_test.protocol_ACE_Protocol_Client_init_err_test();
    case 16:
        return auto_test.protocol_ACE_Protocol_Client_release_test();
    case 17:
        return auto_test.protocol_ACE_Protocol_Client_operator_connect_success_test();
    case 18:
        return auto_test.protocol_ACE_Protocol_Client_operator_param_fail_test();
    case 19:
        return auto_test.protocol_ACE_Protocol_Client_receive_test();
    default:
        return -1;
    }

    return -1;
}
