#pragma once

#include <SFML/Graphics.hpp>

namespace game {

class GameManager {
    public:
        GameManager();

        void run();
    private:
        sf::RenderWindow _window;

        void processEvent(const sf::Event& event);
        void update();
};

}