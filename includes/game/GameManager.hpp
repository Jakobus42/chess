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
        bool _isSelectingFrom;
        std::optional<std::pair<std::size_t, std::size_t>> _fromPosition;

        void processEvent(const sf::Event& event);
        void update();
        std::pair<std::size_t, std::size_t> pixelToGrid(const sf::Vector2i& pixelPos) const;
};

}