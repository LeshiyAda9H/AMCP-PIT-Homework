#ifndef FUNCTIONS_TABLE
#define FUNCTIONS_TABLE

#include "matrix.h"


typedef Matrix(*pfuncUIUI) (unsigned int, unsigned int);
typedef Matrix(*pfuncM) (const Matrix&);
typedef Matrix(*pfuncMM) (const Matrix&, const Matrix&);
typedef Matrix& (*pfuncMm) (Matrix&, const Matrix&);


struct FuncMMInfo {
	const char* name;
	pfuncMM func;
};
struct FuncMInfo {
	const char* name;
	pfuncM func;
};
struct FuncUIUIInfo {
	const char* name;
	pfuncUIUI func;
};
struct FuncMmInfo {
	const char* name;
	pfuncMm func;
};

class FunctionsMMTable {
	static const FuncMMInfo FMMTable[];
	static const int sizeFMMTable;
public:
	static int funcMMNumberByName(const char*);
	static const FuncMMInfo& getFuncMM(int);
};

class FunctionsMTable {
	static const FuncMInfo FMTable[];
	static const int sizeFMTable;
public:
	static int funcMNumberByName(const char*);
	static const FuncMInfo& getFuncM(int);
};

class FunctionsUIUITable {
	static const FuncUIUIInfo FUIUITable[];
	static const int sizeFUIUITable;
public:
	static int funcUIUINumberByName(const char*);
	static const FuncUIUIInfo& getFuncUIUI(int);
};

class FunctionsMmTable {
	static const FuncMmInfo FMmTable[];
	static const int sizeFMmTable;
public:
	static int funcMmNumberByName(const char*);
	static const FuncMmInfo& getFuncMm(int);
};

#endif