#include "../includes/game/GameManager.hpp"
#include <iostream>

int main() {
    try {
        game::GameManager game;
        game.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
