#include "InOutStream.h"

//Fungsi rekursif untuk mengubah sebuah integer ke string
string IntToString(int k) {
    switch (k) {
        case 0 : return "0"; break;
        case 1 : return "1"; break;
        case 2 : return "2"; break;
        case 3 : return "3"; break;
        case 4 : return "4"; break;
        case 5 : return "5"; break;
        case 6 : return "6"; break;
        case 7 : return "7"; break;
        case 8 : return "8"; break;
        case 9 : return "9"; break;
        default : return (IntToString(k/10) + IntToString(k%10));
    }
}

//Fungsi untuk traversal setiap karakter dari string
//dan mengubahnya ke integer
int StringToInt(string s) {
    int bil = 0, i=0;
    do {
        bil = bil*10 + (s[i] - '0');
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
        if(c!=';') {
            sinput.resize(i,c);
            i++;
        }
    } while (c!=';');
}

//Setiap file hasil compress akan memiliki header file mengandung
//informasi nama file sebelumnya(asli) yang dicompress
//Fungsi ini akan menulis informasi nama file tsb ke 
//file hasil compress
void WriteFileName(ofstream &outfile, string sinput) {
    for (int i=0; i<sinput.length(); i++) {
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
unsigned char ReadBits(ifstream & infile)
{
    //Bit pos bernilai 0 hingga 7 yang merepresentasikan
    //8 bit dari kiri ke kanan
    //Bit yang dimaksud adalah kumpulan 8 bit dari sebuah karakter
    //yang memiliki ukuran 1 byte
    static int bit_pos=0; 
    static unsigned char c=infile.get();

    unsigned char i;

    //Mengambil sebuah bit dari satu byte karakter
    i=(c>>(7-bit_pos))%2; 
    ++bit_pos;
    bit_pos%=8;
    if(bit_pos==0)
        if(!infile.eof())
        {
            c=infile.get();
        }
        else
            i=2;

    return i;     
}

//Fungsi untuk menulis sebuah bit ke file eksternal output (bit per bit)
//Jika input unsigned char adalah 0, maka akan ditulis satu bit bernilai 0
//Jika input unsigned char adalah 1, maka akan ditulis satu bit bernilai 1
//Jika input unsigned char adalah 2, maka akan ditulis EOF yaitu '\0'
void WriteBits(unsigned char i, ofstream & outfile)
{
    static int bit_pos=0; //0 to 7 (left to right) on the byte block
    static unsigned char c='\0'; //byte block to write

    //Jika input unsigned char bukan dua
    if(i<2) 
    {
        if(i==1)
            //Tambahkan satu bit bernilai 1 ke sebuah byte karakter
            c=c | (i<<(7-bit_pos)); 
        else // i==0
            //Tambahkan satu bit bernilai 0 ke sebuah byte karakter
            c=c & static_cast<unsigned char>(255-(1<<(7-bit_pos))); 
        ++bit_pos;
        bit_pos%=8;
        if(bit_pos==0)
        {
            outfile.put(c);
            c='\0';
        }
    }
    else 
    //Jika input unsigned char adalah dua
    {
        //Tulis EOF
        outfile.put(c);
    }
}