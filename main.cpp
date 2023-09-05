#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "welcome.h"
#include "buttons.h"
#include "board.h"

#include "leaderboard.h"

int main()
{
    int height, width, mineCount;
    ifstream in("files/board_config.cfg");
    in >> width;
    in >> height;
    in >> mineCount;
    in.close();
    //cout << width << height << mineCount << endl;

    int i = 0;
    sf::Clock clock;
    bool inWelcome = true;
    //bool inGame = false;
    sf::RenderWindow window(sf::VideoMode(width*32, (height * 32) + 100), "Minesweeper");
    sf::RenderWindow leaderboardWindow;
    window.setFramerateLimit(60);
    Welcome* welcomeWindow = new Welcome(window, width, height);
    Board board(height, width, mineCount);
    Buttons buttons(width, height);
    board.LoadTiles();
    board.LoadTileNeighbors();

    buttons.loadButtons();
    buttons.loadCounter();
    buttons.loadClock(clock);

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f mousePos(float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y));
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            welcomeWindow->textboxLogic(event);
            if (event.type == sf::Event::KeyPressed) {
                if (event.text.unicode == sf::Keyboard::Enter && welcomeWindow->getUserName() != "" && inWelcome) {
                    inWelcome = false;
                    //clock.restart();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && !inWelcome) {
                //if (!buttons.buttonFunction)
                buttons.onClick(event, mousePos);
                board.onClick(event, mousePos, buttons, window, clock);
                if (buttons.faceButton.getGlobalBounds().contains(mousePos) && !(board.won || board.lost)) {
                    buttons.facePressed = false;
                    buttons.elaspedTime = 0;
                    board.reveals = 0;
                    clock.restart();
                    board.Reload(clock);
                } else if (buttons.faceButton.getGlobalBounds().contains(mousePos) && (board.won || board.lost)) {
                    board.won = false;
                    board.lost = false;
                    buttons.facePressed = false;
                    buttons.buttonFunction = true;
                    buttons.elaspedTime = 0;
                    board.reveals = 0;
                    clock.restart();
                    board.Reload(clock);
                }
            }
        }

        if (inWelcome) {

            window.clear(sf::Color::Blue);
            window.draw(welcomeWindow->title);
            window.draw(welcomeWindow->caption);
            window.draw(welcomeWindow->getTextBox());


        } else {
            if (i <= 0)
                clock.restart();
            window.clear(sf::Color::White);
            sf::RectangleShape background;
            background.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
            background.setFillColor(sf::Color::White);
            window.draw(background);
            board.checkGameState(buttons, clock);
            buttons.displayTime(window, clock);
            board.debug = buttons.returnDebug();
            board.DrawTiles(window, leaderboardWindow, buttons, event, mousePos, clock, welcomeWindow->getUserName());
            buttons.displayButtons(window);
            buttons.displayCounter(window, board.getMineCount(), board.getFlagCount());
            i++;
        }
        window.display();
    }
    board.DeleteTiles();
    return 0;
}

