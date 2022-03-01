#pragma once
#include "SFML/Graphics.hpp"
class Poster
{
public:
	Poster(std::string filename, sf::Vector2f pos);
	sf::Sprite getSprite();

private:
	sf::Sprite sprite;
	sf::Texture texture;
};

