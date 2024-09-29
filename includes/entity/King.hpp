#include "APiece.hpp"

namespace entity {

class King: public APiece {
    public:
        King(const sf::Texture& texture, Color color);
        bool isValidMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, const std::unique_ptr<APiece> board[8][8]) const;
        bool isInCheck(sf::Vector2<std::size_t> kingPosition, const std::unique_ptr<APiece> board[8][8]) const;
};

}