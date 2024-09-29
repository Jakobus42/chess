#include "../../includes/entity/King.hpp"

namespace entity {

King::King(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool King::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}