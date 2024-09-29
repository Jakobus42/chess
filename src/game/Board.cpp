#include "../../includes/game/Board.hpp"

namespace game {

//TODO add special pawn move

Board::Board(sf::RenderWindow& window): 
_window(window),
_frameBorder(5),
_promotionActive(false),
_halfMoveClock(0) {
    _offsetX = ((window.getSize().x - (BOARD_SIZE * TILE_SIZE + 2 * _frameBorder)) / 2.0f);
    _offsetY = ((window.getSize().y - (BOARD_SIZE * TILE_SIZE + 2 * _frameBorder)) / 2.0f);
    initTextures();
    initPieces(entity::Color::BLACK);
    initPieces(entity::Color::WHITE);
}

int Board::generateTextureKey(Components component, entity::Color color) const {
    return (static_cast<int>(color) << 8) | static_cast<int>(component);
}


void Board::loadTexture(const std::string& path, int key) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)) {
        throw std::runtime_error("Can't load " + path);
    }
    _textures[key] = std::move(texture);
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

bool Board::isPawnPromotion(sf::Vector2<std::size_t> dest, entity::Color currentPlayer) const {
    auto& piece = _board[dest.y][dest.x];
    if (!piece) {
        return false;
    }
    if (dynamic_cast<entity::Pawn*>(piece.get()) == nullptr) {
        return false;
    }
    int promotionRow = (currentPlayer == entity::Color::WHITE) ? 0 : 7;
    return dest.y == promotionRow;
}

bool Board::hasAnyLegalMoves(entity::Color currentPlayer) {
    // Iterate through all pieces of the current player
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            auto& piece = _board[y][x];
            if (piece && piece->getColor() == currentPlayer) {
                // Check all possible destinations
                for (std::size_t destY = 0; destY < BOARD_SIZE; ++destY) {
                    for (std::size_t destX = 0; destX < BOARD_SIZE; ++destX) {
                        sf::Vector2<std::size_t> from{x, y};
                        sf::Vector2<std::size_t> dest{destX, destY};
                        // Check if the move is valid and safe for the king
                        if (piece->isValidMove(from, dest, _board) && isMoveSafeForKing(from, dest, currentPlayer)) {
                            return true; // Found a legal move, not stalemate or checkmate
                        }
                    }
                }
            }
        }
    }

    return false; // No legal moves found
}


bool Board::isCheckmate(entity::Color currentPlayer) {
    auto kingPosition = getPiecePosition<entity::King>(currentPlayer);
    if (!isSquareUnderAttack(kingPosition, currentPlayer)) {
        return false; // The king is not in check, so it's not checkmate.
    }
    return !hasAnyLegalMoves(currentPlayer);
}

bool Board::isStalemate(entity::Color currentPlayer) {
    auto kingPosition = getPiecePosition<entity::King>(currentPlayer);

    if (isSquareUnderAttack(kingPosition, currentPlayer)) {
        return false;
    }
    return !hasAnyLegalMoves(currentPlayer);
}

bool Board::isInsufficientMaterial() const {
    int whiteMaterial = 0;
    int blackMaterial = 0;

    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            auto& piece = _board[y][x];
            if (!piece) {
                continue;
            }
            if(dynamic_cast<entity::Queen*>(piece.get())) {
                return false;
            } else if(dynamic_cast<entity::Knight*>(piece.get())) {
                if (piece->getColor() == entity::Color::WHITE) {
                    whiteMaterial++;
                } else {
                    blackMaterial++;
                }
            }
        }
    }
    return (whiteMaterial <= 1 && blackMaterial <= 1);
}

bool Board::isMoveSafeForKing(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer) {
    auto& movingPiece = _board[from.y][from.x];
    auto& destinationPiece = _board[dest.y][dest.x];

    auto tempPiece = std::move(movingPiece);
    auto backupDest = std::move(destinationPiece);
    _board[dest.y][dest.x] = std::move(tempPiece);
    _board[from.y][from.x] = nullptr;

    auto kingPosition = getPiecePosition<entity::King>(currentPlayer);
    bool isInCheck = isSquareUnderAttack(kingPosition, currentPlayer);

    _board[from.y][from.x] = std::move(_board[dest.y][dest.x]);
    _board[dest.y][dest.x] = std::move(backupDest);

    return !isInCheck;
}

void Board::performCastle(entity::Color currentPlayer, bool isKingside) {
    std::cout << "perfoming castl" << std::endl;
    sf::Vector2<std::size_t> kingPosition = getPiecePosition<entity::King>(currentPlayer);
    sf::Vector2<std::size_t> rookPosition = isKingside ? sf::Vector2<std::size_t>{7, kingPosition.y} : sf::Vector2<std::size_t>{0, kingPosition.y};

    std::size_t kingDestX = isKingside ? kingPosition.x + 2 : kingPosition.x - 2;
    std::size_t rookDestX = isKingside ? kingPosition.x + 1 : kingPosition.x - 1;

    auto kingPiece = std::move(_board[kingPosition.y][kingPosition.x]);
    _board[kingPosition.y][kingDestX] = std::move(kingPiece);
    _board[kingPosition.y][kingPosition.x] = nullptr;

    auto rookPiece = std::move(_board[rookPosition.y][rookPosition.x]);
    _board[rookPosition.y][rookDestX] = std::move(rookPiece);
    _board[rookPosition.y][rookPosition.x] = nullptr;
}

template <typename T>
sf::Vector2<std::size_t> Board::getPiecePosition(entity::Color color) const {
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            const auto& piece = _board[y][x];
            if (piece && piece->getColor() == color) {
                if (T* castedPiece = dynamic_cast<T*>(piece.get())) {
                    return sf::Vector2{x, y};
                }
            }
        }
    }
    throw std::runtime_error("Piece not found on the board");
}

void Board::displayPromotionOptions(entity::Color currentPlayer) {
    sf::Sprite queen(_textures.at(generateTextureKey(Components::QUEEN, currentPlayer)));
    sf::Sprite rook(_textures.at(generateTextureKey(Components::ROOK, currentPlayer)));
    sf::Sprite bishop(_textures.at(generateTextureKey(Components::BISHOP, currentPlayer)));
    sf::Sprite knight(_textures.at(generateTextureKey(Components::KNIGHT, currentPlayer)));

    float textureWidth = queen.getTexture()->getSize().x;
    float promotionX = _window.getSize().x - (_frameBorder + _offsetX) + textureWidth;
    float promotionY = (_frameBorder + _offsetY) + TILE_SIZE / 2;
    float gap = TILE_SIZE * 2;

    queen.setPosition(promotionX, promotionY);
    rook.setPosition(promotionX, promotionY + gap);
    bishop.setPosition(promotionX, promotionY + 2 * gap);
    knight.setPosition(promotionX, promotionY + 3 * gap);
    _window.draw(queen);
    _window.draw(rook);
    _window.draw(bishop);
    _window.draw(knight);
}


void Board::promotePawn(Components selection, entity::Color currentPlayer) {
    std::unique_ptr<entity::APiece> newPiece;

    switch (selection) {
        case Components::QUEEN:
            newPiece = std::make_unique<entity::Queen>(_textures.at(generateTextureKey(Components::QUEEN, currentPlayer)), currentPlayer);
            break;
        case Components::ROOK:
            newPiece = std::make_unique<entity::Rook>(_textures.at(generateTextureKey(Components::ROOK, currentPlayer)), currentPlayer);
            break;
        case Components::BISHOP:
            newPiece = std::make_unique<entity::Bishop>(_textures.at(generateTextureKey(Components::BISHOP, currentPlayer)), currentPlayer);
            break;
        case Components::KNIGHT:
            newPiece = std::make_unique<entity::Knight>(_textures.at(generateTextureKey(Components::KNIGHT, currentPlayer)), currentPlayer);
            break;
        default:
            return;
    }
    _board[_promotionPos.y][_promotionPos.x] = std::move(newPiece);
    _promotionActive = false;
    _promotionPos = {0, 0};
}

void Board::triggerPromotion(sf::Vector2<std::size_t> dest, entity::Color currentPlayer) {
    _promotionActive = true;
    _promotionPos = dest;
}

Components Board::getPromotionSelection(sf::Vector2i mouse) const {

    float textureWidth = _textures.at(generateTextureKey(Components::QUEEN, entity::Color::WHITE)).getSize().x;
    float promotionX = _window.getSize().x - (_frameBorder + _offsetX) + textureWidth;
    float promotionY = (_frameBorder + _offsetY) + TILE_SIZE / 2;
    float gap = TILE_SIZE * 2;

    if (mouse.x >= promotionX && mouse.x <= promotionX + TILE_SIZE) {
        if (mouse.y >= promotionY && mouse.y <= promotionY + TILE_SIZE) {
            return Components::QUEEN;
        } else if (mouse.y >= promotionY + gap && mouse.y <= promotionY + gap + TILE_SIZE) {
            return Components::ROOK;
        } else if (mouse.y >= promotionY + 2 * gap && mouse.y <= promotionY + 2 * gap + TILE_SIZE) {
            return Components::BISHOP;
        } else if (mouse.y >= promotionY + 3 * gap && mouse.y <= promotionY + 3 * gap + TILE_SIZE) {
            return Components::KNIGHT;
        }
    }
    return Components::NONE;
}

bool Board::isSquareUnderAttack(sf::Vector2<std::size_t> square, entity::Color currentPlayer) const {
    entity::Color opponent = (currentPlayer == entity::Color::WHITE) ? entity::Color::BLACK : entity::Color::WHITE;
    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            auto& piece = _board[y][x];
            if (piece && piece->getColor() == opponent) {
                if (piece->isValidMove({x, y}, square, _board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::canCastle(entity::Color currentPlayer, bool isKingside) const {
    std::cout << "can castl?" << std::endl;
    sf::Vector2<std::size_t> kingPosition = getPiecePosition<entity::King>(currentPlayer);
    sf::Vector2<std::size_t> rookPosition = isKingside ? sf::Vector2<std::size_t>{7, kingPosition.y} : sf::Vector2<std::size_t>{0, kingPosition.y};

    auto king = dynamic_cast<entity::King*>(_board[kingPosition.y][kingPosition.x].get());
    auto rook = dynamic_cast<entity::Rook*>(_board[rookPosition.y][rookPosition.x].get());
    if (!king || !rook || king->getHasMoved() || rook->getHasMoved()) {
        return false;
    }
    std::size_t start = std::min(kingPosition.x, rookPosition.x) + 1;
    std::size_t end = std::max(kingPosition.x, rookPosition.x);
    for (std::size_t x = start; x < end; ++x) {
        if (_board[kingPosition.y][x] != nullptr) {
            return false;
        }
    }

    for (std::size_t x = kingPosition.x; x <= rookPosition.x; x++) {
        if (isSquareUnderAttack({x, kingPosition.y}, currentPlayer)) {
            return false;
        }
    }

    return true;
}

bool Board::tryCastle(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer, std::unique_ptr<entity::APiece>& piece) {
    if (dynamic_cast<entity::King*>(piece.get())) {
        if (dest.x == from.x + 2 && canCastle(currentPlayer, true)) {
            performCastle(currentPlayer, true);
            return true;
        }
        if (dest.x == from.x - 2 && canCastle(currentPlayer, false)) {
            performCastle(currentPlayer, false);
            return true;
        }
    }
    return false;
}

bool Board::requestMove(sf::Vector2<std::size_t> from, sf::Vector2<std::size_t> dest, entity::Color currentPlayer) {
    if (from.x >= BOARD_SIZE || from.y >= BOARD_SIZE || dest.x >= BOARD_SIZE || dest.y >= BOARD_SIZE || from == dest) {
        return false;
    }
    auto& movingPiece = _board[from.y][from.x];
    if (!movingPiece || movingPiece->getColor() != currentPlayer) {
        return false;
    }
    if (!isMoveSafeForKing(from, dest, currentPlayer)) {
        return false;
    }
    if(tryCastle(from, dest, currentPlayer, movingPiece)) {
        return true;
    }
    if (!movingPiece->isValidMove(from, dest, _board)) {
        return false;
    }
    auto& destinationPiece = _board[dest.y][dest.x];
    if (destinationPiece && destinationPiece->getColor() == currentPlayer) {
        return false;
    }
    movingPiece->setHasMoved(true);
    auto tempPiece = std::move(movingPiece);
    _board[dest.y][dest.x] = std::move(tempPiece);
    _board[from.y][from.x] = nullptr;
    if(isPawnPromotion(dest, currentPlayer)) {
        triggerPromotion(dest, currentPlayer);
    }
    return true;
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
    if (_board[pos.y][pos.x]->getColor() != currentPlayer) {
        return;
    }

    for (std::size_t y = 0; y < BOARD_SIZE; ++y) {
        for (std::size_t x = 0; x < BOARD_SIZE; ++x) {
            sf::Vector2<std::size_t> dest = {x, y};
            if (_board[pos.y][pos.x]->isValidMove(pos, dest, _board)) {
                if (isMoveSafeForKing(pos, dest, currentPlayer)) {
                    highlightTile(dest);
                }
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

bool Board::isPromotionActive() const { return _promotionActive; }

void Board::resetHalfMoveClock() {
    _halfMoveClock = 0;
}

void Board::incrementHalfMoveClock() {
    _halfMoveClock++;
}

bool Board::isFiftyMoveRule() const {
    return _halfMoveClock >= 100;
}

} // namespace game
