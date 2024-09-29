#include "../../includes/entity/Knight.hpp"

namespace entity {

Knight::Knight(const sf::Texture& texture, Color color): APiece(texture, color) {}

bool Knight::isValidMove(std::size_t x, std::size_t y) const {
    return true;
}

}