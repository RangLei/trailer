#ifndef DATABASE_SQL_H
#define DATABASE_SQL_H

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

    int do_db_real_query(const char* cmd, const int &length);

private:
    Database_SQL();

    Database_SQL_Impl   *_sql_impl;
};

#endif // DATABASE_SQL_H
