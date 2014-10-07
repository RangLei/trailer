#include <iostream>

using namespace std;

#include "msg_parse/client_msg_parse/client_msg_parse.h"
#include "msg_parse/server_msg_parse/server_msg_parse.h"

#include "msg_handler/msg_handler.h"

int test_server_msg()
{
    int rc = 0;

    cout << "server msg parse begin ..." << endl;

    char server_msg[] = "#[TYYYYYYY,Data_length,N,HHMMSS,S,latitude,D,longitude,G,speed,direction,DDMMYY,PDOP,RSSI,Box_status,Battery_voltage,Trailer_status,Checksum]";
    Msg_Handler_Base *msg_handler = NULL;
    rc = server_msg_parse(server_msg, sizeof(server_msg), msg_handler);

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

