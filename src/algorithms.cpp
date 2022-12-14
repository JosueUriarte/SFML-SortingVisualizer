#include "Algorithms.hpp"
#include <random>
#include <chrono>


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
	if (selectedAlg == 0) shuffle();
	else if (selectedAlg == 1) insertionSort();
	else if (selectedAlg == 2) selectionSort();
	else if (selectedAlg == 3) bubbleSort();
	else if (selectedAlg == 4) recursive_bubblesort();
	else if (selectedAlg == 5) shellSort();
	else if (selectedAlg == 6) gnomeSort();
	else if (selectedAlg == 7) cocktailSort();
	else if (selectedAlg == 8) quickSort();
	else if (selectedAlg == 9) mergeSort();
	else if (selectedAlg == 10) radixSort();
	else if (selectedAlg == 11) heapSort();
	std::cout << "FINISHED THREAD...." << std::endl;
	working = false;
}

// ALGORITHMS //////////////////////////////////////////////////////////

// SHUFFLE BLOCKS -----------------------------------------------------
void Algorithms::shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(blocks.blockSize.begin(), blocks.blockSize.end(), g);
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
void merge(Blocks& _blocks, int left, int mid, int right) {
	auto subArrOne = mid - left + 1;
	auto subArrTwo = right - mid;

	// Create temp arr
	auto*leftArray = new int[subArrOne],
		*rightArray = new int[subArrTwo];

	// Copy data to temp arr
	for (int i = 0; i < subArrOne; i++)
		leftArray[i] = _blocks[left + i];
	for (int i = 0; i < subArrTwo; i++)
		rightArray[i] = _blocks[mid + 1 + i];

	int idxSubArrOne = 0;
	int idxSubArrTwo = 0;
	int idxMergedArr = left;

	while (idxSubArrOne < subArrOne && idxSubArrTwo < subArrTwo)
	{
		if (leftArray[idxSubArrOne] <= rightArray[idxSubArrTwo])
		{
			_blocks(idxMergedArr, leftArray[idxSubArrOne]);
			idxSubArrOne++;
		}
		else {
			_blocks(idxMergedArr, rightArray[idxSubArrTwo]);
			idxSubArrTwo++;
		}
		idxMergedArr++;
	}

	// Copy remaining left elements
	while (idxSubArrOne < subArrOne)
	{
		_blocks(idxMergedArr, leftArray[idxSubArrOne]);
		idxSubArrOne++;
		idxMergedArr++;
	}

	// Copy remaining right elements
	while (idxSubArrTwo < subArrTwo)
	{
		_blocks(idxMergedArr, rightArray[idxSubArrTwo]);
		idxSubArrTwo++;
		idxMergedArr++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void main_merge_sort(Blocks& t_blocks, int begin, int end) {
	if (begin >= end) // BASE CASE
		return;

	auto midpoint = begin + (end - begin) / 2;
	main_merge_sort(t_blocks, begin, midpoint);
	main_merge_sort(t_blocks, midpoint + 1, end);
	merge(t_blocks, begin, midpoint, end);
}

void Algorithms::mergeSort() {
	main_merge_sort(this->blocks, 0, this->blocks.num_blocks - 1);
}

// RADIX SORT ---------------------------------------------------

// Counting sort for the radix sort
void countSort(Blocks& _blocks, int exp) {
	int* output = new int[_blocks.num_blocks];
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < _blocks.num_blocks; i++)
		count[(_blocks[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = _blocks.num_blocks - 1; i >= 0; i--)
	{
		output[count[(_blocks[i] / exp) % 10] - 1] = _blocks[i];
		count[(_blocks[i] / exp) % 10]--;
	}

	// Copy the output array to _blocks[], so that _blocks[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < _blocks.num_blocks; i++)
		_blocks(i, output[i]);
}

void Algorithms::radixSort() {
	int max = this->blocks[0];
	for (int i = 1; i < this->blocks.num_blocks; i++)
		if (this->blocks[i] > max)
			max = this->blocks[i];

	for (int exp = 1; max / exp > 0; exp *= 10)
		countSort(this->blocks, exp);
}

// HEAP SORT ---------------------------------------------------
// heapify
void heapify(Blocks& _blocks, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && _blocks[l] > _blocks[largest])
		largest = l;

	if (r < n && _blocks[r] > _blocks[largest])
		largest = r;

	if (largest != i) {
		_blocks.block_swap(i, largest);
		heapify(_blocks, n, largest);
	}
}
void Algorithms::heapSort() {
	// Build heap (rearrange array)
	for (int i = this->blocks.num_blocks / 2 - 1; i >= 0; i--)
		heapify(this->blocks, this->blocks.num_blocks, i);

	// One by one extract an element from heap
	for (int i = this->blocks.num_blocks - 1; i >= 0; i--)
	{
		// Move current root to end
		this->blocks.block_swap(0, i);

		// call max heapify on the reduced heap
		heapify(this->blocks, i, 0);
	}
}