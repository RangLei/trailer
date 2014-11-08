#ifndef DATABASE_SQL_H
#define DATABASE_SQL_H

#include <list>
#include "object/object.h"

class Database_SQL_Impl;
class Database_SQL
{
public:
    static Database_SQL* instance();

    ~Database_SQL();

    bool init(const char *host,
              const char *user,
              const char *passwd,
              const char *db = 0,
              unsigned int port = 3306,
              const char *unix_socket = 0,
              unsigned long clientflag = 0);

    void release();

    int do_db_real_query(const char* p_cmd, const int &length);

    int do_db_insert_table(const char* table, const TRA_Table_Data &table_data);
    int do_db_select_table(const char* table, std::list<TRA_Table_Data> &result_table_datas);
    int do_db_update_table(const char* table, const TRA_Table_Data &table_data);


private:
    Database_SQL();

    Database_SQL_Impl   *_sql_impl;
};

#endif // DATABASE_SQL_H
