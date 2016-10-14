#include "InOutStream.h"

//Fungsi untuk mendapatkan ukuran file 
long int GetFileSize(string input) {
	char ch;
	long int counter = 0;
	ifstream inputfile(input.c_str(), ios::in | ios::binary);
	inputfile.seekg(0);

	while (inputfile.get(ch)){
		counter = counter + 1;
	}

	inputfile.close();
	return counter;
}

//Fungsi rekursif untuk mengubah sebuah integer ke string
string IntToString(int k) {
	switch (k) {
	case 0: return "0"; break;
	case 1: return "1"; break;
	case 2: return "2"; break;
	case 3: return "3"; break;
	case 4: return "4"; break;
	case 5: return "5"; break;
	case 6: return "6"; break;
	case 7: return "7"; break;
	case 8: return "8"; break;
	case 9: return "9"; break;
	default: return (IntToString(k / 10) + IntToString(k % 10));
	}
}

string LongIntToString(long int k)
{
	switch (k) {
	case 0: return "0"; break;
	case 1: return "1"; break;
	case 2: return "2"; break;
	case 3: return "3"; break;
	case 4: return "4"; break;
	case 5: return "5"; break;
	case 6: return "6"; break;
	case 7: return "7"; break;
	case 8: return "8"; break;
	case 9: return "9"; break;
	default: return (IntToString(k / 10) + IntToString(k % 10));
	}
}


//Fungsi untuk traversal setiap karakter dari string
//dan mengubahnya ke integer
int StringToInt(string s) {
	int bil = 0, i = 0;
	do {
		bil = bil * 10 + (s[i] - '0');
		i++;
	} while (i<s.length());
	return bil;
}

//Setiap file hasil compress akan memiliki header file mengandung
//informasi nama file sebelumnya(asli) yang dicompress
//Fungsi ini akan membaca informasi nama file tsb dari
//file hasil compress
void ReadFileName(ifstream &infile, string &sinput) {
	char c = '\0';
	int i = 1;

	do {
		infile.get(c);
		if (c != ';') {
			sinput.resize(i, c);
			i++;
		}
	} while (c != ';');
}

//Setiap file hasil compress akan memiliki header file mengandung
//informasi nama file sebelumnya(asli) yang dicompress
//Fungsi ini akan menulis informasi nama file tsb ke 
//file hasil compress
void WriteFileName(ofstream &outfile, string sinput) {
	for (int i = 0; i<sinput.length(); i++) {
		outfile.put(sinput[i]);
	}
	outfile.put(';');
}

//Fungsi untuk membaca sebuah bit dari file eksternal input (bit per bit)
//Jika bit yang terbaca adalah 0, maka dikembalikan unsigned char
//bernilai 0
//Jika bit yang terbaca adalah 1, maka dikembalikan unsigned char
//bernilai 1
//Jika EOF, maka akan mengembalikan unsigned char bernilai 2
unsigned char ReadBits(ifstream &inputfile)
{
	//Bit pos bernilai 0 hingga 7 yang merepresentasikan
	//8 bit dari kiri ke kanan
	//Bit yang dimaksud adalah kumpulan 8 bit dari sebuah karakter
	//yang memiliki ukuran 1 byte
	static int PosisiBit = 0;
	static unsigned char UChr = inputfile.get();
	unsigned char uc;

	//Mengambil sebuah bit dari satu byte karakter
	uc = (UChr >> (7 - PosisiBit)) % 2;
	PosisiBit++;
	PosisiBit %= 8;
	if (PosisiBit == 0)
	if (!inputfile.eof()) {
		UChr = inputfile.get();
	}
	else {
		uc = 2;
	}
	return uc;
}

//Fungsi untuk menulis sebuah bit ke file eksternal output (bit per bit)
//Jika input unsigned char adalah 0, maka akan ditulis satu bit bernilai 0
//Jika input unsigned char adalah 1, maka akan ditulis satu bit bernilai 1
//Jika input unsigned char adalah 2, maka akan ditulis EOF yaitu '\0'
void WriteBits(unsigned char uc, ofstream &outputfile)
{
	//Bit pos bernilai 0 hingga 7 yang merepresentasikan
	//8 bit dari kiri ke kanan
	//Bit yang dimaksud adalah kumpulan 8 bit dari sebuah karakter
	//yang memiliki ukuran 1 byte
	static int PosisiBit = 0;
	static unsigned char UChr = '\0';

	//Jika input unsigned char bukan dua
	if (uc<2)
	{
		if (uc == 1) {
			//Tambahkan satu bit bernilai 1 ke sebuah byte karakter
			UChr = UChr | (uc << (7 - PosisiBit));
		}
		else { // i==0
			//Tambahkan satu bit bernilai 0 ke sebuah byte karakter
			UChr = UChr & static_cast<unsigned char>(255 - (1 << (7 - PosisiBit)));
		}

		PosisiBit++;
		PosisiBit %= 8;
		if (PosisiBit == 0) {
			outputfile.put(UChr);
			UChr = '\0';
		}
	}
	else { //Jika input unsigned char adalah dua 
		//Tulis EOF
		outputfile.put(UChr);
	}
}