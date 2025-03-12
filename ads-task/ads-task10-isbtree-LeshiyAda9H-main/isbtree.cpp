#include <iostream>
#include <fstream>
#include <limits>

struct Node{
	int number;
	int* key;
	int stashCounter;
	int* numberKids;
	int stashCounterKids;
	bool isLeaf;

	Node() : key(nullptr), numberKids(nullptr), number(0), stashCounter(0), stashCounterKids(0), isLeaf(false) {}
	~Node() {
		delete[] key;
		delete[] numberKids;
	}
};

void BubbleSort(Node** M, int n) {

	for (int step = 1; step < n; ++step) {
		bool isSorted = true;
		for (int i = n - 1; i >= step; --i) {
			if (M[i]->number < M[i - 1]->number) {
				isSorted = false;
				std::swap(M[i], M[i - 1]);
			}
		}
		if (isSorted) break;
	}
}

int binarySearch(Node** Btree, int N, int number) {
	int left = 0;
	int right = N - 1;

	while (left < right) {
		int mid = (left + right) / 2;
		if (Btree[mid]->number < number) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}

	return Btree[left]->number == number ? left : -1;
}

int check(Node** Btree, int N, const Node& cur, int left, int right) {
	for (int i = 0; i < cur.stashCounter; ++i) {
		if (cur.key[i] < left || right < cur.key[i]) { return -1; }
	}

	if (cur.isLeaf) { return 0; }

	int firstChild = binarySearch(Btree, N, cur.numberKids[0]);
	if (firstChild < 0) { return -1; }
	int lvl = check(Btree, N, *Btree[firstChild], left, cur.key[0]);
	if (lvl < 0) { return -1; }

	for (int i = 1; i < cur.stashCounter; ++i) {
		int midChild = binarySearch(Btree, N, cur.numberKids[i]);
		if (midChild < 0 || lvl != check(Btree, N, *Btree[binarySearch(Btree, N, cur.numberKids[i])], cur.key[i - 1], cur.key[i])) {
			return -1;
		}
	}

	int lastChild = binarySearch(Btree, N, cur.numberKids[cur.stashCounterKids - 1]);
	if (lastChild < 0 || lvl != check(Btree, N, *Btree[lastChild], cur.key[cur.stashCounter - 1], right)) { return -1; }

	return lvl + 1;
}

int main(int argv, const char* argc[]) {

	std::ifstream inFile(argc[1]);

	int N = 0;
	int t = 0;
	int root = 0;

	inFile >> N >> t >> root;

	Node** Btree = new Node*[N];

	for (int i = 0; i < N; ++i) {

		while (isalpha(inFile.peek()) == 0) { inFile.ignore(); }

		Btree[i] = new Node;

		if (inFile.peek() == 'b') {
			Btree[i]->isLeaf = 0;
		}
		if (inFile.peek() == 'l') {
			Btree[i]->isLeaf = 1;
		}

		while (inFile.get() != 'x') {}

		inFile >> Btree[i]->number;

		while (isdigit(inFile.peek()) == 0) {
			inFile.ignore();
		}

		inFile >> Btree[i]->stashCounter;

		if (root != Btree[i]->number && (2*t-1 < Btree[i]->stashCounter || Btree[i]->stashCounter < t - 1  )) {
			std::cout << "no";
			for (int j = 0; j <= i; ++j) {
				delete Btree[j];
			}
			delete[] Btree;
			return 0;
		}

		inFile.ignore();

		Btree[i]->key = new int[Btree[i]->stashCounter];
		inFile >> Btree[i]->key[0];

		for (int j = 1; j < Btree[i]->stashCounter; ++j) {
			inFile >> Btree[i]->key[j];

			if (Btree[i]->key[j] < Btree[i]->key[j - 1]) {
				std::cout << "no";
				for (int j = 0; j <= i; ++j) {
					delete Btree[j];
				}
				delete[] Btree;
				return 0;
			}
		}



		if (Btree[i]->isLeaf) {
			inFile.ignore();
			if (inFile.get() != '\n') {
				std::cout << "no";
				for (int j = 0; j <= i; ++j) {
					delete Btree[j];
				}
				delete[] Btree;
				return 0;
			}
		}
		else {
			while (isdigit(inFile.peek()) == 0) {
				inFile.ignore();
			}

			inFile >> Btree[i]->stashCounterKids;

			if (Btree[i]->stashCounterKids != Btree[i]->stashCounter + 1 ) {
				std::cout << "no";
				for (int j = 0; j <= i; ++j) {
					delete Btree[j];
				}
				delete[] Btree;
				return 0;
			}

			inFile.ignore();


			Btree[i]->numberKids = new int[Btree[i]->stashCounterKids];

			for (int j = 0; j < Btree[i]->stashCounterKids; ++j) {
				inFile >> Btree[i]->numberKids[j];
			}

			while (inFile.get() != '\n' && inFile.peek() != EOF) {}

		}
		
	}

	BubbleSort(Btree, N);
	if (check(Btree, N, *Btree[binarySearch(Btree, N, root)], std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) < 0) {
		std::cout << "no";
	}
	else {
		std::cout << "yes";
	}

	for (int j = 0; j < N; ++j) {
		delete Btree[j];
	}

	delete[] Btree;

	return 0;
}
