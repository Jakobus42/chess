#include "../../includes/game/Board.hpp"

namespace game {

Board::Board() {
    initTextures();
    initTiles();
    initPieces(entity::Color::BLACK);
    initPieces(entity::Color::WHITE);
}

void Board::loadTexture(const std::string& path, Components component) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)) {
        throw std::runtime_error("cant load " + path);
    }
    _textures[component] = texture;
}

void Board::initTextures() {
    loadTexture("assets/tiles/tile1.png", Components::EVEN_TILE);
    loadTexture("assets/tiles/tile2.png", Components::ODD_TILE);
    loadTexture("assets/pieces/b_pawn.png", Components::PAWN);
    loadTexture("assets/pieces/w_pawn.png", Components::PAWN);
}

void Board::initTiles() {
    _evenTile.texture = _textures.at(Components::EVEN_TILE);
    _oddTile.texture = _textures.at(Components::ODD_TILE);
    _evenTile.sprite.setTexture(_evenTile.texture);
    _oddTile.sprite.setTexture(_oddTile.texture);   
}

void Board::initPieces(entity::Color color) {
    std::size_t pawnRow = (color == entity::Color::WHITE) ? 6 : 1;
    std::size_t backRow = (color == entity::Color::WHITE) ? 7 : 0;

    for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
        _board[pawnRow][x] = std::make_unique<entity::Pawn>(
            _textures.at(Components::PAWN), color);
    }
    std::vector<std::unique_ptr<entity::APiece>> backRowPieces;
    // backRowPieces.push_back(std::make_unique<entity::Rook>(_textures.at(Components::ROOK), color));
    // backRowPieces.push_back(std::make_unique<entity::Knight>(_textures.at(Components::KNIGHT), color));
    // backRowPieces.push_back(std::make_unique<entity::Bishop>(_textures.at(Components::BISHOP), color));
    // backRowPieces.push_back(std::make_unique<entity::Queen>(_textures.at(Components::QUEEN), color));
    // backRowPieces.push_back(std::make_unique<entity::King>(_textures.at(Components::KING), color));
    // backRowPieces.push_back(std::make_unique<entity::Bishop>(_textures.at(Components::BISHOP), color));
    // backRowPieces.push_back(std::make_unique<entity::Knight>(_textures.at(Components::KNIGHT), color));
    // backRowPieces.push_back(std::make_unique<entity::Rook>(_textures.at(Components::ROOK), color));
    // for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
    //     std::size_t posX = (color == entity::Color::WHITE) ? x : BOARD_SIZE - 1 - x;
    //     _board[backRow][posX] = std::move(backRowPieces[x]);
    // }
}

void Board::displayBoard(sf::RenderWindow& window) const {
    const std::size_t boardSize = BOARD_SIZE * _oddTile.texture.getSize().x;
    const float offsetX = (window.getSize().x - boardSize) / 2.0f;
    const float offsetY = (window.getSize().y - boardSize) / 2.0f;

    for (uint8_t y = 0; y < BOARD_SIZE; ++y) {
        for (uint8_t x = 0; x < BOARD_SIZE; ++x) {
            sf::Sprite tile = ((x + y) % 2 == 0) ? _evenTile.sprite : _oddTile.sprite;
            entity::APiece* piece = _board[y][x].get();
            tile.setPosition(x * _oddTile.texture.getSize().x + offsetX, y * _oddTile.texture.getSize().x + offsetY);
            window.draw(tile);
            if(piece) {
                std::size_t newPieceX = (x * _oddTile.texture.getSize().x) + (_oddTile.texture.getSize().x / 2)  + offsetX;
                std::size_t newPieceY = (y *  _oddTile.texture.getSize().y) + (_oddTile.texture.getSize().y / 2)  + offsetY;
                if(piece->getColor() == entity::Color::WHITE) {
                    piece->getSprite().setColor(sf::Color::White);
                }
                piece->getSprite().setOrigin(piece->getSprite().getTexture()->getSize().x / 2, piece->getSprite().getTexture()->getSize().y / 2);
                piece->getSprite().setScale(0.9, 0.9);
                piece->getSprite().setPosition(newPieceX, newPieceY);
                window.draw(piece->getSprite());
            }
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
    displayBoard(window);
}

}