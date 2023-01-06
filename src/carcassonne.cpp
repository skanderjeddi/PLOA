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
                { CarcassonneTileGrid::TOP_CENTER, grid[CarcassonneTileGrid::MIDDLE_LEFT] },
                { CarcassonneTileGrid::TOP_RIGHT, grid[CarcassonneTileGrid::TOP_LEFT] },
                { CarcassonneTileGrid::MIDDLE_LEFT, grid[CarcassonneTileGrid::BOTTOM_CENTER] },
                { CarcassonneTileGrid::MIDDLE_CENTER, grid[CarcassonneTileGrid::MIDDLE_CENTER] },
                { CarcassonneTileGrid::MIDDLE_RIGHT, grid[CarcassonneTileGrid::TOP_CENTER] },
                { CarcassonneTileGrid::BOTTOM_LEFT, grid[CarcassonneTileGrid::BOTTOM_RIGHT] },
                { CarcassonneTileGrid::BOTTOM_CENTER, grid[CarcassonneTileGrid::MIDDLE_RIGHT] },
                { CarcassonneTileGrid::BOTTOM_RIGHT, grid[CarcassonneTileGrid::TOP_RIGHT] },
            });
            break;
        case TileRotation::COUNTERCLOCKWISE:
            // TODO
            break;
    }
}

void CarcassonneTile::setEdges(CarcassonneTileType left, CarcassonneTileType top, CarcassonneTileType right, CarcassonneTileType bottom) {
    properties[TileEdge::LEFT] = left;
    properties[TileEdge::TOP] = top;
    properties[TileEdge::RIGHT] = right;
    properties[TileEdge::BOTTOM] = bottom;
}

void CarcassonneTile::setGrid(CarcassonneTileType tc, CarcassonneTileType tl, CarcassonneTileType tr, CarcassonneTileType cl, CarcassonneTileType cc, CarcassonneTileType cr, CarcassonneTileType bl, CarcassonneTileType bc, CarcassonneTileType br) {
    grid[CarcassonneTileGrid::TOP_CENTER] = tc;
    grid[CarcassonneTileGrid::TOP_LEFT] = tl;
    grid[CarcassonneTileGrid::TOP_RIGHT] = tr;
    grid[CarcassonneTileGrid::MIDDLE_LEFT] = cl;
    grid[CarcassonneTileGrid::MIDDLE_CENTER] = cc;
    grid[CarcassonneTileGrid::MIDDLE_RIGHT] = cr;
    grid[CarcassonneTileGrid::BOTTOM_LEFT] = bl;
    grid[CarcassonneTileGrid::BOTTOM_CENTER] = bc;
    grid[CarcassonneTileGrid::BOTTOM_RIGHT] = br;
}

void CarcassonneTile::setPawn(CarcassonnePawn p, CarcassonneTileGrid tg) {
    switch (grid[tg]) {
        case CarcassonneTileType::CITY:
            p.type = CarcassonnePawnType::KNIGHT;
            break;
        case CarcassonneTileType::ROAD:
            p.type = CarcassonnePawnType::THIEF;
            break;
        case CarcassonneTileType::FIELD:
            p.type = CarcassonnePawnType::PEASANT;
            break;
        case CarcassonneTileType::MONASTERY:
            p.type = CarcassonnePawnType::MONK;
            break;
        }
        pawns.push_back(std::make_pair(p, tg));
}

bool CarcassonneTile::hasCenter() const  {
    if (grid.count(CarcassonneTileGrid::MIDDLE_CENTER)){
        return true;
    } else {        
        return false; 
    }
}

bool CarcassonneTile::hasMonastery() const {
    return grid.at(CarcassonneTileGrid::MIDDLE_CENTER) == CarcassonneTileType::MONASTERY; 
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
bool CarcassonneBoard::isCityClosed(const CarcassonneTile& tile, const std::pair<int,int>& position ){
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
            cout += isCityClosedRecursive(previous, neighborTile, neighborPos); 
        }

    }
    return (neigh&&cout==0);

}

int CarcassonneBoard::isCityClosedRecursive(std::vector<std::pair<int,int>> previous,  const CarcassonneTile& Tile, const std::pair<int, int>& position) {
    /*auto neighbors = getNeighbors(position);
    for (auto neighbor : neighbors){
        auto edge = neighbor.first; 
        auto neighborTile= neighbor.second; 
        auto tileProperties = tile.dataStructure(); 
        if (tileProperties[TileEdge::LEFT]==CarcassonneTileType::CITY){
            if(neighbor.first==TileEdge::LEFT){
                neighborPos.first = position.first-1; 
                for (auto paire : previous){
                    if (neighborPos==paire){
                    present = true; 
                    } 
                }
                if (!present){
                    previous.push_back(position); 
                    closedCityRec(previous, neighborTile, neighborPos);
                }
            }
        }
        
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
        bool present = false; 
       
        
    }*/
    //todo 
    return 0;
}

bool CarcassonneBoard::hasMonastery(const CarcassonneTile& tile, const std::pair<int, int>& position, std::map<int, std::pair<std::string, int>> &scoreBoard, std::map<std::string, CarcassonnePawnColor> playerColors){ 
    std::cout<<"entree"<<std::endl;
    bool b = false; 
    //todo : si une case dans les 9 autour est un monastere on apelle closedMonastery sur le monastere qui verifie juste que autour de lui y'a une tuile placée partout.
    auto t = getTile(position.first,position.second);
    if (t != nullptr) {
        t->hasCenter(); 
        if (t->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
        // if (true){
            std::cout<<"onyva"<<std::endl;
            std::cout<<"monastere uwu"<<std::endl;
            b = isMonasteryClosed(tile, position, scoreBoard, playerColors); 
            
        }
    }
    
    if ((tiles.count(std::pair<int,int> (position.first-1,position.second)))&&(position.first-1 >=0)&&tiles.find(std::pair<int,int> (position.first-1,position.second))!=tiles.end()){
        std::cout<<"monastere uwu"<<std::endl;
        // changer ça part auto t = getTile(position.first-1,position.second);
        // if (t != nullptr) { 
        auto o = getTile(position.first-1,position.second);
         if (o!=nullptr){
            
            if (t->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                std::cout<<"onyva"<<std::endl;
               b =  isMonasteryClosed(*o, std::pair<int,int> (position.first-1,position.second), scoreBoard, playerColors); 
                if (b){
                    return b ;
                }   
            }  
        }
    }
  
    if ((tiles.count(std::pair<int,int> (position.first-1,position.second+1)))&&(position.first-1 >=0&&position.second+1 <=7)&&tiles.find(std::pair<int,int> (position.first-1,position.second+1))!=tiles.end()){
        auto o = getTile(position.first-1,position.second+1);
          if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
                b = isMonasteryClosed(*o, std::pair<int,int> (position.first-1,position.second+1), scoreBoard, playerColors); 
                if (b){
                    return b ;
                }   
            }  
        }
    }
   
    if (tiles.count(std::pair<int,int> (position.first,position.second+1))&&(position.second+1 <=7)&&tiles.find(std::pair<int,int> (position.first,position.second+1))!=tiles.end()){
        auto o = getTile(position.first,position.second+1); 
          if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
                b = isMonasteryClosed(*o, std::pair<int,int> (position.first,position.second+1), scoreBoard, playerColors); 
                if (b){
                    return b ;
                }   
            }  
        }
    }
    if (tiles.count(std::pair<int,int> (position.first+1,position.second+1))&&(position.first+1 <=7&&position.second+1<=7)&&tiles.find(std::pair<int,int> (position.first+1,position.second+1))!=tiles.end()){
        auto o = getTile(position.first+1,position.second+1); 
         if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
               b =  isMonasteryClosed(*o, std::pair<int,int> (position.first+1,position.second+1), scoreBoard, playerColors); 
                 if (b){
                    return b ;
                }   
            }  
        }
    }
    if (tiles.count(std::pair<int,int> (position.first+1,position.second))&&(position.first+1 <=7)&&tiles.find(std::pair<int,int> (position.first+1,position.second))!=tiles.end()){
        auto o = getTile(position.first+1,position.second);
        std::cout<<"monastere uwu"<<std::endl;

          if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
                b = isMonasteryClosed(*o, std::pair<int,int> (position.first+1,position.second), scoreBoard, playerColors); 
                  if (b){
                    return b ;
                }   
            }  
        }
    }
    if (tiles.count(std::pair<int,int> (position.first+1,position.second-1))&&(position.first+1<=7&&position.second-1>=0)&&tiles.find(std::pair<int,int> (position.first+1,position.second-1))!=tiles.end()){
        auto o = getTile(position.first+1,position.second-1);
        std::cout<<"monastere uwu"<<std::endl;
         if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
               b =  isMonasteryClosed(*o, std::pair<int,int> (position.first+1,position.second-1), scoreBoard, playerColors); 
                  if (b){
                    return b ;
                }   
            }  
        }
    }
    if (tiles.count(std::pair<int,int> (position.first,position.second-1))&&(position.second-1 >=0)&&tiles.find(std::pair<int,int> (position.first,position.second-1))!=tiles.end()){
       auto o = getTile(position.first,position.second-1);
        std::cout<<"monastere uwu"<<std::endl;
         if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
              b =   isMonasteryClosed(*o, std::pair<int,int> (position.first,position.second-1), scoreBoard, playerColors); 
              if (b){
                    return b ;
                }   
            }  
        }
    }
    if (tiles.count(std::pair<int,int> (position.first-1,position.second-1))&&(position.first-1 >=0&&position.second-1>=0)&&tiles.find(std::pair<int,int> (position.first-1,position.second-1))!=tiles.end()){
       auto o = getTile(position.first-1,position.second-1);
        std::cout<<"monastere uwu"<<std::endl;
          if (o!=nullptr){
            
            if (o->hasMonastery()){ //hasMonastery = fonction qui dit si y'a un monastere au centre. (todo)
                //if (true){
                    std::cout<<"onyva"<<std::endl;
              b =   isMonasteryClosed(*o, std::pair<int,int> (position.first-1,position.second-1), scoreBoard, playerColors); 
                  if (b){
                    return b ;
                }   
            }  
        }
    }
    return false; 
}
bool CarcassonneBoard::isMonasteryClosed(const CarcassonneTile& t,const std::pair<int, int>& position, std::map<int, std::pair<std::string, int>> &scoreBoard, std::map<std::string, CarcassonnePawnColor> playerColors){
    //todo : verifier les 8 cases autour.. 
    int eight = 0; 
    if ( (getTile(position.first-1,position.second))!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile (position.first-1,position.second+1)!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile(position.first,position.second+1)!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile (position.first+1,position.second+1)!=nullptr){
       eight +=1;
       std::cout<<eight<<std::endl;
    }
    if (getTile (position.first+1,position.second)!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile(position.first+1,position.second-1)!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile(position.first,position.second-1)!=nullptr){
        eight +=1;
        std::cout<<eight<<std::endl;
    }
    if (getTile(position.first-1,position.second-1)!=nullptr){
       eight +=1;
       std::cout<<eight<<std::endl;
    }
    //JE SAIS CA AURAIT PU ETRE ECRIT PLUS JOLIMENT MAIS JAI LA GASTRO OK ?
    //TODO rajouter les points du bonhomme dessus + enlever le bonhomme
    std::cout<<"monastere uwu"<<std::endl;
    std::cout<<"fincheck"<<std::endl;
    auto tilePawns = t.getPawns(); 
    if (eight==8){
    for (auto p : tilePawns){
        std::cout<<"boucle1"<<std::endl;
        if (p.first.type==CarcassonnePawnType::MONK){
            for (auto c : playerColors){
                std::cout<<"boucle2"<<std::endl;
                if (c.second==p.first.color){
                    for (auto pl : scoreBoard){
                        std::cout<<"boucle3"<<std::endl;
                        if (pl.second.first.std::string::compare( c.first)){
                            std::cout<<"compare"<<std::endl;
                            scoreBoard.at(pl.first).second +=9;
                        }
                    }
                   
                }
            }
        }
    }}//todo : enlever le pion

    for(auto s : scoreBoard){
        std::cout<<s.second.second<<std::endl;
    }
    return eight==8;
   


}
bool CarcassonneBoard::isRoadFinished(const CarcassonneTile& tile,const std::pair<int, int>& position,std::map<int, std::pair<std::string, int>> &scoreBoard, std::map<std::string, CarcassonnePawnColor> playerColors){
    auto neighbors = getNeighbors(position); 
    std::map<CarcassonnePawnColor,int>m;
     m[CarcassonnePawnColor::RED]=0;
     m[CarcassonnePawnColor::BLUE]=0;
     m[CarcassonnePawnColor::YELLOW]=0;
     m[CarcassonnePawnColor::GREEN]=0;
    int c = 0; 
     for (auto neighbor : neighbors) {
        auto neighborPos = position; 
        auto edge = neighbor.first;
        std::cout<<neighbors.size()<<std::endl;
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
        auto edge1 = tileProperties.at(edge);
        auto edge2 = neighborTileProperties.at(neighborEdge);
        if (edge1==CarcassonneTileType::ROAD){
            std::cout<<"roaded"<<std::endl;
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
            if (neighborTile.getTextureId()==6||neighborTile.getTextureId()==8||neighborTile.getTextureId()==21||neighborTile.getTextureId()==3||neighborTile.getTextureId()==13||neighborTile.getTextureId()==19){
                std::cout<<"tuile speciale banal"<<std::endl;
                auto pions = neighborTile.getPawns(); 
                    for(auto p : pions){
                        if (neighborEdge == TileEdge::LEFT){
                            if (p.second==CarcassonneTileGrid::MIDDLE_LEFT){
                                m[p.first.color]+=1;
                            }
                        }
                        else if (neighborEdge == TileEdge::RIGHT){
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::MIDDLE_RIGHT){
                                m[p.first.color]+=1;
                            }
                        }
                        else if (neighborEdge==TileEdge::TOP){
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::TOP_CENTER){
                                m[p.first.color]+=1;
                            }
                        }
                        else{
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::BOTTOM_CENTER){
                                m[p.first.color]+=1;
                            }
                        }       
                    }
                c += isRoadFinishedRecursive2(1,tile,position,neighborPos,m, scoreBoard, playerColors);
            }
            else {
                std::cout<<"appel normal banal "<<neighborPos.first<< " " <<neighborPos.second<<std::endl;
            c += isRoadFinishedRecursive1(neighborTile, neighborPos, position, scoreBoard, playerColors); 
            }
        }
        
    }
    return c>0; 
}

int CarcassonneBoard::isRoadFinishedRecursive1(const CarcassonneTile& tile, const std::pair<int,int>&position, const std::pair<int,int>& previous,std::map<int, std::pair<std::string, int>> &scoreBoard, std::map<std::string, CarcassonnePawnColor> playerColors){
     std::map<CarcassonnePawnColor,int>m;

     m[CarcassonnePawnColor::RED]=0;
     m[CarcassonnePawnColor::BLUE]=0;
     m[CarcassonnePawnColor::YELLOW]=0;
     m[CarcassonnePawnColor::GREEN]=0;
    auto neighbors = getNeighbors(position); 
    
    int c = 0 ;
    
    for (auto neighbor : neighbors){
        auto neighborPos = position;
        auto edge = neighbor.first;
        
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
        auto edge1 = tileProperties.at(edge);
        auto edge2 = neighborTileProperties.at(neighborEdge);
        if (edge1==CarcassonneTileType::ROAD){
            std::cout<<"type road first"<<neighborPos.first<< " " <<neighborPos.second<<std::endl;
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
            if (neighborPos != previous){
                if (neighborTile.getTextureId()==6||neighborTile.getTextureId()==8||neighborTile.getTextureId()==21||neighborTile.getTextureId()==3||neighborTile.getTextureId()==13||neighborTile.getTextureId()==19){
                    std::cout<<"tuile speciale FIRST"<<neighborPos.first<< " " <<neighborPos.second<<std::endl;
                    auto pions = neighborTile.getPawns(); 
                    for(auto p : pions){
                        if (neighborEdge == TileEdge::LEFT){
                            if (p.second==CarcassonneTileGrid::MIDDLE_LEFT){
                                m[p.first.color]+=1;
                            }
                        }
                        else if (neighborEdge == TileEdge::RIGHT){
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::MIDDLE_RIGHT){
                                m[p.first.color]+=1;
                            }
                        }
                        else if (neighborEdge==TileEdge::TOP){
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::TOP_CENTER){
                                m[p.first.color]+=1;
                            }
                        }
                    
                        else{
                            if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::BOTTOM_CENTER){
                                m[p.first.color]+=1;
                            }
                        }       
                    }
                c += isRoadFinishedRecursive2(1,tile,position, neighborPos,m, scoreBoard, playerColors);
                }
                else {
                    std::cout<<"appel normal first"<<neighborPos.first<< " " <<neighborPos.second<<std::endl;
                    c += isRoadFinishedRecursive1(neighborTile, neighborPos, position, scoreBoard, playerColors); 
                }
            } 
        }
    }
    return c; 
}
bool CarcassonneBoard::isRoadFinishedRecursive2(int longueur,const CarcassonneTile& tile, const std::pair<int,int>&position, const std::pair<int,int>& previous, std::map<CarcassonnePawnColor, int>& reg,std::map<int, std::pair<std::string, int>> &scoreBoard, std::map<std::string, CarcassonnePawnColor> playerColors){
    
    auto neighbors = getNeighbors(position); 
    
    int c = 0 ;
    
    for (auto neighbor : neighbors){
        auto edge = neighbor.first;
        auto neighborPos = position;
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
        auto edge1 = tileProperties.at(edge);
        auto edge2 = neighborTileProperties.at(neighborEdge);
        if (tile.getTextureId()==6||tile.getTextureId()==8||tile.getTextureId()==21||tile.getTextureId()==3||tile.getTextureId()==13||tile.getTextureId()==19){
            auto tileProperties=tile.dataStructure(); 
            auto pions = tile.getPawns(); 
            for(auto p : pions){
            if (edge == TileEdge::LEFT){
                if (p.second==CarcassonneTileGrid::MIDDLE_LEFT){
                    reg[p.first.color]+=1;
                }
            }
            else if (edge == TileEdge::RIGHT){
                if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::MIDDLE_RIGHT){
                    reg[p.first.color]+=1;
                }
            }
            else if (edge==TileEdge::TOP){
                if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::TOP_CENTER){
                    reg[p.first.color]+=1;
                }
            }
            else{
                if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::BOTTOM_CENTER){
                    reg[p.first.color]+=1;
                }
            }
            std::cout<<"tuile speciale SECOND"<<std::endl;
            }

            int max = std::max({reg[CarcassonnePawnColor::RED],reg[CarcassonnePawnColor::BLUE],reg[CarcassonnePawnColor::YELLOW], reg[CarcassonnePawnColor::GREEN] });
            longueur +=1;
            if (max>0){
                for(auto el : reg){
                    if (el.second==max){
                        for (auto c : playerColors){
                            std::cout<<"boucle2"<<std::endl;
                            if (c.second==el.first){
                                for (auto pl : scoreBoard){
                                    std::cout<<"boucle3"<<std::endl;
                                    if (pl.second.first.std::string::compare( c.first)){
                                        std::cout<<"compare"<<std::endl;
                                        scoreBoard.at(pl.first).second +=longueur;
                                    }
                                }
                   
                           }
                        }
                    }
                }
            }

            return 1; 
            
        }
        if (edge1==CarcassonneTileType::ROAD){
            std::cout<<"type road second"<<std::endl;
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
            if (neighborPos != previous){
                auto pions = tile.getPawns(); 
                for(auto p : pions){
                    if (edge == TileEdge::LEFT){
                        if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::MIDDLE_LEFT){
                            reg[p.first.color]+=1;
                        }
                    }
                    else if (edge == TileEdge::TOP){
                        if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::TOP_CENTER){
                            reg[p.first.color]+=1;
                        }
                    }
                     else if (edge == TileEdge::BOTTOM){
                        if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::BOTTOM_CENTER){
                            reg[p.first.color]+=1;
                        }
                    }
                    else{
                        if (p.second==CarcassonneTileGrid::MIDDLE_CENTER||p.second==CarcassonneTileGrid::MIDDLE_RIGHT){
                            reg[p.first.color]+=1;
                        }
                    }
                }
                    
                    
               std::cout<<"appel normal second"<<neighborPos.first<< " " <<neighborPos.second<<std::endl;
                c += isRoadFinishedRecursive2(longueur +1, neighborTile, neighborPos, position, reg, scoreBoard, playerColors); 
                
            }
        }
    }
    return c; 
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
            case CarcassonneTileGrid::MIDDLE_LEFT:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2));
                break;
            case CarcassonneTileGrid::MIDDLE_CENTER:
                centerPos = sf::Vector2f((tileX * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2), (tileY * CARCASSONNE_TILE_SIZE) + squareSize + (squareSize / 2));
                break;
            case CarcassonneTileGrid::MIDDLE_RIGHT:
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
        for (int i = 0; i < 40; i++) tiles.push_back(tile13);//40 attention a enlever
    }

    // Tile 14
    {
        CarcassonneTile* tile14 = new CarcassonneTile(13);
        tile14->setEdges(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD);
        tile14->setGrid(CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::MONASTERY, CarcassonneTileType::FIELD, CarcassonneTileType::FIELD, CarcassonneTileType::ROAD, CarcassonneTileType::FIELD);
        for (int i = 0; i < 40; i++) tiles.push_back(tile14);
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
    std::string instructions;
    if (isPlacingPawn) {
        instructions = "Cliquez sur votre tuile pour placer votre pion"; 
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
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::MIDDLE_LEFT);
                    break;
                case 4:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::MIDDLE_CENTER);
                    break;
                case 5:
                    board.getTile(currentTileX, currentTileY)->setPawn(newPawn, CarcassonneTileGrid::MIDDLE_RIGHT);
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
            }
        }
        tiles.erase(std::remove(tiles.begin(), tiles.end(), currentTile), tiles.end());
        if (tiles.size() == 0) {
                        isGameOver = true;
                        return;
        }
        currentTile = tiles.at(rand() % tiles.size());
        
        isPlacingPawn = false;
        currentPlayer += 1;
        currentPlayer %= scoreboard.size();
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
                    bool b = board.hasMonastery(*currentTile, position, scoreboard,playerColors);
                    if (b){
                        std::cout<<"monastere !!!!"<<std::endl;
                    }
                    bool r = board.isRoadFinished(*currentTile, position, scoreboard, playerColors);
                    if (r){
                        std::cout<<"ROUTE!!!"<<std::endl;
                    }
                }
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (!isGameOver) {
            if (event.key.code == sf::Keyboard::R) {
                currentTile->rotate(TileRotation::CLOCKWISE);
            }
        } else {
            if (event.type == sf::Event::KeyPressed) {
                // TODO
            }
        }
    }
}