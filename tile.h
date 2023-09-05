#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "texture.h"
using namespace std;

class Tile : public sf::Sprite {
public:
    int xCoordinate, yCoordinate;
    vector<Tile*> surroundingTiles;
    unsigned int surroundingMines = 0;
    bool isHidden;
    bool isFlagged;
    bool hasMine;

    sf::Sprite mineCount;
    sf::Sprite flag;
    sf::Sprite mine;

    Tile(int x = 0, int y = 0);
    void countSurroundingMines();
    //bool isClicked();
    void revealNeighbors(int& reveals);
};