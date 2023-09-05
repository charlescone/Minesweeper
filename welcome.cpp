#include "welcome.h"

Welcome::Welcome(sf::RenderWindow& window, int width, int height) {

    width *= 32;
    height *= 32;
    height += 10;

    this->width = width;
    this->height = height;

    font.loadFromFile("files/font.ttf");

    title.setFont(font);
    title.setCharacterSize(24);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setString("WELCOME TO MINESWEEPER!");
    this->setText(title, width/2, (height/2) - 150);

    caption.setFont(font);
    caption.setStyle(sf::Text::Bold);
    caption.setCharacterSize(20);
    caption.setString("Enter your name:");
    this->setText(caption, width/2, (height/2) - 75);

    textbox.setFont(font);
    textbox.setFillColor(sf::Color::Yellow);
    textbox.setCharacterSize(18);
    textbox.setStyle(sf::Text::Bold);


    //textbox.setString("bruh npc moment LOL");

}

sf::Text Welcome::getTextBox() {
    return this->textbox;
}

void Welcome::textboxLogic(sf::Event event) {
    if (i == 0) {
        textbox.setString("|");
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            inputText.erase(inputText.size()-1, 1);
            userName.erase(userName.size()-1, 1);
            textbox.setString(inputText + "|");
            i -= 1;
        } else if (i < 10) {
            unsigned int validator = event.text.unicode;
            if (validator < 91) {
                if (validator > 64) {
                    inputText += event.text.unicode;
                    userName = inputText;
                    userName[0] = toupper(userName[0]);
                    for (int j = 1; j < userName.size(); j++) {
                        userName[j] = tolower(userName[j]);
                    }
                    i += 1;
                    textbox.setString(inputText + "|");
                }
            }
            if (validator < 123) {
                if (validator > 96) {
                    inputText += event.text.unicode;
                    userName = inputText;
                    userName[0] = toupper(userName[0]);
                    for (int j = 1; j < userName.size(); j++) {
                        userName[j] = tolower(userName[j]);
                    }
                    i += 1;
                    textbox.setString(inputText + "|");
                }
            }
        }
        //std::cout << getUserName() << std::endl;
    }
    //std::cout << width << " " << height << std::endl;
    this->setText(textbox, width/2, height/2 - 45);
}

void Welcome::setText(sf::Text &text, float x, float y){
     sf::FloatRect textRect = text.getLocalBounds();
     text.setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
     text.setPosition(sf::Vector2f(x, y));
}

std::string Welcome::getUserName() {
    return this->userName;
}

