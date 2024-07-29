#ifndef __DB__
#define __DB__
#include "sqlite3.h"
#include "Game.hpp"
#include "Task.hpp"
#include <iostream>
#include <vector>

class db
{
    public:
        db(const std::string dbName);
        ~db();

        bool executeQuery(const std::string& query);
        bool createTable();
        bool insertGame(const Game& game);
        bool insertTask(const Task& task);

    private:
        sqlite3* db_;
        std::string dbName;
        

};




#endif