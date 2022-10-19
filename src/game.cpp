#define _CRTDBG_MAP_ALLOC

#include "Game.hpp"
#include "Algorithms.hpp"
#include "Blocks.hpp"

Game::Game(char* title)
{
	// CREATE WINDOW
	this->v_mode.height = 480;
	this->v_mode.width = 800;
	this->window = new sf::RenderWindow(v_mode, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// SET VARIABLES
	const int numBlocks = 200;

	// CREATE BLOCK OBJECT
	blocks = new Blocks(numBlocks, 480, 800);

	// CREATE ALGORITHM OBJECT
	alg = new Algorithms(*blocks);

}

Game::~Game()
{
	delete this->window;
}

void Game::handleEvents()
{
	while (this->window->pollEvent(this->ev))
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape) {
					this->alg->stop(); this->window->close();
				}
				else if (this->ev.key.code == sf::Keyboard::BackSpace) {
					this->alg->stop(); this->window->close();
				}
				else if (this->ev.key.code == sf::Keyboard::LShift)
					this->alg->setAlg(0);
				else if (this->ev.key.code == sf::Keyboard::I)
					this->alg->setAlg(1);
				else if (this->ev.key.code == sf::Keyboard::Space)
					this->alg->start();
		}			
}

void Game::render()
{
	this->window->clear();
	this->blocks->render(this->window);
	this->window->display();
}
