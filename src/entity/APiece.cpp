#include "../../includes/entity/APiece.hpp"

namespace entity {

APiece::APiece(const sf::Texture& texture, Color color):
_texture(texture),
_color(color) {
    _sprite.setTexture(texture);
}

APiece::~APiece() {}

sf::Sprite& APiece::getSprite() { return _sprite; }

}