#include "../../includes/game/Board.hpp"

namespace game {

Board::Board(sf::Sprite& evenTile, sf::Sprite& oddTile): 
_evenTile(evenTile),
_oddTile(oddTile) {
    //TODO board
}

void Board::display(sf::RenderWindow& window) const {
    for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
        for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
            if ((x + y) % 2 == 0) {
                window.draw(_evenTile);
            } else {
                window.draw(_oddTile);
            }
        }
    }
}

}