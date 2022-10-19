#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

#include <Algorithms.hpp>
#include <Blocks.hpp>

class Game
{
public:
	// Constructors / Destructors
	Game(char* title);
	~Game();

	// Game Objects
	//sf::RectangleShape blocks[1000];

	// Functions
	void update();
	void handleEvents();
	void render();

	// Accessors
	bool isRunning() { return window->isOpen(); }

private:
	int iblocks = 0;
	float dx = 2.0f, dy = 4.0f;
	Algorithms* alg;
	Blocks* blocks;
	sf::RenderWindow* window = nullptr;
	sf::VideoMode v_mode;
	sf::Event ev;
};