#include "Blocks.hpp"

Blocks::Blocks(int numBlocks, int maxHeight, int w):
	num_blocks(numBlocks), max_height(maxHeight), width(w) {

	// Init the blocks
	blockData = std::vector<sf::RectangleShape>(num_blocks);
	blockColors = std::vector<sf::Color>(num_blocks, sf::Color::White);
}

void Blocks::render(sf::RenderWindow* window) {
	float s_block = this->width/this->num_blocks;
	for (int i = 0; i < this->num_blocks; i++)
	{
		this->blockData[i].setSize(sf::Vector2f(s_block, max_height));
		this->blockData[i].setPosition(i*s_block, max_height - i);
		this->blockData[i].setFillColor(this->blockColors[i]);
		window->draw(this->blockData[i]);
	}
}