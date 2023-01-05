#include "include/carcassonne.hpp"

/**
 * ----------------
 * CARCASSONNE TILE
 * ----------------
 */

CarcassonneTile::CarcassonneTile() : Tile() {
    properties = std::map<TileEdge, CarcassonneTileType>();
    this->textureId = 0;
    this->rotationAngle = 0;
    this->grid = std::map<CarcassonneTileGrid, CarcassonneTileType>();
    this->pawns = std::vector<std::pair<CarcassonnePawn, CarcassonneTileGrid>>();
    for (int i = 0; i < 4; i++) {
        properties[(TileEdge) i] = CarcassonneTileType::FIELD;
    }
}

CarcassonneTile::CarcassonneTile(int textureId) : Tile() {
    properties = std::map<TileEdge, CarcassonneTileType>();
    this->textureId = textureId;
    this->rotationAngle = 0;
    this->grid = std::map<CarcassonneTileGrid, CarcassonneTileType>();
    this->pawns = std::vector<std::pair<CarcassonnePawn, CarcassonneTileGrid>>();
}

CarcassonneTile::CarcassonneTile(const CarcassonneTile& tile) : Tile(tile) {
    properties = tile.properties;
    pawns = tile.pawns;
    textureId = tile.textureId;
    rotationAngle = tile.rotationAngle;
}

void CarcassonneTile::rotate(const TileRotation& rotation) {
    switch (rotation) {
        case TileRotation::CLOCKWISE:
            rotationAngle += 90;
            properties = std::map<TileEdge, CarcassonneTileType>({
                { TileEdge::LEFT, properties[TileEdge::BOTTOM] },
                { TileEdge::TOP, properties[TileEdge::LEFT] },
                { TileEdge::RIGHT, properties[TileEdge::TOP] },
                { TileEdge::BOTTOM, properties[TileEdge::RIGHT] }
            });
            // Rotate carcassonne tile grid
            grid = std::map<CarcassonneTileGrid, CarcassonneTileType>({
                { CarcassonneTileGrid::TOP_LEFT, grid[CarcassonneTileGrid::BOTTOM_LEFT] },
                { CarcassonneTileGrid::TOP_CENTER, grid[CarcassonneTileGrid::CENTER_LEFT] },
                { CarcassonneTileGrid::TOP_RIGHT, grid[CarcassonneTileGrid::TOP_LEFT] },
                { CarcassonneTileGrid::CENTER_LEFT, grid[CarcassonneTileGrid::BOTTOM_CENTER] },
                { CarcassonneTileGrid::CENTER_CENTER, grid[CarcassonneTileGrid::CENTER_CENTER] },
                { CarcassonneTileGrid::CENTER_RIGHT, grid[CarcassonneTileGrid::TOP_CENTER] },
                { CarcassonneTileGrid::BOTTOM_LEFT, grid[CarcassonneTileGrid::BOTTOM_RIGHT] },
                { CarcassonneTileGrid::BOTTOM_CENTER, grid[CarcassonneTileGrid::CENTER_RIGHT] },
                { CarcassonneTileGrid::BOTTOM_RIGHT, grid[CarcassonneTileGrid::TOP_RIGHT] },
            });
            break;
        case TileRotation::COUNTERCLOCKWISE:
            // TODO
            break;
    }
}

/**
 * -------------
 * CARCASSONNE BOARD
 * -------------
 */

CarcassonneBoard::CarcassonneBoard(BoardProperties& properties) : Board(properties) {
    // this->setTile(properties.width / 2, properties.height / 2, CarcassonneTile());
}

bool CarcassonneBoard::canSet(const CarcassonneTile& tile, const std::pair<int, int>& position) const {
    bool canSet = true;
    if (tiles.find(position) != tiles.end()) {
        return false;
    }
    auto neighbors = getNeighbors(position);
    if (neighbors.size() == 0) {
        return false;
    }
    for (auto neighbor : neighbors) {
        auto edge = neighbor.first;
        // Print edge with switch
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
        auto edge1 = tileProperties.at(edge);
        auto edge2 = neighborTileProperties.at(neighborEdge);
        if (edge1 != edge2) {
            canSet = false;
            break;
        }
        if (!canSet) {
            break;
        }
    }
    return canSet;
}

int CarcassonneBoard::handleTile(const CarcassonneTile& tile, const std::pair<int, int>& position) {
    return 0;
}
bool CarcassonneBoard::closedCity(const CarcassonneTile& tile, const std::pair<int,int>& position ){
    //Il faut regarder si un coté d'une tuile de la ville n'est pas adjacent à un trou(i.e pas de tuile)
    auto neighbors = getNeighbors(position);
    bool neigh = false; 
    int cout = 0; 
    auto previous = std::vector<std::pair<int,int>>();
    for(auto neighbor : neighbors){
        auto edge = neighbor.first; 
        auto neighborTile= neighbor.second; 
        auto tileProperties = tile.dataStructure(); 
        if (tileProperties[edge]==CarcassonneTileType::CITY){
            neigh = true;
            auto neighborPos = position;
            switch (edge){
                case TileEdge::LEFT : 
                    neighborPos.first = position.first-1; 
                break;
                case TileEdge::TOP : 
                    neighborPos.second = position.second-1;
                    break; 
                case TileEdge::BOTTOM : 
                    neighborPos.second = position.second+1;
                break; 
                case TileEdge::RIGHT : 
                    neighborPos.first = position.first  + 1; 
                break;
            }
            previous.push_back(position);
            cout += closedCityRec(previous, neighborTile, neighborPos); 
        }

    }
    return (neigh&&cout==0);

}

int CarcassonneBoard::closedCityRec(std::vector<std::pair<int,int>> previous,  const CarcassonneTile& Tile, const std::pair<int, int>& position){
    //todo 
}
bool CarcassonneBoard::anyMonastery(const CarcassonneTile& Tile,const std::pair<int, int>& position){ 
    //todo : si une case dans les 9 autour est un monastere on apelle closedMonastery sur le monastere qui verifie juste que autour de lui y'a une tuile placée partout.
    if (tiles.find(position)!=tiles.end()){
        auto t = tiles.find(position)->second;
        if (t.hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
            closedMonastery(t, position); 
        }

    }
    if (tiles.find(std::pair<int,int> (position.first-1,position.second))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first-1,position.second))->second; 
        if (t.hasMonastery()){
            return closedMonastery(t, std::pair<int,int> (position.first-1,position.second)); 
        } 
    }
    if (tiles.find(std::pair<int,int> (position.first-1,position.second+1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first-1,position.second+1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first-1,position.second+1)); 
        }  
    }
    if (tiles.find(std::pair<int,int> (position.first,position.second+1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first,position.second+1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first,position.second+1)); 
        }
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second+1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first+1,position.second+1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first+1,position.second+1)); 
        }  
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first+1,position.second))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first+1,position.second)); 
        }  
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second-1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first+1,position.second-1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first+1,position.second-1)); 
        }  
    }
    if (tiles.find(std::pair<int,int> (position.first,position.second-1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first+1,position.second-1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first+1,position.second-1)); 
        }  
    }
    if (tiles.find(std::pair<int,int> (position.first-1,position.second-1))!=tiles.end()){
        auto t = tiles.find(std::pair<int,int> (position.first-1,position.second-1))->second; 
        if (t.hasMonastery()){
            closedMonastery(t, std::pair<int,int> (position.first-1,position.second-1)); 
        }  
    }
}
bool CarcassonneBoard::closedMonastery(const CarcassonneTile& Tile,const std::pair<int, int>& position){
    //todo : verifier les 8 cases autour.. 
    int eight = 0; 
    if (tiles.find(std::pair<int,int> (position.first-1,position.second))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first-1,position.second+1))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first,position.second+1))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second+1))!=tiles.end()){
       eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first+1,position.second-1))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first,position.second-1))!=tiles.end()){
        eight +=1;
    }
    if (tiles.find(std::pair<int,int> (position.first-1,position.second-1))!=tiles.end()){
       eight +=1;
    }
    //JE SAIS CA AURAIT PU ETRE ECRIT PLUS JOLIMENT MAIS JAI LA GASTRO OK ?
    //TODO rajouter les points du bonhomme dessus + enlever le bonhomme
    return eight==8;
   


}
bool CarcassonneBoard::finishedRoad(const CarcassonneTile& Tile,const std::pair<int, int>& position){
    //todo
}

/**
 * -----------------
 * CARCASSONNE INTERFACE
 * -----------------
 */

CarcassonneInterface::CarcassonneInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) {
    tileSet.loadFromFile("assets/tileset.png");
    tileSet.setSmooth(false);
}

void CarcassonneInterface::draw(CarcassonneBoard& board) {
    if (DEBUG) std::cout << "Drawing board..." << std::endl;
    // Find coordinates to center the board 
    // int x = (properties.windowSize.x - (boardProperties.width + 2) * properties.tileSize.x) / 2;
    // int y = (properties.windowSize.y - (boardProperties.height + 1) * properties.tileSize.y) / 2;
    drawBoard(board);
}

void CarcassonneInterface::drawBoard(CarcassonneBoard& board, const sf::Vector2i& position) {
    if (DEBUG) std::cout << "Drawing grid..." << std::endl;
    drawGrid(position);
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto tile = board.getTile(x, y);
            if (tile != nullptr) {
                if (DEBUG) std::cout << "Drawing tile at (" << x << ", " << y << ")" << std::endl;
                drawTile(*tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y), position);
            }
        }
    } 
}

void CarcassonneInterface::drawTile(CarcassonneTile& tile, const sf::Vector2i& position, const sf::Vector2i& offset) {
    // std::cout << tile.getTextureId() << std::endl;
    sf::Sprite* sprite = new sf::Sprite(tileSet);
    sprite->setTextureRect(sf::IntRect(tile.getTextureId() * CARCASSONNE_TILE_SIZE, 0, CARCASSONNE_TILE_SIZE, CARCASSONNE_TILE_SIZE));
    sprite->setOrigin(CARCASSONNE_TILE_SIZE / 2, CARCASSONNE_TILE_SIZE / 2);
    sprite->setRotation(tile.getRotationAngle());
    sprite->setPosition(position.x + offset.x + properties.tileSize.x / 2, position.y + offset.y + properties.tileSize.y / 2);
    registerForRendering(sprite);
    // std::cout << "tile at " << position.x << ", "   << position.y << " has " << tile.getPawns().size() << " pawns" << std::endl;
    for (auto pawn : tile.getPawns()) {
        // std::cout << "drawing pawn" << std::endl;
        sf::Texture* pawnTexture = new sf::Texture();
        switch (pawn.first.color) {
            case CarcassonnePawnColor::RED:
                pawnTexture->loadFromFile("assets/red.png");
                break;
            case CarcassonnePawnColor::BLUE:
                pawnTexture->loadFromFile("assets/blue.png");
                break;
            case CarcassonnePawnColor::GREEN:
                pawnTexture->loadFromFile("assets/green.png");
                break;
            case CarcassonnePawnColor::YELLOW:
                pawnTexture->loadFromFile("assets/yellow.png");
                break;
        }

        sf::Sprite* pawnSprite = new sf::Sprite(*pawnTexture);
        
        auto tileX = position.x / CARCASSONNE_TILE_SIZE;
        auto tileY = position.y / CARCASSONNE_TILE_SIZE;

        int squareSize = CARCASSONNE_TILE_SIZE / 3;

        sf::Vector2f centerPos;
        switch (pawn.second) {
            case CarcassonneTileGrid::TOP_LEFT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize / 2));
                break;
            case CarcassonneTileGrid::TOP_CENTER:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize / 2));
                break;
            case CarcassonneTileGrid::TOP_RIGHT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize / 2));
                break;
            case CarcassonneTileGrid::CENTER_LEFT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2));
                break;
            case CarcassonneTileGrid::CENTER_CENTER:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2));
                break;
            case CarcassonneTileGrid::CENTER_RIGHT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2));
                break;
            case CarcassonneTileGrid::BOTTOM_LEFT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2));
                break;
            case CarcassonneTileGrid::BOTTOM_CENTER:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2));
                break;
            case CarcassonneTileGrid::BOTTOM_RIGHT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + (squareSize * 2) + (squareSize / 2));
                break;
        }
        pawnSprite->setOrigin(pawnSprite->getTextureRect().width / 2, pawnSprite->getTextureRect().height / 2);
        pawnSprite->setPosition(centerPos);   
        registerForRendering(pawnSprite);
    }
}

/**
 * -------
 * CARCASSONNE
 * -------
 */

Carcassonne::Carcassonne(UserInterfaceProperties properties, BoardProperties boardProperties) : Game(properties, boardProperties) {
    // TODO HANDLE FAILURE
    // Tile 1
    {
        CarcassonneTile* tile1 = new CarcassonneTile(0);
        tile1->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD);
        tile1->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 9; i++) tiles.push_back(tile1);
    }

    // Tile 2
    {
        CarcassonneTile* tile2 = new CarcassonneTile(1);
        tile2->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile2->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile2);
    }

    // Tile 3
    {
        CarcassonneTile* tile3 = new CarcassonneTile(2);
        tile3->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile3->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 2; i++) tiles.push_back(tile3);
    }

    // Tile 4
    {
        CarcassonneTile* tile4 = new CarcassonneTile(3);
        tile4->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::ROAD);
        tile4->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        tiles.push_back(tile4);
    }    

    // Tile 5
    {
        CarcassonneTile* tile5 = new CarcassonneTile(4);
        tile5->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile5->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        tiles.push_back(tile5);
    }

    // Tiile 6
    {
        CarcassonneTile* tile6 = new CarcassonneTile(5);
        tile6->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile6->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile6);   
    }

    // Tile 7
    {
        CarcassonneTile* tile7 = new CarcassonneTile(6);
        tile7->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::CITY, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile7->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile7);
    }

    // Tile 8
    {
        CarcassonneTile* tile8 = new CarcassonneTile(7);
        tile8->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD);
        tile8->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 8; i++) tiles.push_back(tile8);
    }

    // Tile 9
    {
        CarcassonneTile* tile9 = new CarcassonneTile(8);
        tile9->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile9->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, // TODO NOT SURE
                       CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 4; i++) tiles.push_back(tile9);
    }

    // Tile 10
    {
        CarcassonneTile* tile10 = new CarcassonneTile(9);
        tile10->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        tile10->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 5; i++) tiles.push_back(tile10);
    }

    // Tile 11
    {
        CarcassonneTile* tile11 = new CarcassonneTile(10);
        tile11->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile11->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 2; i++) tiles.push_back(tile11);
    }

    // Tile 12
    {
        CarcassonneTile* tile12 = new CarcassonneTile(11);
        tile12->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile12->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile12);
    }

    // Tile 13
    {
        CarcassonneTile* tile13 = new CarcassonneTile(12);
        tile13->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        tile13->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::MONASTERY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 4; i++) tiles.push_back(tile13);
    }

    // Tile 14
    {
        CarcassonneTile* tile14 = new CarcassonneTile(13);
        tile14->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD);
        tile14->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::MONASTERY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 2; i++) tiles.push_back(tile14);
    }

    // Tile 15
    {
        CarcassonneTile* tile15 = new CarcassonneTile(14);
        tile15->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        tile15->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile15);
    }

    // Tile 16
    {
        CarcassonneTile* tile16 = new CarcassonneTile(15);
        tile16->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile16->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY);
        for (int i = 0; i < 2; i++) tiles.push_back(tile16);
    }

    // Tile 17
    {
        CarcassonneTile* tile17 = new CarcassonneTile(16);
        tile17->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::CITY, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        tile17->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 4; i++) tiles.push_back(tile17);
    }

    // Tile 18
    {
        CarcassonneTile* tile18 = new CarcassonneTile(17);
        tile18->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD);
        tile18->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile18);
    }

    // Tile 19
    {
        CarcassonneTile* tile19 = new CarcassonneTile(18);
        tile19->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile19->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY);
        for (int i = 0; i < 1; i++) tiles.push_back(tile19);
    }

    // Tile 20
    {
        CarcassonneTile* tile20 = new CarcassonneTile(19);
        tile20->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::ROAD);
        tile20->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 2; i++) tiles.push_back(tile20);
    }

    // Tile 21
    {
        CarcassonneTile* tile21 = new CarcassonneTile(20);
        tile21->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY);
        tile21->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::CITY);
        for (int i = 0; i < 1; i++) tiles.push_back(tile21);
    }

    // Tile 22
    {
        CarcassonneTile* tile22 = new CarcassonneTile(21);
        tile22->setEdges(CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD, CarcassonneTileType::ROAD);
        tile22->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::CITY, // TODO NOT SURE
                       CarcassonneTileType::ROAD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 1; i++) tiles.push_back(tile22);
    }

    // Tile 23
    {
        CarcassonneTile* tile23 = new CarcassonneTile(22);
        tile23->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        tile23->setGrid(CarcassonneTileType::CITY, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 2; i++) tiles.push_back(tile23);
    }

    // Tile 24
    {
        CarcassonneTile* tile24 = new CarcassonneTile(23);
        tile24->setEdges(CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD);
        tile24->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::CITY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 3; i++) tiles.push_back(tile24);
    }

    CarcassonneTile* randTile = tiles.at(rand() % tiles.size());

    board.setTile(board.getProperties().width / 2, board.getProperties().height / 2, *randTile);

    currentTile = tiles.at(rand() % tiles.size());
    currentPlayer = 0;
}

void Carcassonne::drawGameScreen() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();

    int tileWidth = uiProperties.tileSize.x;
    int tileHeight = uiProperties.tileSize.y;

    int windowWidth = uiProperties.windowSize.x;
    int windowHeight = uiProperties.windowSize.y;

    interface.draw(board);
    // Draw the current player's name and score
    std::string currentPlayerName = scoreboard[currentPlayer].first + (" (" + std::to_string(scoreboard[currentPlayer].second) + "pts)");
    interface.drawText(currentPlayerName, sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, windowHeight / 10), 21);
    // Draw scoreboard
    interface.drawText("Scoreboard", sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, (int) (windowHeight / 1.5f)), 21);
    // Sort scoreboard
    auto scores = std::vector<std::pair<int, int>>();
    for (auto score : scoreboard) {
        scores.push_back(std::make_pair(score.first, score.second.second));
    }
    std::sort(scores.begin(), scores.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });
    for (size_t i = 0; i < scores.size(); i++) {
        auto mapEntry = scoreboard[scores[i].first];
        std::string playerName = mapEntry.first + (" - " + std::to_string(mapEntry.second) + "pts");
        interface.drawText(playerName, sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, (int) (windowHeight / 1.45f) + (int) (windowHeight / 1.45f) / 16 * (i + 1)), 16);
    }
    interface.drawTile(*currentTile, sf::Vector2i(windowWidth - 2 * tileWidth + tileWidth / 2, windowHeight / 12));

    for (int i = 0; i < remainingPawns.at(scoreboard[currentPlayer].first); i++) {
        // std::cout << "drawing pawn" << std::endl;
        sf::Texture* pawnTexture = new sf::Texture();
        auto color = playerColors.at(scoreboard[currentPlayer].first);
        switch (color) {
            case CarcassonnePawnColor::RED:
                pawnTexture->loadFromFile("assets/red.png");
                break;
            case CarcassonnePawnColor::BLUE:
                pawnTexture->loadFromFile("assets/blue.png");
                break;
            case CarcassonnePawnColor::GREEN:
                pawnTexture->loadFromFile("assets/green.png");
                break;
            case CarcassonnePawnColor::YELLOW:
                pawnTexture->loadFromFile("assets/yellow.png");
                break;
        }
        sf::Sprite* pawnSprite = new sf::Sprite(*pawnTexture); 
        pawnSprite->setPosition(sf::Vector2f(windowWidth - tileWidth - 14, windowHeight / 2 + tileHeight + i * tileHeight / 2));
        interface.registerForRendering(pawnSprite);
    }

    std::string instructions;
    if (isPlacingPawn) {
        instructions = "Cliquez sur votre tuile pour placer votre pion, 'ESPACE' pour sauter votre tour"; 
    } else {
        instructions = "Appuyez sur 'R' pour tourner la tuile";
    }
    // Draw instructions at the bottom of the screen
    interface.drawText(instructions, sf::Vector2f(0, windowHeight - 2 * DOMINOS_TILE_SIZE), sf::Vector2f(windowWidth, 2 * DOMINOS_TILE_SIZE), 20);
}

void Carcassonne::drawGameOverScreen() {
    // TODO
}

void Carcassonne::handlePawnPlacement(sf::RenderWindow * windowPtr) {
    if (remainingPawns.at(scoreboard[currentPlayer].first) == 0) {
        isPlacingPawn = false;
        return;
    }
    
    CarcassonnePawn newPawn;
    newPawn.color = playerColors.at(scoreboard.at(currentPlayer).first);

    sf::RectangleShape grid[9];
    for (int dy = 0; dy < 3; ++dy) {
        for (int dx = 0; dx < 3; ++dx) {
            int index = dy * 3 + dx;
            grid[index].setSize(sf::Vector2f(CARCASSONNE_TILE_SIZE / 3, CARCASSONNE_TILE_SIZE / 3));
            grid[index].setPosition((currentTileX * CARCASSONNE_TILE_SIZE) + (dx * CARCASSONNE_TILE_SIZE / 3), (currentTileY * CARCASSONNE_TILE_SIZE) + (dy * CARCASSONNE_TILE_SIZE / 3));
        }
    }

    auto mousePosition = sf::Mouse::getPosition(*windowPtr);

    bool done = false;

    for (int i = 0; i < 9; ++i) {
        if (grid[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            std::cout << "in " << i << std::endl;
            switch (i) {
                case 0:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::TOP_LEFT);
                    break;
                case 1:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::TOP_CENTER);
                    break;
                case 2:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::TOP_RIGHT);
                    break;
                case 3:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::CENTER_LEFT);
                    break;
                case 4:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::CENTER_CENTER);
                    break;
                case 5:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::CENTER_RIGHT);
                    break;
                case 6:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::BOTTOM_LEFT);
                    break;
                case 7:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::BOTTOM_CENTER);
                    break;
                case 8:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::BOTTOM_RIGHT);
                    break;
                }
            done = true;
        }
    }
    if (done) {
        remainingPawns.at(scoreboard[currentPlayer].first) -= 1;
        tiles.erase(std::remove(tiles.begin(), tiles.end(), currentTile), tiles.end());
        currentTile = tiles.at(rand() % tiles.size());
        isPlacingPawn = false;
        currentPlayer += 1;
        currentPlayer %= scoreboard.size();
    }
}

void Carcassonne::handleEvent(const sf::Event & event, sf::RenderWindow * windowPtr) {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    int tileWidth = uiProperties.tileSize.x;
    int tileHeight = uiProperties.tileSize.y;
    int windowWidth = uiProperties.windowSize.x;
    int windowHeight = uiProperties.windowSize.y;
    int boardOffsetX = (uiProperties.windowSize.x - (boardProperties.width + 2) * tileWidth) / 2;
    int boardOffsetY = (uiProperties.windowSize.y - (boardProperties.height + 1) * tileHeight) / 2;
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(windowWidth, windowHeight));
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (!isGameOver) {
            auto mousePosition = sf::Mouse::getPosition(*windowPtr);
            auto x = (mousePosition.x - boardOffsetX) / tileWidth;
            auto y = (mousePosition.y - boardOffsetY) / tileHeight;
            auto position = std::make_pair(x, y);
            if (x < boardProperties.width && y < boardProperties.height) {
                if (isPlacingPawn) {
                    handlePawnPlacement(windowPtr);
                } else if (board.canSet(*currentTile, position)) {
                    board.setTile(x, y, *currentTile);
                    currentTileX = x;
                    currentTileY = y;
                    isPlacingPawn = true;
                }
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (!isGameOver) {
            if (isPlacingPawn) {
                if (event.key.code == sf::Keyboard::Space) {
                    tiles.erase(std::remove(tiles.begin(), tiles.end(), currentTile), tiles.end());
                    currentTile = tiles.at(rand() % tiles.size());
                    isPlacingPawn = false;
                    currentPlayer += 1;
                    currentPlayer %= scoreboard.size();
                }
            } else {
                if (event.key.code == sf::Keyboard::R) {
                    currentTile->rotate(TileRotation::CLOCKWISE);
                }
            }
        } else {
            if (event.type == sf::Event::KeyPressed) {
                // TODO
            }
        }
    }
}