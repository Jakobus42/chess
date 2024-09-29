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

enum class Components { ODD_TILE = 0, EVEN_TILE, PAWN, KNIGHT, BISHOP, KING, QUEEN, ROOK, NONE };

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

        bool isPromotionActive() const;
        void promotePawn(Components selection, entity::Color currentPlayer);
        void displayPromotionOptions(entity::Color currentPlayer);
        Components getPromotionSelection(sf::Vector2i mouse) const;

        bool isCheckmate(entity::Color currentPlayer);
        bool isStalemate(entity::Color currentPlayer);
        bool isFiftyMoveRule() const;
        bool isInsufficientMaterial() const;
    private:
        std::unique_ptr<entity::APiece> _board[BOARD_SIZE][BOARD_SIZE];
        std::unordered_map<int, sf::Texture> _textures;
        std::vector<sf::Vector2<std::size_t>> _highlightedTiles;
        sf::RenderWindow& _window;
        std::size_t _halfMoveClock;
        float _offsetX;
        float _offsetY;
        float _frameBorder;
        bool _promotionActive;
        sf::Vector2<std::size_t> _promotionPos;

        void displayFrame(std::size_t frameSize) const;
        void displayBoard() const;
        void displayHighlightedTiles() const;

        void initTextures();
        void loadTexture(const std::string& path, int key);
        
        void initPieces(entity::Color color);

        int generateTextureKey(Components component, entity::Color color) const;

        template <typename T>
        sf::Vector2<std::size_t> getPiecePosition(entity::Color color) const;
        bool isSquareUnderAttack(sf::Vector2<std::size_t> square, entity::Color currentPlayer) const;

        bool isMoveSafeForKing(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer);
        bool isPawnPromotion(sf::Vector2<std::size_t> from, entity::Color currentPlayer) const;
        bool canCastle(entity::Color currentPlayer, bool isKingside) const;
        bool tryCastle(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer, std::unique_ptr<entity::APiece>& piece);
        void performCastle(entity::Color currentPlayer, bool isKingside);
        bool hasAnyLegalMoves(entity::Color currentPlayer);

        void triggerPromotion(sf::Vector2<std::size_t> dest, entity::Color currentPlayer);

        void resetHalfMoveClock();
        void incrementHalfMoveClock();
};

}