#include "../../includes/entity/APiece.hpp"

namespace entity {

APiece::APiece(const sf::Texture& texture, Color color):
_texture(texture),
_color(color) {
    _sprite.setTexture(texture);
}

APiece::~APiece() {}

sf::Sprite& APiece::getSprite() { return _sprite; }

Color APiece::getColor() { return _color; }

bool APiece::isPathClear(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    int dx = static_cast<int>(dest.x) - static_cast<int>(from.x);
    int dy = static_cast<int>(dest.y) - static_cast<int>(from.y);

    int stepX = (dx != 0) ? (dx / std::abs(dx)) : 0;
    int stepY = (dy != 0) ? (dy / std::abs(dy)) : 0;

    std::size_t currentX = from.x + stepX;
    std::size_t currentY = from.y + stepY;

    while (currentX != dest.x || currentY != dest.y) {
        if (board[currentY][currentX]) {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }

    return true;
}

bool APiece::isEnemyPiece(sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8], Color pieceColor) const {
    if (board[dest.y][dest.x]) {
        return board[dest.y][dest.x]->getColor() != pieceColor;
    }
    return false;
}

bool APiece::isDiagonalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const {
    return std::abs(static_cast<int>(dest.x) - static_cast<int>(from.x)) == std::abs(static_cast<int>(dest.y) - static_cast<int>(from.y));
}

bool APiece::isHorizontalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const {
    return from.y == dest.y;
}

bool APiece::isVerticalMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const {
    return from.x == dest.x;
}

void APiece::setHasMoved(bool hasMoved) {
    _hasMoved = hasMoved;
}

bool APiece::getHasMoved() const {
    return _hasMoved;
}

}