#include "../../includes/game/GameManager.hpp"

namespace game {

GameManager::GameManager():
_window(sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" }) { //TODO dont hardcode size
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
    if (event.type == sf::Event::Closed) {
        _window.close();
    }
}

void GameManager::update() {
    _window.clear();
    _window.display();
}

}