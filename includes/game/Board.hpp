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

enum class Components { ODD_TILE = 0, EVEN_TILE, PAWN, KNIGHT, BISHOP, KING, QUEEN, ROOK };

class Board {
    public:
        Board(sf::RenderWindow& window);

        void display() const;
        bool requestMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer);
        
        void highlightTile(sf::Vector2<std::size_t> tile);
        void clearHighlights();

        void highlightValidMoves(sf::Vector2<std::size_t> pos, entity::Color currentPlayer);

        float getOffsetX() const;
        float getOffsetY() const;
        float getFrameBorder() const;
    private:
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
        std::unordered_map<int, sf::Texture> _textures;
        std::vector<sf::Vector2<std::size_t>> _highlightedTiles;
        sf::RenderWindow& _window;
        float _offsetX;
        float _offsetY;
        float _frameBorder;

        void displayFrame(std::size_t frameSize) const;
        void displayBoard() const;
        void displayHighlightedTiles() const;

        void initTextures();
        void loadTexture(const std::string& path, int key);
        
        void initPieces(entity::Color color);

        int generateTextureKey(Components component, entity::Color color) const;

        template <typename T>
        const std::unique_ptr<entity::APiece>& getPiece(entity::Color color) const;
};

}