#ifndef GENERICPRIORQUEUE_H
#define GENERICPRIORQUEUE_H

#include<iostream>
#include<fstream>
using namespace std;

//Class PriorQueue
//Adalah kelas generik dengan menerapkan template
//Menggunakan struktur data priority queue
//Implementasi dengan array dinamis

template<class Type>
class PriorQueue {
public:
	//Ctor, Cctor, Operator assignment, Dtor 

	//Constructor
	PriorQueue(int = 2);
	//Copy constructor
	PriorQueue(const PriorQueue&);
	//Operator assignment
	const PriorQueue& operator= (const PriorQueue&);
	//Destructor
	~PriorQueue();

	//Getter

	//Mengambil head dari PriorQueue
	Type* GetHead();

	//Fungsi untuk menambah ukuran array dinamik

	void Grow();

	//Const method untuk mengetahui kondisi Queue

	//Fungsi untuk mengecek apakah PriorQueue kosong
	bool IsEmpty() const;
	//Fungsi untuk mengecek apakah PriorQueue penuh
	bool IsFull() const;

	//Fungsi-fungsi untuk melakukan pengurutan pada saat 
	//elemen ditambahkan atau dihapus sehingga elemen
	//tetap terurut layaknya priority queue

	//Fungsi pembantu untuk menukar elemen
	void Swap(Type*&, Type*&);
	//Fungsi untuk melakukan pengurutan dari tail ke head
	//(dari bawah ke atas)
	void FixQueueUp(int, int);
	//Fungsi untuk melakukan pengurutan dari head ke tail
	//(dari atas ke bawah)
	void FixQueueDown(int, int);

	//Method untuk mengelola PriorQueue (Add dan Del)

	//Fungsi untuk menambah elemen
	void Add(Type*);
	//Fungsi untuk menghapus elemen dan mendapatkan nilainya
	Type* Del();

private:
	//Data member

	//Array dinamis untuk implementasi PriorQueue
	Type* *DArray;
	//Ukuran array dinamis
	int size;
	//Jumlah memori yang dialokasi ataupun didealokasi
	//setiap terjadi perubahan ukuran pada array dinamis
	static const int IncrementSize = 10;
	//Elemen terakhir  
	int Tail; //the last element in the queue
	//Jumlah minimum ChildNode dari ParentNode 
	int NChild;
};

//Implementasi Generic Class langsung dilakukan di header file (.h)
//tidak dilakukan di implementation file (.cpp)

//Constructor PriorQueue
template<class Type>
PriorQueue<Type>::PriorQueue(int n_child) {
	NChild = n_child;
	Tail = 0;
	size = IncrementSize;
	DArray = new Type*[size];
}

//Destructor PriorQueue untuk menghapus array dinamis
template<class Type>
PriorQueue<Type>::~PriorQueue() {
	delete[] DArray;
}

//Getter untuk Head element yaitu DArray[0] 
template<class Type>
Type* PriorQueue<Type>::GetHead() {
	if (!IsEmpty()) {
		return DArray[0];
	}
	else {
		return 0;
	}
}

//Fungsi untuk memeriksa apakah PriorQueue kosong
template<class Type>
bool PriorQueue<Type>::IsEmpty() const {
	return (Tail < 1);
}

//Fungsi untuk memeriksa apakah PriorQueue penuh
template<class Type>
bool PriorQueue<Type>::IsFull() const {
	return (Tail >(size - 1));
}

template<class Type>
void PriorQueue<Type>::Grow() {
	//Ukuran baru
	int NewSize = size + IncrementSize;
	//Array dinamis baru
	Type* *NewDArray = new Type*[NewSize];
	//Salin elemen satu per satu dari DArray ke NewDArray
	for (int i = 0; i<size; i++) {
		NewDArray[i] = DArray[i];
	}
	//Dealokasi DArray
	delete[] DArray;

	//Salin pointer NewDArray ke DArray agar menunjuk ke alamat baru yg sama
	DArray = NewDArray;
	//Ganti dengan ukuran baru
	size = NewSize;
}

//Menukar dua elemen generik
template<class Type>
void PriorQueue<Type>::Swap(Type* &x, Type* &y) {
	Type* z;
	z = x;
	x = y;
	y = z;
}

//Fungsi rekursif untuk mengurutkan PriorQueue dari bawah ke atas
//setelah sebuah elemen ditambahkan ke tail PriorQueue
template<class Type>
void PriorQueue<Type>::FixQueueUp(int NodeAkar, int NodeBottom) {
	//Node parent dari elemen NodeBottom
	int NodeParent;

	if (NodeBottom > NodeAkar) {
		NodeParent = (NodeBottom - 1) / NChild;

		//Bandingkan kedua node dan jika urutannya salah, maka lakukan swap
		//Lakukan secara rekursif dari bawah ke atas hingga 
		//seluruh urutan Node pada BinTree sesuai urutan semula 
		//Urutan salah jika frekuensi karakter pada parent lebih besar 
		//dari frekuensi parent pada bottom
		if (*DArray[NodeParent] > *DArray[NodeBottom]) {
			Swap(DArray[NodeParent], DArray[NodeBottom]);
			FixQueueUp(NodeAkar, NodeParent);
		}
	}
}

//Fungsi rekursif untuk mengurutkan PriorQueue dari atas ke bawah
//setelah sebuah elemen dihapus 
template<class Type>
void PriorQueue<Type>::FixQueueDown(int NodeAkar, int NodeBottom) {
	int tempchild, firstchild, minimumchild;

	//posisi firstchild dari NodeAkar
	firstchild = NodeAkar * NChild + 1;

	//jika firstchild ada di PriorQueue
	if (firstchild <= NodeBottom) {
		//inisiasi minchild dengan firstchild
		minimumchild = firstchild;

		for (int k = 2; k <= NChild; k++) {
			//posisi nextchild 
			tempchild = NodeAkar*NChild + k;

			//jika child ada di PriorQueue
			if (tempchild <= NodeBottom) {
				//Jika frekuensi karakter child lebih kecil dari 
				//frekuensi minchild, maka jadikan child sbg minchild
				if (*DArray[tempchild] < *DArray[minimumchild]) {
					minimumchild = tempchild;
				}
			}
		}

		//Jika minchild yang ditemukan lebih kecil dari root atau parent node,
		//maka tukar keduanya dan lakukan pengurutan dari atas ke bawah
		//pada BinTree secara rekursif
		if (*DArray[NodeAkar] > *DArray[minimumchild]) {
			Swap(DArray[NodeAkar], DArray[minimumchild]);
			FixQueueDown(minimumchild, NodeBottom);
		}
	}
}

//Fungsi untuk menambahkan elemen ke tail dari PriorQueue
template<class Type>
void PriorQueue<Type>::Add(Type* item) {
	//Jika array dinamis sudah penuh, buat ukurannya jadi lebih besar
	//Grow DArray
	if (IsFull()) {
		Grow();
	}

	//Tambahkan elemen baru ke tail dari PriorQueue
	DArray[Tail] = item;
	//Tambahkan nilai tail
	Tail++;
	//Lakukan pengurutan dari bawah ke atas
	FixQueueUp(0, Tail - 1);
}

//Fungsi untuk menghapus elemen head dari PriorQueue
//dan mengembalikan nilainya
template<class Type>
Type* PriorQueue<Type>::Del() {
	if (!IsEmpty()) { //Jika PriorQueue tidak kosong
		//Set return value
		Type* rval = DArray[0];
		//Pindahkan elemen tail ke head
		DArray[0] = DArray[Tail - 1];
		//Kurangi tail
		Tail--;
		//Lakukan pengurutan dari atas ke bawah
		FixQueueDown(0, Tail - 1);
		return rval;
	}
	else {
		//Queue kosong, tdk mungkin delete head
		return 0;
	}
}

#endif