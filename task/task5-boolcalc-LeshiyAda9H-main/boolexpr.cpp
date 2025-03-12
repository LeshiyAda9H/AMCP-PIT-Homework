#include "boolexpr.h"
#include "booleannodes.h"
#include <algorithm>


void BooleanExpression::InfixFilter(const char* instr, char* outstr) {
	int i = 0; 
	int j = 0; 
	int row = 0;
	int col = 0;
	unsigned char action = 0;

	do {
		col = actionsNumberFilter(instr[i]);
		row = (i == 0) ? 0 : actionsNumberFilter(instr[i - 1]);
		action = ActionsTableFilter[row][col];

		switch (action){
		case 1:
			throw "error";
		case 2:
			outstr[j++] = instr[i++];
			break;
		case 3:
			++i;
		}
		
	} while (col != 0);
	outstr[j] = '\0';
}

const unsigned char BooleanExpression::ActionsTableFilter[][8] = {
	{1,2,1,2,1,3,2,2},
	{1,1,1,1,1,1,2,1},
	{1,2,1,2,1,3,2,2},
	{1,2,1,2,1,3,2,2},
	{2,1,2,1,2,3,1,1},
	{2,2,2,2,2,3,2,2},
	{2,1,2,1,2,3,2,1},
	{1,2,1,2,1,3,2,2}
};

int BooleanExpression::actionsNumberFilter(char sym) {
	if (binaryOperation(sym)) {
		return 2;
	}
	if (isdigit(sym) != 0) {
		return 6;
	}
	switch (sym){
	case '\0':
		return 0;
	case 'x':
		return 1;
	case '(':
		return 3;
	case ')':
		return 4;
	case '\r':
	case '\n':
	case '\t':
	case ' ':
		return 5;
	case '~':
		return 7;
	default:
		throw "error";
	}
}




void BooleanExpression::Infix2Postfix(const char* instr, char* outstr){
	int i = 0; 
	int j = 0;
	int row = 0; 
	int col = 0;
	unsigned char action;
	std::stack<char> S;
	do {
		col = actionColNumber2Postfix(instr[i]);
		row = S.empty() ? 6 : actionsRowNumber2Postfix(S.top());
		action = ActionsTable2Postfix[row][col];

		switch (action) {
		case 1: outstr[j] = instr[i]; 	++j; ++i;
			while (isdigit(instr[i]) != 0) {
				outstr[j] = instr[i];
				++j; ++i;
			}
			outstr[j] = ' ';
			++j;
			break; 
		case 2: 
			outstr[j] = S.top(); S.pop(); ++j; break; 
		case 3: 
			S.push(instr[i]); ++i;	break; 
		case 4: 
			while (!S.empty() && S.top() != '(') {
				outstr[j++] = S.top();
				S.pop();
			}
			++i;
			S.pop();
			break;
		case 5: 
			throw "error";
		case 6: 
			outstr[j] = '\0'; break;
		}
	} while (action != 6);
}

const unsigned char BooleanExpression::ActionsTable2Postfix[][9] = {

	{1,2,2,2,3,3,3,4,2},
	{1,3,2,2,3,3,3,4,2},
	{1,3,3,2,3,3,3,4,2},
	{1,2,2,2,2,3,3,4,2},
	{1,2,2,2,2,3,3,4,2},
	{1,3,3,3,3,3,3,5,5},
	{1,3,3,3,3,3,3,5,6}

};

bool BooleanExpression::binaryOperation(char sym) {
	return sym == 'v' || sym == '+' || sym == '^' || sym == '|' || sym == '<' || sym == '>' || sym == '=' || sym == '&';
}
bool BooleanExpression::highPriority(char sym) {
	return sym == 'v' || sym == '+';
}
bool BooleanExpression::midPriority(char sym) {
	return sym == '>' || sym == '<';
}
bool BooleanExpression::lowPriority(char sym) {
	return sym == '|' || sym == '^' || sym == '=';
}

int BooleanExpression::actionsRowNumber2Postfix(char sym) {
	if (highPriority(sym)) {
		return 0;
	}
	if (midPriority(sym)) {
		return 1;
	}
	if (lowPriority(sym)) {
		return 2;
	}

	switch (sym) {
	case '&':
		return 3;
	case '~':
		return 4;
	case '(':
		return 5;
	default:
		throw "error";
	}
	
}

int BooleanExpression::actionColNumber2Postfix(char sym) {
	if (isdigit(sym) != 0) {
		return 0;
	}
	if (highPriority(sym)) {
		return 1;
	}
	if (midPriority(sym)) {
		return 2;
	}
	if (lowPriority(sym)) {
		return 3;
	}

	switch (sym) {
	case 'x':
		return 0;
	case '&':
		return 4;
	case '~':
		return 5;
	case '(':
		return 6;
	case ')':
		return 7;
	case '\0':
		return 8;
	default:
		throw "error";
	}

}

void BooleanExpression::Postfix2Tree(const char* instr) {
	std::stack<BooleanNode*> S;
	int index = static_cast<int>(strlen(instr)) - 1;
	
	char number[12];
	int len = 0;

	BooleanNode* result = nullptr;

	while (index >= 0) {
		try {
			switch (instr[index])
			{
			case ' ':
				break;
			case '&':
				result = new ConNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case 'v':
				result = new DisNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '+':
				result = new XORNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '>':
				result = new ImplNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '<':
				result = new ReverseImplNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '^':
				result = new ArrowNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '|':
				result = new ChiefNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '=':
				result = new EqNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			case '~':
				result = new InverseNode();
				if (!S.empty()) {
					if (!S.top()->ICanAdd()) {
						throw "error";
					}
					S.top()->add(result);
				}
				S.push(result);
				break;
			default:
				while (index >= 0 && isdigit(instr[index])!= 0) {
					number[len++] = instr[index--];
				}
				for (int i = 0; i < len / 2; ++i) {
					std::swap(number[i], number[len - i - 1]);
				}
				number[len] = '\0';
				if (instr[index] == 'x') {
					int num = std::stoi(number);
					if (std::find(global::nums.begin(), global::nums.end(), num) == global::nums.end()) {
						global::nums.push_back(num);
					}
					result = new ParamNode(std::stoi(number));
				}
				else {
					result = new NumNode(std::stoi(number) != 0);
					++index;
				}
				if (S.empty()) {
					S.push(result);
				}
				else {
					S.top()->add(result);
				}
				while (S.size() > 1 && !S.top()->ICanAdd()) {
					S.pop();
				}
				len = 0;
			}
			--index;
		}
		catch (...) {
			delete result;
			while (!S.empty()) {
				delete S.top();
				S.pop();
			}
		}
	}

	if (S.size() != 1) {
		throw "error";
	}

	root = S.top(); S.pop();
	std::sort(global::nums.begin(), global::nums.end());
}


void BooleanExpression::calcTrueTable() {
	trueTable.resize(1 << global::nums.size());
	global::args.resize(global::nums.size());

	for (int i = 0; i < trueTable.size(); ++i) {
		bool value = true;
		trueTable[i] = root->calc();
		for (int j = static_cast<int>(global::nums.size()) - 1; value && j >= 0; --j) {
			global::args[j] = global::args[j] ^ value;
			value = value ^ global::args[j];
		}
	}
	global::args.clear();
	variables = std::move(global::nums);
}

std::string BooleanExpression::zhegalkin() const {

	std::vector<bool> arr = trueTable;
	std::string result;

	bool was = false;

	if (arr[0]) {
		result = "1";
		was = true;
	}

	for (int i = 1; i < arr.size(); ++i) {
		for (int j = 0; j < arr.size() - i; ++j) {
			arr[j] = arr[j] ^ arr[j + 1];
		}
		if (arr[0]) {
			if (was) {
				result += " + ";
			}
			int index = 0;
			int var = 1 << (variables.size() - 1);
			bool con = false;
			while (var > 0) {
				if ((i & var) != 0) {
					if (con) {
						result += " & ";
					}
					result += std::string("x") + std::to_string(variables[index]);
					con = true;
				}
				var >>= 1;
				++index;
			}
			was = true;
		}
	}

	if (result.empty()) {
		result = '0';
	}

	return result;
}


std::string  BooleanExpression::cnf() const {

	std::string result;
	bool was = false;

	if (trueTable.size() == 1) {
		return trueTable[0] ? "1" : "0";
	}

	for (int i = 0; i < trueTable.size(); ++i) {
		if (!trueTable[i]) {
			if (was) {
				result += " & ";
			}
			if (variables.size() > 1) {
				result += "(";
			}
			int var = 1 << (variables.size() - 1);
			int index = 0;
			while (var > 0) {
				if (index != 0) {
					result += " v ";
				}
				if ((var & i) != 0) {
					result += "~";
				}
				result += "x" + std::to_string(variables[index]);
				
				var >>= 1;
				++index;
			}
			if (variables.size() > 1) {
				result += ")";
			}

			was = true;
		}
	}

	if (result.empty()) {
		result = "1";
	}

	return result;
}



std::string  BooleanExpression::dnf() const {
	std::string result;
	bool was = false;

	if (trueTable.size() == 1) {
		return trueTable[0] ? "1" : "0";
	}

	for (int i = 0; i < trueTable.size(); ++i) {
		if (trueTable[i]) {
			if (was) {
				result += " v ";
			}
			
			int var = 1 << (variables.size() - 1);
			int index = 0;
			while (var > 0) {
				if (index != 0) {
					result += " & ";
				}
				if ((var & i) == 0) {
					result += "~";
				}
				result += "x" + std::to_string(variables[index]);

				var >>= 1;
				++index;
			}
			

			was = true;
		}
	}

	if (result.empty()) {
		result = "0";
	}

	return result;
}

bool BooleanExpression::T0() const {
	return !trueTable[0];
}
bool BooleanExpression::T1() const {
	return trueTable[trueTable.size() - 1];
}
bool BooleanExpression::S() const {
	for (int i = 0; i < trueTable.size() / 2; ++i) {
		if (trueTable[i] ^ trueTable[trueTable.size() - i - 1]) {
			return false;
		}
	}
	return true;
}
bool BooleanExpression::M() const {
	int offset = 1 << (variables.size() - 1);

	for (int i = 0; i < variables.size(); ++i) {
		int countSteps = 1 << i;
		for (int j = 0; j < countSteps; ++j) {
			int b = j << offset;
			for (int k = 0; k < offset; ++k) {
				if (trueTable[b + k] && !trueTable[b + k + offset]) {
					return false;
				}
			}
		}
		offset >>= 1;
	}

	return true;
}
bool BooleanExpression::L() const {
	std::vector<bool> arr = trueTable;
	
	for (int i = 1; i < arr.size(); ++i) {
		for (int j = 0; j < arr.size() - i; ++j) {
			arr[j] = arr[j] ^ arr[j + 1];
		}
		if (arr[0]) {
			
			int var = 1 << (variables.size() - 1);
			int counter = 0;
			while (var > 0) {
				if ((i & var) != 0) {
					++counter;
				}
				var >>= 1;
			}
			if (counter > 1) { return false; }
		}
	}
	return true;
}


bool isFullSystem(const std::vector<BooleanExpression>& function) {
	bool flag = true;
	
	for (int i = 0; i < function.size(); ++i) {
		flag &= function[i].T0();
		if (!flag) {
			break;
		}
	}
	if (flag) {
		return false;
	}

	flag = true;
	for (int i = 0; i < function.size(); ++i) {
		flag &= function[i].T1();
		if (!flag) {
			break;
		}
	}
	if (flag) {
		return false;
	}

	flag = true;
	for (int i = 0; i < function.size(); ++i) {
		flag &= function[i].M();
		if (!flag) {
			break;
		}
	}
	if (flag) {
		return false;
	}

	flag = true;
	for (int i = 0; i < function.size(); ++i) {
		flag &= function[i].S();
		if (!flag) {
			break;
		}
	}
	if (flag) {
		return false;
	}

	flag = true;
	for (int i = 0; i < function.size(); ++i) {
		flag &= function[i].L();
		if (!flag) {
			break;
		}
	}
	return !flag;
}
