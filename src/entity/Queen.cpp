#include "../../includes/entity/Queen.hpp"

namespace entity {

Queen::Queen(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Queen::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}