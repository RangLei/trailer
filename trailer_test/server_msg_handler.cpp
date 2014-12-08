#include <sstream>
#include <string>
#include <cstring>

#include <ace/Guard_T.h>

#include "server_msg_handler.h"
#include "database_mysql/database_sql.h"
#include "addr_handler_map.h"
#include "msg_define.h"

Server_MSG_Handler::Server_MSG_Handler()
    :_handle(NULL)
    , _db_sql(Database_SQL::instance())
{
}

int Server_MSG_Handler::open(void* acceptor_or_connector)
{
    int rc = Super::open(acceptor_or_connector);

    if(rc == 0)
    {
        this->peer().get_remote_addr(_remote_addr);

        Server_MSG_Handler_List *handler_list =
                Handler_List_Singleton::instance();

        ACE_ASSERT(handler_list != NULL);

        handler_list->push_handler(this);
    }
    return 0;
}

int Server_MSG_Handler::close(u_long flags)
{
    Server_MSG_Handler_List *handler_list =
            Handler_List_Singleton::instance();

    ACE_ASSERT(handler_list != NULL);

    handler_list->erase_handler(this);

    int rc = Super::close(flags);

    return  rc;
}

int Server_MSG_Handler::handle_recv_message(const char* buf, int length)
{
    std::string str_msg = buf;

    std::size_t found = str_msg.find(LOGIN_MSG, 0, strlen(LOGIN_MSG));
    if (found != std::string::npos && found == 0)
    {
        // todo login_handle()
        std::string str_t = str_msg.substr(strlen(LOGIN_MSG), str_msg.size());
        found = str_t.find(SEP);
        if (found != std::string::npos)
        {
            std::string str_serial_no = str_t.substr(0, found);
            if (_db_sql)
            {
                ACE_TCHAR addr_str [128];
                _remote_addr.addr_to_string(addr_str, sizeof(addr_str));
                std::stringstream cmd;
                cmd << "insert into " << "tra_test_box" << " (" << "serial_no, ip, tra_download_cmd" << ")"
                    << " values " << "("
                    << "\"" << str_serial_no << "\""
                    << ", "
                    << "\"" << addr_str << "\""
                    << ", "
                    << "\"" << buf << "\""
                    << ")";

                std::string str = cmd.str();
                _db_sql->do_db_real_query(str.c_str(), str.size());
                ACE_OS::fprintf(stdout, "!!!%d--:%s\n", length, buf);

                ACE_OS::fflush(stdout);
            }
        }
    }
    else
    {
        (this->*_handle)(buf, length);
    }


    return 0;
}

int Server_MSG_Handler::handle_send_message(const char* buf, int length)
{
    if (strncmp(buf, GPS_MSG_TYPE, strlen(GPS_MSG_TYPE)) == 0)
    {
        _handle = &Server_MSG_Handler::handle_gps;
    }

    ACE_Time_Value tv(_time_out);
    int rc = peer().send_n(buf, length, &tv);
    ACE_OS::fprintf(stdout, "send to client %d--:%s\n", rc, buf);

    return rc == length ? 0 : -1;
}

void Server_MSG_Handler::handle_gps(const char* buf, const int& length)
{
    ACE_OS::fprintf(stdout, "Server_MSG_Handler::handle_gps %s--:%d\n", buf, length);
}
