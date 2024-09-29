#include "APiece.hpp"

namespace entity {

class Bishop: public APiece {
    public:
        Bishop(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}