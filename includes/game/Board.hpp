#pragma once

#include "../entity/APiece.hpp"
#include "../entity/Pawn.hpp"
#include <unordered_map>

namespace game {

constexpr const uint8_t BOARD_SIZE = 8;

struct Tile {
    sf::Sprite sprite;
    sf::Texture texture;
};

enum Components { ODD_TILE, EVEN_TILE, PAWN };

class Board {
    public:
        Board();

        void display(sf::RenderWindow& window) const;
    private:
        Tile _evenTile;
        Tile _oddTile;
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
        std::unordered_map<Components, sf::Texture> _textures;

        void displayFrame(sf::RenderWindow& window) const;
        void displayBoard(sf::RenderWindow& window) const;

        void initTiles();
        void initPieces();
        void initTextures();

        void loadTexture(const std::string& path, Components component);
};

}