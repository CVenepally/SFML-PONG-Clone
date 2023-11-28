#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Menu
{
public:
	sf::RenderWindow& window;
	sf::Font menuFont;
	sf::Text title;
	sf::Text instructions;
	Menu(sf::RenderWindow& rWindow);
	void InitTitle();
	void InitInst();

	sf::Text GetTitleText();
	sf::Text GetInstructionText();
};

