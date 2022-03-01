#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	Player();
	sf::Vector2f getPosition();
	void move(sf::RenderWindow* window, float delta_t);
	sf::RectangleShape getShape();

private:
	float speed;
	sf::RectangleShape shape;
};