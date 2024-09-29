#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

namespace game {

class GameManager {
    public:
        GameManager();

        void run();

    private:
        sf::RenderWindow _window;
        Board _board;

        void processEvent(const sf::Event& event);
        void update();
};

}