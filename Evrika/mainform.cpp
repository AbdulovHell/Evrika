//#define _CRT_SECURE_NO_WARNINGS

#include "EventLog.pb.h"
#include <fstream>
#include "templates.h"
#include "settings.h"
#include "loading_page.h"
#include "device_prop.h"
#include "mapform.h"
#include <Windows.h>
#include <Psapi.h>
#include "mainform.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace Evrika;

ref class Worker {
	static loading_page^ ldwnd;
	static Thread^ loadthrd;

public:
	Worker() {
	}

	static void Work() {
		loadthrd = gcnew Thread(gcnew ThreadStart(showload));
		loadthrd->IsBackground = true;
		loadthrd->Start();

		mainform^ mainwnd = gcnew mainform();
		Application::Run(mainwnd);
	}
	static void showload() {
		ldwnd = gcnew loading_page();
		Application::Run(ldwnd);
	}

};

[STAThreadAttribute]
void Main(cli::array<String^>^ args) {
	//Kill other "Evrika.exe"
	{
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
			MessageBoxA(0, "EnumProcesses", "err", 0);
		}
		cProcesses = cbNeeded / sizeof(DWORD);
		DWORD myPID = GetCurrentProcessId();
		for (DWORD i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) {
				wchar_t szProcessName[MAX_PATH] = TEXT("<unknown>");
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
				if (hProcess != NULL) {
					HMODULE hMod;
					DWORD cbNeedeb2;
					if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeedeb2)) {
						GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
						String^ str = gcnew String(szProcessName);
						if (str == "Evrika.exe") {
							if (aProcesses[i] == myPID) {
								;
							}
							else {
								if (!TerminateProcess(hProcess, 0)) {
									MessageBoxA(0, "TerminateProcess", "err", 0);
								}
							}
						}
					}
				}
				CloseHandle(hProcess);
			}
		}
	}
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	try {
		Worker^ w = gcnew Worker();
		w->Work();
	}
	catch (Exception ^e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
	}
}

Evrika::mainform::mainform(void)
{
	//создание окна загрузки
	//Thread^ oThread = gcnew Thread(gcnew ThreadStart(&ThreadExample::ThreadProc));
	/*ThreadStart^ threadDelegate = gcnew ThreadStart(w, &Work::DoMoreWork);
	Thread^ newThread = gcnew Thread(threadDelegate);*/
	//ldng_wnd = gcnew Evrika::loading_page();
	//ThreadStart^ threadDelegate = gcnew ThreadStart(&loading_page::dummy);
	//Thread^ thrd = gcnew Thread(threadDelegate);
	//thrd->Start();
	//ldng_wnd = gcnew Evrika::loading_page();
	//ldng_wnd->Show();
	Label^ lbl;
	do {
		lbl = Evrika::loading_page::getLabel();
	} while (!lbl);

	ProgressBar^ pbar;
	do {
		pbar = Evrika::loading_page::getPBar();
	} while (!pbar);

	Semaphore^ mut = loading_page::getMutex();
	mut->WaitOne();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), " Старт.");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 1);

	//notLoaded = true;
	InitializeComponent();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Запуск окна карты...");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 2);

	mapform = gcnew Evrika::mapform();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Загрузка карты...");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 3);

	map = mapform->getMapPointer();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Инициализация настроек...");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 4);

	settings_window = gcnew Evrika::settings();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Подготовка программы...");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 5);

	lCoordsCount = 0;
	MyCoords = gcnew List< geoPoint^ >(20);
	Devices = gcnew List<Device^>(20);
	Events = gcnew List<Event^>(50);
	logs = gcnew List<TextBox^>;
	logs->Add(proglog);
	//cDevices = 0;
	markers = gcnew cli::array< GMarkerGoogle^ >(50);
	sEnumCom = gcnew Semaphore(0, 3);
	sPointReciver = gcnew Semaphore(0, 3);
	listBox1->Items->Clear();
	mrkrOvrl = mapform->mrkrOvrl;
	areaOvrl = mapform->areaOvrl;
	myPosOvrl = mapform->myPosOvrl;
	ourPort = gcnew String("");
	eGPS = false;
	myPos = gcnew MyPosition();
	this->Width = 512;
	this->Height = 570;

	//proglog->Clear();

	//lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Перечисление COM...");
	//pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 6);

	//EnumCOMs();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Запуск карты...");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 7);

	mapform->Show();

	lbl->Invoke(gcnew Action<String^>(&loading_page::change_lbl), "Готово.");
	pbar->Invoke(gcnew Action<int>(&loading_page::change_bar), 8);

	//разблок
	//ldng_wnd->Hide();
	//Semaphore^ mut=loading_page::getMutex();
	//mut->Release();

	loading_page^ p = loading_page::getHandle();
	p->Invoke(gcnew Action(&loading_page::Suicide));

	//this->BringToFront();
	//BringWindowToTop();	//TODO: почему на заднем фоне?!
	SetWindowPos((HWND)this->Handle.ToInt32(), HWND_TOP, NULL, NULL, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE);
}

void Evrika::mainform::CheckComConn()
{
	try {
		isOurCom = false;
		ConstructCMD(serialPort1, CMDtype::CHECK_COM);
		sEnumCom->WaitOne(10000);
		if (isOurCom) {
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "Есть соединение");
			LastStateIsOpen = true;
		}
		else {
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "Подключение отсутствует");
			if (serialPort1->IsOpen)
				serialPort1->Close();
			LastStateIsOpen = false;
		}

	}
	catch (...) {

	}
}

void Evrika::mainform::EnumCOMs()
{
	this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "Поиск последовательного порта...");
	cli::array<String^>^ coms = IO::Ports::SerialPort::GetPortNames();
	size_t coms_count = coms->GetLength(0);
	try {
		if (serialPort1->IsOpen)
			serialPort1->Close();
		if (coms_count > 0) {
			for (int i = 0; i < coms_count; i++) {
				if (serialPort1->IsOpen)
					serialPort1->Close();
				serialPort1->PortName = coms[i];
				try {
					serialPort1->Open();
					if (serialPort1->IsOpen) {
						isOurCom = false;
						ConstructCMD(serialPort1, CMDtype::CHECK_COM);
						sEnumCom->WaitOne(10000);	//TODO: настроить
						if (isOurCom) {
							this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), serialPort1->PortName);
							this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ найден по " + whatCOM->Text);
							LastStateIsOpen = true;
							return;
						}
					}
				}
				catch (Exception^ e) {
					this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), e->Message);
				}
				Sleep(100);
			}
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ не найден.");
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), "COM?");
			LastStateIsOpen = false;
		}
		else {
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ не найден.");
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), "COM?");
			LastStateIsOpen = false;
		}
	}
	catch (Exception^ e) {
		this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), e->Message);
	}
	if (serialPort1->IsOpen)
		serialPort1->Close();
	LastStateIsOpen = false;
}

bool Evrika::mainform::CheckSum(cli::array<wchar_t>^ rbuf)
{
	if (!((rbuf[0] == 0x65) && (rbuf[1] == 0x76))) return false;	//базовая проверка

	int len = (rbuf[4] << 8) + rbuf[5];

	uint8_t mCK_A = (uint8_t)rbuf[5 + len + 1], mCK_B = (uint8_t)rbuf[5 + len + 2];
	uint8_t cCK_A = 0, cCK_B = 0;
	for (int i = 2; i < (5 + len + 1); i++) {
		cCK_A += (uint8_t)rbuf[i];
		cCK_B += cCK_A;
	}
	if ((cCK_A == mCK_A) && (cCK_B == mCK_B)) return true;
	return false;
}

void Evrika::mainform::update_device_list()
{
	dataGridView1->Rows->Clear();
	for (int i = 0; i < Devices->Count; i++) {
		dataGridView1->Rows->Add(1);
		if (Devices[i]->missing_counter == 0)
			dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex();	//id
		else
			dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex() + " (!)";	//id
		dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[1]->Value = Devices[i]->signal_lvl;	//sgnl lvl
		dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[2]->Value = Devices[i]->signal_quality;	//quality
		dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[3]->Value = Devices[i]->battery_lvl;	//batt lvl
		dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[4]->Value = Devices[i]->work_mode;	//mode
	}

	for (int i = 0; i < dataGridView1->RowCount; i++) {
		double tempval = 0;
		int templvl = 100;
		//try {
		tempval = double(dataGridView1->Rows[i]->Cells[3]->Value);
		//}
		//catch (...) {}
		if (tempval) {
			if (tempval < Evrika::settings::GetMySettingP()->voltLvl[0]) {
				dataGridView1->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[0];
			}
			else if (tempval < Evrika::settings::GetMySettingP()->voltLvl[1]) {
				dataGridView1->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[1];
			}
			else {
				dataGridView1->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[2];
			}
		}

		//try {
		templvl = (int)(dataGridView1->Rows[i]->Cells[1]->Value);
		//}
		//catch (...) {}
		if (templvl < 100) {
			if (templvl < Evrika::settings::GetMySettingP()->signlLvl[0]) {
				dataGridView1->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[0];
			}
			else if (templvl < Evrika::settings::GetMySettingP()->signlLvl[1]) {
				dataGridView1->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[1];
			}
			else {
				dataGridView1->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[2];
			}
		}
	}
}

void Evrika::mainform::update_event_list()
{
	dataGridView2->Rows->Clear();
	for (int i = 0; i < Events->Count; i++) {
		dataGridView2->Rows->Add(1);

		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[0]->Value = Events[i]->device->IdInHex();	//id
		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[1]->Value = Events[i]->device->signal_lvl;	//sgnl lvl
		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[2]->Value = Events[i]->device->battery_lvl;	//batt lvl
		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[3]->Value = Events[i]->device->work_mode;	//mode
		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[4]->Value = Events[i]->sEvent;	//event type
		dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[5]->Value = Events[i]->td->ToSysString();	//dt
	}
}

void Evrika::mainform::ParseDeviceBuffer(cli::array<wchar_t>^ rbuf)
{
	//проверка синхробайтов и контрольной суммы, в случае ошибки выдаем в лог и не обрабатываем
	if (!CheckSum(rbuf)) {
		WriteLog("Какая-то дичь... : " + gcnew String(rbuf));
		return;
	}
	//проверка пройдена, обработка
	switch (rbuf[2]) {	//message class
	case 0x0A:
		switch (rbuf[3]) {	//message ID
		case 0x00:	//ответ на любую введеную команду
			if ((rbuf[6] == 0x4F) && (rbuf[7] == 0x4B)) WriteLog("Ок");	//OK
			else if ((rbuf[6] == 0x45) && (rbuf[7] == 0x52)) WriteLog("Ошибка");	//ER
			else WriteLog("ParseBuffer error: Unknown response code");
			break;
		case 0x01:	//для проверки COM порта
			isOurCom = true;
			sEnumCom->Release();
			break;
		case 0x02:
			WriteLog("Параметры СС1101 сброшены");
			break;
		case 0x03:
			WriteLog("Параметры СС1101 изменены");
			break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0A");
			break;
		}
		break;
	case 0x0B:
		switch (rbuf[3]) {
		case 0x01:
			if (eGPS)
				WriteLog("GPS включен");
			else
				WriteLog("GPS выключен");
			break;
		case 0x02:
		{
			int len = (rbuf[4] << 8) + rbuf[5];	//28
			uint8_t hh = (uint8_t)rbuf[6];	//1
			uint8_t mm = (uint8_t)rbuf[7];	//2
			uint8_t ss = (uint8_t)rbuf[8];	//3
			int8_t lat_p = (int8_t)rbuf[9];	//4
			uint8_t lat_dd = (uint8_t)rbuf[10];	//5
			uint8_t lat_mm = (uint8_t)rbuf[11];	//6
			double lat_ss = GetFloatFromBuf(rbuf, 12);	//10
			int8_t lng_p = (int8_t)rbuf[17];	//11
			uint8_t lng_dd = (uint8_t)rbuf[18];	//12
			uint8_t lng_mm = (uint8_t)rbuf[19];	//13
			double lng_ss = GetFloatFromBuf(rbuf, 20);	//17
			uint8_t satellites = (uint8_t)rbuf[25];	//18
			double HDOP = GetFloatFromBuf(rbuf, 26);	//22
			double height = GetFloatFromBuf(rbuf, 30);	//26

			double lat = lat_dd + (lat_mm + lat_ss) / 60.0,
				lng = lng_dd + (lng_mm + lng_ss) / 60.0;

			if (myPos->bFirstRead) {
				myPos->bFirstRead = false;
				myPos->SetState(lat, lng, HDOP, height);
			}
			myPos->Correct(lat, lng, HDOP, height);
			//test
			/*{
			GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::red_small);
			mrkrOvrl->Markers->Add(marker);

			GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Red));
			circ->Stroke = gcnew Pen(Color::Red, 1);
			areaOvrl->Polygons->Add(circ);
			}*/
			myPos->GetState(&lat, &lng, &HDOP, &height);
			toolStripStatusLabel3->Text = "Sat: " + satellites;
			toolStripStatusLabel3->Visible = true;
			toolStripStatusLabel4->Text = "HDOP: " + (float)HDOP;
			toolStripStatusLabel4->Visible = true;
			toolStripStatusLabel5->Text = "H: " + (float)height + " m";
			toolStripStatusLabel5->Visible = true;
			/*myPosOvrl->Clear();
			myPosOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::blue_small));
			GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Blue));
			circ->Stroke = gcnew Pen(Color::Blue, 1);
			myPosOvrl->Polygons->Add(circ);*/
			my_pos_accepted = true;
			//sPointReciver->Release();
		}
		break;
		case 0x03:
		{
			GPS_KnownPos = rbuf[6];
		}
		break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0B");
			break;
		}
		break;
	case 0x0C:
		switch (rbuf[3]) {	//message ID
		case 0x01:	//список устройств
		{
			int len = (rbuf[4] << 8) + rbuf[5];
			int devices = (len - 0) / 8;	//количество устройств в буфере
			List<Device^>^ tempdev = gcnew List<Device^>;
			//парсинг буфера в список у-в
			for (int i = 0; i < devices; i++) {	//массив у-в в список у-в
				int addr = rbuf[6 + 8 * i] + (rbuf[7 + 8 * i] << 8) + (rbuf[8 + 8 * i] << 16) + (rbuf[9 + 8 * i] << 24);
				int raw_v = rbuf[12 + 8 * i];
				double volt = raw_v >> 4;
				volt += ((double)(raw_v & 0xF)) / 10.0;
				tempdev->Add(gcnew Device(addr, (char)rbuf[10 + 8 * i], rbuf[11 + 8 * i], volt, rbuf[13 + 8 * i], NULL));
			}
			//сброс флагов обработки у-в, уже наход в памяти
			for (int i = 0; i < Devices->Count; i++) Devices[i]->Processed = false;
			//сравнение и обновление у-в, которые уже были в памяти
			for (int i = 0; i < Devices->Count; i++) {
				for (int j = 0; j < tempdev->Count; j++) {
					if (Devices[i]->unique_id == tempdev[j]->unique_id) {
						Devices[i]->copy(tempdev[j]);
						Devices[i]->Processed = true;
						Devices[i]->missing_counter = 0;
						tempdev->RemoveAt(j);
					}
				}
			}
			//обработка "устаревших" у-в
			for (int i = 0; i < Devices->Count; i++) {
				if (Devices[i]->Processed == false) {
					if (Devices[i]->missing_counter > 3) {
						//generate_event_disconnect
						Events->Add(gcnew Event(Devices[i], Event::EventCode::DEV_DISCONNECTED));
						update_event_list();
						Devices->RemoveAt(i);
					}
					else
						Devices[i]->missing_counter++;
				}
			}
			//обработка "новых" у-в
			for (int i = 0; i < tempdev->Count; i++) {
				//generate_newdev_event
				Events->Add(gcnew Event(tempdev[i], Event::EventCode::DEV_CONNECTED));
				update_event_list();
				Devices->Add(tempdev[i]);
				tempdev->RemoveAt(i);
			}
			if (Devices->Count > 0)
				this->device_get = true;
			else
				device_get = false;
			//обновление списка у-в
			update_device_list();
		}
		break;
		case 0x02:	//резутат измерения времени
		{
			//invoke в device_prop
			int size = (rbuf[4] << 8) + rbuf[5];
			int count = size / 5;
			List<int>^ sign_lvls = gcnew List<int>;
			List<int64_t>^ cycles = gcnew List<int64_t>;
			//unsigned int min = -1;
			for (int i = 0; i < count; i++) {
				sign_lvls->Add((char)(rbuf[6 + 5 * i]));
				cycles->Add(rbuf[7 + 5 * i] + (rbuf[8 + 5 * i] << 8) + (rbuf[9 + 5 * i] << 16) + (rbuf[10 + 5 * i] << 24));
				//if (cycles[i] < min) min = cycles[i];
			}
			if (cycles->Count == 0) return;
			try {
				device_prop::hDevice_prop->Invoke(gcnew Action< List<int64_t>^ >(device_prop::hDevice_prop, &device_prop::ProceedPoints), cycles);
				double mid = 0;
				for (int i = 0; i < sign_lvls->Count; i++)
					mid += sign_lvls[i];
				mid /= sign_lvls->Count;
				double powers[] = { 0,3,6,9,12,15,20,27 };
				float temp = (float)(SignalLvlToMeters(mid, powers[device_prop::PowerIndex->SelectedIndex])*double::Parse(device_prop::kTextBox->Text));
				float temp2 = (float)(ConvertToMeters(mid, double::Parse(n_text->Text), double::Parse(A_text->Text)));
				device_prop::SignLvlDistLabel->Text = "v1: " + temp.ToString() + " m; v2: " + temp2.ToString() + " m.";
			}
			catch (...) {

			}
		}
		break;
		case 0x03:
		{
			if (rbuf[6]) {
				WriteLog("Параметры изменены");
			}
			else {
				WriteLog("Ошибка при изменении параметров");
			}
		}
		break;
		case 0x04:
		{
			WriteLog("Режим измерения задержки");
		}
		break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0C");
			break;
		}
		break;
	default:
		WriteLog("ParseBuffer error: Unknown message class");
		break;
	}
}

System::Void Evrika::mainform::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (mapform->Visible)
		mapform->Hide();
	else mapform->Show();
}

System::Void Evrika::mainform::savemap_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	TimeAndDate dt;
	dt.GetCurrentTimeAndDate();
	String^ datatime = dt.ToSysString();
	saveFileDialog1->FileName = "Evrika_map_screenshot_" + datatime;
	saveFileDialog1->ShowDialog();
	Drawing::Bitmap^ btmp = gcnew Drawing::Bitmap(map->ClientRectangle.Width, map->ClientRectangle.Height);
	map->DrawToBitmap(btmp, map->ClientRectangle);
	try {
		btmp->Save(saveFileDialog1->FileName);
	}
	catch (...) {
		;
	}

	//EvLog::EventLog a;
	//a.add_events();
}

System::Void Evrika::mainform::настройкиToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	settings_window->Show();
}

System::Void Evrika::mainform::button8_Click_1(System::Object ^ sender, System::EventArgs ^ e)
{
	for (int i = 0; i < dataGridView1->RowCount; i++) {
		double tempval = 0;
		int templvl = 100;
		//try {
		tempval = double(dataGridView1->Rows[i]->Cells[4]->Value);
		//}
		//catch (...) {}
		if (tempval) {
			if (tempval < Evrika::settings::GetMySettingP()->voltLvl[0]) {
				dataGridView1->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[0];
			}
			else if (tempval < Evrika::settings::GetMySettingP()->voltLvl[1]) {
				dataGridView1->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[1];
			}
			else {
				dataGridView1->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[2];
			}
		}

		//try {
		templvl = (int)(dataGridView1->Rows[i]->Cells[2]->Value);
		//}
		//catch (...) {}
		if (templvl < 100) {
			if (templvl < Evrika::settings::GetMySettingP()->signlLvl[0]) {
				dataGridView1->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[0];
			}
			else if (templvl < Evrika::settings::GetMySettingP()->signlLvl[1]) {
				dataGridView1->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[1];
			}
			else {
				dataGridView1->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[2];
			}
		}
	}
}

System::Void Evrika::mainform::open_device(System::Object ^ sender, System::Windows::Forms::DataGridViewCellEventArgs ^ e)
{
	int row = e->RowIndex;
	if ((row < 0) || (Devices->Count == 0) || (row > Devices->Count - 1)) return;

	//ConstructCMD(serialPort1, Devices[row]->unique_id, true);
	device_prop^ prop = gcnew device_prop(Devices[row], serialPort1);
	prop->Show();
	logs->Add(prop->my_log);
}

System::Void Evrika::mainform::save_events(System::Object ^ sender, System::EventArgs ^ e)
{
	TimeAndDate dt;
	dt.GetCurrentTimeAndDate();
	String^ datatime = dt.ToSysString();
	saveFileDialog2->FileName = "Evrika_session_" + datatime;
	saveFileDialog2->ShowDialog();

	EvLog::EventLog eLog;
	for (int i = 0; i < Events->Count; i++) {
		EvLog::Event* tempevent = eLog.add_events();

		EvLog::Device* dev = new EvLog::Device();

		dev->set_battery_lvl(Events[i]->device->battery_lvl);
		dev->set_signal_lvl(Events[i]->device->signal_lvl);
		dev->set_signal_quality(Events[i]->device->signal_quality);
		dev->set_unique_id(Events[i]->device->unique_id);
		dev->set_work_mode(Events[i]->device->work_mode);

		dev->set_allocated_pmode1(new EvLog::Device_mode1());
		dev->set_allocated_pmode2(new EvLog::Device_mode2());
		dev->set_allocated_pmode3(new EvLog::Device_mode3());
		dev->set_allocated_pmode4(new EvLog::Device_mode4());

		tempevent->set_allocated_dev(dev);

		EvLog::TD* td = new EvLog::TD();

		td->set_day(Events[i]->td->day);
		td->set_month(Events[i]->td->month);
		td->set_year(Events[i]->td->year);
		td->set_hour(Events[i]->td->hours);
		td->set_minute(Events[i]->td->minutes);
		td->set_second(Events[i]->td->seconds);

		tempevent->set_allocated_td(td);

		tempevent->set_ecode((UINT32)Events[i]->eCode);

		//delete dev;
		//delete td;
	}
	ofstream fs((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(saveFileDialog2->FileName), ios::out | ios::trunc | ios::binary);
	int b = eLog.ByteSize();
	void *output = malloc(b);
	if (!eLog.SerializeToArray(output, b)) {
		//WriteLog("Error loading settings.");
	}
	fs.write((char*)output, b);
	fs.close();
	delete output;
	//saveFileDialog2->FileName; путь
}

System::Void Evrika::mainform::load_session(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog1->ShowDialog();

	ifstream ifs((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName), ios::in | ios::binary);

	struct stat fi;
	stat((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName), &fi);
	int filesize = fi.st_size;

	void *input = malloc(filesize);
	ifs.read((char*)input, filesize);

	EvLog::EventLog *eLog = new EvLog::EventLog();
	if (!eLog->ParseFromArray(input, filesize)) {
		//cerr << "Failed to parse address book." << endl;
		return;
	}

	Events->Clear();
	for (int i = 0; i < eLog->events_size(); i++) {
		EvLog::Event tempevent = eLog->events(i);

		EvLog::Device dev = tempevent.dev();
		Event::EventCode eCode = (Event::EventCode)tempevent.ecode();
		EvLog::TD td = tempevent.td();

		Events->Add(gcnew Event(gcnew Device(dev.unique_id(), dev.signal_lvl(), dev.signal_quality(), dev.battery_lvl(), dev.work_mode(), NULL),
			gcnew TimeAndDate(td.day(), td.month(), td.year(), td.hour(), td.minute(), td.second()), eCode));
	}
	update_event_list();
}

System::Void Evrika::mainform::button11_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!eGPS) return;
	try {
		if (!serialPort1->IsOpen)
			serialPort1->Open();
		ConstructCMD(serialPort1, CMDtype::GETGPS);
	}
	catch (IO::IOException ^ioexception) {
		proglog->AppendText("\r\n" + ioexception->Message);
	}
}

System::Void Evrika::mainform::checkBox3_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (!serialPort1->IsOpen)
			serialPort1->Open();
		eGPS = GPS_En->Checked;
		myPos->bFirstRead = true;
		ConstructCMD(serialPort1, eGPS);
	}
	catch (IO::IOException ^ioexception) {
		proglog->AppendText("\r\n" + ioexception->Message);
	}
}

System::Void Evrika::mainform::sys_task_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	//T=0.2c
	if (sys_task_counter & 0x01) {
		//Обновление состояния порта
		if (serialPort1->IsOpen && LastStateIsOpen) {
			System::ComponentModel::ComponentResourceManager^ resource = (gcnew System::ComponentModel::ComponentResourceManager(loading_page::typeid));
			ImageIndication->Image = (safe_cast<System::Drawing::Image^>(resource->GetObject("green_icon")));
			LastStateIsOpen = false;
		}
		else if (!serialPort1->IsOpen && !LastStateIsOpen) {
			System::ComponentModel::ComponentResourceManager^ resource = (gcnew System::ComponentModel::ComponentResourceManager(loading_page::typeid));
			ImageIndication->Image = (safe_cast<System::Drawing::Image^>(resource->GetObject("4IAzyrhy9rkis")));
			LastStateIsOpen = true;
			whatCOM->Text = "COM?";
		}
	}
	//T=5c
	if (sys_task_counter % 50 == 0) {

		if (GPS_KnownPos) {
			//my_pos_accepted = false;
			try {
				if (serialPort1->IsOpen)
					ConstructCMD(serialPort1, CMDtype::GETGPS);
			}
			catch (IO::IOException ^ioexception) {
				proglog->AppendText("\r\n" + ioexception->Message + " in sys_task_Tick gpsknownpos.");
			}
			//sPointReciver->WaitOne(1000);
		}
		if (Get_Dev->Checked) {
			get_device_progress->Value = 0;
			try {
				if (serialPort1->IsOpen)
					ConstructCMD(serialPort1, (uint32_t)3000);
			}
			catch (IO::IOException ^ioexception) {
				proglog->AppendText("\r\n" + ioexception->Message);
			}
			//sPointReciver->WaitOne(4000);
		}
		if (/*my_pos_accepted&&device_get*/false) {
			double lat = 0, lng = 0, r_m = 0;
			myPos->GetPos(&lat, &lng);
			int RSSI = Devices[0]->signal_lvl;
			double powers[] = { 0,3,6,9,12,15,20,27 };
			//r_m = ConvertToMeters(RSSI, double::Parse(n_text->Text), double::Parse(A_text->Text));
			r_m = SignalLvlToMeters(RSSI, powers[3])*1.4;
			label10->Text = r_m.ToString();
			MyCoords->Add(gcnew geoPoint(lat, lng, r_m));
			if (MyCoords->Count > 8)
				MyCoords->RemoveAt(0);
			groupBox1->Text = "Точек сохранено: " + MyCoords->Count.ToString(); //обновление при получении точк
			if (MyCoords->Count > 3) {
				areaOvrl->Clear();
				mrkrOvrl->Clear();
				//metod_5();
				for (int i = 0; i < MyCoords->Count; i++) {
					GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(MyCoords[i]->get_pointLatLng(), Markers::GMarkerGoogleType::blue_small);
					mrkrOvrl->Markers->Add(marker);

					GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::SortPoints_distance(MyCoords[i]->CreateCircle()), "circ");
					circ->Fill = gcnew SolidBrush(Color::FromArgb(10, Color::Blue));
					circ->Stroke = gcnew Pen(Color::Blue, 1);
					areaOvrl->Polygons->Add(circ);
				}
			}
		}
	}
	//T=1c
	else if (sys_task_counter % 10 == 0) {
		if (this->Get_Dev->Checked) get_device_progress->Value++;
		if (GPS_En->Checked) {
			try {
				if (serialPort1->IsOpen) {
					ConstructCMD(serialPort1, CMDtype::GPSSTAT);
				}
			}
			catch (IO::IOException ^ioexception) {
				proglog->AppendText("\r\n" + ioexception->Message + " in sys_task_Tick.");
			}
		}
	}
	sys_task_counter++;
}
