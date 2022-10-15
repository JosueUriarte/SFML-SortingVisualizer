#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

Game::Game(char* title)
{
	// CREATE WINDOW
	this->v_mode.height = 480;
	this->v_mode.width = 800;
	this->window = new sf::RenderWindow(v_mode, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// INIT THE BLOCKS
	int numOfBlocks = 265;
	float heightOfBlocks = 5.0f;
	float widthOfBlocks = 2.0f;
	float blockGaps = 1.0f;
	for(int i = 0; i < numOfBlocks; i++)
	{
		int newheightOfBlocks = heightOfBlocks + i * 1.8;
		this->blocks[this->iblocks].setSize(sf::Vector2f(widthOfBlocks, newheightOfBlocks));
		this->blocks[this->iblocks].setPosition((widthOfBlocks + blockGaps) * i, this->window->getSize().y - newheightOfBlocks);
		this->blocks[this->iblocks].setFillColor(sf::Color::White);
		this->iblocks++;
	}

}

Game::~Game()
{
	delete this->window;
}

void Game::handleEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();

		else if (this->ev.type == sf::Event::KeyPressed)
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
	}

}

void Game::update()
{
}

void Game::render()
{
	this->window->clear();

	for (int i = 0; i < this->iblocks; i++)
	{
		this->window->draw(this->blocks[i]);
	}

	this->window->display();
}
