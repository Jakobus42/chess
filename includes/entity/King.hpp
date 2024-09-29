#include "APiece.hpp"

namespace entity {

class King: public APiece {
    public:
        King(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t x, std::size_t y) const;
};

}