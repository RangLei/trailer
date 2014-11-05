#ifndef AUTO_TEST_H
#define AUTO_TEST_H

class AUTO_TEST{
public:
    AUTO_TEST();
    ~AUTO_TEST();
    int protocol_get_default_route_test();
    int protocol_dotini_open_right_test();
    int protocol_dotini_open_err_test();

    int protocol_init_sendsock_test();
    int protocol_init_recvsock_test();
    int protocol_create_port_test();
    int protocol_get_local_ipaddr_test();
    int protocol_is_addr_local_no_test();
    int protocol_select_localaddr_for_remote_test();

    int protocol_Transfer_Registe_Param_assign_test();
    int protocol_Transfer_Registe_Param_cmp_test();
    int protocol_Transfer_Registe_Param_cmp_not_test();

    int protocol_Protocol_Head_assign_test();
    int protocol_dotini_close_test();

    int protocol_ACE_Protocol_Client_init_err_test();
    int protocol_ACE_Protocol_Client_release_test();
    int protocol_ACE_Protocol_Client_operator_connect_success_test();
    int protocol_ACE_Protocol_Client_operator_param_fail_test();
    int protocol_ACE_Protocol_Client_receive_test();
};

#endif //AUTO_TEST_H
