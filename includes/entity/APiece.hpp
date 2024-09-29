#pragma once

#include <SFML/Graphics.hpp>

namespace entity {

enum Color { NONE = 0, BLACK, WHITE };

class APiece {
    public:
        APiece(const sf::Texture& texture, Color color);
        virtual ~APiece();

        sf::Sprite& getSprite();
        Color getColor();
         virtual bool isValidMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY,
                             const std::unique_ptr<APiece> board[8][8]) const = 0;

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        Color _color;
};

}