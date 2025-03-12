#ifndef	BOOLCALC
#define BOOLCALC

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include "booleannodes.h"

class BooleanExpression {

	BooleanNode* root;
	std::vector<bool> trueTable;
	std::vector<int> variables;

	static void InfixFilter(const char*, char*);
	static const unsigned char ActionsTableFilter[][8];
	static int actionsNumberFilter(char);

	static void Infix2Postfix(const char* instr, char* outstr);
	static const unsigned char ActionsTable2Postfix[][9];
	static int actionsRowNumber2Postfix(char);
	static int actionColNumber2Postfix(char);

	static bool binaryOperation(char);
	static bool highPriority(char);
	static bool midPriority(char);
	static bool lowPriority(char);

	void Postfix2Tree(const char*);

	void calcTrueTable();


public:

	BooleanExpression(const char* str) {
		char strFilter[1024];
		char str2Filter[1024];
		char strPostfix[1024];

		try {
			InfixFilter(str, strFilter);
			InfixFilter(strFilter, str2Filter);
			Infix2Postfix(str2Filter, strPostfix);
			Postfix2Tree(strPostfix);
		}
		catch (...) {
			root = nullptr;
			throw;
		}
		calcTrueTable();
	}

	BooleanExpression(const BooleanExpression& alien) : root(nullptr), trueTable(alien.trueTable), variables(alien.variables){}

	operator std::string() const {
		return root->str();
	}

	bool calc() const {
		if (root != nullptr) {
			return root->calc();
		}
		return false;
	}

	std::string zhegalkin() const;
	std::string cnf() const;
	std::string dnf() const;

	BooleanExpression& operator= (const BooleanExpression& alien) {
		if (this != &alien) {
			delete root;
		}
		root = nullptr;
		trueTable = alien.trueTable;
		variables = alien.variables;

		return *this;
	}

	

	bool T0() const;
	bool T1() const;
	bool S() const;
	bool M() const;
	bool L() const;

	~BooleanExpression() {
		delete root;
	}

};


bool isFullSystem(const std::vector<BooleanExpression>&);

#endif

