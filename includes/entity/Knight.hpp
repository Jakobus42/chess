#include "APiece.hpp"

namespace entity {

class Knight: public APiece {
    public:
        Knight(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}