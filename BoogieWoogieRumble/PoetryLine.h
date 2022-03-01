#pragma once
#include <string>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class PoetryLine
{
public:
	PoetryLine(std::string line, sf::Vector2f position, float prox, float scale);
	PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, float volChange);
	PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, sf::Uint32 style);
	PoetryLine(std::string line, sf::Vector2f position, float prox, float scale, float volChange, sf::Uint32 style);
	void checkProximity(Player* player, sf::Music* music);
	sf::Text getText();
	void setStyle(sf::Uint32 style);

private:
	sf::Text text;
	sf::Font font;

	float prox;
	float lastDist;
	float volChange;
};

