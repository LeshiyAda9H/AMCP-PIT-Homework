#include <fstream>
#include <cstring>
#include <iostream>


int findSubstring(const char* str, int strSize, const char* checked_string, int sizeCheckStr, int* tableBadSym){
	int counter = 0;

	int indxStrSymCheck = 0;
	int tmpSize = sizeCheckStr - strSize;
	
	while (indxStrSymCheck <= tmpSize){
		
		int indxStrSym = strSize - 1;
		
		while (checked_string[indxStrSymCheck + indxStrSym] == str[indxStrSym] && indxStrSym >= 0){
			--indxStrSym;
		}
		
		if (indxStrSym < 0){
			++counter;
		}

		int tmp = indxStrSym - tableBadSym[checked_string[indxStrSymCheck + indxStrSym]];
		
		indxStrSymCheck += (tmp < 1) ? 1 : tmp;
	}

	return counter;
}

int main(int argc, const char* argv[]){

	std::ifstream inFile(argv[2]);

	int counter = 0;

	int tableBadSym[256];
	int sizeStr = strlen(argv[1]);

	for (int i = 0; 256 > i; ++i){
		tableBadSym[i] = sizeStr;
	}
	
	for (int i = 0; sizeStr > i; ++i){
		tableBadSym[argv[1][i]] = i;
	}

	char buffer[524288 + 1024];

	while (!inFile.eof()){

		inFile.read(buffer, 524288);
		
		int size = inFile.gcount();
		
		buffer[size] = '\0';
		
		inFile.getline(buffer + 524288, 1024);
		
		size += inFile.gcount();

		counter += findSubstring(argv[1], sizeStr, buffer, size, tableBadSym);
	}

	std::cout << counter << std::endl;

	inFile.close();
	return 0;
}
