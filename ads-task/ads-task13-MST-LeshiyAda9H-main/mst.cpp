#include <iostream>
#include <fstream>


class Graph {
private:
	struct Edge	{
		int start;
		int end;
		int length;
	};
	
	int numberVertex;
	int numberEdge;

	Edge* mas;

	Edge* MergeSortA(Edge* M, int n) {

		Edge* tmp = new Edge[n];
		Edge* from = M;
		Edge* to = tmp;
		for (int step = 1; step < n; step *= 2) {
			int start1, end1, start2, end2;
			int indto = 0;
			for (int start = 0; start < n; start += 2 * step) {
				start1 = start; end1 = start1 + step; end1 = end1 < n ? end1 : n;
				start2 = end1;  end2 = start2 + step; end2 = end2 < n ? end2 : n;
				while (start1 < end1 && start2 < end2) {

					to[indto++] = (from[start1].length < from[start2].length) ? from[start1++] : from[start2++];
				}
				while (start1 < end1) {
					to[indto++] = from[start1++];
				}
				while (start2 < end2) {
					to[indto++] = from[start2++];
				}
			}

			std::swap(from, to);
		}

		delete[] to;
		return from;
	}

	int find(int* masInt, int X) {
		if (masInt[X] == X) {
			return X;
		}
		return masInt[X] = find(masInt, masInt[X]);
	}


public:
	Graph(int nV, int nE) : numberVertex(nV), numberEdge(0) {
		mas = new Edge[nE];
	}

	void addEdge(int start, int end, int lenght) {
		if (start < end)
		{
			mas[numberEdge].start = start;
			mas[numberEdge].end = end;
		}
		else
		{
			mas[numberEdge].start = end;
			mas[numberEdge].end = start;
		}
		mas[numberEdge].length = lenght;
		++numberEdge;
	}

	

	int alcKrascal() {

		mas = MergeSortA(mas, numberEdge);
		
		int* masInt = new int[numberVertex];
		int* sizeH = new int[numberVertex];
		for (int i = 0; i < numberVertex; ++i) {
			masInt[i] = i;
			sizeH[i] = 0;
		}

		int counter = 0;
		int sum = 0;
		int indxE = 0;
		int foundFirst = 0;
		int foundSecond = 0;

		while (numberVertex - 1 > counter ) {
			
			foundFirst = find(masInt, mas[indxE].start);
			foundSecond = find(masInt, mas[indxE].end);

			if (foundFirst != foundSecond) {
				sum += mas[indxE].length;
				++counter;

				if (sizeH[foundFirst] > sizeH[foundSecond]) {
					masInt[foundSecond] = foundFirst;
				}
				else {
					masInt[foundFirst] = foundSecond;
				}

				if (sizeH[foundFirst] == sizeH[foundSecond]) {
					++sizeH[foundSecond];
				}

			}
			++indxE;
		}
		delete[] sizeH;
		delete[] masInt;

		return sum;
	}
	
	~Graph() {
		delete[] mas;
	}
};

int main(int argc, const char* argv[]){
   
	std::ifstream inFile(argv[1]);

	int nE = 0;
	int nV = 0;

	inFile >> nV >> nE;

	Graph graph(nV,nE);

	for (int indxE = 0; indxE < nE; ++indxE) {

		int vFirst = 0;
		int vSecond = 0;
		int length = 0;

		inFile >> vFirst >> vSecond >> length;

		graph.addEdge(vFirst, vSecond, length);
	}

	std::cout << graph.alcKrascal();

	inFile.close();
	return 0;
}
