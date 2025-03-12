#ifndef BOOLEANNODES
#define BOOLEANNODES

#include <string>
#include <vector>

class BooleanNode {
public:
	virtual bool calc() const = 0;
	virtual std::string str() const = 0;
	virtual bool ICanAdd() const = 0;
	virtual void add(BooleanNode* unused) {
	}
	virtual ~BooleanNode() {}
};

namespace global {
	extern std::vector<bool> args;
	extern std::vector<int> nums;
}

class ParamNode : public BooleanNode {
	int number;
	static int find(int number) {
		for (int i = 0; i < global::nums.size(); ++i) {
			if (global::nums[i] == number) {
				return i;
			}
		}
		throw "error";
	}
public:
	ParamNode(int num) : number(num){}
	bool calc() const {
		return global::args[find(number)];
	}
	std::string str() const {
		return std::string("x") + std::to_string(number);
	}
	bool ICanAdd() const {
		return false;
	}
	void add(BooleanNode* adding) {
	}
};

class NumNode : public BooleanNode {
	bool value;
public:
	NumNode(bool val) : value(val) {}
	bool calc() const {
		return value;
	}
	std::string str() const {
		return (value) ? std::string("1") : std::string("0");
	}
	bool ICanAdd() const {
		return false;
	}
	void add(BooleanNode* adding) {
	}
};

class InverseNode : public BooleanNode {
	BooleanNode* child;
public:
	InverseNode() : child(nullptr){}
	InverseNode(BooleanNode* chl) : child(chl){}
	bool calc() const {
		return !child->calc();
	}
	std::string str() const {
		return std::string("~") + child->str();
	}
	~InverseNode() {
		delete child;
	}
	bool ICanAdd() const {
		return child == nullptr;
	}
	void add(BooleanNode* adding) {
		if (ICanAdd()) {
			child = adding;
		}
		else {
			throw "error";
		}
	}
};

class BinNode : public BooleanNode {
protected:
	BooleanNode* left;
	BooleanNode* right;
public:
	BinNode() : left(nullptr), right(nullptr){}
	BinNode(BooleanNode* Misha_le, BooleanNode* Kolya_ri) : left(Misha_le), right(Kolya_ri) {}
	bool ICanAdd() const {
		return left == nullptr || right == nullptr;
	}
	void add(BooleanNode* adding) {
		if (right == nullptr) {
			right = adding;
		}
		else if (left == nullptr) {
			left = adding;
		}
		else {
			throw "error";
		}
	}
	~BinNode() {
		delete left;
		delete right;
	}
};

class ConNode : public BinNode {
public:
	ConNode(){}
	ConNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R){}
	bool calc() const {
		return left->calc() && right->calc();
	}
	std::string str() const{
		return "(" + left->str() + " & " + right->str() + ")";
	}
};

class DisNode : public BinNode {
public:
	DisNode(){}
	DisNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return left->calc() || right->calc();
	}
	std::string str() const {
		return "(" + left->str() + " v " + right->str() + ")";
	}
};

class XORNode : public BinNode {
public:
	XORNode(){}
	XORNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return left->calc() ^ right->calc();
	}
	std::string str() const {
		return "(" + left->str() + " + " + right->str() + ")";
	}
};

class ImplNode : public BinNode {
public:
	ImplNode(){}
	ImplNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return !left->calc() || right->calc();
	}
	std::string str() const {
		return "(" + left->str() + " > " + right->str() + ")";
	}
};

class ReverseImplNode : public BinNode {
public:
	ReverseImplNode(){}
	ReverseImplNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return left->calc() || !right->calc();
	}
	std::string str() const {
		return "(" + left->str() + " < " + right->str() + ")";
	}
};

class EqNode : public BinNode {
public:
	EqNode(){}
	EqNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return left->calc() == right->calc();
	}
	std::string str() const {
		return "(" + left->str() + " = " + right->str() + ")";
	}
};

class ChiefNode : public BinNode {
public:
	ChiefNode(){}
	ChiefNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return !(left->calc() && right->calc());
	}
	std::string str() const {
		return "(" + left->str() + " | " + right->str() + ")" ;
	}
};

class ArrowNode : public BinNode {
public:
	ArrowNode(){}
	ArrowNode(BooleanNode* L, BooleanNode* R) : BinNode(L, R) {}
	bool calc() const {
		return !(left->calc() || right->calc());
	}
	std::string str() const {
		return "(" + left->str() + " ^ " + right->str() + ")";
	}
};



#endif // !BOOLEANNODES
