#pragma once

#include<thread>
#include<chrono>
#include <iostream>
#include <sstream>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Menu.h";

class Game
{
private:

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	bool gameOn = false;

	// Event
	sf::Event event;

	// Bat P1
	sf::RectangleShape* batOne;
	sf::Vector2f batOneDim;
	sf::Vector2f batOnePos;
	int oneScoreNum;

	// Bat P2
	sf::RectangleShape* batTwo;
	sf::Vector2f batTwoDim;
	sf::Vector2f batTwoPos;
	int twoScoreNum;

	//Ball
	sf::CircleShape* ball;
	sf::Vector2f ballPos;
	sf::Vector2f ballVelocity;
	float ballDim;
	float ballXDir;
	float ballYDir;

	// Scores
	sf::Font font;
	sf::Text oneScore;
	sf::Text twoScore;

	bool IntersectsBatOne();
	bool IntersectsBatTwo();
	void ResetBall();

	//Init
	void InitWindow();
	void InitBatOne();
	void InitBatTwo();
	void InitBall();
	void InitText();

	//Delta Time
	sf::Time dt;
	sf::Clock clock;
	float bounceTime = 0.10f;

	// Menu
	Menu* myMenu;

public:

	// Constructor / Destructor
	Game();
	~Game();

	// Event Polling
	void PollEvents();

	//Getter
	const bool IsRunning() const;
	bool& isGameOn();

	// Update game
	void UpdateBatOnePos();
	void UpdateBatTwoPos();
	void UpdateBallPos();
	void UpdateOneScore();
	void UpdateTwoScore();
	void Update();

	// Render game
	void Render();
};
