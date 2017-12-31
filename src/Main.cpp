
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlyphTileMap.hpp"

class Game {
public:

    Game();

private:
};

Game::Game()
{
    std::cout << "In constructor!" << std::endl;
}

int main() {

    Game game;

    return 0;
}