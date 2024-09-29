#include "APiece.hpp"

namespace entity {

class Queen: public APiece {
    public:
        Queen(const sf::Texture& texture, Color color);
        bool isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const;
};

}