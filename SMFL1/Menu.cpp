#include "Menu.h"

void Menu::InitTitle()
{

	// set up title "PONG!!!"

	if(!menuFont.loadFromFile("Uni Sans Heavy.otf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}

	title.setFont(menuFont);
	std::stringstream titleString;

	titleString << "PONG!!!\n\n";

	title.setString(titleString.str());
	title.setCharacterSize(30);
	title.setPosition((window.getSize().x / 2) - 75, (window.getSize().y / 2) - 20);
	title.setFillColor(sf::Color::White);
}

void Menu::InitInst()
{
	// set up instructions text

	if(!menuFont.loadFromFile("Uni Sans Heavy.otf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}

	instructions.setFont(menuFont);
	std::stringstream insString;

	insString << "\nPress A, D to move blue bat\nPress <- -> (left and right) to move green bat\n\n\nPress 'Space' key to begin. Press 'esc' to quit";

	instructions.setString(insString.str());
	instructions.setCharacterSize(20);
	instructions.setPosition((window.getSize().x / 2) - 125, (window.getSize().y / 2) + 20);
	instructions.setFillColor(sf::Color::White);
}

Menu::Menu(sf::RenderWindow& rWindow) : 
	window(rWindow)
{
	InitTitle();
	InitInst();
}

sf::Text Menu::GetTitleText()
{
	return title;
}

sf::Text Menu::GetInstructionText()
{
	return instructions;
}
