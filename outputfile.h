#pragma once
//#include "huffman.h"
#include "Compression.h"
#include <cstring>
#include <string>
#include <cstddef>
#include <msclr\marshal_cppstd.h>	
namespace MINZIP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for outputfile
	/// </summary>
	public ref class outputfile : public System::Windows::Forms::Form
	{
	public:
		outputfile(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		array<String^> ^ input;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~outputfile()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(29, 44);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(202, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Untitled";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(229, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 18);
			this->label1->TabIndex = 1;
			this->label1->Text = L".minzip";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(25, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(234, 22);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Masukkan Nama File Keluaran";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(110, 76);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(85, 24);
			this->button1->TabIndex = 3;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &outputfile::button1_Click);
			// 
			// outputfile
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->ClientSize = System::Drawing::Size(308, 119);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"outputfile";
			this->Text = L"Output Name";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	
	
	public: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				
				//this->output = this->textBox1->Text;
				String ^ putoutput = this->textBox1->Text;
				string masukan[MaxFile + 1];/*
				for (int i = 0; i < input->Length; i++)
				{
					String ^ putinput = input[i];
					string put = msclr::interop::marshal_as<string>(putinput);
					string auk;
					String^ kua;
					
					kua = input[i];
					auk = msclr::interop::marshal_as<string>(kua);

					size_t found = auk.find_last_of("/\\");
					string uak = auk.substr(found + 1);
					int panjang = uak.length();
					string spanjang = IntToString(panjang);
					String^ dummy = msclr::interop::marshal_as<String^>(spanjang);
					MessageBox::Show(dummy);
					//string uak = auk.substr(auk.find_last_of('\\') + 1);
					masukan[i] = uak;
				}
				for (int i = input->Length; i >= 1; i--)
				{
					masukan[i] = masukan[i - 1];

				}	*/
				
				Compression ^ comp = gcnew Compression();
				comp->input = this->input;
				comp->output = putoutput;
				comp->Show();
				comp->Start();
				
				//Compress(input->Length, masukan, out);
				//encoder(put,out , false);
				//Compress()
				this->Close();
	}

};
}
