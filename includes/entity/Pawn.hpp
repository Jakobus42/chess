#include "APiece.hpp"

namespace entity {

class Pawn: public APiece {
    public:
        Pawn(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}