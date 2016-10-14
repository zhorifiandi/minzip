#ifndef BINTREE_H
#define BINTREE_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

#include "ConstVariables.h"
using namespace std;

// Class untuk Huffman Binary Tree
class BinTree {
	//Class Node sebagai nested class dari Class BinTree
private:
	class Node {
	public:
		//Constructor Node
		Node();
		//Destructor Node
		~Node();
		//Copy constructor Node
		Node(const Node&);
		//Operator overloading untuk assignment Node
		const Node& operator= (const Node&);

		//Data member dari Class Node
		//Left child
		Node *Left;
		//Right child
		Node *Right;
		//Karakter yang disimpan
		unsigned char Kar;
		//Frekuensi karakter
		unsigned int Frekuensi;
	};

	//Data member dari BinTree yang merupakan Node
	Node *Akar;

public:
	//ctor, cctor, operator assignment, dtor dari Class BinTree

	//Constructor BinTree
	BinTree();
	//Destructor BinTree
	~BinTree();
	//Copy constructor BinTree
	BinTree(const BinTree&);
	//Operator overloading untuk assignment BinTree
	const BinTree& operator= (const BinTree&);

	//Setter BinTree
	void SetFrekuensi(unsigned int);
	void SetChar(unsigned char);
	void SetLeft(Node*);
	void SetRight(Node*);

	//Getter BinTree
	unsigned int GetFrekuensi() const;
	unsigned char GetChar() const;
	Node* GetLeft() const;
	Node* GetRight() const;
	Node* GetAkar() const;

	//Fungsi untuk mengecek apakah sebuah simpul merupakan daun

	bool IsLeaf(Node*) const;

	//Fungsi-fungsi manipulasi karakter dan Huffman string pada BinTree

	//Untuk memeroleh Huffman string dari sebuah karakter pada BinTree yang bersangkutan
	void HuffString(Node*, unsigned char, string, string&) const;
	//Untuk mendapatkan karakter dari Huffman string pada BinTree yang bersangkutan
	//Jika karakter ditemukan akan mengembalikan true dan variabel diisi dengan
	//char yang sesuai, jika tidak akan mengembalikan false
	bool HuffChar(string, unsigned char&) const;

	//Fungsi-fungsi operator overloading untuk perbandingan dua BinTree
	//Perbandingan berdasarkan informasi frekuensi karakter 
	//yang disimpan pada Akar
	//Fungsi diimplementasikan sbg fungsi anggota

	//Mengembalikan true apabila current BinTree memiliki 
	//nilai frekuensi lebih kecil daripada BinTree masukan
	bool operator< (const BinTree&) const;
	//Mengembalikan true apabila current BinTree memiliki 
	//nilai frekuensi lebih besar daripada BinTree masukan
	bool operator> (const BinTree&) const;

	//Fungsi Untuk mendealokasi BinTree, akan dipanggil pada dtor

	void BurnTree(Node*);
};

#endif