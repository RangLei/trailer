#include <iostream>

using namespace std;

#include "msg_parse/client_msg_parse/client_msg_parse.h"
#include "msg_parse/server_msg_parse/server_msg_parse.h"

int test_server_msg()
{
    int rc = 0;

    cout << "server msg parse begin ..." << endl;

    char server_msg[] = "asdfasdfasdf";
    rc = server_msg_parse(server_msg, sizeof(server_msg));

    cout << "server msg parse end." << endl;

    return 0;
}

int test_client_msg()
{
    int rc = 0;

    cout << "client msg parse begin ..." << endl;

    char client_msg[] = "asdfasdfasdf";
    rc = client_msg_parse(client_msg, sizeof(client_msg));

    cout << "client msg parse end." << endl;

    return 0;
}

int main(int argc, char *argv[])
{
    test_client_msg();
    test_server_msg();

    return 0;
}

