#pragma once

#include <cstdlib>
#include "Pila.h"
#include <string>

#ifndef ARRAYBST_H
#define ARRAYBST_H

//Implement to deliver friday as array with deletion and traversal


template <typename T>
class ArrayBST {

	template <typename T>
	struct TreeNode {
		int key = 0;
		T data = T();
		int lChild = 0;
		int rChild = 0;
	};




public:

	//Fields
	TreeNode<T> * tree;
	int boundSize;

	ArrayBST(int capacity = 14) {
		boundSize = capacity;

		tree = new TreeNode<T>[boundSize];

		tree[0].lChild = 0;	//Tree[0] is sentinel node
		tree[0].rChild = 1;

		//for (int i = 0; i < boundSize; i++) {
		//	tree[i].rChild = i + 1;  //Free space starts at first actual node
		//}

	}


	

	bool insert(int key, T data) {

		//Don't add if "FreeIndex" is beyond MaxSize (index1 notation) because index0 is excluded due to sentinel
		if (!(tree[0].rChild - 1 < boundSize)) return false;

		//temp->key = key;
		//temp->data = data;

		//If no root defined yet
		if (tree[0].lChild == 0) {
			tree[tree[0].rChild].key = key;
			tree[tree[0].rChild].data = data;
			tree[0].lChild = 1;						//The root will always be at index 1.
			++tree[0].rChild;
			return true;
		}
		else {

			//TreeNode<T>* prevNode = &tree[0];		//Point to the data at the adress that holds the root.
			//TreeNode<T>* nextNode = left(*prevNode);
			TreeNode<T>* nextNode = left(tree[0]);
			TreeNode<T>* trailingNode = nextNode;


			bool side;

			//condition makes sense because for leaf nodes, child(prevNode) = tree[0];
			while (nextNode != &tree[0]) {
				if (key == nextNode->key) return false;			//Same key data not allowed.
				trailingNode = nextNode;
				if (key < nextNode->key) {
					nextNode = left(*nextNode);
					side = 0;
				}
				else {
					nextNode = right(*nextNode);
					side = 1;
				}
			}

			//Add node at "free index"
			tree[tree[0].rChild].key = key;
			tree[tree[0].rChild].data = data;
	
			// Update parent in traversal to link to the added node
			if (side == 0) trailingNode->lChild = tree[0].rChild;
			else trailingNode->rChild = tree[0].rChild;

			// Increment "free" index
			++tree[0].rChild;

			return true;


			//The same
			//int comparedKey = nextNode->key;
			//int comparedKey = left(*prevNode)->key;

			////tree[0].rChild is insert pos;
			////tree[0].rChild = tree[tree[0].rChild];
			////int next = tree[0].rChild;

			////Step 1 is to simply insert the nodes.
			//tree[tree[0].rChild].key = key;
			//tree[tree[0].rChild].data = data;

			//if (parentNode != NULL)
			//	while (peekNode != NULL) {
			//		if (key == comparedKey) return false;
			//		else if (key < comparedKey) {
			//			peekNode = left();
			//		}
			//		else {
			//			parentNode = right(parentNode);
			//		}
			//	}



			//++tree[0].rChild;
			return true;
		}
	}


	TreeNode<T>* left(const TreeNode<T>& root) { return &tree[root.lChild]; }
	TreeNode<T>* right(const TreeNode<T>& root) { return &tree[root.rChild]; }

	//search node to delete
	//holding ref to parent of node to delete, remove then link parent-children_to_delete
	//overwrite and swap the start of the "free space" by setting right child of of deleted node to previous start of first (sentinel) node.
	//Having the sentinel hold the space dedicated to show the beginning of the free space may only be done when representing the tree as an array.


	////Print the data, not the keys...
	//std::string traversePreorder(TreeNode<T>* node) {

	//}

	////Print the data, not the keys...
	//std::string traversePostOrder(TreeNode<T>* node) {

	//}

	////Print the data, not the keys...
	//std::string traverseInOrder(TreeNode<T>* node) {

	//}


};

#endif // !ARRAYBST_H
