#include "Game.hpp"
#include <iostream>

Game::Game(int id, std::string& nom) : id(id), nom(nom) {};

int Game::getId() const
{
    return this->id;
}
std::string Game::getNom() const
{
    return this->nom;
}