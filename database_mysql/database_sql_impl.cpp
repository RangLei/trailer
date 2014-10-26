#include "database_sql_impl.h"

Database_SQL_Impl::Database_SQL_Impl()
    : _mysql(NULL)
{
}

Database_SQL_Impl::~Database_SQL_Impl()
{
    this->release();
}

bool Database_SQL_Impl::init(const char *host,
                             const char *user,
                             const char *passwd,
                             const char *db,
                             unsigned int port,
                             const char *unix_socket,
                             unsigned long clientflag)
{
    // init mysqlclient
    if (_mysql) return false;

    _mysql = mysql_init(0);
    if (!_mysql)
    {
        fprintf(stderr, "Failed to init to database: Error: [null].\n");
        fflush(stderr);
        return false;
    }

    // assignment member variables
    memset(_host, 0, SV_DATA_LEN);
    memset(_user, 0, SV_DATA_LEN);
    memset(_passwd, 0, SV_DATA_LEN);
    memset(_db, 0, SV_DATA_LEN);
    memset(_unix_socket, 0, SV_DATA_LEN);
    if (host) memcpy(_host, host, strlen(host));
    if (user) memcpy(_user, user, strlen(user));
    if (passwd) memcpy(_passwd, passwd, strlen(passwd));
    if (db) memcpy(_db, db, strlen(db));
    if (unix_socket) memcpy(_unix_socket, unix_socket, strlen(unix_socket));
    _port = port;
    _clientflag = clientflag;

    // connect mysql
    bool fr = this->connect_sql();
    // select specify mysql db; if not exist then create else use
    if (fr) fr = this->select_sql_db();

    return fr;
}

bool Database_SQL_Impl::connect_sql()
{
    //if (!mysql_real_connect(_mysql, "localhost", "root", "123456", "trailer", 0, NULL, 0))
    if (!mysql_real_connect(_mysql, _host, _user, _passwd, NULL, _port, NULL, _clientflag))
    {
        fprintf(stderr, "Error connect to sql:[%s]\n",
                const_cast<char*>(mysql_error(_mysql)));
        fflush(stderr);
        return false;
    }

    fprintf(stdout, "Success to connect to mysql.\n");
    fflush(stdout);

    return true;
}

bool Database_SQL_Impl::select_sql_db()
{
    int rc = 0;
    rc = mysql_select_db(_mysql, _db);

    if (rc != 0)
    {
        if(ER_BAD_DB_ERROR  == mysql_errno(_mysql))
        {
            char c_create_db_query[64];
            sprintf(c_create_db_query, "CREATE DATABASE %s", _db);
            rc = mysql_real_query(_mysql, c_create_db_query, strlen(c_create_db_query));
            if (!rc)
            {
                fprintf(stdout, "Success making query command:[%s].\n",
                        c_create_db_query);
                fflush(stdout);

                rc = mysql_select_db(_mysql, _db);
                if (rc != 0)
                {
                    fprintf(stderr, "Error select sql db: [%s] [%s].\n",  _db, mysql_error(_mysql));
                    fflush(stderr);

                    close_sql_db();

                    return false;
                }
            }
            else
            {
                fprintf(stderr, "Error making query command:[%s]: %s.\n",
                        c_create_db_query,
                        mysql_error(_mysql));
                fflush(stderr);

                close_sql_db();

                return false;
            }
        }
        else
        {
            fprintf(stderr, "Error select sql [%s] : [%s].\n",  _db, mysql_error(_mysql));
            fflush(stderr);

            return false;
        }
    }

    fprintf(stdout, "Success to select to database: [%s].\n", _db);
    fflush(stdout);

    return true;
}

void Database_SQL_Impl::close_sql_db()
{
    if (_mysql)
    {
        mysql_close(_mysql);
        _mysql = NULL;

        fprintf(stdout, "close database %s.\n", _db);
        fflush(stdout);
    }
}

void Database_SQL_Impl::release()
{
    this->close_sql_db();
}

//            //_mysql->reconnect = 2;
//            const char* query = "select * from test";

//            if (mysql_real_query(_mysql, query, strlen(query)))
//            {
//                printf("Error making query: %s !!!\n",mysql_error(_mysql));
//                return false;
//            }
//            else
//            {
//                MYSQL_RES* result = mysql_store_result(_mysql);
//                MYSQL_ROW row;
//                while ((row = mysql_fetch_row(result)))
//                {
//                    fprintf(stdout, "%s\n", row[0]);
//                }
//                printf("query %s succeed!\n",query);
//                return true;
//            }
//        }
//        else
//        {
//            printf("Error select sql db %s %s rc = %d\n",  db, mysql_error(_mysql), rc);
//            return false;
//        }
//    }
//return true;
//}



