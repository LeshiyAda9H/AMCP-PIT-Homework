#include "compressor.h"
#include <iostream>
#include <cstring>


int main(int argc, const char* argv[]) {
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "?") == 0) {
		help(std::cout);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		decompress(argv[argc - 2], argv[argc - 1]);
	}
	else {
		int way = 0;

		for (int index = 1; index < argc - 2; ++index) {
			if (strcmp(argv[index], "-mtf") == 0) { way += 1; }
			if (strcmp(argv[index], "-lz77") == 0) { way += 2; }
			if (strcmp(argv[index], "-huffman") == 0) { way += 4; }
		}

		compress(argv[argc - 2], argv[argc - 1], static_cast<char>(way));
	}
	return 0;
}