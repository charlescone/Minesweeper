#include "buttons.h"
#include "texture.h"
//#include "leaderboard.h"
//#include "board.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;

Buttons::Buttons(int width, int height) {
    this->width = width;
    this->height = height;
    //cout << this->width << " " << this->height << endl;
}

void Buttons::loadButtons() {
    faceButton.setTexture(Textures::GetTexture("face_happy.png"));
    faceButton.setPosition((width/2)*32,(height+0.5f)*32);

    debugButton.setTexture(Textures::GetTexture("debug.png"));
    debugButton.setPosition((width*32)-304, (height+0.5f)*32);

    if (pausePlay) {
        pausePlayButton.setTexture(Textures::GetTexture("play.png"));
    } else {
        pausePlayButton.setTexture(Textures::GetTexture("pause.png"));
    }
    pausePlayButton.setPosition((width*32)-240, (height+0.5f)*32);

    leaderboardButton.setTexture(Textures::GetTexture("leaderboard.png"));
    leaderboardButton.setPosition((width*32)-176, (height+0.5f)*32);
}

void Buttons::displayButtons(sf::RenderWindow &window) {
    window.draw(faceButton);
    window.draw(debugButton);
    window.draw(pausePlayButton);
    window.draw(leaderboardButton);
}

void Buttons::loadClock(sf::Clock &clock) {
    totalTime = 0;
    for (int i = 0; i < 4; ++i) {
        if (i < 2) {
            digits.push_back(sf::Sprite(Textures::GetTexture("digits.png")));
            digits[i].setPosition(float((width*32) - 97 + (i * 21)), float(((height+0.5f)*32)+16));
            digits[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
        } else {
            digits.push_back(sf::Sprite(Textures::GetTexture("digits.png")));
            digits[i].setPosition(float((width*32) - 54 + ((i-2) * 21)), float(((height+0.5f)*32)+16));
            digits[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
            //cout << i << endl;
        }
    }
}

void Buttons::displayTime(sf::RenderWindow& window, sf::Clock& clock) {

    if (!pausePlay) {
        time = clock.getElapsedTime();
        totalTime = std::lround(time.asSeconds())+elaspedTime;
    } else if (pausePlay || facePressed) {
        elaspedTime = 0;
        clock.restart();
        facePressed = !facePressed;
    }
    else {
        elaspedTime = totalTime;
        clock.restart();
    }



    int minutes = (totalTime / 60) % 60;
    int seconds = totalTime%60;

    secondSecondNum = seconds%10;
    firstSecondNum = (seconds/10)%10;

    secondMinuteNum = minutes%10;
    firstMinuteNum = (minutes/10)%10;

    digits[3].setTextureRect(sf::IntRect(secondSecondNum*21,0,21,32));
    digits[2].setTextureRect(sf::IntRect(firstSecondNum*21,0,21,32));
    digits[1].setTextureRect(sf::IntRect(secondMinuteNum*21,0,21,32));
    digits[0].setTextureRect(sf::IntRect(firstMinuteNum*21,0,21,32));


    for (int i = 0; i < 4; i++) {
        window.draw(digits[i]);
    }
}

void Buttons::loadCounter() {
    for (int i = 0; i < 4; ++i) {
        int x = 33 + (i * 21);
        int y = ((height+0.5f)*32)+16;
        //cout << x << " " << y << endl;
        counterDigits.push_back(sf::Sprite(Textures::GetTexture("digits.png")));
        counterDigits[i].setPosition(x, y);
        counterDigits[i].setTextureRect(sf::IntRect(0,0,21,32));
    }
}

void Buttons::displayCounter(sf::RenderWindow &window, int mineCount, int flagCount) {
    mineCount -= flagCount;
    int absMineCount = mineCount;
    if (mineCount < 0) {
       absMineCount = mineCount * -1;
    }
    int unitDigit = absMineCount%10;
    int tensDigit = (absMineCount/10)%10;
    int hundredsDigit = (absMineCount/100)%10;

    counterDigits[3].setTextureRect(sf::IntRect(21*unitDigit, 0, 21, 32));
    counterDigits[2].setTextureRect(sf::IntRect(21*tensDigit, 0, 21, 32));
    counterDigits[1].setTextureRect(sf::IntRect(21*hundredsDigit, 0, 21, 32));
    counterDigits[0].setTextureRect(sf::IntRect(21*10,0,21,32));
    if (mineCount >= 0) {
        int i = 1;
        for (; i < 4; i++) {
            window.draw(counterDigits[i]);
        }
    } else {
        int i = 0;
        for (; i < 4; i++) {
            window.draw(counterDigits[i]);
        }
    }

}

void Buttons::onClick(sf::Event& event, sf::Vector2f &mousePosition) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (debugButton.getGlobalBounds().contains(mousePosition) && !pausePlay && buttonFunction) {
            debug = !debug;
        } else if (pausePlayButton.getGlobalBounds().contains(mousePosition) && buttonFunction) {
            pausePlay = !pausePlay;
            if (pausePlay) {
                pausePlayButton.setTexture(Textures::GetTexture("play.png"));
            } else {
                pausePlayButton.setTexture(Textures::GetTexture("pause.png"));

            }
        } else if (leaderboardButton.getGlobalBounds().contains(mousePosition)) {
            leaderboardPressed = !leaderboardPressed;
        }
    }
}

bool Buttons::returnDebug() {
    return debug;
}

void Buttons::pauseTime(sf::Clock &clock) {
    elaspedTime = totalTime;
    clock.restart();
}