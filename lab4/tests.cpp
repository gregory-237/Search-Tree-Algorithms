#include "tree.h"

int main() {
	MySet tree;
	tree.insert(40);
	tree.insert(10);
	tree.insert(57);
	tree.insert(14);
	tree.insert(45);
	tree.insert(80);
	tree.insert(9);
	tree.insert(16);
	tree.insert(47);
	tree.insert(84);

	tree.print();

	tree.erase(50);
	tree.print();

	tree.erase(57);
	tree.print();

	cout << tree.contains(30);
	cout << tree.contains(57);
	cout << tree.contains(14);
	cout << tree.contains(50);
	cout << tree.contains(45);
	cout << tree.contains(9);
	cout << endl;

	cout << "Tree:" << endl;
	tree.print();
	MySet tree2(tree);
	cout << "Copy of Tree:" << endl;
	tree2.print();

	MySet tree3;
	tree3.insert(8);
	tree3.insert(2);
	tree3.insert(9);
	cout << "Third Tree:" << endl;
	tree3.print();

	tree3 = tree;

	cout << "Third Tree after assignment:" << endl;
	tree3.print();

	MySet tree4;
	tree4.insert(5);
	tree4.insert(7);
	tree4.insert(2);
	tree4.insert(8);
	tree4.insert(9);
	tree4.insert(6);
	tree4.insert(1);
	cout << "Tree:" << endl;
	tree4.print();

	MySet tree5;
	tree5.insert(6);
	tree5.insert(5);
	tree5.insert(9);
	tree5.insert(2);
	tree5.insert(3);
	tree5.insert(4);
	cout << "Second Tree:" << endl;
	tree5.print();

	cout << "Difference (tree - second tree):" << endl;
	difference(tree4, tree5).print();
	cout << endl << "Difference (second tree - tree):" << endl;
	difference(tree5, tree4).print();
	cout << endl << "Intersection:" << endl;
	intersection(tree4, tree5).print();
}