#include "../../includes/game/Board.hpp"
#include "../../includes/game/GameManager.hpp"

namespace game {

Board::Board() {
    if(!_evenTile.texture.loadFromFile("assets/tiles/tile1.png")) {
        throw std::runtime_error("cant load assets/tiles/tile1.png");
    }
    if(!_oddTile.texture.loadFromFile("assets/tiles/tile2.png")) {
               throw std::runtime_error("cant load assets/tiles/tile2.png");
    }
    _evenTile.sprite.setTexture(_evenTile.texture);
    _oddTile.sprite.setTexture(_oddTile.texture);
}

void Board::displayTiles(sf::RenderWindow& window) const {
    const std::size_t boardSize = BOARD_SIZE * _oddTile.texture.getSize().x;
    const float offsetX = (window.getSize().x - boardSize) / 2.0f;
    const float offsetY = (window.getSize().y - boardSize) / 2.0f;

    for (uint8_t y = 0; y < BOARD_SIZE; ++y) {
        for (uint8_t x = 0; x < BOARD_SIZE; ++x) {
            sf::Sprite tile = ((x + y) % 2 == 0) ? _evenTile.sprite : _oddTile.sprite;
            tile.setPosition(x * _oddTile.texture.getSize().x + offsetX, y * _oddTile.texture.getSize().x + offsetY);
            window.draw(tile);
        }
    }
}

void Board::displayFrame(sf::RenderWindow& window) const {
    std::size_t frameSize = BOARD_SIZE * _oddTile.texture.getSize().x + 10;
    const float offsetX = (window.getSize().x - frameSize) / 2.0f;
    const float offsetY = (window.getSize().y - frameSize) / 2.0f;

    sf::RectangleShape frame(sf::Vector2f(frameSize, frameSize));
    frame.setPosition(offsetX, offsetY);
    frame.setFillColor(sf::Color::Black);
    window.draw(frame);
}

void Board::display(sf::RenderWindow& window) const {
    displayFrame(window);
    displayTiles(window);
}


}