#include "PoetryLine.h"

PoetryLine::PoetryLine(std::string line, sf::Vector2f position, float prox, float scale) : PoetryLine(line, position, prox, scale, -1.f)
{
}

PoetryLine::PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, float volChange)
{
	font.loadFromFile("resources/Gabriola.ttf");
	text = sf::Text(line, font);
	text.setPosition(position);
	sf::Color color = sf::Color::Red;
	color.a = 0;
	text.setFillColor(color);
	text.setLineSpacing(.7);

	sf::FloatRect rect = text.getGlobalBounds();
	text.setOrigin(rect.width / 2, rect.height / 2);

	text.setScale(scale, scale);

	this->prox = prox;
	lastDist = prox;

	this->volChange = volChange;
}

PoetryLine::PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, sf::Uint32 style) : PoetryLine(line, position, prox, scale, -1.f, style)
{
}

PoetryLine::PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, float volChange, sf::Uint32 style) : PoetryLine(line, position, prox, scale, volChange)
{
	setStyle(style);
}

void PoetryLine::checkProximity(Player* player, sf::Music* music)
{
	sf::Vector2f pos = player->getPosition();
	sf::Vector2f textPos = text.getPosition();
	float xDist = pos.x - textPos.x;
	float yDist = pos.y - textPos.y;

	float dist = sqrt((xDist * xDist) + (yDist * yDist));

	if (dist < prox) {
		sf::Color currentColor = text.getFillColor();
		currentColor.a = 255 - (255 / prox) * dist;
		text.setFillColor(currentColor);

		if (volChange >= 0) {
			music->setVolume(volChange + ((100 - volChange) / prox) * dist);
		}

		lastDist = dist;
	}
}

sf::Text PoetryLine::getText()
{
	return text;
}

void PoetryLine::setStyle(sf::Uint32 style)
{
	text.setStyle(style);
}
