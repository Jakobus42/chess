#include "../../includes/game/GameManager.hpp"

namespace game {

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

void getScreenSizeMac() {
    uint32_t displayCount;
    CGGetActiveDisplayList(0, NULL, &displayCount);
    std::cout << "Number of Active Displays: " << displayCount << std::endl;

    CGDirectDisplayID displays[16];
    CGGetActiveDisplayList(16, displays, &displayCount);

    for (uint32_t i = 0; i < displayCount; ++i) {
        CGRect displayBounds = CGDisplayBounds(displays[i]);
        int width = displayBounds.size.width;
        int height = displayBounds.size.height;
        std::cout << "Display " << i + 1 << ": " << width << "x" << height << " pixels" << std::endl;
    }
}


GameManager::GameManager():
_window(sf::VideoMode::getDesktopMode(), "Chess", sf::Style::Default, sf::ContextSettings(0, 0, 16, 2, 0)) { //TODO dont hardcode size
    std::cout << _window.getSize().x << " " << _window.getSize().y << std::endl;
    _window.setFramerateLimit(60);
    getScreenSizeMac();
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