#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace entity {

enum Color { NONE = 0, BLACK, WHITE };

class APiece {
    public:
        APiece(const sf::Texture& texture, Color color);
        virtual ~APiece();

        sf::Sprite& getSprite();
        Color getColor();
        virtual bool isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const = 0;

        void setHasMoved(bool hasMoved);
        bool getHasMoved() const;
    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        Color _color;
        bool _hasMoved;

        bool isPathClear(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const;
        bool isEnemyPiece(sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8], Color pieceColor) const;
        bool isDiagonalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const;
        bool isHorizontalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const;
        bool isVerticalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const;
};

}