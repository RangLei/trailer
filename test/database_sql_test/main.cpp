#include <iostream>

using namespace std;

#include <cstring>
#include <list>
#include "object/object.h"

#include "database_mysql/database_sql.h"


int main(int argc, char** argv)
{
    // test begin
    Database_SQL *test_sql = Database_SQL::instance();
    const char *table = "tra_download";

    if (!test_sql->init("localhost", "root", "123456", "telitek", 3306, NULL))
    {
        return -1;
    }
    char *creat_table_cmd = "CREATE TABLE IF NOT EXISTS `tra_download` ("
                            "`id` int(11) NOT NULL AUTO_INCREMENT,"
                            "`created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,"
                            "`ip` varchar(16) COLLATE utf8_unicode_ci NOT NULL,"
                            "`content` varchar(255) COLLATE utf8_unicode_ci NOT NULL,"
                            "`flag` tinyint(4) NOT NULL DEFAULT '0',"
                            "PRIMARY KEY (`id`)"
                            ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
    if (test_sql->do_db_real_query(creat_table_cmd, strlen(creat_table_cmd)))
    {
        return -1;
    }
    TRA_Download_Table_Data tra_table_data;
    tra_table_data.ip = "127.0.0.1";
    tra_table_data.content = "xxxxxxxx";
    tra_table_data.flag = 0;
    if (test_sql->do_db_insert_table(table, tra_table_data))
    {
        return -1;
    }
    std::list<TRA_Download_Table_Data> tra_table_datas;
    if (test_sql->do_db_select_table(table, tra_table_datas))
    {
        return -1;
    }
    for (std::list<TRA_Download_Table_Data>::iterator iter = tra_table_datas.begin();
         iter != tra_table_datas.end(); ++iter)
    {
        cout << iter->primart_key << " | " << iter->ip
             << " | " << iter->content << " | " << iter->date
             << " | " << iter->flag << endl;
        iter->flag = 1;
        test_sql->do_db_update_table(table, *iter);
    }


    return 0;
}

