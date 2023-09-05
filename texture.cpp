#include "texture.h"

map<string, sf::Texture> Textures::textures;

sf::Texture& Textures::GetTexture(string textureName) {
    if (textures.find(textureName) == textures.end()) {
        textures[textureName].loadFromFile("files/images/" + textureName);
    }

    return textures[textureName];
}