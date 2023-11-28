#include "Game.h"

//Initialisation
void Game::InitWindow()
{
	videoMode.width = 1360;
	videoMode.height = 760;

	window = new sf::RenderWindow(videoMode, "PONG!!!", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::InitBatOne()
{
	// dimensions of bat
	batOneDim.x = 150.0f;
	batOneDim.y = 15.0f;

	//position of the bat params
	batOnePos.x = (window->getSize().x) / 2.0f; 
	batOnePos.y = window->getSize().y - 40;

	// Creating the bat and placcing it
	batOne = new sf::RectangleShape(batOneDim);
	batOne->setOrigin(75.0f, 10.0f);
	batOne->setPosition(batOnePos);
	batOne->setFillColor(sf::Color::Cyan);
}

void Game::InitBatTwo()
{
	// dimensions of bat
	batTwoDim.x = 150.0f;
	batTwoDim.y = 15.0f;

	//position of the bat params
	batTwoPos.x = (window->getSize().x) / 2.0f;
	batTwoPos.y = 40;

	// Creating the bat and placcing it
	batTwo = new sf::RectangleShape(batTwoDim);
	batTwo->setOrigin(75.0f, 10.0f);
	batTwo->setPosition(batTwoPos);
	batTwo->setFillColor(sf::Color::Green);
}

void Game::InitBall()
{
	// ball size
	ballDim = 12.0f;

	// ball velocity
	ballVelocity.x = 4.0f;
	ballVelocity.y = 1.5f;

	// ball position params
	ballPos.x = window->getSize().x / 2.0;
	ballPos.y = window->getSize().y / 2.0;

	// Instatiate Ball
	ball = new sf::CircleShape(ballDim);

	// Ball Origin and Position
	ball->setOrigin(10.0f, 10.0f);
	ball->setPosition(ballPos);
	ball->setFillColor(sf::Color::White);
}


void Game::InitText()
{
	if(!font.loadFromFile("Uni Sans Heavy.otf"))
	{
		std::cout << "Unable to load font" << std::endl;
	}

	// Initializing player 1 score
	oneScore.setFont(font);
	std::stringstream ss;
	ss << "Score: " << oneScoreNum;
	oneScore.setString(ss.str());
	oneScore.setCharacterSize(20);
	oneScore.setPosition(20, window->getSize().y - 30);
	oneScore.setFillColor(sf::Color::Cyan);

	// Initializing player 2 score
	twoScore.setFont(font);
	std::stringstream ss2;
	ss2 << "Score: " << twoScoreNum;
	twoScore.setString(ss.str());
	twoScore.setCharacterSize(20);
	twoScore.setPosition(window->getSize().x - 100, 10);
	twoScore.setFillColor(sf::Color::Green);
}
///////////////////////////////
// Constructor / Destructor
Game::Game()
{
	InitWindow();
	myMenu = new Menu(*window);
	InitBatOne();
	InitBatTwo();
	InitBall();
	InitText();
}

Game::~Game()
{
	delete window;
	delete batOne;
	delete batTwo;
	delete myMenu;
}

///////////////////////////////////////////
// Getter method
const bool Game::IsRunning() const
{
	return window->isOpen();
}

bool& Game::isGameOn()
{
	return gameOn;
}

///////////////////////////
// Update window

void Game::PollEvents()
{
	while(window->pollEvent(event))
	{
		if(event.type == event.Closed)
		{
			window->close();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
		}
	}
}

void Game::UpdateBatOnePos()
{
	/*
		**Updates bat position**
		- When 'A' is pressed, the bat moves towards left until it reaches the edge of the window
		- When 'D' is pressed, the bat moves towards right until it reaches the right edge of the window.
	*/

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(batOne->getPosition().x >= ((batOneDim.x / 2) + 10))
		{
			batOne->move(-10.0f, 0.0f);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(batOne->getPosition().x <= (window->getSize().x - ((batOneDim.x / 2) + 10)))
		{
			batOne->move(10.0f, 0.0f);
		}
	}
}

void Game::UpdateBatTwoPos()
{
	/*
		**Updates bat position**
		- When '<-' (Left arrow) is pressed, the bat moves towards left until it reaches the edge of the window
		- When '->' (Right Arrow) is pressed, the bat moves towards right until it reaches the right edge of the window.
	*/

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(batTwo->getPosition().x >= ((batTwoDim.x / 2) + 10))
		{
			batTwo->move(-10.0f, 0.0f);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(batTwo->getPosition().x <= (window->getSize().x - ((batTwoDim.x / 2) + 10)))
		{
			batTwo->move(10.0f, 0.0f);
		}
	}
}

bool Game::IntersectsBatOne()
{
	/*
		Checks if the ball is in contact with the bat one
		returns a bool
	*/
	return ball->getGlobalBounds().intersects(batOne->getGlobalBounds());
}

bool Game::IntersectsBatTwo()
{
	/*
		Checks if the ball is in contact with the bat two
		returns a bool
	*/
	return ball->getGlobalBounds().intersects(batTwo->getGlobalBounds());
}

void Game::ResetBall()
{
	/*
		Reset ball's position and speed when a player misses the ball
	*/
	ball->setPosition(ballPos);

	ballXDir = (rand() % 2 == 0) ? 1.0f : -1.0f;
	ballYDir = (rand() % 2 == 0) ? 1.0f : -1.0f;

	ballVelocity.x = ballXDir * 4.0f;
	ballVelocity.y = ballYDir * 1.5f;
}

void Game::UpdateBallPos()
{
	ball->move(ballVelocity.x, ballVelocity.y);

	// collision with sides
	if(ball->getPosition().x <= 0 || ball->getPosition().x >= window->getSize().x)
	{
		ballVelocity.x = -ballVelocity.x;
	}

	//collision with bats
	if((IntersectsBatOne() || IntersectsBatTwo()) && bounceTime < 0)
	{
		ballVelocity.y = -ballVelocity.y;
		ballVelocity += (ballVelocity) * 0.1f;
	}

	// Collison with top border
	if(ball->getPosition().y <= 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		ResetBall();
		oneScoreNum += 1;
		UpdateOneScore();
		if(oneScoreNum == 10)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			gameOn = false;
		}
	}

	// Collison with bottom border
	if(ball->getPosition().y >= window->getSize().y)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		ResetBall();
		twoScoreNum += 1;
		UpdateTwoScore();
		if(twoScoreNum == 10)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			gameOn = false;
		}	
	}
}

void Game::UpdateOneScore()
{
	std::stringstream ss;
	ss << "Score: " << oneScoreNum;
	oneScore.setString(ss.str());
	oneScore.setCharacterSize(20);
}

void Game::UpdateTwoScore()
{
	std::stringstream ss2;
	ss2 << "Score: " << twoScoreNum;
	twoScore.setString(ss2.str());
	twoScore.setCharacterSize(20);
}

void Game::Update() 
{
	
	/*
		When the game is running (gameOn = true) update all the elements, frame by frame
		When the game is not running (gameOn = false) allow the player to press 'space' to start the game.
	*/
	
	dt = clock.restart();
	bounceTime -= dt.asSeconds();
	PollEvents();

	if(!gameOn) 
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		{
			gameOn = true;
		}
	}
	else 
	{
		UpdateBatOnePos();
		UpdateBatTwoPos();
		UpdateBallPos();
		UpdateOneScore();
		UpdateTwoScore();
	}
}

//////////////////////////////////////
// Render Window
void Game::Render() 
{
	/*
		when gameOn = false; display menu
		when gameOn = true; display all other element
	*/
	window->clear(sf::Color::Black);

	if(gameOn) {
		window->draw(*batOne);
		window->draw(*batTwo);
		window->draw(*ball);
		window->draw(oneScore);
		window->draw(twoScore);
	}
	else 
	{
		window->draw(myMenu->GetTitleText());
		window->draw(myMenu->GetInstructionText());

	}

	window->display();
}