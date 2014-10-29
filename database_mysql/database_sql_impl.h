#ifndef DATABASE_SQL_IMPL_H
#define DATABASE_SQL_IMPL_H

#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <cstring>
#include <cstdio>

#ifndef SV_DATA_LEN
#define SV_DATA_LEN 128
#endif

class Database_SQL;
class Database_SQL_Impl
{
    friend class Database_SQL;
public:
    ~Database_SQL_Impl();
    bool init(const char *host,
              const char *user,
              const char *passwd,
              const char *db = 0,
              unsigned int port = 0,
              const char *unix_socket = 0,
              unsigned long clientflag = 0);

    void release();

    int do_db_real_query(const char* cmd, const int &length);

private:
    bool connect_sql();

    bool select_sql_db();

    void close_sql_db();

private:
    Database_SQL_Impl();

private:
    MYSQL   *_mysql;
    char _host[SV_DATA_LEN];
    char _user[SV_DATA_LEN];
    char _passwd[SV_DATA_LEN];
    char _db[SV_DATA_LEN];
    unsigned int _port;
    char _unix_socket[SV_DATA_LEN];
    unsigned long _clientflag;
};

#endif // DATABASE_SQL_IMPL_H
