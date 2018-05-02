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
		boundSize = capacity+1;

		tree = new TreeNode<T>[boundSize];

		tree[0].lChild = 0;	//Tree[0] is sentinel node
		tree[0].rChild = 1;

		//for (int i = 1; i < boundSize; i++) {
		//	tree[i].lChild = tree[i].rChild = 0;  //Free space starts at first actual node
		//}

	}


	

	void insert(int key, T data) {

		//Don't add if "FreeIndex" is beyond MaxSize (index1 notation) because index0 is excluded due to sentinel
		if (!(tree[0].rChild < boundSize)) return;

		//temp->key = key;
		//temp->data = data;


		//TreeNode<T>* prevNode = &tree[0];		//Point to the data at the adress that holds the root.
		//TreeNode<T>* nextNode = left(*prevNode);
		TreeNode<T>* nextNode = left(tree[0]);
		TreeNode<T>* trailingNode = nextNode;

		// Will avoid repeating the comparison 
		int side = -1;

		//condition makes sense because for leaf nodes, child(prevNode) = tree[0];
		while (nextNode != &tree[0]) {						//As long as we haven't returned to the sentinel
			if (key == nextNode->key) {						//If same key, overwrite data.
				nextNode->data = data;
				return;			
			}
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

		int freeIndex = tree[tree[0].rChild].rChild;

		//Add node at "free index"
		tree[tree[0].rChild].key = key;
		tree[tree[0].rChild].data = data;
		tree[tree[0].rChild].lChild = tree[tree[0].rChild].rChild = 0;
	
		// Update parent in traversal to link to the added node
		if (side == 0) trailingNode->lChild = tree[0].rChild;
		else if (side == 1) trailingNode->rChild = tree[0].rChild;
		else tree[0].lChild = 1;										//If no root defined yet  //The root will always be at index 1.

		// Increment "free" index
		if (freeIndex != 0) tree[0].rChild = freeIndex;
		else ++tree[0].rChild;
		

	}

	//Get node with the min(key) starting at a given node. This node must not be the sentinel.
	TreeNode<T>* min(TreeNode<T>& root, int &index) { 
		index = root.rChild;
		TreeNode<T>* nextNode = right(root);
		if (nextNode == &tree[0]) return &root;

		TreeNode<T>* trailingNode = &root;
		
		while (nextNode != &tree[0]) {				//As long as we haven't returned to the sentinel			
			index = trailingNode->rChild;
			trailingNode = nextNode;			
			nextNode = left(*nextNode);			
		}
		return trailingNode;
	}

	//Get node with the max(key) starting at a given node. This node must not be the sentinel.
	TreeNode<T>* max(TreeNode<T>& root) {
		TreeNode<T>* nextNode = right(root);
		if (nextNode == &tree[0]) return &root;

		TreeNode<T>* trailingNode = NULL;
		
		while (nextNode != &tree[0]) {				//As long as we haven't returned to the sentinel
			trailingNode = nextNode;
			nextNode = right(*nextNode);
		}
		return trailingNode;			//Guaranteed to be != nulll
	}

	TreeNode<T>* left(const TreeNode<T>& root) { return &tree[root.lChild]; }
	TreeNode<T>* right(const TreeNode<T>& root) { return &tree[root.rChild]; }

	//TODO leave as is or change return type to only the data. If not found, return empty T;
	//When returning, we are passing variables by value, meaning deep copy, meaning copy meaning, memory overhead?
	TreeNode<T>* search(int key) {
		TreeNode<T>* nextNode = left(tree[0]);
		while (nextNode != &tree[0]) {				//As long as we haven't returned to the sentinel
			if (key == nextNode->key) return nextNode;			
			if (key < nextNode->key) nextNode = left(*nextNode);
			else nextNode = right(*nextNode);
		}
		//We stood at a leaf node and it wasn't the node to find. Then it doesn't exist.
		return NULL;
	}

	//search node to delete
	//holding ref to parent of node to delete, remove then link parent-children_to_delete
	//overwrite and swap the start of the "free space" by setting right child of of deleted node to previous start of first (sentinel) node.
	//Having the sentinel hold the space dedicated to show the beginning of the free space may only be done when representing the tree as an array.
	void deleteNode(int key) {
		TreeNode<T>* toDelete = left(tree[0]);
		TreeNode<T>* parentNode = NULL;

		while (toDelete != &tree[0]) {				//As long as we haven't returned to the sentinel			
			if (key == toDelete->key) break;
			parentNode = toDelete;
			if (key < toDelete->key) toDelete = left(*toDelete);
			else toDelete = right(*toDelete);

		}

		bool children[] = { 0,0 };
		int freeIndex = 0;
		if (toDelete->lChild != 0) children[0]++;
		if (toDelete->rChild != 0) children[1]++;

		TreeNode<T> *replacement = NULL;
		
		if (children[0]) {
			if (children[1]) {	//left and right child
				replacement = min(*toDelete, freeIndex);
				toDelete->data = replacement->data;
				toDelete->key = replacement->key;
				if (replacement->rChild != 0) {
					max(*replacement)->rChild = toDelete->rChild;
				}
				toDelete->rChild = replacement->rChild;
				replacement->lChild = replacement->key = 0;						//Zero-out child data to be that of free nodes
				replacement->rChild = tree[0].rChild;
			}
			else {			// only left child
				replacement = left(*toDelete);
				freeIndex = toDelete->lChild;
				*toDelete = *replacement;									//Overwrite "deleted" node data with its child
				replacement->lChild = replacement->key = 0;						//Zero-out child data to be that of free nodes
				replacement->rChild = tree[0].rChild;					//Add child to be in free node chain
			}
		}
		else if (children[1]){  //only right child
			replacement = right(*toDelete);
			freeIndex = toDelete->rChild;
			*toDelete = *replacement;									//Overwrite "deleted" node data with its child
			replacement->lChild = replacement->key = 0;						//Zero-out child data to be that of free nodes
			replacement->rChild = tree[0].rChild;					//Add child to be in free node chain
		}
		else{ 
			//It's leaf node. Is this leaf a right or left child?
			if (left(*parentNode)->key == toDelete->key) {	
				freeIndex = parentNode->lChild;			//deletedNode array index is now the new free index
				parentNode->lChild = 0;					//deletedNode is no longer parent's child
			}
			else {
				freeIndex = parentNode->rChild;			//deletedNode array index is now the new free index
				parentNode->rChild = 0;					//deletedNode is no longer parent's child
			}
			toDelete->lChild = toDelete->key = 0;
			toDelete->rChild = tree[0].rChild;			//Old free index will be after new free index			
		}
		tree[0].rChild = freeIndex;						//Mark child to be a free node	
		return;


	}

	

	TreeNode<T>* getRoot() {
		return &tree[1];
	}

	//Print the data, not the keys...
	std::string traversePreorder(TreeNode<T>* node) {
		//if (node==&tree[0]) return "";

		std::string output;
		Pila<TreeNode<T>*> stack;								//Holds the data, not the keys
		stack.push(node);										//push the first node.
		while (!stack.PilaVacia()) {							//Meaningful for 2th and onwards iterations			
			node = stack.pop();									//Obtain(POP) the data at top
			output += to_string(node->key) + "\t";			     		//Store IT			
			output += to_string(node->lChild) + "\t";			     		//Store IT
			output += to_string(node->rChild) + "\t";			     		//Store IT
			output += node->data + "\t\n";			     		//Store IT
			if (node->rChild!=0) stack.push(&tree[node->rChild]);
			if (node->lChild!=0) stack.push(&tree[node->lChild]);
		}
		return output;
	}

	////Print the data, not the keys...
	//std::string traversePostOrder(TreeNode<T>* node) {

	//}

	////Print the data, not the keys...
	//std::string traverseInOrder(TreeNode<T>* node) {

	//}


};

#endif // !ARRAYBST_H
