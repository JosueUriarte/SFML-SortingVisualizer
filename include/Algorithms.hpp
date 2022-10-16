#pragma once
#include <iostream>
#include "Blocks.hpp"

class Algorithms {
public:
	// Constructor
	Algorithms(int blocks);

	// Controllers
	void start();
	void stop();

	// Variables
	bool working;
	bool sorted;
	int selectedAlg;

	// Setters
	void setAlg(int algnumber);

	// Getters
	std::string getAlg();
};