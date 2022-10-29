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
	if (algNum == -1) selectedAlg = (selectedAlg + 1) % algList.size();
	else if (algNum == -2) selectedAlg = (selectedAlg + algList.size() - 1) % algList.size();
	else selectedAlg = algNum;
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
	case 3:
		Algorithms::bubbleSort();
		break;
	case 4:
		Algorithms::recursive_bubblesort();
		break;
	case 5:
		Algorithms::shellSort();
		break;
	case 6:
		Algorithms::gnomeSort();
		break;
	case 7:
		Algorithms::cocktailSort();
		break;
	case 8:
		Algorithms::quickSort();
		break;
	case 9:
		Algorithms::mergeSort();
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
	for (int i = 1;i < this->blocks.num_blocks;i++) // Start from index after first element
	{ 
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

// BUBBLE SORT --------------------------------------------------
void Algorithms::bubbleSort() {
	for(int i = 0; i < this->blocks.num_blocks - 1;i++)
		for(int j = 0; j < this->blocks.num_blocks - i - 1;j++)
			if(this->blocks.cmp(j, j+1) == 1)
				this->blocks.block_swap(j, j+1);
}

void r_bubblesort_main(Blocks& b_blocks, int n_blocks) {
	if (n_blocks == 1) return;

	int count = 0;

	for (int i = 0; i < n_blocks - 1; i++)
	{
		if (b_blocks.cmp(i, i + 1) == 1) {
			b_blocks.block_swap(i, i + 1);
			count++;
		}
	}

	if (count == 0) return;
	r_bubblesort_main(b_blocks, n_blocks - 1);
}

void Algorithms::recursive_bubblesort() {
	r_bubblesort_main(this->blocks, this->blocks.num_blocks);
}

// SHELL SORT ---------------------------------------------------
void Algorithms::shellSort() {
	for (int gap = this->blocks.num_blocks / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < this->blocks.num_blocks;i += 1)
		{
			int temp = this->blocks[i];
			int j;
			for (j = i; j >= gap && this->blocks[j - gap] > temp; j -= gap)
				this->blocks(j, this->blocks[j - gap]);
			this->blocks(j, temp);
		}
	}
}

// GNOME SORT ---------------------------------------------------
void Algorithms::gnomeSort() {
	int idx = 0;

	while (idx < this->blocks.num_blocks)
	{
		if (idx == 0) idx++;
		if (this->blocks[idx] >= this->blocks[idx - 1]) idx++;
		else {
			this->blocks.block_swap(idx, idx - 1);
			idx--;
		}
	}
}

// COCKTAIL SORT (LOOKS LIKE A COCKTAIL LOL) --------------------
void Algorithms::cocktailSort() {
	bool swapped = true;
	int start = 0;
	int end = this->blocks.num_blocks - 1;

	while (swapped)
	{
		swapped = false;
		for (int i = start; i < end; ++i)
		{
			if (this->blocks.cmp(i, i + 1) == 1)
			{
				this->blocks.block_swap(i, i + 1);
				swapped = true;
			}
		}

		if (!swapped) break;
		swapped = false;
		--end;

		for (int i = end - 1; i >= start; --i)
		{
			if (this->blocks.cmp(i, i + 1) == 1)
			{
				this->blocks.block_swap(i, i + 1);
				swapped = true;
			}
		}

		++start;
	}
}

// QUICK SORT ---------------------------------------------------
void Algorithms::quickSort() {
	quickSortMain(0, this->blocks.num_blocks - 1);
}

void Algorithms::quickSortMain(int l_idx, int r_idx) {
	if (l_idx < r_idx) {
		int pi = partition(l_idx, r_idx);
		quickSortMain(l_idx, pi - 1);
		quickSortMain(pi + 1, r_idx);
	}
}

int Algorithms::partition(int l_idx, int r_idx) {
	int pivot = this->blocks[r_idx];
	int i = l_idx - 1;

	for (int j = l_idx; j < r_idx; j++)
	{
		if (this->blocks[j] <= pivot)
		{
			i++;
			this->blocks.block_swap(i, j);
		}
	}

	this->blocks.block_swap(i + 1, r_idx);
	return (i + 1);
}


// MERGE SORT ---------------------------------------------------
void Algorithms::mergeSort() {

}

// RADIX SORT ---------------------------------------------------