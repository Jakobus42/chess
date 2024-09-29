#include "../includes/game/GameManager.hpp"
#include <iostream>

int main() {
    try {
        game::GameManager game;
        std::cout << sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height;
        game.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
