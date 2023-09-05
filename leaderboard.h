#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Leaderboard {
    ifstream in;
    ofstream out;
    string leaderboardText;
    bool isDataInputed = false;

    int width;
    int height;
    //sf::RenderWindow window;


public:
    sf::Font font;
    sf::Text title;
    sf::Text leaderboard;
    map<string, string> playerData;

    Leaderboard(int width, int height);

    void loadData(string playerName);
    void writeData();
    void getUserData(string playerName, string firstMinute, string secondMinute, string firstSecond, string secondSecond);
    void displayLeaderboard(sf::RenderWindow& window);
    void setText(sf::Text &text, float x, float y);

};