#include "../../includes/entity/Rook.hpp"

namespace entity {

Rook::Rook(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Rook::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}