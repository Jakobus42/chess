#include "APiece.hpp"

namespace entity {

class Queen: public APiece {
    public:
        Queen(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}