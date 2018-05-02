#include <iostream>
#include <fstream>
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

void demoLinkedBST() {
	cout << "\nDemostracion de Arbol Binario de Busqueda.\n\n";

	BST<string> bbb;
	bbb.insert(5, "Alpha");
	bbb.insert(10, "Beta");
	bbb.insert(1, "Gama");
	bbb.insert(3, "Delta");

	cout << bbb.traversePreorder(bbb.root);
	cout << "\n\n";
	cout << bbb.traversePostOrder(bbb.root);
	cout << "\n\n";
	cout << bbb.traverseInOrder(bbb.root);
	cout << "\n";
}


int main() {

	//ArrayBST<LinkedList<string>> arr;
	int tam = 10;
	ArrayBST<string> arr(tam);


	LinkedList<string> l;
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");

	arr.insert(110, "A");
	arr.insert(100, "B");
	arr.insert(230, "C");
	arr.deleteNode(230);
	arr.insert(40, "D");
	arr.insert(30, "X");
	arr.deleteNode(110);
	arr.insert(31, "Z");
	arr.insert(32, "D");
	arr.insert(33, "Z");
	arr.insert(34, "Z");
	arr.insert(35, "Z");
	arr.insert(9, "W");
	arr.deleteNode(9);
	arr.insert(150, "Alfa");
	arr.insert(160, "Alfa");
	arr.insert(170, "Alfa");

	for (int i = 0; i <= tam; i++) {
		cout << "/  " << arr.tree[i].key << " " << arr.tree[i].lChild << " " << arr.tree[i].rChild;
	}
	cout << "\n\n";


	//string s = arr.tree[1].data.get(3);
	//cout << s;
	//arr.tree[1].data.remove_last();
	
	//string s = arr.left(*arr.left(arr.tree[1]))->data;
	//string p = arr.max(arr.tree[2])->data;
	//string q = arr.search(25)->data;

	ofstream of("out.txt");
	string out = arr.traversePreorder(arr.getRoot()) + "\n";

	of << out;
	cout << out;

	//cout << s << "\t" << p;
	//arr.tree[1].data.remove_last();

	//demoLinkedBST();

	cout << "\nPresione enter para terminar.    ";
	cin.get();
	return 0;
}
