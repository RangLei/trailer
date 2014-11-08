#ifndef DATABASE_SQL_IMPL_H
#define DATABASE_SQL_IMPL_H

#include <mysql/mysql.h>
#include <mysql/mysqld_error.h>
#include <cstring>
#include <list>
#include <cstdio>

#include "object/object.h"

#ifndef SV_DATA_LEN
#define SV_DATA_LEN 128
#endif

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

    int do_db_real_query(const char *p_cmd, const int &length);

    int do_db_insert_table(const char *table, const TRA_Table_Data &table_data);
    int do_db_select_table(const char *table, std::list<TRA_Table_Data> &result_table_datas);
    int do_db_update_table(const char* table, const TRA_Table_Data &table_data);


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
