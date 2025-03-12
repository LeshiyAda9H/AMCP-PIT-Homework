#ifndef HUFFMAN_NODE
#define HUFFMAN_NODE

struct Node {

	unsigned char symbol;
	int frequency;

	Node* parent;
	Node* left;
	Node* right;

	Node() : frequency(0), symbol('\0'),
		parent(nullptr), left(nullptr), right(nullptr) {}

	Node(Node* left, Node* right) : parent(nullptr), symbol('\0') {

		this->frequency = left->frequency + right->frequency;
		this->left = left;
		left->parent = this;
		this->right = right;
		right->parent = this;
	}

	Node(unsigned char symbol, int frequency) : symbol(symbol), frequency(frequency),
		parent(nullptr), right(nullptr), left(nullptr){}

	~Node() {
		delete left;
		delete right;
	}
};

#endif

