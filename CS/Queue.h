#pragma once

#include <stddef.h>

#ifndef Queue_h
#define QUeue_h

template<class T>
struct ListNode {
	T data;
	ListNode<T> *next;
};

template<class T>
class DoublyQueue{

	int _size;
	ListNode<T> *root, *last;
	ListNode<T>* getNode(int index);

public:

	DoublyQueue() {
		root = NULL;
		last = NULL;
		_size = 0;
	};

	DoublyQueue(const DoublyQueue<T> &list) {
		root = NULL;
		_size = 0;
		ListNode<T>* tmp = list.root;
		while (tmp != NULL) {
			enqueueLeft(tmp->data);
			tmp = tmp->next;
		}
	}

	DoublyQueue<T> &operator=(DoublyQueue<T> src)
		// pass by reference performs the copy
	{
		//this->_size = src._size;
		std::swap(root, src.root); // now just swap the head of the copy 
								   // for the head of the source
		return *this;
	}

	/*
	Until the head is null,
	Store the current head as a dummy pointer.
	Shift the actual head by one using it's next node.
	Free memory allocated to the previous head using the dummy pointer.
	*/
	~DoublyQueue() {
		ListNode<T>* tmp;
		while (root != NULL)
		{
			tmp = root;
			root = root->next;
			delete tmp;
		}
		last = NULL;
	};


	/*
	Add(Insert) given object at the end of the list. Increase size.
	*/
	virtual bool enqueueLeft(T);

	/*
	Add(Insert) given object at the start of the list. Increase size.
	*/
	virtual bool enqueueRight(T);
	

	virtual int size();

	/*
	Remove first object;
	*/
	virtual T dequeueLeft();


	/*
	Also known as Pop()
	*/
	virtual T dequeueRight();

	/*
	Get the index'th element on the list;
	Return Element if accessible,
	else, return false;
	*/
	virtual T get(int index);


};


template<typename T>
int  DoublyQueue<T>::size() {
	return _size;
}

/*
Create a dummy node that will receive the passed data and will have no next element.
If this node is the first node ever added, the make it both root and last.
Else,
make the -to-be-updated last node point to the new to-be last node. (that is, the dummy)
Then set the real last node to the dummy.
Forget about the dummy.
*/
template<typename T>
bool DoublyQueue<T>::enqueueLeft(T t) {
	ListNode<T> *tmp = new ListNode<T>();
	tmp->data = t;
	tmp->next = NULL;

	if (root) {
		// Already have elements inserted
		last->next = tmp;
		last = tmp;
	}
	else {
		// First element being inserted
		root = tmp;
		last = tmp;
	}

	_size++;
	return true;
}

/*
If attempting to add(insert) when list is empty, lets add_end() function solve the request.
Otherwise,
create a dummy node and set its next field to the current root
then, set this dummy to be the new current root linked to the previous root.
Forget about the dummy.
*/

template<typename T>
bool DoublyQueue<T>::enqueueRight(T t) {
	if (_size == 0) return enqueueLeft(t);

	ListNode<T> *tmp = new ListNode<T>();
	tmp->next = root;
	tmp->data = t;
	root = tmp;

	_size++;

	return true;
}

/*
Move along the sequence of links using the dummmy variable (current) until we're at the position requested
Index-0 logic.
For Index-1, calls must increment its argument by one.
*/

template<typename T>
ListNode<T>* DoublyQueue<T>::getNode(int index) {

	int pos = 1;
	ListNode<T>* current = root;

	while (pos < index && current) {
		current = current->next;
		pos++;
	}

	if (pos == index) return current;

	return 0;
}


/*
Returns the data at the removed node for validation
*/
template<typename T>
T DoublyQueue<T>::dequeueRight() {

	//nothing to remove or invalid call so return T() = 0;
	if (_size < 1)	return T();

	if (_size >= 2) {
		ListNode<T> *tmp = getNode(_size - 1);   // size -2

												 //-2 because size is really an index. It is _size = desiredIndex + 1 so desiredIndex = _size - 1.
												 //Furthermore, for deletion we operate using a double pointer from the previous to last element.

		T deleted_data = tmp->next->data;
		delete(tmp->next);
		tmp->next = NULL;
		last = tmp;
		_size--;
		return deleted_data;
	}
	else {
		// Only one element left on the list then both root and last must be null
		T deleted_data = root->data;
		delete(root);
		root = NULL;
		last = NULL;
		_size = 0;
		return deleted_data;
	}
}

/*
Shift head by one. Similar to add_start but it must, aside from redefining the root, free the memory for the old root.
*/

template<typename T>
T DoublyQueue<T>::dequeueLeft() {

	//nothing to remove or invalid call so return T() = 0;
	if (_size < 1)
		return T();

	if (_size > 1) {
		ListNode<T> *_next = root->next;
		T deleted_data = root->data;
		delete(root);
		root = _next;
		_size--;

		return deleted_data;
	}
	else {
		// Only one left, then let remove_last() solve it
		return dequeueRight();
	}

}

template<typename T>
T DoublyQueue<T>::get(int index) {
	ListNode<T> *tmp = getNode(index);

	return (tmp ? tmp->data : T());
}

#endif