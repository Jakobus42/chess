#pragma once

#include "../entity/APiece.hpp"

namespace game {

constexpr const uint8_t BOARD_SIZE = 8;

class Board {
    public:
        Board() {};
        Board(sf::Sprite& evenTile, sf::Sprite& oddTile);

        void display(sf::RenderWindow& window) const;
    private:
        sf::Sprite _evenTile;
        sf::Sprite _oddTile;
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
};

}