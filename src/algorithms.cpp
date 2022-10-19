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
	for (int i = 1;i < this->blocks.num_blocks;++i) {
		int curr = this->blocks[i];
		int prev = i - 1;

		while (prev >= 0 && curr < this->blocks[prev]) {
			this->blocks(prev + 1, this->blocks[prev]);
			--prev;
		}
		this->blocks(prev + 1, curr);
	}
}