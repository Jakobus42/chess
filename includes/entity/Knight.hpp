#include "APiece.hpp"

namespace entity {

class Knight: public APiece {
    public:
        Knight(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY,
                             const std::unique_ptr<APiece> board[8][8]) const;
};

}