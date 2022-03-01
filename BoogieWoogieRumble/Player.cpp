#include "Player.h"

const int leftBoundary = -600;
const int rightBoundary = 1400;
const int upBoundary = -600;
const int downBoundary = 1200;


Player::Player() {
	shape = sf::RectangleShape(sf::Vector2f(10, 10));
	shape.setOrigin(5, 5);
	shape.setPosition(sf::Vector2f(400, 200));
	sf::Color fillColor = sf::Color::Black;
	fillColor.a = 200;
	shape.setFillColor(fillColor);

	speed = 0.15f;
}

sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}

void Player::move(sf::RenderWindow* window, float delta_t)
{
	if (window->hasFocus()) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && getPosition().x > leftBoundary) {
			shape.move(-speed * delta_t, 0);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && getPosition().x < rightBoundary) {
			shape.move(speed * delta_t, 0);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && getPosition().y > upBoundary) {
			shape.move(0, -speed * delta_t);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && getPosition().y < downBoundary) {
			shape.move(0, speed * delta_t);
		}
	}
}

sf::RectangleShape Player::getShape()
{
	return shape;
}
