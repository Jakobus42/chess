#include "APiece.hpp"

namespace entity {

class Rook: public APiece {
    public:
        Rook(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}