#include "Blocks.hpp"

Blocks::Blocks(int numBlocks, int maxHeight, int w):
	num_blocks(numBlocks), max_height(maxHeight), width(w) {

	// Init the blocks
	blockData = std::vector<sf::RectangleShape>(num_blocks);
	blockColors = std::vector<sf::Color>(num_blocks, sf::Color::White);
	
	for (int i=1;i<=num_blocks;i++)
	{
		blockSize.push_back(i*max_height/num_blocks);
	}
}

void Blocks::render(sf::RenderWindow* window) {
	float s_block = this->width/this->blockData.size();
	for (int i=0;i<this->blockData.size();i++)
	{
		this->blockData[i].setSize(sf::Vector2f(s_block, max_height));
		this->blockData[i].setPosition(i*s_block, max_height - blockSize[i]);
		this->blockData[i].setFillColor(this->blockColors[i]);
		window->draw(this->blockData[i]);
	}

}