#ifndef __TASK__
#define __TASK__
#include <iostream>

class Task
{
    public:
        Task(int id, int idGame, const std::string description) : id(id), idGame(idGame), description(description) {};
        int getTaskId() const;
        int getGameId() const;
        std::string getDescription() const;
    
    private:
        int id;
        int idGame;
        std::string description;
};

#endif