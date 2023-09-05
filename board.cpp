#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "board.h"
#include "leaderboard.h"
using namespace std;

Board::Board(int height, int width, int mineCount) {
    //cout << "in board" << endl;
    this->height = height;
    this->width = width;
    this->mineCount = mineCount;
}

void Board::LoadTiles() {
    //cout << height << width << endl;
    rng.seed(chrono::system_clock::now().time_since_epoch().count());
    //mineCount = 10;
    int xPos, yPos;


    for(int i = 0; i < height; ++i) {
        vector<Tile*> tileRow;
        for(int j = 0; j < width; ++j) {
            tileRow.push_back(new Tile(j * 32, i * 32));

        }
        tiles.push_back(tileRow);
    }
    while (mineCount > 0) {
        uniform_int_distribution<int> xDist(0, width -1);
        uniform_int_distribution<int> yDist(0, height - 1);
        xPos = xDist(rng);
        yPos = yDist(rng);
        if (tiles[yPos][xPos]->hasMine) {
            continue;
        } else {
            tiles[yPos][xPos]->hasMine = true;
            mineCount--;
        }
    }
    //cout << "loaded tiles" << endl;
}

/*
                 +++ Form of surroundingTiles vector for each tile +++

    0      1      2             tiles[i-1][j-1]  tiles[i-1][j]  tiles[i-1][j+1]
    7  currTile   3     ->      tiles[i][j-1]      currTile     tiles[i][j+1]
    6      5      4             tiles[i+1][j-1]  tiles[i+1][j]  tiles[i+1][j+1]

 */

void Board::LoadTileNeighbors() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile *currTile = tiles[i][j];
            if (i == 0) {
                //std::cout << "row 1" << std::endl;
                if (j == 0) {
                    //std::cout << "col 1" << std::endl;
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                    currTile->surroundingTiles[4] = tiles[i + 1][j + 1];
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                } else if (j == (width-1)) {
                    //std::cout << "col 25" << std::endl;
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                    currTile->surroundingTiles[6] = tiles[i + 1][j - 1];
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                } else {
                    //std::cout << "col " << j + 1 << std::endl;
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                    currTile->surroundingTiles[4] = tiles[i + 1][j + 1];
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                    currTile->surroundingTiles[6] = tiles[i + 1][j - 1];
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                }
            } else if (i == (height - 1)) {
                //std::cout << "row 16" << std::endl;
                if (j == 0) {
                    //std::cout << "col 1" << std::endl;
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                    currTile->surroundingTiles[2] = tiles[i - 1][j + 1];
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                } else if (j == (width - 1)) {
                    //std::cout << "col 25" << std::endl;
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                    currTile->surroundingTiles[0] = tiles[i - 1][j - 1];
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                } else {
                    //std::cout << "col " << j + 1 << std::endl;
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                    currTile->surroundingTiles[0] = tiles[i - 1][j - 1];
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                    currTile->surroundingTiles[2] = tiles[i - 1][j + 1];
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                }
            } else {
                //TODO Side edge cases and general form
                //std::cout << "row " << i + 1 << std::endl;
                if (j == 0) {
                    //std::cout << "col 1" << std::endl;
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                    currTile->surroundingTiles[2] = tiles[i - 1][j + 1];
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                    currTile->surroundingTiles[4] = tiles[i + 1][j + 1];
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                } else if (j == (width - 1)) {
                    //std::cout << "col 25" << std::endl;
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                    currTile->surroundingTiles[0] = tiles[i - 1][j - 1];
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                    currTile->surroundingTiles[6] = tiles[i + 1][j - 1];
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                } else {
                    //std::cout << "col " << j + 1 << " benen" << std::endl;
                    currTile->surroundingTiles[0] = tiles[i - 1][j - 1];
                    currTile->surroundingTiles[1] = tiles[i - 1][j];
                    currTile->surroundingTiles[2] = tiles[i - 1][j + 1];
                    currTile->surroundingTiles[3] = tiles[i][j + 1];
                    currTile->surroundingTiles[4] = tiles[i + 1][j + 1];
                    currTile->surroundingTiles[5] = tiles[i + 1][j];
                    currTile->surroundingTiles[6] = tiles[i + 1][j - 1];
                    currTile->surroundingTiles[7] = tiles[i][j - 1];
                }
            }
            currTile->countSurroundingMines();
        }
    }
    //cout << "loaded neighbors" << endl;
}


void Board::DrawTiles(sf::RenderWindow& window, sf::RenderWindow& leaderboardWindow, Buttons& buttons, sf::Event& event, sf::Vector2f& mousePosition, sf::Clock& clock, string playerName) {
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            window.draw(*(tiles[i][j]));
            if (tiles[i][j]->hasMine && (debug || lost)) {
                window.draw(tiles[i][j]->mine);
            }
            if (tiles[i][j]->isFlagged) {
                window.draw(tiles[i][j]->flag);
            }
            if (!(tiles[i][j]->hasMine) && !(tiles[i][j]->isHidden)) {
                window.draw(tiles[i][j]->mineCount);
            }
            if (buttons.pausePlay) {
                paused = true;
                tiles[i][j]->setTexture(Textures::GetTexture("tile_revealed.png"));
                window.draw(*(tiles[i][j]));
                if (tiles[i][j]->isHidden)
                    tiles[i][j]->setTexture(Textures::GetTexture("tile_hidden.png"));
            } else {
                paused = false;
            }
            if (buttons.leaderboardPressed || wonLeaderboard) {

                paused = true;
                if (!wonLeaderboard || buttons.leaderboardPressed) {
                    tiles[i][j]->setTexture(Textures::GetTexture("tile_revealed.png"));
                    window.draw(*(tiles[i][j]));
                    if (tiles[i][j]->isHidden)
                        tiles[i][j]->setTexture(Textures::GetTexture("tile_hidden.png"));
                }
                if (i == (height - 1) && j == (width - 1)) {
                    buttons.displayCounter(window, getMineCount(), getFlagCount());
                    buttons.displayButtons(window);
                    buttons.displayTime(window, clock);
                    window.display();
                    leaderboardWindow.create(sf::VideoMode((width*16), (height*16)+50), "Minesweeper");

                    while(leaderboardWindow.isOpen()) {
                        sf::Event leaderboardEvent;
                        while (leaderboardWindow.pollEvent(leaderboardEvent)) {
                            if (leaderboardEvent.type == sf::Event::Closed) {
                                leaderboardWindow.close();
                                wonLeaderboard = false;
                                buttons.leaderboardPressed = false;
                                return;
                            }
                        }
                        leaderboardWindow.clear(sf::Color::Blue);
                        Leaderboard leaderboardInfo(width, height);

                        if (won)
                            leaderboardInfo.getUserData(playerName, to_string(buttons.firstMinuteNum), to_string(buttons.secondMinuteNum),
                                                        to_string(buttons.firstSecondNum), to_string(buttons.secondSecondNum));
                        leaderboardInfo.loadData(playerName);
                        leaderboardInfo.setText(leaderboardInfo.title, (width*16)/2, ((height*16)/2)-120);
                        leaderboardInfo.setText(leaderboardInfo.leaderboard, (width*16)/2, ((height*16)/2)+20);
                        leaderboardInfo.displayLeaderboard(leaderboardWindow);
                        leaderboardInfo.writeData();
                        leaderboardWindow.display();
                    }

                    buttons.pauseTime(clock);
                    buttons.leaderboardPressed = !buttons.leaderboardPressed;
                }
            } else {
                paused = false;
            }
        }
    }
}

void Board::DeleteTiles() {
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            delete tiles[i][j];
        }
    }
}

void Board::Reload(sf::Clock& clock) {
    DeleteTiles();
    tiles.clear();
    LoadTiles();
    LoadTileNeighbors();
    clock.restart();
}

void Board::onClick(sf::Event& event, sf::Vector2f& mousePosition, Buttons& buttons, sf::RenderWindow& window, sf::Clock& clock)   {
    Tile *currTile;
    if (event.mouseButton.button == sf::Mouse::Left) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                currTile = tiles[i][j];
                if (!(won || lost)) {
                    if (currTile->getGlobalBounds().contains(mousePosition) && !paused) {
                        if (currTile->isFlagged) {
                            return;
                        }
                        if (currTile->isHidden) {
                            currTile->setTexture(Textures::GetTexture("tile_revealed.png"));
                            currTile->isHidden = false;
                            if (currTile->hasMine) {
                                lose(buttons);
                            } else {
                                reveals++;
                                currTile->revealNeighbors(reveals);
                                if (reveals == (400 - getMineCount())) {
                                    win(buttons);
                                }
                            }
                        }
                    }
                    if (currTile->getGlobalBounds().contains(mousePosition) && !paused) {
                        if (currTile->isFlagged) {
                            return;
                        }
                        if (currTile->isHidden) {
                            currTile->setTexture(Textures::GetTexture("tile_revealed.png"));
                            currTile->isHidden = false;
                            if (currTile->hasMine) {
                                lose(buttons);
                            } else {
                                reveals++;
                                currTile->revealNeighbors(reveals);
                                if (reveals == ((width*height) - getMineCount())) {
                                    win(buttons);
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if (event.mouseButton.button == sf::Mouse::Right && !(won || lost)) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                currTile = tiles[i][j];
                if (currTile->getGlobalBounds().contains(mousePosition) && !paused) {
                    if (currTile->isHidden) {
                        currTile->isFlagged = !(currTile->isFlagged);
                    }
                }
            }
        }
    }
}

int Board::getMineCount() {
    mineCount = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles[i][j]->hasMine) {
                mineCount++;
            }
        }
    }
    return mineCount;
}

int Board::getFlagCount() {
    flagCount = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles[i][j]->isFlagged) {
                flagCount++;
            }
        }
    }
    return flagCount;
}

void Board::lose(Buttons& buttons){
    lost = true;
    buttons.buttonFunction = false;
    Tile* currTile;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            currTile = tiles[i][j];
            if (currTile->hasMine) {
                currTile->setTexture(Textures::GetTexture("tile_revealed.png"));
                currTile->isHidden = false;
                currTile->isFlagged = false;
            }
        }
    }
}

void Board::win(Buttons& buttons) {
    won = true;
    wonLeaderboard = true;
    buttons.buttonFunction = false;
    Tile* currTile;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            currTile = tiles[i][j];
            if (currTile->hasMine) {
                currTile->isFlagged = true;
                buttons.debug = false;
            }
        }
    }
}

void Board::checkGameState(Buttons& buttons, sf::Clock& clock) {
    if (lost) {
        buttons.faceButton.setTexture(Textures::GetTexture("face_lose.png"));
        buttons.pauseTime(clock);
        reveals = 0;
    } else if (won) {
        buttons.faceButton.setTexture(Textures::GetTexture("face_win.png"));
        buttons.pauseTime(clock);
        reveals = 0;
    } else {
        //cout << won << lost << endl;
        buttons.faceButton.setTexture(Textures::GetTexture("face_happy.png"));
    }
}