#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"

#include "include/trax.hpp"

#include <SFML/Graphics.hpp>

/**
 * ---------
 * TRAX TILE
 * ---------
 */

TraxTile::TraxTile() : Tile() {
    auto face = random(0, 1) == 0 ? TraxTileFace::HEADS : TraxTileFace::TAILS;
    properties = std::make_pair(face, std::map<TileEdge, TraxTileEdge>());
    properties.second[TileEdge::LEFT] = face == TraxTileFace::HEADS ? TraxTileEdge::WHITE : TraxTileEdge::BLACK;
    properties.second[TileEdge::TOP] = face == TraxTileFace::HEADS ? TraxTileEdge::BLACK : TraxTileEdge::WHITE;
    properties.second[TileEdge::RIGHT] = TraxTileEdge::WHITE;
    properties.second[TileEdge::BOTTOM] = TraxTileEdge::BLACK;
}

TraxTile::TraxTile(const TraxTile& tile) : Tile(tile) {
    properties = tile.properties;
}

TraxTile::TraxTile(const std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>& properties) : Tile(properties) {
    this->properties = properties;
}

void TraxTile::rotate(const TileRotation& rotation) {
    switch (rotation) {
        case TileRotation::CLOCKWISE:
            properties.second = std::map<TileEdge, TraxTileEdge>({
                { TileEdge::LEFT, properties.second[TileEdge::BOTTOM] },
                { TileEdge::TOP, properties.second[TileEdge::LEFT] },
                { TileEdge::RIGHT, properties.second[TileEdge::TOP] },
                { TileEdge::BOTTOM, properties.second[TileEdge::RIGHT] }
            });
            break;
        case TileRotation::COUNTERCLOCKWISE:
            properties.second = std::map<TileEdge, TraxTileEdge>({
                { TileEdge::LEFT, properties.second[TileEdge::TOP] },
                { TileEdge::TOP, properties.second[TileEdge::RIGHT] },
                { TileEdge::RIGHT, properties.second[TileEdge::BOTTOM] },
                { TileEdge::BOTTOM, properties.second[TileEdge::LEFT] }
            });
            break;
    }
}
void TraxTile::flip(){
    if (properties.first==TraxTileFace::HEADS){
    properties.first=TraxTileFace::TAILS;
    }
    else {
        properties.first=TraxTileFace::HEADS;
    }
}

/**
 * ----------
 * TRAX BOARD
 * ----------
 */

TraxBoard::TraxBoard() : Board(BoardProperties(8, 8)) {
    tiles = std::map<std::pair<int, int>, TraxTile>();
}

TraxBoard::TraxBoard(BoardProperties& properties) : Board(BoardProperties(8, 8)) {
    tiles = std::map<std::pair<int, int>, TraxTile>();
}

bool TraxBoard::canSet(const TraxTile& tile, const std::pair<int, int>& position) const {
   bool canSet = true;
   bool checkempty;
   for (int i = 0; i<8; i++){
        for( int j = 0; j<8;j++){
            auto neighbors = getNeighbors(std::pair<int,int> (i,j));
            if (neighbors.size() != 0){
                checkempty= false; 
            }

        }
    }
    if (checkempty){

     return true; 
    }
    if (tiles.find(position) != tiles.end()) {
        return false;
    }
    auto neighbors = getNeighbors(position);
    if (neighbors.size() == 0) {
        return false;
    }
    for (auto neighbor : neighbors) {
        auto edge = neighbor.first;
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
       
        if (tileProperties.second.at(edge) != neighborTileProperties.second.at(neighborEdge)) {
            canSet = false;
            break;
        
        }
        if (!canSet) {
            break;
        }
    }
    return canSet;
}
bool TraxBoard::isEmpty(){
    for (int i = 0; i<8; i++){
        for( int j = 0; j<8;j++){
            auto neighbors = getNeighbors(std::pair<int,int> (i,j));
            if (neighbors.size() != 0){
                return false; 
            }

        }
    }
    return true;
}

int TraxBoard::handleTile(const TraxTile& tile, const std::pair<int, int>& position) {
//TODO : coups forcés + handleTIle
 if (canSet(tile, position)) {
    this->tiles[position] = tile;
    if  (checkForced( std::pair<int, int>(position.first - 1, position.second))||
        checkForced( std::pair<int, int>(position.first - 1, position.second))||
        checkForced( std::pair<int, int>(position.first - 1, position.second))||
        checkForced( std::pair<int, int>(position.first - 1, position.second))){
            return 1; 
        }
        
    
    }
    return 0; 
}

bool TraxBoard::checkForced( const std::pair<int,int>& position){
    if (tiles.find(position)==tiles.end()){
        return false ;
    }
    auto neighbors = getNeighbors(position);
    if (neighbors.size() == 0|| neighbors.size()==1) {
        return false;
    }
    if (neighbors.size()== 3|| neighbors.size()==4){
        return true; 
    }
    else{
        std::pair<TileEdge, TraxTile> n1 = neighbors.at(0);
        std::pair<TileEdge, TraxTile>n2 = neighbors.at(1);
        if (n1.second.dataStructure().second.at(oppositeEdge(n1.first))==n2.second.dataStructure().second.at(oppositeEdge(n2.first))){
            return true;
        }
    }
    return false; 
}

/**
 * --------------
 * TRAX INTERFACE
 * --------------
 */

TraxInterface::TraxInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) { 
    properties.windowSize = sf::Vector2i(8, 8);
    properties.tileSize = sf::Vector2i(90, 90);
}

void TraxInterface::draw(TraxBoard& board) { 
    if (DEBUG) std::cout << "Drawing board..." << std::endl;
    // Find coordinates to center the board 
    int x = (properties.windowSize.x - (boardProperties.width + 2) * properties.tileSize.x) / 2;
    int y = (properties.windowSize.y - (boardProperties.height + 1) * properties.tileSize.y) / 2;
    drawBoard(board, sf::Vector2i(x, y));
}

void TraxInterface::drawBoard(TraxBoard& board, const sf::Vector2i& position) {
    if (DEBUG) std::cout << "Drawing grid..." << std::endl;
    drawGrid(position);
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto optTile = board.getTile(x, y);
            if (optTile.hasValue()) {
                auto tile = optTile.unwrap();
                if (DEBUG) std::cout << "Drawing tile at (" << x << ", " << y << ")" << std::endl;
                drawTile(tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y), position);
            }
        }
    } 
}

void TraxInterface::drawTile(TraxTile& tile, const sf::Vector2i& position, const sf::Vector2i& offset) {
    sf::Texture facetuile; 
    sf::Texture tailstuile;
    sf::Sprite facetuileS(facetuile);
    sf::Sprite tailstuileS(tailstuile);
    if (!facetuile.loadFromFile("assets/traxTile1.PNG")||(!tailstuile.loadFromFile("assets/traxTile2.PNG"))){
        std::cout<<"erreur image"<<std::endl;

    }
    sf::Vector2u sizeFace = facetuile.getSize();
    sf::Vector2u sizeTails = tailstuile.getSize();
    facetuileS.setOrigin(sizeFace.x/2, sizeFace.y/2);
    tailstuileS.setOrigin(sizeTails.x/2, sizeTails.y/2);
    facetuileS.setPosition(position.x, position.y);
    //j'y comprends rien
}

/**
 * ----
 * TRAX
 * ----properties.windowSize = sf::Vector2i(DOMINOS_BOARD_WIDTH, DOMINOS_BOARD_HEIGHT);
    properties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
 */

Trax::Trax(UserInterfaceProperties properties) : Game(properties, BoardProperties(8, 8)) { 
    currentTile = TraxTile();
    currentPlayer = 0 ; 


}

void Trax::run() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    interface.show(board);
    sf::RenderWindow* window = interface.getWindow();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            handleEvent(event, window);
        }
        window->clear(sf::Color::White);
        interface.draw(board);
        interface.drawTile(currentTile, sf::Vector2i(uiProperties.tileSize.x * boardProperties.width + uiProperties.tileSize.x / 2, uiProperties.tileSize.y / 2));
        interface.render();
        window->display();
    }
}

void Trax::handleEvent(const sf::Event& event, sf::RenderWindow* windowPtr) {
  auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    int boardOffsetX = (uiProperties.windowSize.x - (boardProperties.width + 2) * uiProperties.tileSize.x) / 2;
    int boardOffsetY = (uiProperties.windowSize.y - (boardProperties.height + 1) * uiProperties.tileSize.y) / 2;
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(uiProperties.windowSize.x, uiProperties.windowSize.y));
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (!isGameOver) {
            auto mousePosition = sf::Mouse::getPosition(*windowPtr);
            auto x = (mousePosition.x - boardOffsetX) / uiProperties.tileSize.x;
            auto y = (mousePosition.y - boardOffsetY) / uiProperties.tileSize.y;
            auto position = std::make_pair(x, y);
            if (x < boardProperties.width && y < boardProperties.height) {
                std::cout << "inside tile: " << x << ", " << y << std::endl;
                int result = board.handleTile(currentTile, position);
                if (result!=1) {

                    currentPlayer += 1;
                    currentPlayer %= scoreboard.size();
                    currentTile = TraxTile();                    
                    /*if (gameOver) {
                        std::cout << "Game over!" << std::endl;
                        // TODO: Show scoreboard
                        exit(0);
                    }*/
                }
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (!isGameOver) {
            if (event.key.code == sf::Keyboard::Right) {
                currentTile.rotate(TileRotation::CLOCKWISE);
            } else if (event.key.code == sf::Keyboard::Left) {
                currentTile.rotate(TileRotation::COUNTERCLOCKWISE);
            } else if (event.key.code == sf::Keyboard::Space) {
                currentTile.flip();
            }
        } else {
            if (event.type == sf::Event::KeyPressed) {
                // TODO
            }
        }
    }
}