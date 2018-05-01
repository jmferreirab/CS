#include <stddef.h>
#include "StructLib.h"

#ifndef IndexedList_h
#define IndexedList_h
//
//struct Data{
//	char* info;
//	IndexedNode *next;
//};
//
//struct IndexedNode{
//	int index;
//	Data d;
//};

using std::cout;
using std::endl;


/*
	Template type T defines the type used as index in structure "Data".
	This class 'SSLL' implementation is only guaranteed to work for when T represents int types.
*/

class SSLL{
		
    int size;
    IndexedNode* head;
	IndexedNode* getNode(int index) {
	
		int pos = 1;
		IndexedNode* current = head;
	
		while (pos < index && current) {
			current = current->next;
			pos++;
		}
	
		if (pos == index) return current->next;
	
		return 0;
	}

public:     

	SSLL(){
		size = 0;
        head = new IndexedNode();
        head->next = NULL;
    }
    ~SSLL(){
        IndexedNode* tmp;
		while (head != NULL)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
  
    int getSize(){
    	return size;
	}

	void insert(Data<int> dataToAdd){		
	    IndexedNode* tmp = new IndexedNode();
		tmp->data = dataToAdd;
	    	   
        IndexedNode* current = head;  //holds the key for first node in a non-empty sll
        
        //find node before position to add at        
        while( current->next != NULL  &&  tmp->data.key > current->next->data.key   ){
            current = current->next;
        }
        
        tmp->next = current->next;  //Make new node link to whatever previous node linked to.
        current->next = tmp;        //Make previous node link to tmp newNode
        size++;        
	};	
	
	Data<int> get(int index) {
		IndexedNode* tmp = getNode(index);		
		return (tmp ? tmp->data : Data<int>());
	}
	
	template <typename T>
	Data<T> getByKey(T keySrch){
		IndexedNode* x = head->next;
		while( x != NULL && x->data.key != keySrch){
			if( x->data.key > keySrch) return Data<T>();
			x = x->next;
		}
		return x->data;		
	}
		
	template <typename T>
	void modify(const char* info, T keySrch){
		
		IndexedNode* current = head->next;
				
		while( current != NULL && current->data.key != keySrch){
			if (current->data.key > keySrch ) return;
			//previous = current;
			current = current->next;			
		}		
		current->data.info = info;
	};
	
	template <typename T>
	void deleteKey(T keySrch){
		IndexedNode* current = head;
		IndexedNode* target = NULL;
		
		while( current->next != NULL && current->next->data.key != keySrch){
			if (current->next->data.key > keySrch ) return;
			//previous = current;
			current = current->next;			
		}
		
		target = current->next; //to delete		
		current->next = current->next->next;
		
		delete target;
		
		size--;
	}
	
};

#endif
