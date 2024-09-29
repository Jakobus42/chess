#include "APiece.hpp"

namespace entity {

class Bishop: public APiece {
    public:
        Bishop(const sf::Texture& texture, Color color);
        bool isValidMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY,
                             const std::unique_ptr<APiece> board[8][8]) const;
};

}