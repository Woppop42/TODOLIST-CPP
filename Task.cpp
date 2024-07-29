#include "Task.hpp"
#include <iostream>


Task::Task(int id, int idGame, const std::string description) : id(id), idGame(idGame), description(description){};

int Task::getTaskId() const
{
    return this->id;
}
int Task::getGameId() const
{
    return this->idGame;
}
std::string Task::getDescription() const
{
    return this->description;
}