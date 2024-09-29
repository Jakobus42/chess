#include "../../includes/entity/Queen.hpp"

namespace entity {

Queen::Queen(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Queen::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    if (!isHorizontalMove(from, dest) && !isVerticalMove(from, dest) && !isDiagonalMove(from, dest)) {
        return false;
    }
    if (!isPathClear(from, dest, board)) {
        return false;
    }
    return !board[dest.y][dest.x] || isEnemyPiece(dest, board, _color);
}

}