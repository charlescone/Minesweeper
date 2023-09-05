#pragma once
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <map>
#include <ctime>
#include "tile.h"
#include "buttons.h"

using namespace std;

class Board {

    default_random_engine rng;

    vector<vector<int>> randomNums;

public:
    Board(int height, int width, int mineCount);

    vector<vector<Tile*>> tiles;
    int height;
    int width;
    int mineCount = 0;
    int flagCount = 0;
    int reveals = 0;
    bool won = false;
    bool wonLeaderboard = false;
    bool lost = false;
    bool debug;
    bool paused = false;

    void LoadTiles();
    void LoadTileNeighbors();
    void Reload(sf::Clock& clock);
    void DrawTiles(sf::RenderWindow& window, sf::RenderWindow& leaderboardWindow, Buttons& buttons, sf::Event& event, sf::Vector2f& mousePosition, sf::Clock& clock, string playerName);

    void onClick(sf::Event& mouseClick, sf::Vector2f& mousePosition, Buttons& buttons, sf::RenderWindow& window, sf::Clock& clock);
    int getMineCount();
    int getFlagCount();

    void lose(Buttons& buttons);
    void win(Buttons& buttons);
    void checkGameState(Buttons& buttons, sf::Clock& clock);

    void DeleteTiles();
};
