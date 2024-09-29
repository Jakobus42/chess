#include "../../includes/game/GameManager.hpp"

namespace game {

GameManager::GameManager():
_window(sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT}, "Chess" }) { //TODO dont hardcode size
    _window.setFramerateLimit(60);
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
    if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
        _window.close();
    }
}

void GameManager::update() {
    _window.clear(sf::Color(70, 100, 40));
    _board.display(_window);
    _window.display();
}

}