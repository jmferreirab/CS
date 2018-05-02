#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include "ArrayBST.h"
#include <sstream>
#include "Lists.h"
using namespace std;

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

void arraryBSTDemo() {
	int tam = 10;
	ArrayBST<string> arr(tam);

	arr.insert(110, "A");
	arr.insert(100, "B");
	arr.insert(230, "C");
	arr.deleteNode(230);
	arr.insert(40, "D");
	arr.insert(30, "X");
	arr.deleteNode(110);
	arr.insert(33, "Zeta");
	arr.insert(35, "Z");
	arr.insert(9, "W");
	arr.deleteNode(9);
	arr.insert(150, "Alfa");
	arr.insert(160, "BETA");
	arr.insert(170, "Gamma");

	cout << "Array representation of binary tree [SIZE=SENTINEL + 10] using key:left:right \n\n";
	for (int i = 0; i < tam+1; i++) {
		cout << " / " << arr.getTree()[i].key << " "
			<< arr.getTree()[i].lChild << " " << arr.getTree()[i].rChild;
	}
	cout << "\n\n";

	ofstream of("out.txt");
	string preOrder = "Preorder:\n" + arr.traversePreorder(arr.getRoot()) + "\n";
	string postOrder = "Postorder:\n" + arr.traversePostOrder(arr.getRoot()) + "\n";
	string inOrder = "Inorder:\n" + arr.traverseInOrder(arr.getRoot()) + "\n";

	of << preOrder;
	cout << preOrder;
	cout << postOrder;
	cout << inOrder;
}


//Reproduction rate 100%
void readAccessViolationDemoDueToOmissionOfRuleOfThree(){
	ArrayBST<LinkedList<string>> arr;
	LinkedList<string> li;
	li.add_end("123");
	li.add_end("345");
	li.add_end("456");
	li.add_end("789");

	arr.insert(110, li);
	arr.insert(100, li);

	string s = arr.getTree()[1].data.get(2);

	cout << s;

}


int main() {

	//demoLinkedBST();
	arraryBSTDemo();
	//readAccessViolationDemoDueToOmissionOfRuleOfThree();


	cout << "\nPresione enter para terminar.    ";
	cin.get();
	return 0;
}
