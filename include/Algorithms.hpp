#pragma once
#include <iostream>
#include "Blocks.hpp"

class Algorithms {
public:
	// Constructor
	Algorithms(Blocks& _blocks);

	// Controllers
	void start();
	void stop();

	// Variables
	bool working;
	bool sorted;
	int selectedAlg;

	// Setters
	void setAlg(int algnumber);		// Set the algorithm to use

	// Getters
	std::string getAlg();			// Get the current algorithm name

private:
	// Data
	Blocks& blocks;

	const std::vector<std::string> algList = { "shuffle", "insertionSort" };

	// Sorting algorithms
	void shuffle();
	void insertionSort();
};