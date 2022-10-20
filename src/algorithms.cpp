#include "Algorithms.hpp"

Algorithms::Algorithms(Blocks& _blocks):blocks(_blocks) {
	working = false;
	sorted = true;
	selectedAlg = 0;
}

void Algorithms::start() {
	if (working) return;
	working = true;
	if (this->sortingThread.joinable())
		this->sortingThread.join();
	sortingThread = std::thread(&Algorithms::algo, this);
}

void Algorithms::stop() {
	working = false;
	this->sortingThread.detach();
}

void Algorithms::setAlg(int algNum) {
	selectedAlg = algNum;
	std::cout << "ALGORITHM SELECTED: " << this->getAlg() << std::endl;
}

std::string Algorithms::getAlg() {
	return algList[selectedAlg];
}

void Algorithms::algo() {
	std::cout << "STARTING THREAD...." << sortingThread.get_id() << std::endl;
	switch (selectedAlg)
	{
	case 0:
		Algorithms::shuffle();
		break;
	case 1:
		Algorithms::insertionSort();
		break;
	case 2:
		Algorithms::selectionSort();
		break;
	}
	std::cout << "FINISHED THREAD...." << std::endl;
	working = false;
}

// ALGORITHMS //////////////////////////////////////////////////////////

// SHUFFLE -----------------------------------------------------
void Algorithms::shuffle() {
	std::random_shuffle(blocks.blockSize.begin(), blocks.blockSize.end());
	sorted = false;
}

// INSERTION SORT ----------------------------------------------
void Algorithms::insertionSort() {

	
	for (int i = 1;i < this->blocks.num_blocks;i++) { // Start from index after first element

		
		int curr = this->blocks[i]; // Get the current element
		int prev = i - 1;			// Get the previous index
		// While previous is not out of bounds &&
		// While current element is less than the previous element
		while (prev >= 0 && this->blocks[prev] > curr) {         
			this->blocks(prev + 1, this->blocks[prev]);	// Assign current index the value of previous element
			prev--;
		}
		this->blocks(prev + 1, curr); // Assign current index the value of current element
	}
}

// SELECTION SORT -----------------------------------------------
void Algorithms::selectionSort() {
	for (int i = 0; i < this->blocks.num_blocks - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < this->blocks.num_blocks;j++)
			if (this->blocks.cmp(j, min_idx) == -1)
				min_idx = j;
		if (min_idx != i)
			this->blocks.block_swap(min_idx, i);
	}
}

// QUICK SORT ---------------------------------------------------

// BUBBLE SORT --------------------------------------------------

// SHELL SORT ---------------------------------------------------

// MERGE SORT ---------------------------------------------------

// RADIX SORT ---------------------------------------------------