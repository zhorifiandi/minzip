#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<ctime>
#include<msclr\marshal_cppstd.h>

#include "InOutStream.h"
#include "GenericPriorQueue.h" 
#include "BinTree.h"
#include "ConstVariables.h"

using namespace std;
namespace MINZIP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for Compression
	/// </summary>


	using namespace std;


	public ref class Decompression : public System::Windows::Forms::Form
	{
	public:
		Decompression(void)
		{
			InitializeComponent();

			//Compress1()
			//
			//TODO: Add the constructor code here
			//
		}
		//Fungsi pembantu untuk melakukan compress pada satu file
		String^ input;
		long int sizesemula;
		long int sizesesudah;

		long int *ArrayFrekuensiTotal;
		int *ArrayPanjangBitTotal;
		int JumlahFile;

	private: System::Windows::Forms::Label^  rataan;
	public:
	private: System::Windows::Forms::Label^  entropi;
	private: System::Windows::Forms::Label^  nisbah;
	private: System::Windows::Forms::Label^  filesetelah;
	private: System::Windows::Forms::Label^  filesemula;
	private: System::Windows::Forms::Label^  waktu;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::Label^  label1;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Decompression()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	public: void Start(){
				JumlahFile = 0;

				ArrayFrekuensiTotal = new long int[256];
				for (int i = 0; i < 256; i++) {
					ArrayFrekuensiTotal[i] = 0;
				}

				ArrayPanjangBitTotal = new int[256];

				for (int i = 0; i < 256; i++) {
					ArrayPanjangBitTotal[i] = 0;
				}

				String^ dummy = this->input;
				string input = msclr::interop::marshal_as<string>(dummy);
				Stopwatch^ stopwatch = gcnew Stopwatch();
				stopwatch->Start();
				//Decompress()
				Decompress(input);
				//Compress1(input->Length, masukan, out);
				stopwatch->Stop();
				int ms = int(stopwatch->ElapsedMilliseconds);
				int n = ms / 1000;
				int mod = ms % 1000;
				string sn = IntToString(n);
				string smod = IntToString(mod);
				string det = sn + "," + smod;
				String^ Sdetik = msclr::interop::marshal_as<String ^>(det);
				this->waktu->Text = Sdetik + " s";
				this->label1->Text = "100%";

				//FILE SEBELUM
				long int ukuranawal = this->sizesemula;

				string sz; String^ szs;
				if (ukuranawal < 1024) // byte
				{
					sz = LongIntToString(ukuranawal);
					sz += " Byte";
					szs = msclr::interop::marshal_as<String ^>(sz);
				}
				else if (ukuranawal >= 1024 && ukuranawal < 1048576) //ukuran kilobyte
				{
					long int Kuk, Buk;
					string Ksz, Bsz;


					Kuk = ukuranawal / 1024;
					Buk = (ukuranawal % 1024);
					Ksz = LongIntToString(Kuk);
					Bsz = LongIntToString(Buk);
					sz = Ksz + "," + Bsz + " KB";
					szs = msclr::interop::marshal_as<String ^>(sz);
				}
				else if (ukuranawal >= 1048576 && ukuranawal < 1073741824) //ukuran megabyte
				{
					long int Muk, Kuk;
					string Msz, Ksz;

					Muk = ukuranawal / 1048576;
					Kuk = (ukuranawal % 1048576);
					Msz = LongIntToString(Muk);
					Ksz = LongIntToString(Kuk);
					sz = Msz + "," + Ksz + " MB";
					szs = msclr::interop::marshal_as<String ^>(sz);
				}
				else //Gigabyte
				{
					long int Guk, Muk;
					string Gsz, Msz;

					Guk = ukuranawal / 1073741824;
					Muk = (ukuranawal % 1073741824);
					Gsz = LongIntToString(Guk);
					Msz = LongIntToString(Muk);
					sz = Gsz + "," + Msz + " GB";
					szs = msclr::interop::marshal_as<String ^>(sz);
				}
				this->filesemula->Text = szs;


				//FILE SESUDAH
				long int ukuranakhir = this->sizesesudah;

				string szd; String^ szsd;
				if (ukuranakhir < 1024) // byte
				{
					szd = LongIntToString(ukuranakhir);
					szd += " Byte";
					szsd = msclr::interop::marshal_as<String ^>(szd);
				}
				else if (ukuranakhir >= 1024 && ukuranakhir < 1048576) //ukuran kilobyte
				{
					long int Kuk, Buk;
					string Ksz, Bsz;


					Kuk = ukuranakhir / 1024;
					Buk = (ukuranakhir % 1024);
					Ksz = LongIntToString(Kuk);
					Bsz = LongIntToString(Buk);
					szd = Ksz + "," + Bsz + " KB";
					szsd = msclr::interop::marshal_as<String ^>(szd);
				}
				else if (ukuranakhir >= 1048576 && ukuranakhir < 1073741824) //ukuran megabyte
				{
					long int Muk, Kuk;
					string Msz, Ksz;

					Muk = ukuranakhir / 1048576;
					Kuk = (ukuranakhir % 1048576);
					Msz = LongIntToString(Muk);
					Ksz = LongIntToString(Kuk);
					szd = Msz + "," + Ksz + " MB";
					szsd = msclr::interop::marshal_as<String ^>(szd);
				}
				else //Gigabyte
				{
					long int Guk, Muk;
					string Gsz, Msz;

					Guk = ukuranakhir / 1073741824;
					Muk = (ukuranakhir % 1073741824);
					Gsz = LongIntToString(Guk);
					Msz = LongIntToString(Muk);
					szd = Gsz + "," + Msz + " GB";
					szsd = msclr::interop::marshal_as<String ^>(szd);
				}
				this->filesetelah->Text = szsd;


				this->progressBar1->Value = 100;
				this->button1->Enabled = true;

				//NISBAH
				int nisbah = 100 * ukuranawal / ukuranakhir;
				string dmy = IntToString(nisbah);
				dmy += " %";
				String^ dmy2;
				dmy2 = msclr::interop::marshal_as<String ^>(dmy);
				this->nisbah->Text = dmy2;
				
				//ENTROPI
				double ArrayPeluang[256];

				for (int i = 0; i < 256; i++) {
					ArrayPeluang[i] = ((double)ArrayFrekuensiTotal[i]) / ((double) this->sizesesudah);
				}

				double Entropi = 0;

				for (int i = 0; i < 256; i++) {
					if (ArrayPeluang[i] > 0) {
						Entropi += ((-1)*ArrayPeluang[i]) * (log2(ArrayPeluang[i]));
					}
				}
				Entropi = Entropi / (double) JumlahFile;

				double rounded_down = (floorf(Entropi * 10000) / 10000);
				double nearest = (roundf(Entropi * 10000) / 10000);
				double rounded_up = (ceilf(Entropi * 10000) / 10000);

				this->entropi->Text = rounded_up + "";
				
				double RerataBit = 0;
				//int Sum = 0;

				for (int i = 0; i < 256; i++) {
					//Sum += ArrayPanjangBitTotal[i];
					RerataBit += ArrayPanjangBitTotal[i] * ArrayPeluang[i];
				}

				/*RerataBit = ((double)Sum) / ((double)256);*/
				RerataBit = RerataBit / (double) JumlahFile;
				double rounded_down1 = floorf(RerataBit * 10000) / 10000;
				double nearest1 = roundf(RerataBit * 10000) / 10000;
				double rounded_up1 = ceilf(RerataBit * 10000) / 10000;

				this->rataan->Text = rounded_up1 + "";
				this->progressBar1->Value = 100;
				this->button1->Enabled = true;

				delete[] ArrayFrekuensiTotal;


	}
			void InitializeComponent(void)
			{
				this->sizesemula = 0;
				this->sizesesudah = 0;
				
				this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
				this->rataan = (gcnew System::Windows::Forms::Label());
				this->entropi = (gcnew System::Windows::Forms::Label());
				this->nisbah = (gcnew System::Windows::Forms::Label());
				this->filesetelah = (gcnew System::Windows::Forms::Label());
				this->filesemula = (gcnew System::Windows::Forms::Label());
				this->waktu = (gcnew System::Windows::Forms::Label());
				this->label10 = (gcnew System::Windows::Forms::Label());
				this->label9 = (gcnew System::Windows::Forms::Label());
				this->label8 = (gcnew System::Windows::Forms::Label());
				this->label7 = (gcnew System::Windows::Forms::Label());
				this->label6 = (gcnew System::Windows::Forms::Label());
				this->label5 = (gcnew System::Windows::Forms::Label());
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->SuspendLayout();
				// 
				// progressBar1
				// 
				this->progressBar1->Location = System::Drawing::Point(32, 47);
				this->progressBar1->Name = L"progressBar1";
				this->progressBar1->Size = System::Drawing::Size(480, 23);
				this->progressBar1->TabIndex = 0;
				// 
				// rataan
				// 
				this->rataan->AutoSize = true;
				this->rataan->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->rataan->ForeColor = System::Drawing::Color::White;
				this->rataan->Location = System::Drawing::Point(474, 335);
				this->rataan->Name = L"rataan";
				this->rataan->Size = System::Drawing::Size(21, 24);
				this->rataan->TabIndex = 31;
				this->rataan->Text = L"0";
				// 
				// entropi
				// 
				this->entropi->AutoSize = true;
				this->entropi->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->entropi->ForeColor = System::Drawing::Color::White;
				this->entropi->Location = System::Drawing::Point(474, 293);
				this->entropi->Name = L"entropi";
				this->entropi->Size = System::Drawing::Size(21, 24);
				this->entropi->TabIndex = 30;
				this->entropi->Text = L"0";
				// 
				// nisbah
				// 
				this->nisbah->AutoSize = true;
				this->nisbah->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->nisbah->ForeColor = System::Drawing::Color::White;
				this->nisbah->Location = System::Drawing::Point(474, 251);
				this->nisbah->Name = L"nisbah";
				this->nisbah->Size = System::Drawing::Size(40, 24);
				this->nisbah->TabIndex = 29;
				this->nisbah->Text = L"0 %";
				// 
				// filesetelah
				// 
				this->filesetelah->AutoSize = true;
				this->filesetelah->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->filesetelah->ForeColor = System::Drawing::Color::White;
				this->filesetelah->Location = System::Drawing::Point(474, 202);
				this->filesetelah->Name = L"filesetelah";
				this->filesetelah->Size = System::Drawing::Size(38, 24);
				this->filesetelah->TabIndex = 28;
				this->filesetelah->Text = L"0 B";
				// 
				// filesemula
				// 
				this->filesemula->AutoSize = true;
				this->filesemula->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->filesemula->ForeColor = System::Drawing::Color::White;
				this->filesemula->Location = System::Drawing::Point(474, 156);
				this->filesemula->Name = L"filesemula";
				this->filesemula->Size = System::Drawing::Size(38, 24);
				this->filesemula->TabIndex = 27;
				this->filesemula->Text = L"0 B";
				// 
				// waktu
				// 
				this->waktu->AutoSize = true;
				this->waktu->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->waktu->ForeColor = System::Drawing::Color::White;
				this->waktu->Location = System::Drawing::Point(474, 105);
				this->waktu->Name = L"waktu";
				this->waktu->Size = System::Drawing::Size(35, 24);
				this->waktu->TabIndex = 26;
				this->waktu->Text = L"0 s";
				// 
				// label10
				// 
				this->label10->AutoSize = true;
				this->label10->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label10->ForeColor = System::Drawing::Color::White;
				this->label10->Location = System::Drawing::Point(60, 335);
				this->label10->Name = L"label10";
				this->label10->Size = System::Drawing::Size(207, 24);
				this->label10->TabIndex = 25;
				this->label10->Text = L"Rata-Rata Bit / Simbol";
				// 
				// label9
				// 
				this->label9->AutoSize = true;
				this->label9->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label9->ForeColor = System::Drawing::Color::White;
				this->label9->Location = System::Drawing::Point(62, 293);
				this->label9->Name = L"label9";
				this->label9->Size = System::Drawing::Size(76, 24);
				this->label9->TabIndex = 24;
				this->label9->Text = L"Entropi";
				// 
				// label8
				// 
				this->label8->AutoSize = true;
				this->label8->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label8->ForeColor = System::Drawing::Color::White;
				this->label8->Location = System::Drawing::Point(62, 251);
				this->label8->Name = L"label8";
				this->label8->Size = System::Drawing::Size(189, 24);
				this->label8->TabIndex = 23;
				this->label8->Text = L"Nisbah Pemampatan";
				// 
				// label7
				// 
				this->label7->AutoSize = true;
				this->label7->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label7->ForeColor = System::Drawing::Color::White;
				this->label7->Location = System::Drawing::Point(60, 202);
				this->label7->Name = L"label7";
				this->label7->Size = System::Drawing::Size(312, 24);
				this->label7->TabIndex = 22;
				this->label7->Text = L"Ukuran File Setelah diekstrak";
				// 
				// label6
				// 
				this->label6->AutoSize = true;
				this->label6->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label6->ForeColor = System::Drawing::Color::White;
				this->label6->Location = System::Drawing::Point(60, 156);
				this->label6->Name = L"label6";
				this->label6->Size = System::Drawing::Size(183, 24);
				this->label6->TabIndex = 21;
				this->label6->Text = L"Ukuran File Semula";
				// 
				// label5
				// 
				this->label5->AutoSize = true;
				this->label5->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label5->ForeColor = System::Drawing::Color::White;
				this->label5->Location = System::Drawing::Point(62, 105);
				this->label5->Name = L"label5";
				this->label5->Size = System::Drawing::Size(66, 24);
				this->label5->TabIndex = 20;
				this->label5->Text = L"Waktu";
				// 
				// button1
				// 
				this->button1->BackColor = System::Drawing::Color::White;
				this->button1->Enabled = false;
				this->button1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
					static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->button1->Location = System::Drawing::Point(252, 379);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(97, 39);
				this->button1->TabIndex = 32;
				this->button1->Text = L"Finish";
				this->button1->UseVisualStyleBackColor = false;
				this->button1->Click += gcnew System::EventHandler(this, &Decompression::button1_Click_1);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label1->ForeColor = System::Drawing::Color::White;
				this->label1->Location = System::Drawing::Point(518, 46);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(38, 27);
				this->label1->TabIndex = 33;
				this->label1->Text = L"0%";
				// 
				// Decompression
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
					static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->ClientSize = System::Drawing::Size(591, 430);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->button1);
				this->Controls->Add(this->rataan);
				this->Controls->Add(this->entropi);
				this->Controls->Add(this->nisbah);
				this->Controls->Add(this->filesetelah);
				this->Controls->Add(this->filesemula);
				this->Controls->Add(this->waktu);
				this->Controls->Add(this->label10);
				this->Controls->Add(this->label9);
				this->Controls->Add(this->label8);
				this->Controls->Add(this->label7);
				this->Controls->Add(this->label6);
				this->Controls->Add(this->label5);
				this->Controls->Add(this->progressBar1);
				this->Name = L"Decompression";
				this->Text = L"Decompression";
				this->Load += gcnew System::EventHandler(this, &Decompression::Decompression_Load);
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			//Fungsi untuk melakukan decompress pada satu file dengan
			//membaca kumpulan huffman string dari file hasil kompresi 
			//sambil menelusuri pohon Huffman yang informasinya 
			//didapat melalui header file (header file mengandung
			//informasi mengenai frekuensi setiap karakter ASCII)
			void SingleDecompress(ifstream &inputfile, int brp)
			{
				//Membaca informasi nama file
				string sinput;
				ReadFileName(inputfile, sinput);

				//Membuat file output berdasarkan nama file
				ofstream outputfile(sinput.c_str(), ios::out | ios::binary);

				//Membaca array frekuensi kemunculan setiap karakter ASCII
				unsigned char uc;
				unsigned int ArrayFrekuensi[256];
				char c;
				for (int i = 0; i<256; i++) {
					//Melakukan pembacaan untuk setiap 4 byte dan 
					//menggabungkannya menjadi sebuah unsigned integer (32 bit)
					ArrayFrekuensi[i] = 0;
					for (int d = 3; d>-1; d--)
					{
						inputfile.get(c);
						uc = c;
						ArrayFrekuensi[i] = ArrayFrekuensi[i] + uc*(1 << (8 * d));
					}
				}

				//Membuat Huffman BinTree dari array frekuensi ASCII
				//Tentunya, perlu bantuan PriorQueue dengan 3 level prioritas kembali
				PriorQueue<BinTree> PQ(3);
				BinTree* MainTree;

				for (int i = 0; i<256; ++i)
				{
					if (ArrayFrekuensi[i]>0)
					{
						///Membuat simpul BinTree dan mengisikan informasi 
						//karakter ASCII dan frekuensinya pada simpul
						//Setiap simpul Huffman BinTree akan diantrikan ke PriorQueue
						MainTree = new BinTree;
						(*MainTree).SetFrekuensi(ArrayFrekuensi[i]);
						(*MainTree).SetChar(static_cast<unsigned char>(i));
						PQ.Add(MainTree);
					}
				}


				//Algoritma Greedy

				//Membentuk pohon Huffman dengan bantuan PriorQueue yang sudah terurut
				//berdasarkan frekuensi setiap karakter (256 elemen)
				BinTree* TempTree1;
				BinTree* TempTree2;

				do
				{
					MainTree = PQ.Del();
					if (!PQ.IsEmpty())
					{
						//Ambil simpul dengan frekuensi terkecil pertama dengan cara
						//menghapus elemen pertama dari PriorQueue
						TempTree1 = PQ.Del();
						//Gabungkan kedua simpul tersebut ke simpul baru
						TempTree2 = new BinTree;
						(*TempTree2).SetLeft((*MainTree).GetAkar());
						(*TempTree2).SetRight((*TempTree1).GetAkar());
						(*TempTree2).SetFrekuensi((*MainTree).GetFrekuensi() + (*TempTree1).GetFrekuensi());
						//Antrikan kembali simpul gabungan ke PriorQueue
						PQ.Add(TempTree2);
					}
				}
				//Lakukan hingga semua simpul tergabung dan tersisa satu elemen PriorQueue 
				//Hapus elemen tersebut dan kita dapatkan simpul dari Huffman BinTree
				//yang kita inginkan
				//PriorQueue pun menjadi kosong
				while (!PQ.IsEmpty());

				//Melakukan pembacaan Huffman string dari input/compressed file
				//Untuk setiap pembacaan 1 bit karakter, akan dicek apakah 
				//ada karakter yang cocok dengan Huffman string tersebut dengan 
				//memanggil fungsi HuffChar

				unsigned int TotalKarakter = (*MainTree).GetFrekuensi();
				unsigned char KarFound;
				char chr;
				string HuffSt;
				int counter = 0;
				//progress bar
				int value;
				this->progressBar1->Value = 0;
				int totalkarfixed = TotalKarakter;
				this->sizesesudah += totalkarfixed;
				//Melakukan dekompresi hingga jumlah karakter yang didecompress
				//sesuai dengan jumlah informasi frekuensi pada Akar pohon Huffman
				while (TotalKarakter>0)
				{
					if ((counter >= 0) && (counter<jumlahdicatat)) {
						inputfile.get(chr);
						outputfile.put(chr);

						//Menghitung frekuensi setiap karakter
						KarFound = chr;
						ArrayFrekuensiTotal[KarFound]++;

					}
					else {
						//Huffman string tercatat saat ini
						HuffSt = "";
						do
						{
							//Membaca Huffman string bit per bit 
							//dengan bantuan fungsi ReadBits
							uc = ReadBits(inputfile);
							if (uc == 0) {
								HuffSt = HuffSt + '0';
							}
							else if (uc == 1) {
								HuffSt = HuffSt + '1';
							}
						}
						//Melakukan pencarian karakter pada pohon Huffman 
						//berdasarkan Huffman string saat ini yaitu st 
						while (!(*MainTree).HuffChar(HuffSt, KarFound));
						//Jika HuffChar mengembalikan false, dengan kata lain tidak mencapai
						//daun, maka akan dibaca kembali bit berikutnya dan bit terbaca 
						//akan ditambahkan ke Huffman string st

						//Jika HuffChar mengembalikan true, maka informasi karakter 
						//yang terdapat di daun akan ditulis ke file output
						if ((brp != 1) && (counter == jumlahdicatat)) {
							TotalKarakter++;
						}
						else {
							//Menghitung frekuensi setiap karakter
							ArrayFrekuensiTotal[KarFound]++;

							//Output karakter ke file
							outputfile.put(static_cast<char>(KarFound));							
						}
					}
					//Kurangi jumlah karakter seiring karakter per karakter terdekompresi
					TotalKarakter--;
					counter++;
					value = int(float(100 * counter / totalkarfixed));
					string dummy = IntToString(value);
					String^ dummy2 = msclr::interop::marshal_as<String ^>(dummy);
					this->progressBar1->Value = value;
					this->label1->Text = dummy2;

				}

				//Menutup file output
				outputfile.close();
				string temp, result;
				for (unsigned int i = 0; i < 256; i++) {
					unsigned char KarIterasi = i;
					(*MainTree).HuffString((*MainTree).GetAkar(), KarIterasi, temp, result);
					ArrayPanjangBitTotal[KarIterasi] = result.length();
				}	

				//Mencari Huffman string dari setiap karakter dan menaruhnya pada 
				//sebuah array Huffman String
				//Kemudian, dihitung panjang bit Huffman masing-masing karakter
				int h = 0;
				string HuffmanString[256];
				for (unsigned short k = 0; k<256; k++) {
					HuffmanString[k] = "";
					uc = static_cast<unsigned char>(k);
					(*MainTree).HuffString((*MainTree).GetAkar(), uc, "", HuffmanString[k]);
					ArrayPanjangBitTotal[h] = HuffmanString[k].length();
					h++;
				}
			}


			//Fungsi untuk melakukan decompress pada banyak file yang memanfaatkan
			//fungsi SingleDecompress dan menghasilkan banyak file dari satu file mampat
			//Dari satu file mampat, akan dibaca informasi banyak file yang dicompress,
			//nama-nama file yang dicompress, serta melakukan dekompresi untuk setiap file
			//yang terkandung dalam suatu file mampat
			void Decompress(string input) {
				//Membuka file input (file mampat)
				ifstream inputfile(input.c_str(), ios::in | ios::binary);

				//Membaca string pertama yang menyatakan jumlah
				string sjumlah;
				ReadFileName(inputfile, sjumlah);
				//Melakukan konversi dari string ke integer
				int jumlah = StringToInt(sjumlah);
				//Jumlah file
				JumlahFile = jumlah;

				//Melakukan dekompresi file per file
				for (int i = 1; i <= jumlah; i++) {
					SingleDecompress(inputfile, i);
				}

				//Menutup file input (file mampat)
				inputfile.close();
				long int counter = GetFileSize(input);
				this->sizesemula = counter;
			}

#pragma endregion



	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
	}

private: System::Void Decompression_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
