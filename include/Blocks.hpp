#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

class Blocks {
public:
	// Constructor
	Blocks(int numBlocks, int maxHeight, int w);

	// Data
	std::vector<sf::RectangleShape> blockData;
	std::vector<sf::Color> blockColors;
	std::vector<int> blockSize;

	// Variables
	int num_blocks;
	int max_height;
	int width;

	// Renderer
	void render(sf::RenderWindow* window);

private:
};