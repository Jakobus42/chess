#include "../../includes/game/GameManager.hpp"

//TODO change all to std::pair or sf::Vector2

namespace game {

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

GameManager::GameManager(): 
_currentPlayer(entity::Color::WHITE),
_window(sf::VideoMode::getDesktopMode(), "Chess", sf::Style::Default, sf::ContextSettings(0, 0, 16, 2, 0)) {
    _window.setFramerateLimit(60);
}

std::pair<std::size_t, std::size_t> GameManager::pixelToGrid(const sf::Vector2i& pixelPos) const {
    std::size_t gridX = static_cast<std::size_t>(pixelPos.x / TILE_SIZE);
    std::size_t gridY = static_cast<std::size_t>(pixelPos.y / TILE_SIZE);

    if (gridX >= BOARD_SIZE) gridX = BOARD_SIZE - 1;
    if (gridY >= BOARD_SIZE) gridY = BOARD_SIZE - 1;
    return {gridX, gridY};
}

void GameManager::run() {
    while (_window.isOpen()) {
        for (auto event = sf::Event{}; _window.pollEvent(event);) {
            processEvent(event);
        }
        update();
    }
}

void GameManager::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed ||
       (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        _window.close();
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        std::pair<std::size_t, std::size_t> gridPos = pixelToGrid(mousePos);
        std::cout << gridPos.first << " " << gridPos.second << std::endl;
        if (_isSelectingFrom) {
            _fromPosition = gridPos;
            _isSelectingFrom = false;
            std::cout << _fromPosition->first << " " << _fromPosition->second << std::endl;

            //TODO highlight
        } else {
            if (_fromPosition.has_value()) {
                bool moveSuccess = _board.requestMove(
                    _fromPosition->first,
                    _fromPosition->second,
                    gridPos.first,
                    gridPos.second,
                    _currentPlayer
                );
                if (moveSuccess) {
                    _currentPlayer = (_currentPlayer == entity::Color::WHITE) ? entity::Color::BLACK : entity::Color::WHITE;
                }
                _fromPosition = std::nullopt;
                _isSelectingFrom = true;
            }
        }
    }
}

void GameManager::update() {
    _window.clear(sf::Color(70, 100, 40));
    _board.display(_window);
    _window.display();
}

}