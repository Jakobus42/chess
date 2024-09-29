#include "../../includes/game/Board.hpp"

namespace game {

Board::Board() {
    initTextures();
    initPieces(entity::Color::BLACK);
    initPieces(entity::Color::WHITE);
}

void Board::loadTexture(const std::string& path, int key) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)) {
        throw std::runtime_error("Can't load " + path);
    }
    _textures[key] = std::move(texture);
}

bool Board::requestMove(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY, entity::Color currentPlayer) {
    std::cout << fromX << " " << fromY << std::endl;
    std::cout << toX << " " << toY << std::endl;
    if(fromX >= BOARD_SIZE || fromY >= BOARD_SIZE || toX >= BOARD_SIZE || toY >= BOARD_SIZE) {
        return false;
    }
    auto& movingPiece = _board[fromY][fromX];
    if(!movingPiece) {
        return false;
    }
    if(movingPiece->getColor() != currentPlayer) {
        return false;
    }
    if(!movingPiece->isValidMove(fromX, fromY, toX, toY, _board)) {
        return false;
    }
    auto& destinationPiece = _board[toY][toX];
    if(destinationPiece && destinationPiece->getColor() == currentPlayer) {
        return false;
    }
    _board[toY][toX] = std::move(movingPiece);
    _board[fromY][fromX] = nullptr;
    return true;
}

int Board::generateTextureKey(Components component, entity::Color color) const {
    return (static_cast<int>(color) << 8) | static_cast<int>(component);
}

void Board::initTextures() {
    loadTexture("assets/tiles/tile1.png", generateTextureKey(Components::EVEN_TILE, entity::Color::NONE));
    loadTexture("assets/tiles/tile2.png", generateTextureKey(Components::ODD_TILE, entity::Color::NONE));

    loadTexture("assets/pieces/b_pawn.png", generateTextureKey(Components::PAWN, entity::Color::BLACK));
    loadTexture("assets/pieces/b_knight.png", generateTextureKey(Components::KNIGHT, entity::Color::BLACK));
    loadTexture("assets/pieces/b_bishop.png", generateTextureKey(Components::BISHOP, entity::Color::BLACK));
    loadTexture("assets/pieces/b_rook.png",  generateTextureKey(Components::ROOK, entity::Color::BLACK));
    loadTexture("assets/pieces/b_queen.png", generateTextureKey(Components::QUEEN, entity::Color::BLACK));
    loadTexture("assets/pieces/b_king.png",  generateTextureKey(Components::KING, entity::Color::BLACK));

    loadTexture("assets/pieces/w_pawn.png", generateTextureKey(Components::PAWN, entity::Color::WHITE));
    loadTexture("assets/pieces/w_knight.png", generateTextureKey(Components::KNIGHT, entity::Color::WHITE));
    loadTexture("assets/pieces/w_bishop.png", generateTextureKey(Components::BISHOP, entity::Color::WHITE));
    loadTexture("assets/pieces/w_rook.png",  generateTextureKey(Components::ROOK, entity::Color::WHITE));
    loadTexture("assets/pieces/w_queen.png", generateTextureKey(Components::QUEEN, entity::Color::WHITE));
    loadTexture("assets/pieces/w_king.png",  generateTextureKey(Components::KING, entity::Color::WHITE));
}

void Board::initPieces(entity::Color color) {
    std::size_t pawnRow = (color == entity::Color::WHITE) ? 6 : 1;
    std::size_t backRow = (color == entity::Color::WHITE) ? 7 : 0;

    for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
        _board[pawnRow][x] = std::make_unique<entity::Pawn>(
            _textures.at(generateTextureKey(Components::PAWN, color)), color);
    }

    std::vector<std::unique_ptr<entity::APiece>> backRowPieces;
    backRowPieces.push_back(std::make_unique<entity::Rook>(_textures.at(generateTextureKey(Components::ROOK, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Knight>(_textures.at(generateTextureKey(Components::KNIGHT, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Bishop>(_textures.at(generateTextureKey(Components::BISHOP, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Queen>(_textures.at(generateTextureKey(Components::QUEEN, color)), color));
    backRowPieces.push_back(std::make_unique<entity::King>(_textures.at(generateTextureKey(Components::KING, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Bishop>(_textures.at(generateTextureKey(Components::BISHOP, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Knight>(_textures.at(generateTextureKey(Components::KNIGHT, color)), color));
    backRowPieces.push_back(std::make_unique<entity::Rook>(_textures.at(generateTextureKey(Components::ROOK, color)), color));

    for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
        std::size_t posX = x;
        _board[backRow][posX] = std::move(backRowPieces[x]);
    }
}

void Board::displayBoard(sf::RenderWindow& window, float offsetX, float offsetY, float frameBorder) const {
    for (uint8_t y = 0; y < BOARD_SIZE; ++y) {
        for (uint8_t x = 0; x < BOARD_SIZE; ++x) {
            sf::Texture tileTex = ((x + y) % 2 == 0) ? _textures.at(generateTextureKey(Components::EVEN_TILE, entity::Color::NONE)) : _textures.at(generateTextureKey(Components::ODD_TILE, entity::Color::NONE));
            sf::Sprite tile(tileTex);
            entity::APiece* piece = _board[y][x].get();
            tile.setPosition(x * TILE_SIZE + offsetX + frameBorder, y * TILE_SIZE + offsetY + frameBorder);
            window.draw(tile);
            if(piece) {
                float newPieceX = x * TILE_SIZE + (TILE_SIZE / 2.0f) + offsetX + frameBorder;
                float newPieceY = y * TILE_SIZE + (TILE_SIZE / 2.0f) + offsetY + frameBorder;
                if(piece->getColor() == entity::Color::WHITE) {
                    piece->getSprite().setColor(sf::Color::White);
                }
                piece->getSprite().setOrigin(piece->getSprite().getTexture()->getSize().x / 2.0f, piece->getSprite().getTexture()->getSize().y / 2.0f);
                piece->getSprite().setScale(0.9f, 0.9f);
                piece->getSprite().setPosition(newPieceX, newPieceY);
                window.draw(piece->getSprite());
            }
        }
    }
}

void Board::displayFrame(sf::RenderWindow& window, float offsetX, float offsetY, std::size_t frameSize) const {
    sf::RectangleShape frame(sf::Vector2f(static_cast<float>(frameSize), static_cast<float>(frameSize)));
    frame.setPosition(offsetX, offsetY);
    frame.setFillColor(sf::Color::Black);
    window.draw(frame);
}

void Board::display(sf::RenderWindow& window) const {
    const float frameBorder = 5.0f;
    const std::size_t boardSize = BOARD_SIZE * TILE_SIZE;
    const std::size_t frameSize = boardSize + 2 * frameBorder;
    const float offsetX = (window.getSize().x - frameSize) / 2.0f;
    const float offsetY = (window.getSize().y - frameSize) / 2.0f;
 
    displayFrame(window, offsetX, offsetY, frameSize);
    displayBoard(window, offsetX, offsetY, frameBorder);
}

} // namespace game
