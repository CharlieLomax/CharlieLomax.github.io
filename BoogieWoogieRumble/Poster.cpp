#include "Poster.h"

Poster::Poster(std::string filename, sf::Vector2f pos)
{
	texture.loadFromFile(filename);
	sprite = sf::Sprite(texture);
	sprite.setPosition(pos);
}

sf::Sprite Poster::getSprite()
{
	return sprite;
}
