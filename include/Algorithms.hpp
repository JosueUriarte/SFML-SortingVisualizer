#pragma once
#include <iostream>
#include <algorithm>
#include <thread>

#include "Blocks.hpp"

class Algorithms {
public:
	// Constructor
	Algorithms(Blocks&);

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

	// Thread Function
	void algo();

private:
	// Data
	Blocks& blocks;
	const std::vector<std::string> algList = 
	{ "shuffle", "insertionSort", "selectionSort", "bubbleSort",
		"shellSort"};

	std::thread sortingThread;

	// Sorting algorithms
	void shuffle();
	void insertionSort();
	void selectionSort();
	void bubbleSort();
	void shellSort();
};