#include "../include/gui.hpp"
#include "../../common/include/common.hpp"
#include "../../common/include/tile.hpp"

using namespace sf;

#define TILE_TOTAL_SIZE_PXL 80
#define BOARD_SIZE 11
#define WINDOW_SIZE (TILE_TOTAL_SIZE_PXL * BOARD_SIZE)

Image imageFromTile(Tile tile, std::map<int, Image> assets) {
    Image image;
    image.create(400, 400, Color::White);
    image.copy(assets[0], 0, 0);
    image.copy(assets[0], 320, 0);
    image.copy(assets[0], 0, 320);
    image.copy(assets[0], 320, 320);
    for (int i = 0; i < 3; i++) {
        image.copy(assets[tile.getValues()[Edge::TOP][i]], 80 * (i + 1), 0);
        image.copy(assets[tile.getValues()[Edge::BOTTOM][i]], 80 * (i + 1), 320);
        image.copy(assets[tile.getValues()[Edge::LEFT][i]], 0, 80 * (i + 1));
        image.copy(assets[tile.getValues()[Edge::RIGHT][i]], 320, 80 * (i + 1));
    }
    return image;
}

std::map<int, Image> loadAssets() {
    auto assets = std::map<int, Image>();
    // Load corner
    Image corner;
    corner.loadFromFile("assets/corner.png");
    assets[0] = corner;
    // Load numbers
    for (int i = 1; i < 7; i++) {
        Image num;
        num.loadFromFile("assets/" + std::to_string(i) + ".png");
        assets[i] = num;
    }
    return assets;
}

void drawBoard(std::map<int, Image>& assets, const Board& board, RenderWindow& window) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            auto tile = board.retrieveTile(x, y);
            if (tile.isSome()) {
                Texture texture;
                texture.loadFromImage(imageFromTile(tile.unwrap(), assets));
                Sprite sprite;
                sprite.setTexture(texture);
                sprite.scale(0.2, 0.2);
                sprite.setPosition(x * TILE_TOTAL_SIZE_PXL, y * TILE_TOTAL_SIZE_PXL);
                window.draw(sprite);
            }
        }
    }
}



int main(void) {
    std::cout << "Loading assets...";
    auto assets = loadAssets();
    std::cout << "\tDone." << std::endl;

    Board board(Tile(), std::make_pair(BOARD_SIZE / 2, BOARD_SIZE / 2));

    // Generate BOARD_SIZE * BOARD_SIZE rectangles and place them in a vector
    std::vector<RectangleShape> rectangles;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            RectangleShape rectangle;
            rectangle.setSize(Vector2f(TILE_TOTAL_SIZE_PXL, TILE_TOTAL_SIZE_PXL));
            rectangle.setOutlineColor(Color::Black);
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(x * TILE_TOTAL_SIZE_PXL, y * TILE_TOTAL_SIZE_PXL);
            rectangles.push_back(rectangle);
        }
    }

    Tile currentTile;
    Image currentTileImage = imageFromTile(currentTile, assets);
    Texture currentTileTexture;
    currentTileTexture.loadFromImage(currentTileImage);
    Sprite currentTileSprite;
    currentTileSprite.setTexture(currentTileTexture);
    currentTileSprite.scale(0.25, 0.25);
    auto width = currentTileSprite.getGlobalBounds().width;
    auto height = currentTileSprite.getGlobalBounds().height;
    currentTileSprite.setPosition(WINDOW_SIZE + 100 - width / 2, WINDOW_SIZE / 2 - height / 2);

    Font font;
    font.loadFromFile("assets/random.ttf");

    Text lowerInstructions;
    lowerInstructions.setFont(font);
    lowerInstructions.setString("Left click on a tile to place it (if possible)");
    lowerInstructions.setCharacterSize(18);

    std::vector<Text> tileInstructions(3);
    tileInstructions[0].setFont(font);
    tileInstructions[0].setString("LMB = +90deg");
    tileInstructions[0].setCharacterSize(16);
    tileInstructions[1].setFont(font);
    tileInstructions[1].setString("RMB = -90deg");
    tileInstructions[1].setCharacterSize(16);
    tileInstructions[2].setFont(font);
    tileInstructions[2].setString("Space to discard");
    tileInstructions[2].setCharacterSize(16);
    
    RenderWindow window(VideoMode(WINDOW_SIZE + 200, WINDOW_SIZE + 50), "Quadriminos", Style::Close);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                auto mousePos = Mouse::getPosition(window);
                if (currentTileSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    currentTile = currentTile.rotate(Rotation::COUNTERCLOCKWISE);
                } else {
                    auto x = mousePos.x / TILE_TOTAL_SIZE_PXL;
                    auto y = mousePos.y / TILE_TOTAL_SIZE_PXL;
                    if (x < BOARD_SIZE && y < BOARD_SIZE) {
                        if (board.canPlaceTile(currentTile, x, y)) {
                            board.placeTile(currentTile, x, y);
                            currentTile = Tile();
                        } else {
                            currentTile = Tile();
                        }
                    }
                } 
            } else if (Mouse::isButtonPressed(Mouse::Right)) {
                auto mousePos = Mouse::getPosition(window);
                if (currentTileSprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    currentTile = currentTile.rotate(Rotation::CLOCKWISE);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                currentTile = Tile();
            }
            // Refresh tile
            {
                currentTileImage = imageFromTile(currentTile, assets);
                currentTileTexture.loadFromImage(currentTileImage);
                currentTileSprite.setTexture(currentTileTexture);
                width = currentTileSprite.getGlobalBounds().width;
                height = currentTileSprite.getGlobalBounds().height;
                currentTileSprite.setPosition(WINDOW_SIZE + 100 - width / 2, WINDOW_SIZE / 2 - height / 2);
            }
        }
        window.clear();
        for (auto& rectangle : rectangles) {
            window.draw(rectangle);
        }
        drawBoard(assets, board, window);
        window.draw(currentTileSprite);
        window.draw(lowerInstructions, Transform().translate(30, WINDOW_SIZE + 15));
        for (size_t i = 0; i < tileInstructions.size(); i++) {
            window.draw(tileInstructions[i], Transform().translate(WINDOW_SIZE + 15, 200 + WINDOW_SIZE / 2 - 50 + i * 20));
        }
        window.display();
    }
    return 0;
}