#include "../../includes/game/Board.hpp"

namespace game {

//TODO tiles differen colors for selection

Board::Board(sf::RenderWindow& window): 
_window(window),
_frameBorder(5) {
    _offsetX = ((window.getSize().x - (BOARD_SIZE * TILE_SIZE + 2 * _frameBorder)) / 2.0f);
    _offsetY = ((window.getSize().y - (BOARD_SIZE * TILE_SIZE + 2 * _frameBorder)) / 2.0f);
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

bool Board::requestMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer) {
    if(from.x >= BOARD_SIZE || from.y >= BOARD_SIZE || dest.x >= BOARD_SIZE || dest.y >= BOARD_SIZE) {
        return false;
    }
    if(from == dest) {
        return false;
    }
    auto& movingPiece = _board[from.y][from.x];
    if(!movingPiece) {
        return false;
    }
    if(movingPiece->getColor() != currentPlayer) {
        return false;
    }
    if(!movingPiece->isValidMove(from, dest, _board)) {
        return false;
    }
    auto& destinationPiece = _board[dest.y][dest.x];
    if(destinationPiece && destinationPiece->getColor() == currentPlayer) {
        return false;
    }
    _board[dest.y][dest.x] = std::move(movingPiece);
    _board[from.y][from.x] = nullptr;
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

template <typename T>
const std::unique_ptr<entity::APiece>& Board::getPiece(entity::Color color) const {
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            if(const auto& piece = dynamic_cast<T>(_board[y][x])) {
                return piece;
            }
        }
    }
}

void Board::highlightTile(sf::Vector2<std::size_t> tile) {
    for (const auto& highlighted : _highlightedTiles) {
        if (highlighted == tile) {
            return;
        }
    }
    _highlightedTiles.push_back(tile);
}

void Board::clearHighlights() {
    _highlightedTiles.clear();
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

void Board::displayFrame(std::size_t frameSize) const {
    sf::RectangleShape frame(sf::Vector2f(static_cast<float>(frameSize), static_cast<float>(frameSize)));
    frame.setPosition(_offsetX, _offsetY);
    frame.setFillColor(sf::Color::Black);
    _window.draw(frame);
}

void Board::highlightValidMoves(sf::Vector2<std::size_t> pos, entity::Color currentPlayer) {
    if (pos.x >= BOARD_SIZE || pos.y >= BOARD_SIZE) {
        return;
    }
    if (!_board[pos.y][pos.x]) {
        return;
    }
    if(_board[pos.y][pos.x].get()->getColor() != currentPlayer) {
        return ;
    }
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            if (_board[pos.y][pos.x]->isValidMove(pos, {x, y}, _board)) {
                highlightTile(sf::Vector2<std::size_t>(x, y));
            }
        }
    }
}

void Board::displayHighlightedTiles() const {
    sf::RectangleShape highlightShape(sf::Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)));
    highlightShape.setFillColor(sf::Color(255, 255, 0, 100));

    for (const auto& tile : _highlightedTiles) {
        float posX = static_cast<float>(tile.x * TILE_SIZE) + _offsetX + _frameBorder;
        float posY = static_cast<float>(tile.y * TILE_SIZE) + _offsetY + _frameBorder;
        highlightShape.setPosition(posX, posY);
        _window.draw(highlightShape);
    }
}

void Board::displayBoard() const {
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            sf::Texture tileTex = ((x + y) % 2 == 0) ? _textures.at(generateTextureKey(Components::EVEN_TILE, entity::Color::NONE)) 
            : _textures.at(generateTextureKey(Components::ODD_TILE, entity::Color::NONE));
            sf::Sprite tile(tileTex);
            entity::APiece* piece = _board[y][x].get();
            tile.setPosition(x * TILE_SIZE + _offsetX + _frameBorder, y * TILE_SIZE + _offsetY + _frameBorder);
            _window.draw(tile);
            if(piece) {
                float newPieceX = x * TILE_SIZE + (TILE_SIZE / 2.0f) + _offsetX + _frameBorder;
                float newPieceY = y * TILE_SIZE + (TILE_SIZE / 2.0f) + _offsetY + _frameBorder;
                if(piece->getColor() == entity::Color::WHITE) {
                    piece->getSprite().setColor(sf::Color::White);
                }
                piece->getSprite().setOrigin(piece->getSprite().getTexture()->getSize().x / 2.0f, 
                                            piece->getSprite().getTexture()->getSize().y / 2.0f);
                piece->getSprite().setScale(0.9f, 0.9f);
                piece->getSprite().setPosition(newPieceX, newPieceY);
                _window.draw(piece->getSprite());
            }
        }
    }
}

void Board::display() const {
    const std::size_t boardSize = BOARD_SIZE * TILE_SIZE;
    const std::size_t frameSize = boardSize + 2 * _frameBorder;
    displayFrame(frameSize);
    displayBoard();
    displayHighlightedTiles();
}

float Board::getOffsetX() const {
    return _offsetX;
}

float Board::getOffsetY() const {
    return _offsetY;
}

float Board::getFrameBorder() const {
    return _frameBorder;
}

} // namespace game
