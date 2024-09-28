#include "../../includes/entity/Pawn.hpp"

namespace entity {

Pawn::Pawn(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Pawn::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}