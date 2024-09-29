#include "../../includes/game/GameManager.hpp"

//TODO change all to std::pair or sf::Vector2

namespace game {

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

GameManager::GameManager(): 
_currentPlayer(entity::Color::WHITE),
_window(sf::VideoMode::getDesktopMode(), "Chess", sf::Style::Default, sf::ContextSettings(0, 0, 16, 2, 0)),
_board(_window),
_isSelecting(false) {
    _window.setFramerateLimit(60);
}

sf::Vector2<std::size_t> GameManager::pixelToGrid(const sf::Vector2i& pixelPos) const {
    float adjustedX = static_cast<float>(pixelPos.x) - _board.getOffsetX() - _board.getFrameBorder();
    float adjustedY = static_cast<float>(pixelPos.y) - _board.getOffsetY() - _board.getFrameBorder();
    if (adjustedX < 0 || adjustedY < 0 || adjustedX >= BOARD_SIZE * TILE_SIZE || adjustedY >= BOARD_SIZE * TILE_SIZE) {
        return {static_cast<std::size_t>(-1), static_cast<std::size_t>(-1)};
    }
    return {static_cast<std::size_t>(adjustedX / TILE_SIZE), static_cast<std::size_t>(adjustedY / TILE_SIZE)};
}

void GameManager::run() {
    while (_window.isOpen()) {
        for (auto event = sf::Event{}; _window.pollEvent(event);) {
            processEvent(event);
        }
        update();
    }
}

void GameManager::processMouseEvent() {
    sf::Vector2<std::size_t> gridPos = pixelToGrid(sf::Mouse::getPosition(_window));
    if (gridPos.x == static_cast<std::size_t>(-1) || gridPos.y == static_cast<std::size_t>(-1)) {
        _board.clearHighlights();
        _isSelecting = true;
        return;
    }
    if (_isSelecting) {
        _board.clearHighlights();
        _fromPosition = gridPos;
        _board.highlightTile(_fromPosition);
        _board.highlightValidMoves(_fromPosition, _currentPlayer);
        _isSelecting = false;
        return;
    }
    if (_fromPosition == gridPos) {
        _board.clearHighlights();
        _isSelecting = true;
        return;
    }
    _board.clearHighlights();
    if (_board.requestMove(_fromPosition, gridPos, _currentPlayer)) {
        _currentPlayer = (_currentPlayer == entity::Color::WHITE) ? entity::Color::BLACK : entity::Color::WHITE;
    } else {
        _fromPosition = gridPos;
        _board.highlightTile(_fromPosition);
        _board.highlightValidMoves(_fromPosition, _currentPlayer);
    }
}

void GameManager::processEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed: {
            _window.close();
            break;
        }
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Escape) {
                _window.close();
            }
            break;
        }
        case sf::Event::MouseButtonPressed: {
            if(event.mouseButton.button == sf::Mouse::Left) {
                processMouseEvent();
            }
            break;
        }
        default: break;
    }
}

void GameManager::update() {
    _window.clear(sf::Color(70, 100, 40));
    _board.display();
    _window.display();
}

}