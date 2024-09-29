#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"

namespace game {

class GameManager {
    public:
        GameManager();

        void run();

    private:
        sf::RenderWindow _window;
        Board _board;
        entity::Color _currentPlayer;
        sf::Vector2<std::size_t> _fromPosition;
        bool _isSelecting;

        void processEvent(const sf::Event& event);
        void processMouseEvent();
        void update();
        sf::Vector2<std::size_t> pixelToGrid(const sf::Vector2i& pixelPos) const;
};

}