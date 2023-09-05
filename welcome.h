#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#pragma once

class Welcome {
private:
    int i = 0;
    std::string inputText;
    std::string userName;
    std::ostringstream text;
    int width;
    int height;


    sf::Text textbox;
    sf::Window window;

public:
    sf::Font font;
    sf::Text title;
    sf::Text caption;
    Welcome(sf::RenderWindow& window, int width, int height);

    void textboxLogic(sf::Event event);

    void setText(sf::Text &text, float x, float y);

    sf::Text getTextBox();
    std::string getUserName();
};