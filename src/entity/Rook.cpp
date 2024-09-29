#include "../../includes/entity/Rook.hpp"

namespace entity {

Rook::Rook(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Rook::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    if (!isHorizontalMove(from, dest) && !isVerticalMove(from, dest)) {
        return false;
    }
    if (!isPathClear(from, dest, board)) {
        return false;
    }
    if(board[dest.y][dest.x] && !isEnemyPiece(dest, board, _color)) {
        return false;
    }
    return true;
}

}