#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//#include "board.h"


class Buttons {

    int width;
    int height;

    sf::Sprite debugButton;
    sf::Sprite pausePlayButton;



    sf::Time time;


public:
    int firstMinuteNum = 0;
    int secondMinuteNum = 0;
    int firstSecondNum = 0;
    int secondSecondNum = 0;

    sf::Sprite leaderboardButton;
    sf::Sprite faceButton;
    bool buttonFunction = true;
    bool pausePlay = false;
    bool debug = false;
    bool leaderboardPressed = false;
    bool facePressed = false;
    sf::Vector2f position;
    int totalTime;
    int elaspedTime = 0;
    //int mineCount;
    std::vector<sf::Sprite> digits;
    std::vector<sf::Sprite> counterDigits;

    Buttons(int width, int height);

    void loadButtons();
    void displayButtons(sf::RenderWindow& window);

    void onClick(sf::Event& mouseClick, sf::Vector2f& mousePosition);
    bool returnDebug();


    void loadClock(sf::Clock& clock);
    void displayTime(sf::RenderWindow& window, sf::Clock& clock);
    void pauseTime(sf::Clock& clock);

    void loadCounter();
    void displayCounter(sf::RenderWindow& window, int mineCount, int flagCount);
};

