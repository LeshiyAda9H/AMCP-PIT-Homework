#include "compressor.h"
#include "algorithms.h"

void compress(const char* in, const char* out, char way) {
	ibitfstream inFile(in);
	if (!inFile.is_open()) {
		std::cerr << "Can not open input file" << std::endl;
		return;
	}
	
	switch (way) {
	case 1: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		mtfEncode(inFile, outFile);
		outFile.close();
		break;
	}
	case 2: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		lz77Encode(inFile, outFile);
		outFile.close();
		break;
	}
	case 3: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		mtfEncode(inFile, tmpOutputFile);
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		lz77Encode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 4: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		huffEncode(inFile, outFile);
		outFile.close();
		break;
	}
	case 5: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		mtfEncode(inFile, tmpOutputFile);
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		huffEncode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 6: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		lz77Encode(inFile, tmpOutputFile);
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		outFile.put(way);
		huffEncode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 7: {
		obitfstream tmpOutputFile(out);
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		mtfEncode(inFile, tmpOutputFile);
		tmpOutputFile.close();

		ibitfstream tmpInputFile(out);
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream tmpOutputFile2("tmp.txt");
		if (!tmpOutputFile2.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		lz77Encode(tmpInputFile, tmpOutputFile2);
		tmpInputFile.close();
		tmpOutputFile2.close();

		ibitfstream tmpInputFile2("tmp.txt");
		if (!tmpInputFile2.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		outFile.put(way);
		huffEncode(tmpInputFile2, outFile);

		tmpInputFile2.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	}
	inFile.close();
}
void decompress(const char* in, const char* out) {
	ibitfstream inFile(in);
	if (!inFile.is_open()) {
		std::cerr << "Can not open input file" << std::endl;
		return;
	}

	int way = inFile.get();
	switch (way) {
	case 1: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		mtfDecode(inFile, outFile);
		outFile.close();
		break;
	}
	case 2: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			return;
		}
		lz77Decode(inFile, outFile);
		outFile.close();
		break;
	}
	case 3: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		lz77Decode(inFile, tmpOutputFile);
		inFile.close();
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		mtfDecode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 4: {
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		huffDecode(inFile, outFile);
		outFile.close();
		break;
	}
	case 5: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		huffDecode(inFile, tmpOutputFile);
		inFile.close();
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		mtfDecode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 6: {
		obitfstream tmpOutputFile("tmp.txt");
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		huffDecode(inFile, tmpOutputFile);
		inFile.close();
		tmpOutputFile.close();

		ibitfstream tmpInputFile("tmp.txt");
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		lz77Decode(tmpInputFile, outFile);

		tmpInputFile.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
		break;
	}
	case 7: {
		obitfstream tmpOutputFile(out);
		if (!tmpOutputFile.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		huffDecode(inFile, tmpOutputFile);
		inFile.close();
		tmpOutputFile.close();

		ibitfstream tmpInputFile(out);
		if (!tmpInputFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		obitfstream tmpOutputFile2("tmp.txt");
		if (!tmpOutputFile2.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		lz77Decode(tmpInputFile, tmpOutputFile2);
		tmpInputFile.close();
		tmpOutputFile2.close();

		ibitfstream tmpInputFile2("tmp.txt");
		if (!tmpInputFile2.is_open()) {
			std::cerr << "Can not open auxiliary file" << std::endl;
			break;
		}
		obitfstream outFile(out);
		if (!outFile.is_open()) {
			std::cerr << "Can not open output file" << std::endl;
			break;
		}
		mtfDecode(tmpInputFile2, outFile);

		tmpInputFile2.close();
		if (remove("tmp.txt") == -1) {
			std::cerr << "Can not delete auxiliary file" << std::endl;
			break;
		}
		outFile.close();
	}
	}
	inFile.close();
}

void help(std::ostream& out) {
	out << "Use compress as:\n1. compress ?\n2. compress -h\n3. compress -mtf input output\n" <<
		"4. compress -lz77 input output\n5. compress -huffman input output\n" <<
		"6. compress -mtf -huffman input output\n7. compress -mtf -lz77 input output\n" <<
		"8. compress -huffman -lz77 input output\n9. compress -mtf -huffman -lz77 input output\n";
}
