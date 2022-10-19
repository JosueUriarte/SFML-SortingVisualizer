#include "Algorithms.hpp"

Algorithms::Algorithms(Blocks& _blocks):blocks(_blocks) {
	working = false;
	sorted = false;
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
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		break;
	case 1:
		Algorithms::insertionSort();
		break;
	}

	std::cout << "FINISHED THREAD...." << std::endl;
	this->sortingThread.detach();
	working = false;
}

// ALGORITHMS --------------------------------------------------

// SHUFFLE -----------------------------------------------------
void Algorithms::shuffle() {
	std::random_shuffle(blocks.blockSize.begin(), blocks.blockSize.end());
	sorted = false;
}

void Algorithms::insertionSort() {

}