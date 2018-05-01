using namespace std;

template <class T>
struct Nodo {
	T clave;
	int izq;
	int der;
};

template <class T>
class ArbolBinario {

	Nodo <T> *tree;

	int posLibre;
	int current;
	int peekIndex;

public:
	ArbolBinario(int tam = 14) {

		tree = new Nodo<T>[tam];

		for (int i = 0; i < tam; i++) {
			tree[i].right = i + 1;
			tree[i].izq = 0;
			tree[i].key = 0;
		}
		tree[tam - 1].right = 0;
	}


	void insertar(T key) {

		if (tree[0].right != 0) {
			current = tree[0].right;
			tree[current].key = key;
			posLibre = tree[current].right;
			tree[0].right = posLibre;
			tree[current].right = 0;
			peekIndex = tree[0].izq;

			while (true) {
				if (tree[peekIndex].key < tree[current].key) {
					if (tree[peekIndex].right == 0) {
						tree[peekIndex].right = current;
						break;
					}
					else {
						peekIndex = tree[peekIndex].right;
					}
				}
				else {
					if (tree[peekIndex].izq == 0) {
						tree[peekIndex].izq = current;
						break;
					}
					else {
						peekIndex = tree[peekIndex].izq;
					}
				}
			}
		}

	}

	void imprimir() {
		for (int i = 0; i < 14; i++) {
			cout << i << " | " << tree[i].key << " | " << tree[i].izq << " | " << tree[i].right << endl;
		}

	}

};
