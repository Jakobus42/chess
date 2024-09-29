#include "../../includes/entity/Knight.hpp"

namespace entity {

Knight::Knight(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Knight::isLShapeMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest) const {
    int dx = std::abs(static_cast<int>(dest.x) - static_cast<int>(from.x));
    int dy = std::abs(static_cast<int>(dest.y) - static_cast<int>(from.y));
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

bool Knight::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    if (!isLShapeMove(from, dest)) {
        return false;
    }
    return !board[dest.y][dest.x] || isEnemyPiece(dest, board, _color);
}

}