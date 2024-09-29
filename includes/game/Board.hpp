#pragma once

#include <iostream>
#include "../entity/APiece.hpp"
#include "../entity/Pawn.hpp"
#include "../entity/Knight.hpp"
#include "../entity/Rook.hpp"
#include "../entity/King.hpp"
#include "../entity/Queen.hpp"
#include "../entity/Bishop.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


#include <unordered_map>

namespace game {

constexpr const uint8_t BOARD_SIZE = 8;
constexpr const uint8_t TILE_SIZE = 128;

struct Tile {
    sf::Sprite sprite;
    sf::Texture texture;
};

enum class Components { ODD_TILE = 0, EVEN_TILE, PAWN, KNIGHT, BISHOP, KING, QUEEN, ROOK };

class Board {
    public:
        Board();

        void display(sf::RenderWindow& window) const;
        bool requestMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY, entity::Color currentPlayer);
        std::pair<std::size_t, std::size_t> getOrigin() const;
    private:
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
        std::unordered_map<int, sf::Texture> _textures;

        void displayFrame(sf::RenderWindow& window, float offsetX, float offsetY, std::size_t frameSize) const;
        void displayBoard(sf::RenderWindow& window, float offsetX, float offsetY, float frameBorder) const;

        void initTextures();
        void loadTexture(const std::string& path, int key);
        
        void initTiles();
        void initPieces(entity::Color color);

        int generateTextureKey(Components component, entity::Color color) const;
};

}