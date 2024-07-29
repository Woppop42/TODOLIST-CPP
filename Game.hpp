#ifndef __GAME__
#define __GAME__
#include <iostream>


class Game
{
    public:
        Game(int id, std::string& nom) : id(id), nom(nom){};
        int getId() const;
        std::string getNom() const;
    private:
        std::string nom;
        int id;
};

#endif