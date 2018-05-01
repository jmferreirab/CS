#include "StructLib.h"
#include <iostream>
#include <string>

#ifndef SortedMultilist_h
#define SortedMultilist_h

enum Categories {
	NOMBRE = 0,
	CATASTRAL = 1, ELECTRONICA = 2, INDUSTRIAL = 3, SISTEMAS = 4,
	BASKET = 5, BEISBOL = 6, DANZA = 7, NATACION = 8,
	AGE = 9,
	CAREER = 0, HOBBY = 1,
};

class SortedMultilist {
	HeaderNode* headerList;
	Person* personList;

	int sizeUnique;   //Holds true for the size of:   NameChain, AgeChain, 

	int sizes[10] = { 0 };		//name0,car1,car2,car3,car4,hob5,hob6,hob7,hob8,age9
	bool written[10] = { 0 };


public:

	SortedMultilist() {
		headerList = new HeaderNode[10];
		personList = new Person[11];
		initHeaderTags();
		sizeUnique = 0;
	}

	void initHeaderTags() {
		headerList[0] = { "Nombre", 0 };
		headerList[1] = { "Catastral", 0 };
		headerList[2] = { "Electronica", 0 };
		headerList[3] = { "Industrial", 0 };
		headerList[4] = { "Sistemas", 0 };
		headerList[5] = { "Basket", 0 };
		headerList[6] = { "Beisbol", 0 };
		headerList[7] = { "Danza", 0 };
		headerList[8] = { "Natacion", 0 };
		headerList[9] = { "Edad", 0 };
	}

	PersonData getPersonData(int index) {
		int pos = 1;
		Person current = personList[0];

		if (pos == index);

		return PersonData();
	}

	const int* findCategories(PersonData p) {
		//const char* career = p.career;
		//const char* hobby = p.hobby;

		int career, hobby;


		const char* s = new char[9]{"Sistemas"};
		const char* d = new char[6] {"Danza"};

		if (p.career == "Catastral") career = 1;
		else if (p.career == "Electronica") career = 2;
		else if (p.career == "Industrial") career = 3;
		else if (p.career == "Sistemas") career = 4;

		if (p.hobby == "Basket") hobby = 5;
		else if (p.hobby == "Beisbol") hobby = 6;
		else if (p.hobby == "Danza") hobby = 7;
		else if (p.hobby == "Natacion") hobby = 8;

		int carrer_hobby[2] = { career, hobby };

		return carrer_hobby;
	}

	void handleSizeIncrements(const int* categories) {

		sizeUnique++;
		sizes[0]++;		//name
		sizes[9]++;		//age

		for (int i = CATASTRAL; i <= SISTEMAS; i++) {
			if (categories[CAREER] == i) sizes[i]++;
		}

		for (int i = BASKET; i <= NATACION; i++) {
			if (categories[HOBBY] == i) sizes[i]++;
		}
	}

	void updateHeaders(const int* categories, int rollNumber, Person pToAdd) {

		updateNameList(pToAdd.pData);
		updateAgeList(pToAdd.pData);
		//headerList[0].headIndex = newHeaderName;
		//headerList[9].headIndex = newHeaderAge;

		updateCareerList(pToAdd.pData, categories[CAREER]);
		updateHobbyList(pToAdd.pData, categories[HOBBY]);
	}

	std::string makeLower(std::string word) {
		for (int i = 0; i < word.length(); i++)
			if (word[i] >= 'A' and word[i] <= 'Z')	word[i] = word[i] + 32;		

		return word;
	}

	void updateCareerList(PersonData p, int career) {

		// All headers must be updated on every insert. The updated for nodes 2-4 and 5-9 (career and hobby)
		// will be updated once so they remain linking to the first entry ever added to them.
		if (!written[career]) {
			headerList[career].headIndex = sizeUnique; 
			written[career] = 1;
		}else 
		{
			Person* prior = &personList[headerList[career].headIndex];
			for (int i = 2; i < sizes[career]; i++) {
				prior = &personList[prior->nextCareer];
			}
			personList[sizeUnique].nextCareer = 0;
			prior->nextCareer = sizeUnique;
		}
	}

	void updateHobbyList(PersonData p, int hobby) {
		if (!written[hobby]) {
			headerList[hobby].headIndex = sizeUnique;
			written[hobby] = 1;
		}
		else {
			Person* prior = &personList[headerList[hobby].headIndex];
			for (int i = 2; i < sizes[hobby]; i++) {
				prior = &personList[prior->nextHobby];
			}
			personList[sizeUnique].nextHobby = 0;
			prior->nextHobby = sizeUnique;
		}
	}

	/*
	If new Person name goes after current head, return unchangedHeadIndex[0]
	If new Person name goes before current head, return sizeUnique (the index in list of the element inserted)
	*/
	void updateNameList(PersonData p) {
		if (sizeUnique != 1) {
			Person* prior = &personList[headerList[NOMBRE].headIndex];

			if (compare(makeLower(p.name), makeLower(prior->pData.name))) {
				personList[sizeUnique].nextName = headerList[NOMBRE].headIndex;
				headerList[NOMBRE].headIndex = sizeUnique;
				return;
			}
			else if (sizeUnique == 2) {
				personList[sizeUnique].nextName = 0;
				prior->nextName = sizeUnique;
				return;
			}

			if (sizeUnique > 2) {
				Person* peek = &personList[prior->nextName];

				for (int i = 2; i < sizeUnique; i++) {
					if (compare(makeLower(p.name), makeLower(peek->pData.name))) {
						personList[sizeUnique].nextName = prior->nextName;
						prior->nextName = sizeUnique;
						return;
					}
					prior = peek;
					peek = &personList[peek->nextName];
				}

				personList[sizeUnique].nextName = 0;
				prior->nextName = sizeUnique;
				return;
			}
		}else headerList[NOMBRE].headIndex = 1;
	}

	void updateAgeList(PersonData p) {
		if (sizeUnique != 1) {
			Person* prior = &personList[headerList[AGE].headIndex];

			if ( p.age > prior->pData.age ) {
				personList[sizeUnique].nextAge = headerList[AGE].headIndex;
				headerList[AGE].headIndex = sizeUnique;
				return;
			}
			else if (sizeUnique == 2) {
				personList[sizeUnique].nextAge = 0;
				prior->nextAge = sizeUnique;
				return;
			}

			if (sizeUnique > 2) {
				Person* peek = &personList[prior->nextAge];

				for (int i = 2; i < sizeUnique; i++) {
					if ( p.age > peek->pData.age ) {
						personList[sizeUnique].nextAge = prior->nextAge;
						prior->nextAge = sizeUnique;
						return;
					}
					prior = peek;
					peek = &personList[peek->nextAge];
				}

				personList[sizeUnique].nextAge = 0;
				prior->nextAge = sizeUnique;
				return;
			}
		}
		else headerList[AGE].headIndex = 1;
	}

	//true if base is smaller or equal
	bool compare(std::string base, std::string vs) {
		if (base == vs) return true;

		bool result = true;

		if (base < vs) result = true;
		else return false;
	}

	void insert(PersonData p) {
		Person personAdded;
		personAdded.pData = p;

		const int* categories = findCategories(p);
		int categoriesD[2] = { categories[0], categories[1] };

		handleSizeIncrements(categoriesD);			//handles update of sizeUnique and sizes[0-9]

													//perAux.nextAge = 0;     optional. Not really needed i think
		if (sizeUnique == 1) {
			personList[1] = personAdded;

		}
		else personList[sizeUnique] = personAdded;

		updateHeaders(categoriesD, sizeUnique, personAdded);


		//headerList[0] = N

		//check with previous node shifting from the head to validate the need of updating header[0] and header[9]		
		//traverse the proper sublist based on hobby or carrer. 10 different traversal must be modelled.


	};

	// 
	PersonData* getNameSubArray() {
		PersonData* arp = new PersonData[sizeUnique];
		Person current = personList[headerList[NOMBRE].headIndex];
		arp[0] = current.pData;
		for (int i = 1; i < sizeUnique; i++) {			
			current = personList[current.nextName];
			arp[i] = current.pData;
		}
		return arp;
	}

	PersonData* getAgeSubArray() {
		PersonData* arp = new PersonData[sizeUnique];
		Person current = personList[headerList[AGE].headIndex];
		arp[0] = current.pData;
		for (int i = 1; i < sizeUnique; i++) {
			current = personList[current.nextAge];
			arp[i] = current.pData;
		}
		return arp;
	}

	//PersonData* getCareerSubArray(int i) {
	//	switch (i) {
	//		case 5:
	//			

	//	}
	//	PersonData* arp = new PersonData[sizeUnique];
	//	Person current = personList[headerList[AGE].headIndex];
	//	arp[0] = current.pData;
	//	for (int i = 1; i < sizeUnique; i++) {
	//		current = personList[current.nextAge];
	//		arp[i] = current.pData;
	//	}
	//	return arp;
	//}


	int getSize(int i) {
		return sizes[i];
	}

	void print() {
		std::cout << "\nIn order of addition:\n\n";
		for (int i = 1; i <= sizeUnique; i++) {
			std::cout << personList[i].pData.name << "\n";
		}

		std::cout << "\nIn order of nameSublist:\n\n";
		Person current = personList[headerList[NOMBRE].headIndex];
		std::cout << current.pData.name << "\n";
		while (current.nextName != 0) {
			current = personList[current.nextName];
			std::cout << current.pData.name << "\n";

		}

		std::cout << "\nIn order of AgeSublist:\n\n";
		current = personList[headerList[AGE].headIndex];
		std::cout << current.pData.name << "  " << current.pData.age << "\n";
		for(int i = 2; i <= sizeUnique; i++){
			current = personList[current.nextAge];
			std::cout << current.pData.name << "  "<< current.pData.age << "\n";

		}

		std::cout << "\nIn order of Career:\n\n";
		current = personList[headerList[CATASTRAL].headIndex];
		std::cout << current.pData.name << "  " << current.pData.career << "\n";
		for (int i = 2; i <= sizes[CATASTRAL]; i++) {
			current = personList[current.nextCareer];
			std::cout << current.pData.name << "  " << current.pData.career << "\n";		
		}

	}

	//Name insertion must be ordered. Age must ordered. 

	//bool remove(Sublist s, int sublistIndex);

};


#endif


// name a-z		sorted
// age 100>0   sorted
// carrer append  per sublist
// hobby preppend per sublist

//deletion based on list and position - deletion must propagate

//opciones

//1Insertar		-> pide nombre carrera hobby edad 
//2Eliminar		-> pide posicion y especifica lista por cin
//3.Imprimir    -> cual lista 1 2 3 4 - > 2-> 1234  3->1234
//4.Salir