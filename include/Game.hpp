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

	// Functions
	void update();
	void handleEvents();
	void render();

	// Accessors
	bool isRunning() { return window->isOpen(); }

private:
	Algorithms* alg;
	Blocks* blocks;
	sf::RenderWindow* window = nullptr;
	sf::VideoMode v_mode;
	sf::Event ev;
};