#include "../../includes/entity/Bishop.hpp"

namespace entity {

Bishop::Bishop(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Bishop::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    if (!isDiagonalMove(from, dest)) {
        return false;
    }
    if (!isPathClear(from, dest, board)) {
        return false;
    }
    return !board[dest.y][dest.x] || isEnemyPiece(dest, board, _color);
}

}