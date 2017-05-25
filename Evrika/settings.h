#pragma once
#include <fstream>
#include "SaveSettings.pb.h"
#include <windows.h>
#include <sys/stat.h>
#include "mapform.h"
namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Сводка для settings
	/// </summary>
	public ref class settings : public System::Windows::Forms::Form
	{
	public:
		settings(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			sttn_wnd = this;

			comboBox1->Items->Clear();
			for (int i = 0; i < GMap::NET::MapProviders::GMapProviders::List->Count; i++)
				comboBox1->Items->Add(GMap::NET::MapProviders::GMapProviders::List[i]);
			
			InitMySettings();

			folderBrowserDialog1->SelectedPath = mapform::MapPath;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~settings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  SaveSettings;
	protected:
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::Panel^  btClrHi;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  btLvlLow;

	private: System::Windows::Forms::TextBox^  btLvlMid;

	private: System::Windows::Forms::Panel^  btClrLow;
	private: System::Windows::Forms::TextBox^  btLvlHi;


	private: System::Windows::Forms::Panel^  btClrMid;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  sgLvlLow;

	private: System::Windows::Forms::TextBox^  sgLvlMid;

	private: System::Windows::Forms::Panel^  sgClrLow;
	private: System::Windows::Forms::TextBox^  sgLvlHi;


	private: System::Windows::Forms::Panel^  sgClrMid;

	private: System::Windows::Forms::Panel^  sgClrHi;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::ComboBox^  comboBox1;

	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

	private: System::Windows::Forms::Button^  Cancel_bttn;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
	public: ref class MySetting {
	public:
		MySetting() {
			//инициализация переменных
			path = gcnew String("");
			voltCol = gcnew cli::array<Drawing::Color>(3);
			SignlLvlCol = gcnew cli::array<Drawing::Color>(3);
			voltLvl.Add(0);
			voltLvl.Add(0);
			voltLvl.Add(0);
			signlLvl.Add(0);
			signlLvl.Add(0);
			signlLvl.Add(0);

			//попытка загрузки из файла
			ifstream ifs("settings.e", ios::in | ios::binary);
			//если файла нет, то установка по умолчанию
			if (!ifs) {
				set_default();
				return;
			}
			//иначе парсим файлик
			struct stat fi;
			stat("settings.e", &fi);
			int filesize = fi.st_size;

			void *input = malloc(filesize);
			ifs.read((char*)input, filesize);

			SettingPack *set = new SettingPack();
			if (!set->ParseFromArray(input, filesize)) {
				//cerr << "Failed to parse address book." << endl;
				return;
			}

			ProgSettings prg = set->prgstngs(0);//err

			///загрузка цветов и значений
			ProgSettings::BatColor batt = prg.btclr();
			//getting batt color
			voltCol[0] = Drawing::Color::FromArgb(batt.colorlow());
			voltLvl[0] = batt.voltlow();
			voltCol[1] = Drawing::Color::FromArgb(batt.colormid());
			voltLvl[1] = batt.voltmid();
			voltCol[2] = Drawing::Color::FromArgb(batt.colorhigh());
			voltLvl[2] = batt.volthigh();

			ProgSettings::SignalLvlColor sign = prg.sgnllvlclr();
			//getting signl lvl color
			SignlLvlCol[0] = Drawing::Color::FromArgb(sign.colorlow());
			signlLvl[0] = sign.lvllow();
			SignlLvlCol[1] = Drawing::Color::FromArgb(sign.colormid());
			signlLvl[1] = sign.lvlmid();
			SignlLvlCol[2] = Drawing::Color::FromArgb(sign.colorhigh());
			signlLvl[2] = sign.lvlhigh();

			sttn_wnd->btLvlLow->Text = voltLvl[0].ToString();
			sttn_wnd->btLvlMid->Text = voltLvl[1].ToString();
			sttn_wnd->btLvlHi->Text = voltLvl[2].ToString();

			sttn_wnd->btClrLow->BackColor = voltCol[0];
			sttn_wnd->btClrMid->BackColor = voltCol[1];
			sttn_wnd->btClrHi->BackColor = voltCol[2];

			sttn_wnd->sgLvlLow->Text = signlLvl[0].ToString();
			sttn_wnd->sgLvlMid->Text = signlLvl[1].ToString();
			sttn_wnd->sgLvlHi->Text = signlLvl[2].ToString();

			sttn_wnd->sgClrLow->BackColor = SignlLvlCol[0];
			sttn_wnd->sgClrMid->BackColor = SignlLvlCol[1];
			sttn_wnd->sgClrHi->BackColor = SignlLvlCol[2];

			//загрузка пути кэша
			path = gcnew String(prg.mappath().c_str());
			mapform::MapPath = path;
			sttn_wnd->textBox1->Text = path;
			mapform::mymap->CacheLocation = path;
			//mapform::mymap->ReloadMap();
			//загрузка индекса источника карты
			provider = prg.mapprovider();
			mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[provider];
			sttn_wnd->comboBox1->SelectedIndex = provider;

			delete set;
			free(input);
		}
		void SaveToFile() {
			//writting batt color
			Evrika::ProgSettings::BatColor* batclr = new ProgSettings::BatColor();
			batclr->set_colorlow(voltCol[0].ToArgb());
			batclr->set_voltlow(voltLvl[0]);
			batclr->set_colormid(voltCol[1].ToArgb());
			batclr->set_voltmid(voltLvl[1]);
			batclr->set_colorhigh(voltCol[2].ToArgb());
			batclr->set_volthigh(voltLvl[2]);

			//writting singl lvl color
			Evrika::ProgSettings::SignalLvlColor* sgnlclr = new ProgSettings::SignalLvlColor();
			sgnlclr->set_colorlow(SignlLvlCol[0].ToArgb());
			sgnlclr->set_lvllow(signlLvl[0]);
			sgnlclr->set_colormid(SignlLvlCol[1].ToArgb());
			sgnlclr->set_lvlmid(signlLvl[1]);
			sgnlclr->set_colorhigh(SignlLvlCol[2].ToArgb());
			sgnlclr->set_lvlhigh(signlLvl[2]);

			Evrika::SettingPack set;
			ProgSettings *stngs = set.add_prgstngs();
			stngs->set_allocated_sgnllvlclr(sgnlclr);
			stngs->set_allocated_btclr(batclr);
			//write path
			stngs->set_mappath((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path));
			//write map provider
			stngs->set_mapprovider(provider);

			ofstream fs("settings.e", ios::out | ios::trunc | ios::binary);
			//int a = set.GetCachedSize();
			int b = set.ByteSize();
			//int c = sizeof(set);
			void *output = malloc(b);
			if (!set.SerializeToArray(output, b)) {
				//WriteLog("Error loading settings.");
			}
			fs.write((char*)output, b);
			fs.close();

			free(output);
			//delete batclr;
			//delete sgnlclr;
		}
		void setup_batt(Color low, Color mid, Color Hi, double dLow, double dMid, double dHi) {
			voltCol[0] = low;
			voltCol[1] = mid;
			voltCol[2] = Hi;
			voltLvl[0] = dLow;
			voltLvl[1] = dMid;
			voltLvl[2] = dHi;

			sttn_wnd->btLvlLow->Text = voltLvl[0].ToString();
			sttn_wnd->btLvlMid->Text = voltLvl[1].ToString();
			sttn_wnd->btLvlHi->Text = voltLvl[2].ToString();

			sttn_wnd->btClrLow->BackColor = voltCol[0];
			sttn_wnd->btClrMid->BackColor = voltCol[1];
			sttn_wnd->btClrHi->BackColor = voltCol[2];
		}
		void setup_SignlLvl(Color low, Color mid, Color Hi, int dLow, int dMid, int dHi) {
			SignlLvlCol[0] = low;
			SignlLvlCol[1] = mid;
			SignlLvlCol[2] = Hi;
			signlLvl[0] = dLow;
			signlLvl[1] = dMid;
			signlLvl[2] = dHi;

			sttn_wnd->sgLvlLow->Text = signlLvl[0].ToString();
			sttn_wnd->sgLvlMid->Text = signlLvl[1].ToString();
			sttn_wnd->sgLvlHi->Text = signlLvl[2].ToString();

			sttn_wnd->sgClrLow->BackColor = SignlLvlCol[0];
			sttn_wnd->sgClrMid->BackColor = SignlLvlCol[1];
			sttn_wnd->sgClrHi->BackColor = SignlLvlCol[2];
		}
		void set_default() {
			provider = 17;	//GoogleMap
			mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[provider];
			sttn_wnd->comboBox1->SelectedIndex = provider;

			mapform::MapPath = "C:\\EvrikaGMapCache";
			sttn_wnd->textBox1->Text = "C:\\EvrikaGMapCache";
			mapform::mymap->CacheLocation = "C:\\EvrikaGMapCache";
			path = "C:\\EvrikaGMapCache";
			//mapform::mymap->ReloadMap();

			voltCol[0] = System::Drawing::Color::Red;
			voltCol[1] = System::Drawing::Color::Orange;
			voltCol[2] = System::Drawing::Color::LimeGreen;
			voltLvl[0] = 3.0;
			voltLvl[1] = 3.5;
			voltLvl[2] = 4.0;

			SignlLvlCol[0] = System::Drawing::Color::Red;
			SignlLvlCol[1] = System::Drawing::Color::Orange;
			SignlLvlCol[2] = System::Drawing::Color::LimeGreen;
			signlLvl[0] = -90;
			signlLvl[1] = -60;
			signlLvl[2] = -20;

			sttn_wnd->btLvlLow->Text = voltLvl[0].ToString();
			sttn_wnd->btLvlMid->Text = voltLvl[1].ToString();
			sttn_wnd->btLvlHi->Text = voltLvl[2].ToString();

			sttn_wnd->btClrLow->BackColor = voltCol[0];
			sttn_wnd->btClrMid->BackColor = voltCol[1];
			sttn_wnd->btClrHi->BackColor = voltCol[2];

			sttn_wnd->sgLvlLow->Text = signlLvl[0].ToString();
			sttn_wnd->sgLvlMid->Text = signlLvl[1].ToString();
			sttn_wnd->sgLvlHi->Text = signlLvl[2].ToString();

			sttn_wnd->sgClrLow->BackColor = SignlLvlCol[0];
			sttn_wnd->sgClrMid->BackColor = SignlLvlCol[1];
			sttn_wnd->sgClrHi->BackColor = SignlLvlCol[2];
		}
		void ResetForm() {
			sttn_wnd->btLvlLow->Text = voltLvl[0].ToString();
			sttn_wnd->btLvlMid->Text = voltLvl[1].ToString();
			sttn_wnd->btLvlHi->Text = voltLvl[2].ToString();

			sttn_wnd->btClrLow->BackColor = voltCol[0];
			sttn_wnd->btClrMid->BackColor = voltCol[1];
			sttn_wnd->btClrHi->BackColor = voltCol[2];

			sttn_wnd->sgLvlLow->Text = signlLvl[0].ToString();
			sttn_wnd->sgLvlMid->Text = signlLvl[1].ToString();
			sttn_wnd->sgLvlHi->Text = signlLvl[2].ToString();

			sttn_wnd->sgClrLow->BackColor = SignlLvlCol[0];
			sttn_wnd->sgClrMid->BackColor = SignlLvlCol[1];
			sttn_wnd->sgClrHi->BackColor = SignlLvlCol[2];

			mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[provider];
			sttn_wnd->comboBox1->SelectedIndex = provider;

			sttn_wnd->textBox1->Text = mapform::MapPath;
			sttn_wnd->folderBrowserDialog1->SelectedPath = mapform::MapPath;
		}
	public:
		cli::array<Drawing::Color>^ voltCol;
		List<double> voltLvl;
		cli::array<Drawing::Color>^ SignlLvlCol;
		List<int> signlLvl;
		System::String^ path;
		uint32_t provider;
	};
			//function&methods		 
			static MySetting^ GetMySettingP() {
				return mysetting;
			}
			static void InitMySettings() {
				mysetting = gcnew MySetting();
			}
			//variables
	private:
		static settings^ sttn_wnd;
		static MySetting^ mysetting;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SaveSettings = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->btClrHi = (gcnew System::Windows::Forms::Panel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btLvlLow = (gcnew System::Windows::Forms::TextBox());
			this->btLvlMid = (gcnew System::Windows::Forms::TextBox());
			this->btClrLow = (gcnew System::Windows::Forms::Panel());
			this->btLvlHi = (gcnew System::Windows::Forms::TextBox());
			this->btClrMid = (gcnew System::Windows::Forms::Panel());
			this->Cancel_bttn = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->sgLvlLow = (gcnew System::Windows::Forms::TextBox());
			this->sgLvlMid = (gcnew System::Windows::Forms::TextBox());
			this->sgClrLow = (gcnew System::Windows::Forms::Panel());
			this->sgLvlHi = (gcnew System::Windows::Forms::TextBox());
			this->sgClrMid = (gcnew System::Windows::Forms::Panel());
			this->sgClrHi = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// SaveSettings
			// 
			this->SaveSettings->Location = System::Drawing::Point(12, 250);
			this->SaveSettings->Name = L"SaveSettings";
			this->SaveSettings->Size = System::Drawing::Size(75, 23);
			this->SaveSettings->TabIndex = 0;
			this->SaveSettings->Text = L"Сохранить";
			this->SaveSettings->UseVisualStyleBackColor = true;
			this->SaveSettings->Click += gcnew System::EventHandler(this, &settings::SaveSettings_Click);
			// 
			// btClrHi
			// 
			this->btClrHi->BackColor = System::Drawing::Color::LimeGreen;
			this->btClrHi->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btClrHi->Location = System::Drawing::Point(11, 20);
			this->btClrHi->Name = L"btClrHi";
			this->btClrHi->Size = System::Drawing::Size(20, 20);
			this->btClrHi->TabIndex = 1;
			this->btClrHi->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->btLvlLow);
			this->groupBox1->Controls->Add(this->btLvlMid);
			this->groupBox1->Controls->Add(this->btClrLow);
			this->groupBox1->Controls->Add(this->btLvlHi);
			this->groupBox1->Controls->Add(this->btClrMid);
			this->groupBox1->Controls->Add(this->btClrHi);
			this->groupBox1->Location = System::Drawing::Point(6, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(153, 102);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Уровень заряда батареи";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(93, 75);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"В";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(93, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(14, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"В";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(93, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"В";
			// 
			// btLvlLow
			// 
			this->btLvlLow->Location = System::Drawing::Point(37, 72);
			this->btLvlLow->Name = L"btLvlLow";
			this->btLvlLow->Size = System::Drawing::Size(56, 20);
			this->btLvlLow->TabIndex = 4;
			this->btLvlLow->Text = L"3,0";
			this->btLvlLow->TextChanged += gcnew System::EventHandler(this, &settings::textBox3_TextChanged);
			// 
			// btLvlMid
			// 
			this->btLvlMid->Location = System::Drawing::Point(37, 46);
			this->btLvlMid->Name = L"btLvlMid";
			this->btLvlMid->Size = System::Drawing::Size(56, 20);
			this->btLvlMid->TabIndex = 4;
			this->btLvlMid->Text = L"3,5";
			this->btLvlMid->TextChanged += gcnew System::EventHandler(this, &settings::textBox2_TextChanged);
			// 
			// btClrLow
			// 
			this->btClrLow->BackColor = System::Drawing::Color::Red;
			this->btClrLow->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btClrLow->Location = System::Drawing::Point(11, 72);
			this->btClrLow->Name = L"btClrLow";
			this->btClrLow->Size = System::Drawing::Size(20, 20);
			this->btClrLow->TabIndex = 3;
			this->btClrLow->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// btLvlHi
			// 
			this->btLvlHi->Location = System::Drawing::Point(37, 20);
			this->btLvlHi->Name = L"btLvlHi";
			this->btLvlHi->Size = System::Drawing::Size(56, 20);
			this->btLvlHi->TabIndex = 2;
			this->btLvlHi->Text = L"4,0";
			this->btLvlHi->TextChanged += gcnew System::EventHandler(this, &settings::textBox1_TextChanged);
			// 
			// btClrMid
			// 
			this->btClrMid->BackColor = System::Drawing::Color::Orange;
			this->btClrMid->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btClrMid->Location = System::Drawing::Point(11, 46);
			this->btClrMid->Name = L"btClrMid";
			this->btClrMid->Size = System::Drawing::Size(20, 20);
			this->btClrMid->TabIndex = 3;
			this->btClrMid->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// Cancel_bttn
			// 
			this->Cancel_bttn->Location = System::Drawing::Point(262, 250);
			this->Cancel_bttn->Name = L"Cancel_bttn";
			this->Cancel_bttn->Size = System::Drawing::Size(75, 23);
			this->Cancel_bttn->TabIndex = 4;
			this->Cancel_bttn->Text = L"Отмена";
			this->Cancel_bttn->UseVisualStyleBackColor = true;
			this->Cancel_bttn->Click += gcnew System::EventHandler(this, &settings::Cancel_bttn_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->sgLvlLow);
			this->groupBox2->Controls->Add(this->sgLvlMid);
			this->groupBox2->Controls->Add(this->sgClrLow);
			this->groupBox2->Controls->Add(this->sgLvlHi);
			this->groupBox2->Controls->Add(this->sgClrMid);
			this->groupBox2->Controls->Add(this->sgClrHi);
			this->groupBox2->Location = System::Drawing::Point(165, 19);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(153, 102);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Уровень сигнала";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(93, 75);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(20, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"дБ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(93, 49);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(20, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"дБ";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(93, 23);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(20, 13);
			this->label6->TabIndex = 5;
			this->label6->Text = L"дБ";
			// 
			// sgLvlLow
			// 
			this->sgLvlLow->Location = System::Drawing::Point(37, 72);
			this->sgLvlLow->Name = L"sgLvlLow";
			this->sgLvlLow->Size = System::Drawing::Size(56, 20);
			this->sgLvlLow->TabIndex = 4;
			this->sgLvlLow->Text = L"3,0";
			// 
			// sgLvlMid
			// 
			this->sgLvlMid->Location = System::Drawing::Point(37, 46);
			this->sgLvlMid->Name = L"sgLvlMid";
			this->sgLvlMid->Size = System::Drawing::Size(56, 20);
			this->sgLvlMid->TabIndex = 4;
			this->sgLvlMid->Text = L"3,5";
			// 
			// sgClrLow
			// 
			this->sgClrLow->BackColor = System::Drawing::Color::Red;
			this->sgClrLow->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sgClrLow->Location = System::Drawing::Point(11, 72);
			this->sgClrLow->Name = L"sgClrLow";
			this->sgClrLow->Size = System::Drawing::Size(20, 20);
			this->sgClrLow->TabIndex = 3;
			this->sgClrLow->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// sgLvlHi
			// 
			this->sgLvlHi->Location = System::Drawing::Point(37, 20);
			this->sgLvlHi->Name = L"sgLvlHi";
			this->sgLvlHi->Size = System::Drawing::Size(56, 20);
			this->sgLvlHi->TabIndex = 2;
			this->sgLvlHi->Text = L"4,0";
			// 
			// sgClrMid
			// 
			this->sgClrMid->BackColor = System::Drawing::Color::Orange;
			this->sgClrMid->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sgClrMid->Location = System::Drawing::Point(11, 46);
			this->sgClrMid->Name = L"sgClrMid";
			this->sgClrMid->Size = System::Drawing::Size(20, 20);
			this->sgClrMid->TabIndex = 3;
			this->sgClrMid->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// sgClrHi
			// 
			this->sgClrHi->BackColor = System::Drawing::Color::LimeGreen;
			this->sgClrHi->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sgClrHi->Location = System::Drawing::Point(11, 20);
			this->sgClrHi->Name = L"sgClrHi";
			this->sgClrHi->Size = System::Drawing::Size(20, 20);
			this->sgClrHi->TabIndex = 1;
			this->sgClrHi->Click += gcnew System::EventHandler(this, &settings::panel1_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->groupBox2);
			this->groupBox3->Controls->Add(this->groupBox1);
			this->groupBox3->Location = System::Drawing::Point(12, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(325, 127);
			this->groupBox3->TabIndex = 9;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Цвета на вкладке устройств";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->button2);
			this->groupBox4->Controls->Add(this->textBox1);
			this->groupBox4->Location = System::Drawing::Point(12, 145);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(325, 46);
			this->groupBox4->TabIndex = 10;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Местоположение кэша:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(291, 18);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(28, 20);
			this->button2->TabIndex = 1;
			this->button2->Text = L"...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &settings::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(6, 19);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(279, 20);
			this->textBox1->TabIndex = 0;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->comboBox1);
			this->groupBox5->Location = System::Drawing::Point(12, 197);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(325, 47);
			this->groupBox5->TabIndex = 11;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Поставщик карт:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(6, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(313, 21);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &settings::SetMapProvider);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->Description = L"Выберите место хранения кэша";
			this->folderBrowserDialog1->RootFolder = System::Environment::SpecialFolder::MyComputer;
			// 
			// settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(347, 281);
			this->ControlBox = false;
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->Cancel_bttn);
			this->Controls->Add(this->SaveSettings);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"settings";
			this->Text = L"Настройки";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

	}
	private: System::Void panel1_Click(System::Object^  sender, System::EventArgs^  e) {
		colorDialog1->ShowDialog();
		Panel^ temppanel = dynamic_cast<Panel^>(sender);
		temppanel->BackColor = colorDialog1->Color;
	}
	private: System::Void SaveSettings_Click(System::Object^  sender, System::EventArgs^  e) {
		MySetting^ clsttng = GetMySettingP();
		//TODO: memory lock
		clsttng->setup_batt(btClrLow->BackColor, btClrMid->BackColor, btClrHi->BackColor,
			double::Parse(btLvlLow->Text), double::Parse(btLvlMid->Text), double::Parse(btLvlHi->Text));
		clsttng->setup_SignlLvl(sgClrLow->BackColor, sgClrMid->BackColor, sgClrHi->BackColor,
			int::Parse(sgLvlLow->Text), int::Parse(sgLvlMid->Text), int::Parse(sgLvlHi->Text));

		clsttng->provider = comboBox1->SelectedIndex;
		mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[comboBox1->SelectedIndex];

		mapform::MapPath = textBox1->Text;
		mapform::mymap->CacheLocation = mapform::MapPath;
		mysetting->path = mapform::MapPath; //default "C:\\EvrikaGMapCache"
		mapform::mymap->ReloadMap();

		clsttng->SaveToFile();

		this->Hide();
	}
	private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Cancel_bttn_Click(System::Object^  sender, System::EventArgs^  e) {
		mysetting->ResetForm();
		this->Hide();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void SetMapProvider(System::Object^  sender, System::EventArgs^  e) {
		mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[comboBox1->SelectedIndex];
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		folderBrowserDialog1->ShowDialog();
		textBox1->Text = folderBrowserDialog1->SelectedPath;
	}
	};
}
