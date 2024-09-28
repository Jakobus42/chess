#include "../../includes/entity/APiece.hpp"

namespace entity {

APiece::APiece(const sf::Sprite& sprite, Color color):
_sprite(sprite),
_color(color) {}

APiece::~APiece() {}

const sf::Sprite& APiece::getSprite() const { return _sprite; }

void APiece::move(std::size_t x, std::size_t y) { _sprite.move(x, y); }

}