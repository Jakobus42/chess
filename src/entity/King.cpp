#include "../../includes/entity/King.hpp"

namespace entity {

King::King(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool King::isInCheck(sf::Vector2<std::size_t> kingPosition, const std::unique_ptr<APiece> board[8][8]) const {
    for (std::size_t y = 0; y < 8; ++y) {
        for (std::size_t x = 0; x < 8; ++x) {
            if (board[y][x] && board[y][x]->getColor() != _color) {
                if (board[y][x]->isValidMove({x, y}, kingPosition, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool King::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    int dx = std::abs(static_cast<int>(dest.x) - static_cast<int>(from.x));
    int dy = std::abs(static_cast<int>(dest.y) - static_cast<int>(from.y));
    if (dx > 1 || dy > 1) {
        return false;
    }
    if(isInCheck(dest, board)) {
        return false;
    }
    return !board[dest.y][dest.x] || isEnemyPiece(dest, board, _color);
}

}