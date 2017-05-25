#include <fstream>
#include <windows.h>
#include <sys/stat.h>
#include "mapform.h"
#include "SaveSettings.pb.h"
#include "settings.h"

using namespace System::Drawing;

Evrika::settings::settings(void)
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

System::Void Evrika::settings::panel1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	colorDialog1->ShowDialog();
	Panel^ temppanel = dynamic_cast<Panel^>(sender);
	temppanel->BackColor = colorDialog1->Color;
}

System::Void Evrika::settings::SaveSettings_Click(System::Object ^ sender, System::EventArgs ^ e)
{
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

System::Void Evrika::settings::Cancel_bttn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	mysetting->ResetForm();
	this->Hide();
}

System::Void Evrika::settings::SetMapProvider(System::Object ^ sender, System::EventArgs ^ e)
{
	mapform::mymap->MapProvider = GMap::NET::MapProviders::GMapProviders::List[comboBox1->SelectedIndex];
}

System::Void Evrika::settings::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	folderBrowserDialog1->ShowDialog();
	textBox1->Text = folderBrowserDialog1->SelectedPath;
}

Evrika::settings::MySetting::MySetting()
{
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

void Evrika::settings::MySetting::SaveToFile()
{
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

void Evrika::settings::MySetting::setup_batt(Color low, Color mid, Color Hi, double dLow, double dMid, double dHi)
{
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

void Evrika::settings::MySetting::setup_SignlLvl(Color low, Color mid, Color Hi, int dLow, int dMid, int dHi)
{
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

void Evrika::settings::MySetting::set_default()
{
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

void Evrika::settings::MySetting::ResetForm()
{
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
