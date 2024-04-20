#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int _data;
	Node* _left, * _right;
	Node(int data) : _data(data), _left(nullptr), _right(nullptr) {}
};


class MySet {
private:
	Node* _root;

	void swap(MySet& rhs) noexcept {
		std::swap(_root, rhs._root);
	}

	void copy_data(Node* node) {
		if (node) {
			this->insert(node->_data);
			copy_data(node->_left);
			copy_data(node->_right);
		}
	}

	Node* maximum(Node* node) {
		while (node->_right) {
			node = node->_right;
		}
		return node;
	}

	Node* erase_node(Node* node, int key, bool& del) {
		if (node == nullptr) return node;
		if (key < node->_data) node->_left = erase_node(node->_left, key, del);
		else if (key > node->_data) node->_right = erase_node(node->_right, key, del);
		else {
			if (node->_left == nullptr) {
				Node* temp = node->_right;
				delete node;
				del = true;
				return temp;
			}
			else if (node->_right == nullptr) {
				Node* temp = node->_left;
				delete node;
				del = true;
				return temp;
			}
			Node* temp = maximum(node->_left);
			node->_data = temp->_data;
			node->_left = erase_node(node->_left, temp->_data, del);
		}
		return node;
	}

	void subprint(Node* node) {
		if (node != nullptr) {
			subprint(node->_left);
			std::cout << node->_data << ' ';
			subprint(node->_right);
		}
		return;
	}

	void delete_set(Node* node) {
		if (node) {
			delete_set(node->_left);
			delete_set(node->_right);
			delete node;
		}
	}

	void walk(Node* root, vector<int>& vec) {
		if (!root) return;

		if (root)
		{
			walk(root->_left, vec);
			vec.push_back(root->_data);
			walk(root->_right, vec);
		}
	}

public:
	MySet() : _root(nullptr) {}

	MySet(const MySet& rhs) : _root(nullptr) {
		copy_data(rhs._root);
	}

	MySet& operator=(const MySet& rhs) {
		MySet copy(rhs);
		swap(copy);
		return *this;
	}

	void print() {
		subprint(_root);
		cout << endl;
	}

	bool insert(int key) {
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}
		if (contains(key)) return false;
		Node* node = _root;
		bool left = false;
		while (node) {
			if (key < node->_data) {
				if (node->_left) {
					node = node->_left;
					continue;
				}
				left = true;
				break;
			}
			else if (key > node->_data) {
				if (node->_right) {
					node = node->_right;
					continue;
				}
				break;
			}
		}
		if (left) node->_left = new Node(key);
		else node->_right = new Node(key);
		return true;
	}

	bool contains(int key) {
		Node* node = _root;
		while (node) {
			if (key < node->_data) node = node->_left;
			else if (key > node->_data) node = node->_right;
			else return true;
		}
		return false;
	}

	bool erase(int key) {
		bool del = false;
		_root = erase_node(_root, key, del);
		return del;
	}

	~MySet() {
		delete_set(_root);
	}

	vector <int> to_vector() {
		vector<int>result;
		walk(_root, result);
		return result;
	}
};

vector<int>intersection(MySet& lhs, MySet& rhs)
{
	vector<int>lhs_vec = lhs.to_vector();
	vector<int>rhs_vec = rhs.to_vector();
	vector<int>result;
	sort(lhs_vec.begin(), lhs_vec.end());
	sort(rhs_vec.begin(), rhs_vec.end());
	set_intersection(lhs_vec.begin(), lhs_vec.end(), rhs_vec.begin(), rhs_vec.end(), back_inserter(result));
	return result;
}

vector<int>difference(MySet& lhs, MySet& rhs)
{
	vector<int>lhs_vec = lhs.to_vector();
	vector<int>rhs_vec = rhs.to_vector();
	vector<int>result;
	sort(lhs_vec.begin(), lhs_vec.end());
	sort(rhs_vec.begin(), rhs_vec.end());
	set_difference(lhs_vec.begin(), lhs_vec.end(), rhs_vec.begin(), rhs_vec.end(), back_inserter(result));
	return result;
}
