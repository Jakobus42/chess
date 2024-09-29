#pragma once

#include "../entity/APiece.hpp"
#include "../entity/Pawn.hpp"
#include "../entity/Knight.hpp"
#include "../entity/Rook.hpp"
#include "../entity/King.hpp"
#include "../entity/Queen.hpp"
#include "../entity/Bishop.hpp"


#include <unordered_map>

namespace game {

constexpr const uint8_t BOARD_SIZE = 8;

struct Tile {
    sf::Sprite sprite;
    sf::Texture texture;
};

enum class Components { ODD_TILE, EVEN_TILE, PAWN, KNIGHT, BISHOP, KING, QUEEN, ROOK };

class Board {
    public:
        Board();

        void display(sf::RenderWindow& window) const;
    private:
        Tile _evenTile;
        Tile _oddTile;
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
        std::unordered_map<int, sf::Texture> _textures;

        void displayFrame(sf::RenderWindow& window) const;
        void displayBoard(sf::RenderWindow& window) const;

        void initTiles();

        void initPieces(entity::Color color);
        
        void initTextures();

        void loadTexture(const std::string& path, int key);
};

}