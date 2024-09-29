#include "../../includes/entity/Bishop.hpp"

namespace entity {

Bishop::Bishop(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Bishop::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}