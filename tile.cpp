#include "tile.h"
#include <iostream>

Tile::Tile(int x, int y) : sf::Sprite(Textures::GetTexture("tile_hidden.png")) {
    xCoordinate = x/32;
    yCoordinate = y/32;
    setPosition(x, y);

    flag.setTexture(Textures::GetTexture("flag.png"));
    flag.setPosition(getPosition()); // Matches tile_hidden position
    mine.setTexture(Textures::GetTexture("mine.png"));
    mine.setPosition(getPosition());
    mineCount.setPosition(getPosition());

    surroundingMines = 0;
    isFlagged = false;
    isHidden = true;
    hasMine = false;

    for (int i = 0; i < 8; ++i) {
        surroundingTiles.push_back(nullptr);
    }
}

void Tile::countSurroundingMines() {
    for (int i = 0; i < this->surroundingTiles.size(); ++i) {
        if (this->surroundingTiles[i] != nullptr && this->surroundingTiles[i]->hasMine) {
            surroundingMines++;
        }
    }
    if (surroundingMines > 0) {
        mineCount.setTexture(Textures::GetTexture("number_" + std::to_string(surroundingMines) + ".png"));
    }
}

void Tile::revealNeighbors(int& reveals) {
    for(int i = 0; i < surroundingTiles.size(); ++i) {
        if (surroundingTiles[i] == nullptr) {
            continue;
        }
        else if (!surroundingTiles[i]->hasMine && surroundingTiles[i]->isHidden && !surroundingTiles[i]->isFlagged) {
            surroundingTiles[i]->setTexture(Textures::GetTexture("tile_revealed.png"));
            surroundingTiles[i]->isHidden = false;
            reveals++;
            if (surroundingTiles[i]->surroundingMines == 0) {
                surroundingTiles[i]->revealNeighbors(reveals);
            }
        }
    }
}
