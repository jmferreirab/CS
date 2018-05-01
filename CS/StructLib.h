#include <string>

#ifndef StructLib_h
#define StructLib_h

struct Ingrediente {
	std::string nombre;
	float cantidad;
	std::string unidades;
};

template<class T>
struct Data{
	T key;
	const char* info;
};

struct IndexedNode{
	Data<int> data;
	IndexedNode* next;
};

struct Student{	
	int codigo;	
	std::string nombre;
};

struct PersonData{
	std::string name;
	std::string career;
	std::string hobby;
	int age;
};

struct Person{	
	PersonData pData;
	int nextName=0, nextCareer=0, nextHobby = 0, nextAge = 0;
};

struct HeaderNode{
	std::string info;
	int headIndex;
};

#endif
