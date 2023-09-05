#include "leaderboard.h"

Leaderboard::Leaderboard(int width, int height) {
    font.loadFromFile("files/font.ttf");
    this->width = width;
    this->height = height;
}

void Leaderboard::loadData(string playerName) {
    string name, time;
    in.open("files/leaderboard.txt");

    int i = 1;
    int j = 0;
    while (getline(in,time,',')) {

        getline(in,name);
        playerData[time] = name;
    }

    map<string, string>::iterator iter;
    iter = playerData.begin();
    for (; iter != playerData.end(); iter++) {
        if (j < 5) {
            if (iter->second == playerName)
                leaderboardText.append(to_string(i) + ".\t" + iter->first + "\t" + iter->second + "*" + "\n\n");
            else
                leaderboardText.append(to_string(i) + ".\t" + iter->first + "\t" + iter->second + "\n\n");

            i++;
        } else {
            break;
        }
        j++;
    }
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(20);

    leaderboard.setFont(font);
    leaderboard.setString(leaderboardText);
    leaderboard.setFillColor(sf::Color::White);
    leaderboard.setCharacterSize(18);
    in.close();
}

void Leaderboard::writeData() {
    out.open("files/leaderboard.txt");
    if (out.is_open()) {
        map<string,string>::iterator iter;
        iter = playerData.begin();
        string temp;
        for (; iter != playerData.end(); ++iter) {
            temp = (iter->second);
            if (temp.find('*') != string::npos) {
                temp.erase(temp.find('*'));
                cout << temp << " " << iter->second << endl;
                out << iter->first << "," << temp << endl;
            } else {
                out << iter->first << "," << iter->second << endl;
            }
        }
    }


    out.close();
}

void Leaderboard::getUserData(string playerName, string firstMinute, string secondMinute, string firstSecond,
                              string secondSecond) {
    if (!isDataInputed) {
        string time = firstMinute + secondMinute + ":" + firstSecond + secondSecond;

        playerData[time] = playerName;

        isDataInputed = true;
    }
}


void Leaderboard::displayLeaderboard(sf::RenderWindow& window) {
        //window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(leaderboard);
}

void Leaderboard::setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}