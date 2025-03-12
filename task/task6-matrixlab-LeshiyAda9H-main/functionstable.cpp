#include "functionstable.h"
#include <cstring>

const FuncMMInfo FunctionsMMTable::FMMTable[] = {
	{"+", addition},
	{".*", elementByElementMultiplication},
	{"./", elementByElementDivision},
	{"*", matrixMultiplication},
	{"/", matrixDivision},
	{"min", min},
	{"max", max}
};

const int FunctionsMMTable::sizeFMMTable = sizeof(FunctionsMMTable::FMMTable) / sizeof(FunctionsMMTable::FMMTable[0]);

int FunctionsMMTable::funcMMNumberByName(const char* request) {
	for (int index = 0; index < sizeFMMTable; ++index) {
		if (strcmp(FMMTable[index].name, request) == 0) {
			return index;
		}
	}
	return -1;
}

const FuncMMInfo& FunctionsMMTable::getFuncMM(int index) {
	if (index >= 0 && index < sizeFMMTable) {
		return FMMTable[index];
	}
	throw "Invalid index";
}

const FuncMInfo FunctionsMTable::FMTable[] = {
	{"transpose", transpose},
	{"det", det},
	{"inv", inverse},
	{"sum", sum},
	{"prod", prod},
	{"diag", diag}
};

const int FunctionsMTable::sizeFMTable = sizeof(FunctionsMTable::FMTable) / sizeof(FunctionsMTable::FMTable[0]);

int FunctionsMTable::funcMNumberByName(const char* request) {
	for (int index = 0; index < sizeFMTable; ++index) {
		if (strcmp(FMTable[index].name, request) == 0) {
			return index;
		}
	}
	return -1;
}

const FuncMInfo& FunctionsMTable::getFuncM(int index) {
	if (index >= 0 && index < sizeFMTable) {
		return FMTable[index];
	}
	throw "Invalid index";
}

const FuncUIUIInfo FunctionsUIUITable::FUIUITable[] = {
	{"zeros", zeros},
	{"eye", eye},
	{"ones", ones}
};

const int FunctionsUIUITable::sizeFUIUITable = sizeof(FunctionsUIUITable::FUIUITable) / sizeof(FunctionsUIUITable::FUIUITable[0]);

int FunctionsUIUITable::funcUIUINumberByName(const char* request) {
	for (int index = 0; index < sizeFUIUITable; ++index) {
		if (strcmp(FUIUITable[index].name, request) == 0) {
			return index;
		}
	}
	return -1;
}

const FuncUIUIInfo& FunctionsUIUITable::getFuncUIUI(int index) {
	if (index >= 0 && index < sizeFUIUITable) {
		return FUIUITable[index];
	}
	throw "Invalid index";
}

const FuncMmInfo FunctionsMmTable::FMmTable[] = {
	{"vertcat", vertcat},
	{"horzcat", horzcat}
};

const int FunctionsMmTable::sizeFMmTable = sizeof(FunctionsMmTable::FMmTable) / sizeof(FunctionsMmTable::FMmTable[0]);

int FunctionsMmTable::funcMmNumberByName(const char* request) {
	for (int index = 0; index < sizeFMmTable; ++index) {
		if (strcmp(FMmTable[index].name, request) == 0) {
			return index;
		}
	}
	return -1;
}

const FuncMmInfo& FunctionsMmTable::getFuncMm(int index) {
	if (index >= 0 && index < sizeFMmTable) {
		return FMmTable[index];
	}
	throw "Invalid index";
}
