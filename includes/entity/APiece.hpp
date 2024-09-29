#pragma once

#include <SFML/Graphics.hpp>

namespace entity {

enum Color { BLACK, WHITE };

class APiece {
    public:
        APiece(const sf::Texture& texture, Color color);
        virtual ~APiece();

        sf::Sprite& getSprite();
        Color getColor();
        virtual bool isValidMove(std::size_t x, std::size_t y) const = 0;

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        Color _color;
};

}