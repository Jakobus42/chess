#include "../../includes/entity/Pawn.hpp"

namespace entity {

Pawn::Pawn(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Pawn::isPawnDoubleStep(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, int direction, const std::unique_ptr<APiece> board[8][8]) const {
    int startRow = (direction == -1) ? 6 : 1;
    return from.y == startRow && dest.y == from.y + 2 * direction &&
           from.x == dest.x &&
           !board[dest.y][dest.x] &&
           !board[from.y + direction][dest.x];
}


bool Pawn::isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const {
    int direction = (_color == Color::WHITE) ? -1 : 1;

    if (dest.x == from.x && dest.y == from.y + direction && !board[dest.y][dest.x]) {
        return true;
    }
    if (isPawnDoubleStep(from, dest, direction, board)) {
        return true;
    }
    if ((dest.x == from.x + 1 || dest.x == from.x - 1) && dest.y == from.y + direction &&
        board[dest.y][dest.x] && isEnemyPiece(dest, board, _color)) {
        return true;
    }
    return false;
}

}