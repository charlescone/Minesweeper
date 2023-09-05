#pragma once
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;

class Textures {
    static map<string, sf::Texture> textures;

public:
    static sf::Texture& GetTexture(string textureName);

};