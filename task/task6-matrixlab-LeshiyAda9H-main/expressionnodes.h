#ifndef EXPRESSION_NODES
#define EXPRESSION_NODES

#include "matrix.h"
#include <string>
#include <map>

namespace matrixlab {
	std::map<std::string, Matrix> Workspace;
}

const std::string closingParenthesis = ")";

class GeneralNode {
protected:
	std::string name_ = "ans";
public:
	const std::string& getName() const { return name_; }
	virtual const Matrix& getValue() const = 0;
	virtual ~GeneralNode() {}
};

class VariableNode : public GeneralNode {
public:
	VariableNode(const std::string& name) { name_ = name; }
	const Matrix& getValue() const {
		if (matrixlab::Workspace.find(name_) == matrixlab::Workspace.end()) {
			throw "Unknown variable";
		}
		return matrixlab::Workspace[name_];
	}
};

class MatrixNode : public GeneralNode {
	Matrix matrix_;
public:
	MatrixNode(const Matrix& matrix) : matrix_(matrix) {}
	MatrixNode(Matrix&& matrix) : matrix_(std::move(matrix)){}
	const Matrix& getValue() const { return matrix_; }
};

class ClosingParenthesisNode : public GeneralNode {
	Matrix matrix_;
public:
	ClosingParenthesisNode() : matrix_(ZERO_FRAC) { name_ = closingParenthesis; }
	const Matrix& getValue() const { return matrix_; }
};

#endif
