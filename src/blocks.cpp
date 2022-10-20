#include "Blocks.hpp"

Blocks::Blocks(int numBlocks, int maxHeight, int w):
	num_blocks(numBlocks), max_height(maxHeight + 1), width(w) {

	// Init the blocks
	blockData = std::vector<sf::RectangleShape>(num_blocks);
	blockColors = std::vector<sf::Color>(num_blocks, sf::Color::White);
	
	for (int i=1;i<=num_blocks;i++)
	{
		blockSize.push_back(i*max_height/num_blocks);
	}
}

// Render all the blocks (SHAPE, COLOR, SIZE)
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

// Functions to compare and swap blocks --------------------------------
int Blocks::cmp(int i, int j) {
	int a = this->operator[](i);
	int b = this->operator[](j);

	if (a == b)
		return 0;
	else if (a < b)
		return -1;
	else
		return 1;
}

void Blocks::block_swap(int i, int j) {
	int temp = this->operator[](i);
	this->operator()(i, this->operator[](j));
	this->operator()(j, temp);
}

// Override functions to create delays and sound effects ----------------------
int Blocks::operator[](int i) {
	if (i >= this->num_blocks || i < 0) {
		std::cout << "OUT OF BOUNDS VALUE OPERATOR[]: " << i << std::endl;
		return 0;
	}
	int b_val = this->blockSize[i];
	std::this_thread::sleep_for(std::chrono::nanoseconds(500));		// Pause to "read" value
	return b_val;
}

void Blocks::operator()(int dest, int val) {
	if (dest>=num_blocks || dest < 0) {
		std::cout << "OUT OF BOUNDS VALUE OPERATOR(): " << dest << std::endl;
		return;
	}
	std::this_thread::sleep_for(std::chrono::nanoseconds(500));		// Pause to "write" value
	this->blockSize[dest] = val;
}