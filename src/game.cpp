#define _CRTDBG_MAP_ALLOC

#include "Game.hpp"
#include "Algorithms.hpp"
#include "Blocks.hpp"

Game::Game(char* title)
{
	// CREATE WINDOW
	this->v_mode.height = 800;
	this->v_mode.width = 800;
	this->window = new sf::RenderWindow(v_mode, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// SET VARIABLES
	const int numBlocks = 200;

	// CREATE BLOCK OBJECT
	blocks = new Blocks(numBlocks, this->v_mode.height, this->v_mode.width);

	// CREATE ALGORITHM OBJECT
	alg = new Algorithms(*blocks);

}

Game::~Game()
{
	delete this->blocks;
	delete this->alg;
	delete this->window;
}

void Game::update() {

}

void Game::handleEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			//this->alg->stop();
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			switch (this->ev.key.code)
			{
			case sf::Keyboard::Escape:
				//this->alg->stop();
				this->window->close();
				break;

			case sf::Keyboard::BackSpace:
				//this->alg->stop();
				this->window->close();
				break;

			case sf::Keyboard::LShift:
				this->alg->setAlg(0);
				break;

			case sf::Keyboard::I:
				this->alg->setAlg(1);
				break;

			case sf::Keyboard::S:
				this->alg->setAlg(2);
				break;

			case sf::Keyboard::Space:
				this->alg->start();
				break;
			}
			break;

		}
	}		
}

void Game::render()
{
	this->window->clear();
	this->blocks->render(this->window);
	this->window->display();
}
