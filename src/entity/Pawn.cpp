#include "../../includes/entity/Pawn.hpp"

namespace entity {

Pawn::Pawn(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Pawn::isValidMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY, const std::unique_ptr<APiece> board[8][8]) const {
    int direction = (_color == Color::WHITE) ? -1 : 1;
    int startRow = (_color == Color::WHITE) ? 6 : 1;

    if(toX == fromX && toY == fromY + direction && !board[toY][toX]) {
        return true;
    }
    if(toX == fromX && toY == fromY + 2 * direction && fromY == startRow &&
       !board[toY][toX] && !board[fromY + direction][toX]) {
        return true;
    }
    if((toX == fromX + 1 || toX == fromX - 1) && toY == fromY + direction &&
       board[toY][toX] && board[toY][toX]->getColor() != _color) {
        return true;
    }

    // TODO: Implement en passant

    return false;
}

}