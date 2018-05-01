#include <iostream>
#include "BinarySearchTree.h"
#include "ArrayBST.h"
#include <sstream>
#include "Lists.h"
using namespace std;

//template <typename T>
//void print(DoublyQueue<T> &queue) {
//	for (int i = 1; i <= queue.size(); i++) cout << queue.get(i) << " ";
//	cout << endl;
//}



int main() {

	ArrayBST<LinkedList<string>> arr;

	LinkedList<string> l;
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");

	arr.insert(1, l);
	arr.insert(2, l);
	arr.insert(3, l);
	arr.insert(4, l);

	string s = arr.tree[1].data.get(3);
	cout << s;
	arr.tree[1].data.remove_last();
	
	cout << "\nDemostracion de Arbol Binario de Busqueda.\n\n";

	BST<string> bbb;
	bbb.insert(5, "Alpha");
	bbb.insert(10, "Beta");
	bbb.insert(1, "Gama");
	bbb.insert(3, "Delta");


	cout << bbb.traversePreorder(bbb.root);
	cout << "\n\n\n";
	cout << bbb.traversePostOrder(bbb.root);
	cout << "\n\n\n";
	cout << bbb.traverseInOrder(bbb.root);
	cout << "\n\n\n";



	cout << "\n\nPresione enter para terminar.    ";
	cin.get();
	return 0;
}
