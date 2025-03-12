#include "algorithms.h"
#include "node.h"
#include <iostream>

const int ASCIISIZE = 256;
const int LZ77BUFFSIZE = 128;
const int LEN = LZ77BUFFSIZE << 1;
const int LENMINUSONE = LEN - 1;
const int LAST7BITS = 127;

Node** buildHuffmanTree(int* arrayFrequencies, Node** ASCII) {
	for (int index = 0; index < ASCIISIZE; ++index) {

		ASCII[index] = new Node(static_cast<unsigned char>(index), arrayFrequencies[index]);

		for (int jndex = index; jndex > 0; --jndex) {
			if (ASCII[jndex - 1]->frequency > ASCII[jndex]->frequency) { break; }

			std::swap(ASCII[jndex - 1], ASCII[jndex]);
		}
	}

	int lastNon_ZeroElement = ASCIISIZE - 1;

	while (lastNon_ZeroElement > 1 &&
		ASCII[lastNon_ZeroElement]->frequency == 0) {
		delete ASCII[lastNon_ZeroElement];
		--lastNon_ZeroElement;
	}

	Node** arrayLeafs = new Node * [ASCIISIZE] {};

	for (; lastNon_ZeroElement > 0; --lastNon_ZeroElement) {

		if (ASCII[lastNon_ZeroElement]->left == nullptr && ASCII[lastNon_ZeroElement]->right == nullptr) {
			arrayLeafs[static_cast<int>(ASCII[lastNon_ZeroElement]->symbol)] = ASCII[lastNon_ZeroElement];
		}
		if (ASCII[lastNon_ZeroElement - 1]->left == nullptr && ASCII[lastNon_ZeroElement - 1]->right == nullptr) {
			arrayLeafs[static_cast<int>(ASCII[lastNon_ZeroElement - 1]->symbol)] = ASCII[lastNon_ZeroElement - 1];
		}

		ASCII[lastNon_ZeroElement - 1] = new Node(ASCII[lastNon_ZeroElement - 1], ASCII[lastNon_ZeroElement]);

		for (int index = lastNon_ZeroElement - 1; index > 0; --index) {
			if (ASCII[index - 1]->frequency > ASCII[index]->frequency) { break; }

			std::swap(ASCII[index - 1], ASCII[index]);
		}
	}

	return arrayLeafs;
}

void mtfEncode(ibitfstream& inFile, obitfstream& outFile) {

	unsigned char ASCII[ASCIISIZE]{};

	for (int index = 0; index < ASCIISIZE; ++index) {
		ASCII[index] = static_cast<unsigned char> (index);
	}

	int current = 0;

	while ((current = inFile.get()) != EOF) {
		int index = 0;

		unsigned char impostor = ASCII[0];
		while (impostor != current) {
			std::swap(impostor, ASCII[++index]);
		}

		outFile.put(static_cast<char>(index));
		ASCII[0] = impostor;
	}
}
void mtfDecode(ibitfstream& inFile, obitfstream& outFile) {

	char ASCII[ASCIISIZE]{};

	for (int index = 0; index < ASCIISIZE; ++index) {
		ASCII[index] = static_cast<char> (index);
	}

	int current = 0;

	while ((current = inFile.get()) != EOF) {
		int index = 0;
		char impostor = ASCII[0];

		while (index != current) {
			std::swap(impostor, ASCII[++index]);
		}

		outFile.put(impostor);
		ASCII[0] = impostor;
	}
}
void huffEncode(ibitfstream& inFile, obitfstream& outFile) {

	int arrayFrequencies[ASCIISIZE]{ 0 };
	int current = 0;
	while ((current = inFile.get()) != EOF) {
		++arrayFrequencies[current];
	}

	inFile.clear();
	inFile.seekg(0);

	Node* ASCII[ASCIISIZE]{};

	Node** arrayLeafs = buildHuffmanTree(arrayFrequencies, ASCII);

	for (int index = 0; index < ASCIISIZE; ++index) {
		outFile.write(reinterpret_cast<const char*>(&arrayFrequencies[index]), sizeof(int));
	}

	while ((current = inFile.get()) != EOF) {

		Node* node = arrayLeafs[current];
		bool bits[ASCIISIZE]{};
		int index = 0;

		while (node->parent != nullptr) {
			if (node->parent->right == node) {
				bits[index++] = true;
			}
			else {
				bits[index++] = false;
			}
			node = node->parent;
		}
		--index;

		for (; index >= 0; --index) {
			outFile.putbit(bits[index]);
		}
	}
	outFile.cleanBuf();

	delete[] arrayLeafs;
	delete ASCII[0];
}
void huffDecode(ibitfstream& inFile, obitfstream& outFile) {
	int arrayFrequencies[ASCIISIZE]{ 0 };
	unsigned long long countSymbols = 0;

	for (int index = 0; index < ASCIISIZE; ++index) {
		inFile.read(reinterpret_cast<char*>(&arrayFrequencies[index]), sizeof(int));
		countSymbols += arrayFrequencies[index];
	}

	Node* ASCII[ASCIISIZE]{};

	Node** trash = buildHuffmanTree(arrayFrequencies, ASCII);

	while (countSymbols > 0) {
		Node* node = ASCII[0];
		while (node->left != nullptr || node->right != nullptr) {
			int current = inFile.getbit();

			if (current == 0) {
				node = node->left;
			}
			else {
				node = node->right;
			}
		}
		outFile.put(static_cast<char>(node->symbol));
		--countSymbols;
	}

	delete[] trash;
	delete ASCII[0];
}
void lz77Encode(ibitfstream& inFile, obitfstream& outFile) {

	long long lenBuffer = 0;
	long long countSym = 0;

	inFile.seekg(0, std::ios_base::end);
	unsigned long long size = inFile.tellg();
	if (size == 0) {
		return;
	}

	inFile.seekg(0, std::ios_base::beg);
	unsigned char file[LEN];
	unsigned char buffer[LEN];

	inFile.read(reinterpret_cast<char*>(file), LEN);

	while (countSym < size) {

		int indexInFile = static_cast<int>(countSym % LEN);

		int offset = 0;
		int maxLenMatch = 0;
		int symbol = static_cast<int>(file[indexInFile]);

		for (long long i = indexInFile - lenBuffer; i < indexInFile; ++i) {
			int curLengthMatch = 0;
			int curIndexInFile = 0;

			while (curIndexInFile < LENMINUSONE && curIndexInFile < size - countSym) {
				unsigned char sym;
				unsigned char compareSym;

				if ((curIndexInFile + i) >= 0) {
					if ((curIndexInFile + i) < LEN) {
						sym = file[curIndexInFile + i];
					}
					else {
						int counter = static_cast<int>(curIndexInFile + i - LENMINUSONE);
						for (int i = 0; i < counter; ++i) {
							sym = inFile.get();
						}
						for (int i = 0; i < counter; ++i) {
							inFile.unget();
						}
					}
				}
				else {
					sym = buffer[curIndexInFile + i + LEN];
				}


				if (curLengthMatch + indexInFile < LEN) {
					compareSym = file[curLengthMatch + indexInFile];
				}
				else {
					int counter = curLengthMatch + indexInFile - LENMINUSONE;
					for (int i = 0; i < counter; ++i) {
						compareSym = static_cast<unsigned char>(inFile.get());
					}
					for (int i = 0; i < counter; ++i) {
						inFile.unget();
					}
				}

				if (sym == compareSym) {
					++curLengthMatch;
					++curIndexInFile;
				}
				else {
					break;
				}
			}

			if (curLengthMatch != 0 && curLengthMatch >= maxLenMatch) {
				maxLenMatch = curLengthMatch;
				offset = static_cast<int>(indexInFile - i);
				if (countSym + curLengthMatch < size) {
					if (indexInFile + curLengthMatch < LEN) {
						symbol = file[indexInFile + curLengthMatch];
					}
					else {
						int counter = indexInFile + curLengthMatch - LENMINUSONE;
						for (int i = 0; i < counter; ++i) {
							symbol = inFile.get();
						}
						for (int i = 0; i < counter; ++i) {
							inFile.unget();
						}
					}
				}
				else {
					symbol = -1;
				}
			}
		}

		countSym += maxLenMatch;
		++countSym;

		indexInFile += maxLenMatch;
		++indexInFile;
		if (indexInFile >= LEN) {
			indexInFile -= LEN;
			std::swap(buffer, file);
			inFile.read(reinterpret_cast<char*>(file), LEN);
		}

		if (countSym > LZ77BUFFSIZE) {
			lenBuffer = LZ77BUFFSIZE;
		}
		else {
			lenBuffer = indexInFile;
		}
		outFile.put(static_cast<char> (offset));
		outFile.put(static_cast<char> (maxLenMatch));
		if (symbol != -1) {
			outFile.put(static_cast<char>(symbol));
		}
	}
}

void lz77Decode(ibitfstream& inFile, obitfstream& outFile) {
	unsigned char buffer[LZ77BUFFSIZE]{};
	unsigned long long beginBuffer = 0;

	while (inFile.peek() != EOF) {

		int offset = inFile.get();
		int length = inFile.get();
		int symbol = inFile.get();

		int beginCoincidence = static_cast<int>((beginBuffer - offset) & LAST7BITS);

		for (int index = 0; index < length; ++index) {

			int position = (beginCoincidence + index) & LAST7BITS;
			buffer[beginBuffer & LAST7BITS] = buffer[position];

			++beginBuffer;
			outFile.put(static_cast<char>(buffer[position]));
		}

		buffer[beginBuffer & LAST7BITS] = static_cast<unsigned char>(symbol);
		++beginBuffer;
		if (symbol != EOF) { outFile.put(static_cast<char>(symbol)); }
	}
}