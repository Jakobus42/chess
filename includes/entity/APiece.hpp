#pragma once

#include <SFML/Graphics.hpp>

namespace entity {

enum Color { BLACK, WHITE };

class APiece {
    public:
        APiece(const sf::Sprite& sprite, Color color);
        virtual ~APiece();

        const sf::Sprite& getSprite() const;

        void move(std::size_t x, std::size_t y);

        virtual bool isValidMove(std::size_t x, std::size_t y) = 0;

    private:
        sf::Sprite _sprite;
        Color _color;
};

}