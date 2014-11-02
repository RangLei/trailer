#include "database_sql.h"
#include "database_sql_impl.h"

Database_SQL::Database_SQL()
    : _sql_impl(0)
{
}

Database_SQL *Database_SQL::instance()
{
    static Database_SQL db;
    return &db;
}

Database_SQL::~Database_SQL()
{
    this->release();
}

bool Database_SQL::init(const char *host,
                        const char *user,
                        const char *passwd,
                        const char *db,
                        unsigned int port,
                        const char *unix_socket,
                        unsigned long clientflag)
{
    if (!_sql_impl)
    {
        _sql_impl = new Database_SQL_Impl;
        if (!_sql_impl)
        {
            return false;
        }
    }

    return _sql_impl->init(host, user, passwd, db, port, unix_socket, clientflag);
}

void Database_SQL::release()
{
    if (_sql_impl)
    {
        return _sql_impl->release();
        delete _sql_impl;
        _sql_impl = NULL;
    }
}

int Database_SQL::do_db_real_query(const char *p_cmd, const int &length)
{
    if (p_cmd)
        return _sql_impl->do_db_real_query(p_cmd, length);

    return -1;
}

int Database_SQL::do_db_insert_table(const char* table, const TRA_Download_Table_Data& table_data)
{
    if (table)
        return _sql_impl->do_db_insert_table(table, table_data);

    return -1;
}

int Database_SQL::do_db_select_table(const char *table, std::list<TRA_Download_Table_Data> &result_table_datas)
{
    if (table)
        return _sql_impl->do_db_select_table(table, result_table_datas);

    return -1;
}

int Database_SQL::do_db_update_table(const char *table, const TRA_Download_Table_Data &table_data)
{
    if (table)
        return _sql_impl->do_db_update_table(table, table_data);

    return -1;
}
