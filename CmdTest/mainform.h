#pragma once
#include <stdint.h>
#include <iostream>

namespace CmdTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		mainform(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			sEnumCom = gcnew Threading::Semaphore(0,3);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		enum class CMDtype : unsigned char {
			CHECK_COM = 1,
			RESET = 2,
			GETGPS = 3,
			GPSSTAT = 4
		};
		//Конструктор команды на пробуждение меток
		bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t);
		//Конструктор команды запроса параметров конкретной метки
		bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint16_t dummy);
		//Конструктор команд без аргументов
		bool ConstructCMD(System::IO::Ports::SerialPort^, CMDtype);
		//Конструктор команды изменения параметров
		bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint8_t, uint32_t, uint8_t, uint8_t, uint8_t);
		//Конструктор команды запуска цикла измерения задержек
		bool ConstructCMD(System::IO::Ports::SerialPort^, uint32_t, uint8_t);
		//Конструктор команды вкл/выкл GPS
		bool ConstructCMD(System::IO::Ports::SerialPort^, bool);
		//Конструктор команды переключения в режим измерения задержек
		bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, bool enable);

		void CalcSum(cli::array<unsigned char>^, size_t);
		void PasteInBuffer(cli::array<unsigned char>^, size_t, uint32_t);
		void ParseDeviceBuffer(cli::array<wchar_t>^ rbuf);
		void WriteLog(String^ message) {
			textBox1->AppendText("\r\n" + message);
		}
		bool CheckSum(cli::array<wchar_t>^ rbuf);
		String^ IdInHex(int unique_id) {
			char* buf = new char[12];
			std::sprintf(buf,"%X", unique_id);
			String^ str = gcnew String(buf);
			delete[] buf;
			return str;
		}
		int TextToId(String^ str) {
			char *EndPtr;
			char* str2=new char[30];
			int id;
			strcpy(str2, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi("0x" + str));
			sscanf(str2, "%X", &id);
			//int id = strtol(str2, &EndPtr, 0);
			//int id = Convert::ToInt64("0x"+str);
			return id;
		}
		void EnumCOMs();
		bool LastStateIsOpen;
		bool isOurCom;
		bool mode = false;
		Threading::Semaphore^ sEnumCom;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::ComponentModel::IContainer^  components;
			 /// <summary>
			 /// Обязательная переменная конструктора.
			 /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->SuspendLayout();
				 // 
				 // serialPort1
				 // 
				 this->serialPort1->BaudRate = 115200;
				 this->serialPort1->ReadBufferSize = 512;
				 this->serialPort1->ReceivedBytesThreshold = 4;
				 this->serialPort1->WriteBufferSize = 512;
				 this->serialPort1->WriteTimeout = 1000;
				 this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &mainform::serialPort1_DataReceived);
				 // 
				 // textBox1
				 // 
				 this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
				 this->textBox1->Location = System::Drawing::Point(0, 186);
				 this->textBox1->Multiline = true;
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(601, 188);
				 this->textBox1->TabIndex = 0;
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(514, 157);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(75, 23);
				 this->button1->TabIndex = 1;
				 this->button1->Text = L"button1";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
				 // 
				 // comboBox1
				 // 
				 this->comboBox1->FormattingEnabled = true;
				 this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
					 L"Пробуждение", L"Изменение параметров у-ва и метки",
						 L"Перекл. режима изм задержк", L"Цикл изм задержк", L"Изменение парам у-ва", L"Сброс", L"Запрос параметров метки", L"Проверка соед по СОМ",
						 L"Вкл. GPS", L"Выкл. GPS", L"Состояние GPS", L"Данные GPS"
				 });
				 this->comboBox1->Location = System::Drawing::Point(302, 157);
				 this->comboBox1->Name = L"comboBox1";
				 this->comboBox1->Size = System::Drawing::Size(206, 21);
				 this->comboBox1->TabIndex = 2;
				 // 
				 // textBox2
				 // 
				 this->textBox2->Location = System::Drawing::Point(33, 6);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(100, 20);
				 this->textBox2->TabIndex = 3;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(12, 9);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(15, 13);
				 this->label1->TabIndex = 4;
				 this->label1->Text = L"id";
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(15, 157);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(75, 23);
				 this->button2->TabIndex = 6;
				 this->button2->Text = L"button2";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &mainform::button2_Click);
				 // 
				 // comboBox2
				 // 
				 this->comboBox2->FormattingEnabled = true;
				 this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
					 L" 0  dBm", L" 3  dBm", L" 6  dBm", L" 9  dBm",
						 L"12 dBm", L"15 dBm", L"20 dBm", L"27 dBm"
				 });
				 this->comboBox2->Location = System::Drawing::Point(33, 45);
				 this->comboBox2->Name = L"comboBox2";
				 this->comboBox2->Size = System::Drawing::Size(121, 21);
				 this->comboBox2->TabIndex = 7;
				 // 
				 // comboBox3
				 // 
				 this->comboBox3->FormattingEnabled = true;
				 this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
					 L"GFSK_BR4800", L"FSK_BR4800", L"GFSK_BR10K", L"FSK_BR10K",
						 L"GFSK_BR100K", L"FSK_BR100K", L"GFSK_BR250K", L"FSK_BR250K", L"MSK_BR500K"
				 });
				 this->comboBox3->Location = System::Drawing::Point(33, 72);
				 this->comboBox3->Name = L"comboBox3";
				 this->comboBox3->Size = System::Drawing::Size(121, 21);
				 this->comboBox3->TabIndex = 8;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(10, 48);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(17, 13);
				 this->label2->TabIndex = 9;
				 this->label2->Text = L"P:";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(3, 75);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(24, 13);
				 this->label3->TabIndex = 10;
				 this->label3->Text = L"bw:";
				 // 
				 // mainform
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(601, 374);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->comboBox3);
				 this->Controls->Add(this->comboBox2);
				 this->Controls->Add(this->button2);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->textBox2);
				 this->Controls->Add(this->comboBox1);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->textBox1);
				 this->Name = L"mainform";
				 this->Text = L"mainform";
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
};
}
