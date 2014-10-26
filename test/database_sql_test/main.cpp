#include <iostream>

using namespace std;

#include "database_mysql/database_sql.h"

int main()
{
    // test begin
    Database_SQL test_sql;

    if (!test_sql.init("localhost", "root", "123456", "telitek", 3306, NULL))
    {
        return -1;
    }

    return 0;
}

