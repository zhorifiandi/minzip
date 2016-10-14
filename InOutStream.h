#ifndef INOUTSTREAM_H
#define INOUTSTREAM_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

//Fungsi untuk mendapatkan ukuran file 
long int GetFileSize(string);

//Fungsi rekursif untuk mengubah sebuah integer ke string
string IntToString(int k);

string LongIntToString(long int k);

//Fungsi untuk traversal setiap karakter dari string
//dan mengubahnya ke integer
int StringToInt(string s);


//Setiap file hasil compress akan memiliki header file mengandung
//informasi nama file sebelumnya(asli) yang dicompress
//Fungsi ini akan membaca informasi nama file tsb dari
//file hasil compress
void ReadFileName(ifstream &infile, string &sinput);

//Setiap file hasil compress akan memiliki header file mengandung
//informasi nama file sebelumnya(asli) yang dicompress
//Fungsi ini akan menulis informasi nama file tsb ke 
//file hasil compress
void WriteFileName(ofstream &outfile, string sinput);

//Fungsi untuk membaca sebuah bit dari file eksternal input (bit per bit)
unsigned char ReadBits(ifstream & inputfile);

//Fungsi untuk menulis sebuah bit ke file eksternal output (bit per bit)
void WriteBits(unsigned char uc, ofstream & outputfile);

#endif