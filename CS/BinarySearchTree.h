#pragma once

#include <cstdlib>
#include "Pila.h"
#include <string>

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


template <typename T>
class BST{

	template <typename T>
	struct TreeNode {
		int key;
		T data;
		TreeNode<T>* lChild = NULL;
		TreeNode<T>* rChild = NULL;
	};

public:
	TreeNode<T> * root;
	BST() {
		//sentinel = new TreeNode;
		//sentinel->lChild = NULL;
		//sentinel->rChild = NULL;
		root = NULL;
	}

	//search node to delete
	//holding ref to parent of node to delete, remove then link parent-children_to_delete
	//overwrite and swap the start of the "free space" by setting right child of of deleted node to previous start of first (sentinel) node.
	//Having the sentinel hold the space dedicated to show the beginning of the free space may only be done when representing the tree as an array.
	void deleteNode() {
		return;
	}

	void insert(int key, T data) {
		TreeNode<T>* temp = new TreeNode<T>;
		temp->key = key;
		temp->data = data;
		TreeNode<T>** current = &root;

		while (*current != 0) {
			if (key < (*current)->key) {
				current = &((*current)->lChild);
			}
			else if (key > (*current)->key) {
				current = &((*current)->rChild);
			}
		}
		*current = temp;		//Current must be in the right position, so just pass the values.
	}

	//Print the data, not the keys...
	std::string traversePreorder(TreeNode<T>* node) {
		if (!node) return "";
		std::string output;
		Pila<TreeNode<T>*> stack;								//Holds the data, not the keys
		stack.push(node);										//push the first node.
		while (!stack.PilaVacia()) {							//Meaningful for 2th and onwards iterations			
			node = stack.pop();									//Obtain(POP) the data at top
			output += node->data + "\t";			     		//Store IT
			if (node->rChild) stack.push(node->rChild);
			if (node->lChild) stack.push(node->lChild);
		}
		return output;
	}

	//Print the data, not the keys...
	std::string traversePostOrder(TreeNode<T>* node) {
		if (!node) return "";

		Pila<TreeNode<T>*> stack;
		std::string output;
		TreeNode<T>* lastNode = NULL;
		TreeNode<T>* peekNode = NULL;
		while (!stack.PilaVacia() || node) {
			if (node) {
				stack.push(node);
				node = node->lChild;
			}else {
				peekNode = stack.peek();
				if (peekNode->rChild && lastNode != peekNode->rChild) node = peekNode->rChild;
				else {
					output += peekNode->data + "\t";
					lastNode = stack.pop();
				}
			}
		}
		return output;
	}

	//Print the data, not the keys...
	std::string traverseInOrder(TreeNode<T>* node) {
		if (!node) return "";
		Pila<TreeNode<T>*> stack;
		std::string output;
		TreeNode<T>* lastNode = NULL;
		TreeNode<T>* peekNode = NULL;
		while (!stack.PilaVacia() || node) {
			if (node) {
				stack.push(node);
				node = node->lChild;
			}
			else {
				node = stack.pop();
				output += node->data + "\t";
				node = node->rChild;
			}
		}
		return output;
	}


};

#endif // !BINARYSEARCHTREE_H
