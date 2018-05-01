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

	//ArrayBST<LinkedList<string>> arr;
	ArrayBST<string> arr(13);


	LinkedList<string> l;
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");
	l.add_end("2323");

	arr.insert(10, "A");
	arr.insert(5, "B");
	arr.insert(13, "C");
	arr.insert(4, "D");

	//string s = arr.tree[1].data.get(3);
	//cout << s;
	//arr.tree[1].data.remove_last();
	
	

	string s = arr.left(*arr.left(arr.tree[1]))->data;


	cout << s;
	//arr.tree[1].data.remove_last();

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
