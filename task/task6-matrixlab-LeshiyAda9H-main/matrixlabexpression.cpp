#include "matrixlabexpression.h"
#include "expressionnodes.h"
#include "functionstable.h"
#include <cstring>
#include <stack>

bool isFraction(const char* str);
namespace global {
	std::ostream* out;
}

void executingExpression(const char* expression) {
	int index = static_cast<int>(strlen(expression)) - 1;

	std::stack<GeneralNode*> Stack;

	while (index >= 0) {

		if (expression[index] == ' ') {
			--index;
			continue;
		}

		if (expression[index] == ')') {
			Stack.push(new ClosingParenthesisNode());
			--index;
			continue;
		}

		char word[1024]{};

		int length = 0;

		while (expression[index] != '(' && expression[index] != ' ' && index >= 0) {
			word[length] = expression[index];
			++length;
			--index;
		}

		for (int jndex = 0; jndex < length / 2; ++jndex) {
			std::swap(word[jndex], word[length - jndex - 1]);
		}

		word[length] = '\0';
		int funcNumber = -1;
		bool isFunction = false;

		if (!isFunction) { funcNumber = FunctionsMMTable::funcMMNumberByName(word); }

		if (!isFunction && funcNumber != -1) {

			isFunction = true;

			pfuncMM func = FunctionsMMTable::getFuncMM(funcNumber).func;

			GeneralNode* arg1 = nullptr;
			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			arg1 = Stack.top(); Stack.pop();

			GeneralNode* arg2 = nullptr;
			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			arg2 = Stack.top(); Stack.pop();

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}
			delete Stack.top(); Stack.pop();

			Stack.push(new MatrixNode(func(arg1->getValue(), arg2->getValue())));

			delete arg1; delete arg2;
		}

		if (!isFunction) { 
			funcNumber = FunctionsMTable::funcMNumberByName(word);
		}

		if (!isFunction && funcNumber != -1) {
			isFunction = true;

			pfuncM func = FunctionsMTable::getFuncM(funcNumber).func;

			GeneralNode* arg = nullptr;
			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			arg = Stack.top(); Stack.pop();

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();

			Stack.push(new MatrixNode(func(arg->getValue())));

			delete arg;
		}

		if (!isFunction) { 
			funcNumber = FunctionsUIUITable::funcUIUINumberByName(word);
		}

		if (!isFunction && funcNumber != -1) {
			isFunction = true;

			pfuncUIUI func = FunctionsUIUITable::getFuncUIUI(funcNumber).func;

			GeneralNode* arg1 = nullptr;
			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			arg1 = Stack.top(); Stack.pop();

			unsigned int rows = 0;
			unsigned int columns = 0;
			rows = (unsigned int)arg1->getValue();

			if (!Stack.empty() && Stack.top()->getName() != closingParenthesis) {

				GeneralNode* arg2 = Stack.top(); Stack.pop();
				columns = (unsigned int)arg2->getValue();

				delete arg2;
			}
			else {
				columns = rows;
			}

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();

			Stack.push(new MatrixNode(func(rows, columns)));

			delete arg1;
		}

		if (!isFunction) { 
			funcNumber = FunctionsMmTable::funcMmNumberByName(word);
		}

		if (!isFunction && funcNumber != -1) {

			isFunction = true;

			pfuncMm func = FunctionsMmTable::getFuncMm(funcNumber).func;

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			Matrix initial = Stack.top()->getValue();

			delete Stack.top(); Stack.pop();

			while (!Stack.empty() && Stack.top()->getName() != closingParenthesis) {

				func(initial, Stack.top()->getValue());

				delete Stack.top(); Stack.pop();
			}
			
			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();

			Stack.push(new MatrixNode(std::move(initial)));
		}

		if (!isFunction && strcmp(word, "=") == 0) {

			isFunction = true;

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Specify the variable name";
			}

			GeneralNode* name = Stack.top(); Stack.pop();

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Specify the assigned value";
			}

			GeneralNode* value = Stack.top(); Stack.pop();

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();

			matrixlab::Workspace[name->getName()] = value->getValue();

			delete name; delete value;
		}

		if (!isFunction && strcmp(word, "linspace") == 0) {

			isFunction = true;

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			GeneralNode* x0 = Stack.top(); Stack.pop();

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			GeneralNode* x1 = Stack.top(); Stack.pop();

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			GeneralNode* columns = Stack.top(); Stack.pop();

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();

			Stack.push(new MatrixNode(linspace((Fraction)x0->getValue(),
				(Fraction)x1->getValue(), (unsigned int)columns->getValue())));

			delete x0; delete x1; delete columns;
		}

		if (!isFunction && strcmp(word, "disp") == 0) {

			isFunction = true;

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			GeneralNode* matrix = Stack.top(); Stack.pop();

			if (matrix->getValue().isScalar()) {
				*global::out << matrix->getName() << " = " << matrix->getValue() << std::endl;
			}
			else {
				*global::out << matrix->getName() << " = [" << std::endl <<
					matrix->getValue() << std::endl << "]" << std::endl;
			}

			if (expression[index--] != '(' || Stack.empty() || Stack.top()->getName() != closingParenthesis) {
				throw "Incorrect use of brackets";
			}

			delete Stack.top(); Stack.pop();
			delete matrix;
		}

		if (!isFunction && strcmp(word, "-") == 0) {
			isFunction = true;

			if (Stack.empty() || Stack.top()->getName() == closingParenthesis) {
				throw "Incorrect number of arguments";
			}
			GeneralNode* arg1 = Stack.top(); Stack.pop();

			if (expression[index--] != '(' || Stack.empty()) {
				throw "Incorrect use of brackets"; 
			}
			if (Stack.top()->getName() == closingParenthesis) {
				
				delete Stack.top(); Stack.pop();

				Stack.push(new MatrixNode(negative(arg1->getValue())));
			}
			else {
				GeneralNode* arg2 = Stack.top(); Stack.pop();

				if (Stack.empty() || Stack.top()->getName() != closingParenthesis) {
					throw "Incorrect use of brackets";
				}

				delete Stack.top(); Stack.pop();

				Stack.push(new MatrixNode(subtraction(arg1->getValue(), arg2->getValue())));

				delete arg2;
			}

			delete arg1;
		}

		bool isNumber = false;

		if (!isFunction && isFraction(word)) {

			isNumber = true;

			if (expression[index--] != ' ') {
				throw "Enter the function";
			}

			Stack.push(new MatrixNode(Matrix(Fraction(std::string(word)))));
		}

		if (!isFunction && !isNumber) {
			if (expression[index--] != ' ') {
				throw "Enter the function";
			}

			Stack.push(new VariableNode(word));
		}
	}
}

bool isFraction(const char* str) {

	bool isDelimiterPassed = false;
	int index = 0;

	while (str[index] != '\0') {
		if (isdigit(str[index]) != 0) {
			++index;
		}
		else if (str[index] == '/') {

			if (isDelimiterPassed || index == 0 || index == strlen(str) - 1) { return false; }
			isDelimiterPassed = true;
			++index;
		}
		else {
			if (str[index] != '-' || index != 0) { 
				return false;
			}
		}
	}

	return true;
}
