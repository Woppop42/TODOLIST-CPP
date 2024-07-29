#include "db.hpp"
#include <iostream>

db::db(const std::string dbName) : dbName(dbName), db_(nullptr)
{
    if(sqlite3_open(dbName.c_str(), &db_))
    {
        std::cerr << "Ne peut pas ouvrir la base de données" << sqlite3_errmsg(db_) << std::endl;
        db_ = nullptr;
    }
    else 
    {
        std::cout << "Base de données ouverte avec succès" << std::endl;
    }
}
db::~db()
{
    if(db_)
    {
        sqlite3_close(db_);
    }
}
bool db::executeQuery(const std::string& query)
{
    char* errorMsg = nullptr;
    // rc = code de retour
    int rc = sqlite3_exec(db_, query.c_str(), nullptr, nullptr, &errorMsg);
    if(rc != SQLITE_OK)
    {
        std::cerr << "SQL ERROR : " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        return false;
    }

    return true;

}

bool db::createTable()
{
    std::string createGameTableSQL = R"(
    CREATE TABLE IF NOT EXISTS Game (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL
    );
    )";

    std::string createTaskTableSQL = R"(
    CREATE TABLE IF NOT EXISTS Task (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    description TEXT NOT NULL,
    id_game INTEGER
    FOREIGN KEY(id_game) REFERENCES GAME(id)
    );
    )";

    return executeQuery(createGameTableSQL) && executeQuery(createTaskTableSQL);
        
}

bool db::insertGame(const Game& game)
{
    const char* insertSQL = "INSERT INTO Game(nom) VALUES (?);"; // utilisation de char pour compatiblité avec sqlite (C)
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db_, insertSQL, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::cerr << "Erreur de préparation : " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    sqlite3_bind_text(statement, 1, game.getNom().c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(statement) == SQLITE_DONE);
    sqlite3_finalize(statement);
    return success;
}
bool db::insertTask(const Task& task)
{
    const char* insertSQL = "INSERT INTO Task(description, id_game) VALUES (?);";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db_, insertSQL, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::cerr << "Erreur de préparation : " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    sqlite3_bind_text(statement, 1, task.getDescription().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 2,  task.getGameId());
    bool success = (sqlite3_step(statement) == SQLITE_DONE);
    sqlite3_finalize(statement);
    return success;
}