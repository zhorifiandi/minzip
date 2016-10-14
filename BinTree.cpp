#include "BinTree.h"

//Constructor Node (nested class)
BinTree::Node::Node() {
	Left = 0;
	Right = 0;
	Frekuensi = 0;
	Kar = '\0';
}

//Destructor Node (nested class)
BinTree::Node::~Node() {
	//tidak ada yg harus dilakukan
	//tidak ada data member node yang 
	//merupakan free-store object
}

//Constructor BinTree
BinTree::BinTree() {
	Node* simpul = new Node;
	Akar = simpul;
}

//Destructor BinTree
BinTree::~BinTree() {
	BurnTree(Akar);
}

//Setter BinTree
void BinTree::SetFrekuensi(unsigned int frek) {
	Akar->Frekuensi = frek;
}

void BinTree::SetChar(unsigned char chr) {
	Akar->Kar = chr;
}

void BinTree::SetLeft(Node* simpul) {
	Akar->Left = simpul;
}

void BinTree::SetRight(Node* simpul) {
	Akar->Right = simpul;
}

//Getter BinTree
unsigned int BinTree::GetFrekuensi() const {
	return Akar->Frekuensi;
}

unsigned char BinTree::GetChar() const {
	return Akar->Kar;
}

BinTree::Node* BinTree::GetLeft() const {
	return Akar->Left;
}

BinTree::Node* BinTree::GetRight() const {
	return Akar->Right;
}

BinTree::Node* BinTree::GetAkar() const {
	return Akar;
}

//Fungsi untuk mengecek apakah sebuah simpul merupakan daun
bool BinTree::IsLeaf(Node* simpul) const {
	return ((!(simpul->Left)) && (!(simpul->Right)));
}

//Fungsi rekursif untuk mencari sebuah Huffman string dari suatu karakter
//dgn menelusuri BinTree
//I.S : Node dari BinTree dan karakter yang dicari terdefinisi, 
//		string temp dan result bebas. String temp sebagai string input u/ 
//      rekursif, sedangkan string result adalah parameter reference
//F.S : String result mengandung Huffman string yang sesuai untuk karakter chr
void BinTree::HuffString(Node* simpul, unsigned char chr, string temp, string &result) const {
	if (simpul) { //Jika Node terdefinisi (tidak kosong)
		//Bandingkan informasi karakter pada daun dgn karakter input
		if ((simpul->Kar == chr) && (IsLeaf(simpul))) {
			result = temp; //Jika sama, salin temp ke result
		}
		else {
			//Jika beda atau bukan daun, maka
			//lanjutkan pencarian ke kiri dan kanan hingga ditemukan
			HuffString(simpul->Left, chr, temp + "0", result);
			HuffString(simpul->Right, chr, temp + "1", result);
		}
	}
}

//Fungsi rekursif untuk mencari karakter dari sebuah Huffman string 
//dgn menelusuri BinTree
//Jika karakter ditemukan, fungsi akan mengembalikan true dan karakter
//result akan berisi informasi karakter yang dicari
//Jika karakter tidak ditemukan, fungsi akan mengembalikan false
bool BinTree::HuffChar(string input, unsigned char &result) const {
	Node* CurrentNode = Akar;
	for (int i = 0; i<input.size(); i++) {
		//Jika karakter tersimpan pada node adalah '0', traversal ke kiri
		if (input[i] == '0') {
			CurrentNode = CurrentNode->Left;
		}
		else //Jika karakter tersimpan pada node adalah '1', traversal ke kanan
		if (input[i] == '1') {
			CurrentNode = CurrentNode->Right;
		}
	}

	//Jika Node adalah daun, maka karakter ditemukan
	//dan akan disalin ke char result
	bool found = false;
	if (IsLeaf(CurrentNode)) {
		found = true;
		result = CurrentNode->Kar;
	}
	return found;
}

//Operator overloading untuk membandingkan dua buah BinTree
//berdasarkan informasi frekuensi karakter pada masing-masing akar
bool BinTree::operator<(const BinTree &BT) const {
	return (Akar->Frekuensi < BT.Akar->Frekuensi);
}

bool BinTree::operator>(const BinTree &BT) const {
	return (Akar->Frekuensi > BT.Akar->Frekuensi);
}

//Fungsi rekursif untuk mendealokasi seluruh Node dari BinTree
void BinTree::BurnTree(Node *simpul) {
	if (simpul) {
		BurnTree(simpul->Left);
		BurnTree(simpul->Right);
		delete simpul;
	}
}