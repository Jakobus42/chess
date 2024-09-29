#include "../../includes/entity/Rook.hpp"

namespace entity {

Rook::Rook(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Rook::isValidMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY, const std::unique_ptr<APiece> board[8][8]) const {
    return true;
}

}