#include "Algorithms.hpp"

Algorithms::Algorithms(Blocks& _blocks):blocks(_blocks) {
	working = false;
	sorted = false;
	selectedAlg = 0;
}

void Algorithms::start() {
	if (working) return;
	working = true;
}

void Algorithms::stop() {
	working = false;
}

void Algorithms::setAlg(int algNum) {
	selectedAlg = algNum;
}

std::string Algorithms::getAlg() {
	return "alg";
}