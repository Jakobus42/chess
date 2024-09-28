#pragma once

#include "../entity/APiece.hpp"

namespace game {

constexpr const uint8_t BOARD_SIZE = 8;

struct Tile {
    sf::Sprite sprite;
    sf::Texture texture;
};

class Board {
    public:
        Board();

        void display(sf::RenderWindow& window) const;
    private:
        Tile _evenTile;
        Tile _oddTile;
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];

        void displayFrame(sf::RenderWindow& window) const;
        void displayTiles(sf::RenderWindow& window) const;
};

}