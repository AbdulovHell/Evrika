﻿//#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include "EventLog.pb.h"
#include "templates.h"
#include "settings.h"
#include "loading_page.h"
#include "mapform.h"
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
	Devices = gcnew List<Repeater^>(20);
	RadioTags = gcnew List<RadioTag^>(20);
	Events = gcnew List<Event^>(50);
	logs = gcnew List<TextBox^>;
	//PropWindows = gcnew List<device_prop^>;
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
	UpdateMapPos();
	groupBox1->Text = "Точек сохранено: " + MyCoords->Count.ToString(); //обновление при получении точк

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

void Evrika::mainform::Triangulate(geoPoint ^ circle1, geoPoint ^ circle2)
{	//return points and array size
	double d, x31, x32, y31, y32, x0, x1, x2, y0, y1, y2, a, r0 = circle1->get_r() / 1000, r1 = circle2->get_r() / 1000;
	System::Collections::Generic::List<GMap::NET::PointLatLng> ^Points = gcnew System::Collections::Generic::List<GMap::NET::PointLatLng>;
	System::Collections::Generic::List<GMap::NET::PointLatLng> ^cPoints = gcnew System::Collections::Generic::List<GMap::NET::PointLatLng>;

	double Z = Math::Cos(circle1->get_lat()*(Math::PI / 180));	//поправка на длинну мередиана

	double A0, B0, C0;
	//d = circle1->get_dist(circle2);
	//r0 *= 111.11;
	//r1 *= 111.11;
	//listView1->Items->Clear();
	y0 = circle1->get_lat();
	y1 = circle2->get_lat();
	x0 = circle1->get_lng();
	x1 = circle2->get_lng();
	//double x = (x1 - x0)*111.11*Z;
	//double y = (y1 - y0)*111.11;
	double y = circle2->get_lat() - circle1->get_lat();
	double x = circle2->get_lng() - circle1->get_lng();
	x *= 111.11*Z;
	y *= 111.11;
	d = Math::Sqrt(y*y + x*x);
	//d = Math::Sqrt((y1 - y0)*(y1 - y0) + (x1 - x0)*(x1 - x0));
	if (d > r0 + r1)
		return;
	if (d < Math::Abs(r0 - r1))
		return;
	a = ((r0 * r0 - r1 * r1) + d * d) / (2 * d);

	y2 = (a / d) * y;
	x2 = (a / d) * x;

	A0 = x;
	B0 = y;
	C0 = -A0*x2 - B0*y2;

	double alfa = Math::Acos(a / r0);  //угол между отрезком, который соединяет центры, и одним из радиусов первой окружности, проведённым в точку пересечения.
									   //хз как арккосинус считается, поправь если что.
									   //здесь требуется правильно считать a.
	double cosOx = x / (Math::Sqrt(x*x + y*y)); // вычисляем синус и косинус угла между отрезком, который соединяет центры, и осью иксов
	double sinOx = y / (Math::Sqrt(x*x + y*y));  //надо считать корень!)

	double alfa0;             // смотрим на расположение отрезка по знаку sin/cos
	if (sinOx >= 0)
		alfa0 = Math::Acos(cosOx);  //первая и вторая четверть, угол положительный 
	else
		alfa0 = -Math::Acos(cosOx); // третья и четвёртая четверть, знак косинуса не важен, только знак синуса

	double alfa1 = alfa0 + alfa;
	double alfa2 = alfa0 - alfa;

	if ((alfa1 == Math::PI / 2) || (alfa2 == Math::PI / 2) || (alfa1 == -Math::PI / 2) || (alfa2 == -Math::PI / 2))
	{
		//проверяем не равен какой-либо из углов пи на два или минус пи на 2. если хоть один из них равен
		//то нельзя считать тангенс (он бесконечен), решение будет немного другим. Как пи пишется я не знаю.
		if ((alfa1 == Math::PI / 2) || (alfa1 == -Math::PI / 2))
		{
			x31 = 0;
			x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
			y31 = -C0 / B0;
			y32 = x32 * Math::Tan(alfa2);
		}
		if ((alfa2 == Math::PI / 2) || (alfa2 == -Math::PI / 2))
		{
			x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
			x32 = 0;
			y31 = x31 * Math::Tan(alfa1);
			y32 = -C0 / B0;
		}

	}
	else                //здесь собственно решение, если углы норм. тогда тг считать можно.
	{
		x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
		x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
		y31 = x31 * Math::Tan(alfa1);
		y32 = x32 * Math::Tan(alfa2);
	}

	y2 /= 111.11;
	x2 /= 111.11*Z;

	x31 /= 111.11*Z;
	x32 /= 111.11*Z;
	y31 /= 111.11;
	y32 /= 111.11;

	Points->Add(PointLatLng(x0 + x31, y0 + y31));
	Points->Add(PointLatLng(x0 + x32, y0 + y32));
	cPoints->Add(PointLatLng(y0, x0));
	cPoints->Add(PointLatLng(y1, x1));

	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y2, x0 + x2), Markers::GMarkerGoogleType::purple));
	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y31, x0 + x31), Markers::GMarkerGoogleType::red));
	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y32, x0 + x32), Markers::GMarkerGoogleType::red));
	GMapPolygon ^line = gcnew GMapPolygon(Points, "line0");
	GMapPolygon ^lineC = gcnew GMapPolygon(cPoints, "line0");
	line->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(50, Color::Red));
	line->Stroke = gcnew Pen(Color::Red, 1);
	lineC->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(50, Color::Blue));
	lineC->Stroke = gcnew Pen(Color::Blue, 1);
	areaOvrl->Polygons->Add(line);
	areaOvrl->Polygons->Add(lineC);
	return;
}

void Evrika::mainform::Triangulate(geoPoint ^ circle1, geoPoint ^ circle2, List<PointLatLng>^ twoPoints)
{	//return points and array size
	double d, x31, x32, y31, y32, x0, x1, x2, y0, y1, y2, a, r0 = circle1->get_r() / 1000, r1 = circle2->get_r() / 1000;
	List<PointLatLng> ^Points = gcnew List<GMap::NET::PointLatLng>;
	List<PointLatLng> ^cPoints = gcnew List<GMap::NET::PointLatLng>;

	double Z = Math::Cos(circle1->get_lat()*(Math::PI / 180));	//поправка на длинну мередиана
	double A0, B0, C0;
	y0 = circle1->get_lat();
	y1 = circle2->get_lat();
	x0 = circle1->get_lng();
	x1 = circle2->get_lng();
	double y = circle2->get_lat() - circle1->get_lat();
	double x = circle2->get_lng() - circle1->get_lng();
	x *= 111.11*Z;
	y *= 111.11;
	d = Math::Sqrt(y*y + x*x); if (d > r0 + r1)
		return;
	if (d < Math::Abs(r0 - r1))
		return;
	a = ((r0 * r0 - r1 * r1) + d * d) / (2 * d);
	y2 = (a / d) * y;
	x2 = (a / d) * x;
	A0 = x;
	B0 = y;
	C0 = -A0*x2 - B0*y2;

	double alfa = Math::Acos(a / r0);  //угол между отрезком, который соединяет центры, и одним из радиусов первой окружности, проведённым в точку пересечения.
									   //хз как арккосинус считается, поправь если что.
									   //здесь требуется правильно считать a.
	double cosOx = x / (Math::Sqrt(x*x + y*y)); // вычисляем синус и косинус угла между отрезком, который соединяет центры, и осью иксов
	double sinOx = y / (Math::Sqrt(x*x + y*y));  //надо считать корень!)

	double alfa0;             // смотрим на расположение отрезка по знаку sin/cos
	if (sinOx >= 0)
		alfa0 = Math::Acos(cosOx);  //первая и вторая четверть, угол положительный 
	else
		alfa0 = -Math::Acos(cosOx); // третья и четвёртая четверть, знак косинуса не важен, только знак синуса

	double alfa1 = alfa0 + alfa;
	double alfa2 = alfa0 - alfa;

	if ((alfa1 == Math::PI / 2) || (alfa2 == Math::PI / 2) || (alfa1 == -Math::PI / 2) || (alfa2 == -Math::PI / 2))
	{
		//проверяем не равен какой-либо из углов пи на два или минус пи на 2. если хоть один из них равен
		//то нельзя считать тангенс (он бесконечен), решение будет немного другим. Как пи пишется я не знаю.
		if ((alfa1 == Math::PI / 2) || (alfa1 == -Math::PI / 2))
		{
			x31 = 0;
			x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
			y31 = -C0 / B0;
			y32 = x32 * Math::Tan(alfa2);
		}
		if ((alfa2 == Math::PI / 2) || (alfa2 == -Math::PI / 2))
		{
			x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
			x32 = 0;
			y31 = x31 * Math::Tan(alfa1);
			y32 = -C0 / B0;
		}

	}
	else                //здесь собственно решение, если углы норм. тогда тг считать можно.
	{
		x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
		x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
		y31 = x31 * Math::Tan(alfa1);
		y32 = x32 * Math::Tan(alfa2);
	}
	x31 /= 111.11*Z;
	x32 /= 111.11*Z;
	y31 /= 111.11;
	y32 /= 111.11;
	twoPoints->Add(PointLatLng(y0 + y31, x0 + x31));
	twoPoints->Add(PointLatLng(y0 + y32, x0 + x32));
	return;
}

int Evrika::mainform::factorial(int n)
{
	int res = 1;
	for (int i = 1; i < n + 1; i++)
		res *= i;
	return res;
}

List<PointLatLng>^ Evrika::mainform::SortPoint_Line(List<PointLatLng>^ in_p)
{
	List<PointLatLng>^ out_p = gcnew List<PointLatLng>;
	Line^ line = gcnew Line();
	int size = in_p->Count, index = -1, flag = 0;
	out_p->Add(in_p[0]);
	in_p->RemoveAt(0);
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < in_p->Count; j++)
		{
			flag = 0;
			line->set_line(out_p[i], in_p[j]);
			for (int k = 0; k < in_p->Count; k++)
			{
				if (k != j)
					flag += line->check_point(in_p[k]);
			}
			for (int k = 0; k < out_p->Count; k++)
			{
				if (k != i)
					flag += line->check_point(out_p[k]);
			}
			if (Math::Abs(flag) == in_p->Count - 1 + out_p->Count - 1)
			{
				index = j;
				break;
			}
		}
		if (index != -1) {
			out_p->Add(in_p[index]);
			in_p->RemoveAt(index);
		}
	}
	//out_p->Add(in_p[0]);
	//in_p->RemoveAt(0);
	return out_p;
}

bool Evrika::mainform::inTheArea(PointLatLng point)
{
	bool result = true;
	for (int i = 0; i < MyCoords->Count; i++)
	{
		double r = geoPoint::GetDistanceToPointFrom(point, MyCoords[i]->get_pointLatLng()) * 1000;
		double rad = MyCoords[i]->get_r();
		//listBox2->Items->Add(r);
		if (r - 0.002*rad > rad)
		{
			//GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(point, Markers::GMarkerGoogleType::green_pushpin);
			//marker->ToolTipText = r.ToString();
			//marker->ToolTipMode = GMap::NET::WindowsForms::MarkerTooltipMode::OnMouseOver;
			//mrkrOvrl->Markers->Add(marker);
			result = false;
		}
	}
	return result;
}

bool Evrika::mainform::inTheArea(PointLatLng point, int i, int j, int k) {
	bool result = true;
	double r1 = geoPoint::GetDistanceToPointFrom(point, MyCoords[i]->get_pointLatLng()) * 1000;
	double r2 = geoPoint::GetDistanceToPointFrom(point, MyCoords[j]->get_pointLatLng()) * 1000;
	double r3 = geoPoint::GetDistanceToPointFrom(point, MyCoords[k]->get_pointLatLng()) * 1000;
	double radius1 = MyCoords[i]->get_r();
	double radius2 = MyCoords[j]->get_r();
	double radius3 = MyCoords[k]->get_r();
	if ((r1 - 0.002*radius1 > radius1) || (r2 - 0.002*radius2 > radius2) || (r3 - 0.002*radius3 > radius3))
		result = false;
	return result;
}

void Evrika::mainform::metod_5()
{
	List<PointLatLng>^ area_points = gcnew List<PointLatLng>;
	List<int>^ mass = gcnew List<int>;
	for (int i = 0; i < MyCoords->Count; i++)
		for (int j = i + 1; j < MyCoords->Count; j++) {
			List<PointLatLng>^ tempPoints = gcnew List<PointLatLng>;
			Triangulate(MyCoords[i], MyCoords[j], tempPoints);

			for (int p = 0; p < tempPoints->Count; p++) {
				bool duplicate = false;
				int index = -1;
				for (int f = 0; f < area_points->Count; f++)
				{
					if (tempPoints[p].Lat == area_points[f].Lat&&tempPoints[p].Lng == area_points[f].Lng)	//0.0000005
					{
						duplicate = true;
						index = f;
						break;
					}
				}
				if (duplicate)
				{
					if (inTheArea(tempPoints[p])) {
						mass[index]++;
					}
				}
				else
				{
					if (inTheArea(tempPoints[p])) {
						area_points->Add(tempPoints[p]);
						mass->Add(1);
					}
				}
			}
		}
	if (area_points->Count > 3) area_points = SortPoint_Line(area_points);
	GMapPolygon ^cent_area = gcnew GMapPolygon(area_points, "center_area");
	cent_area->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(127, Color::Red));
	cent_area->Stroke = gcnew Pen(Color::Red, 2);
	areaOvrl->Polygons->Add(cent_area);
}

void Evrika::mainform::ParseToPoint(cli::array<wchar_t>^ buf)
{
	int dist = 0;
	dist = buf[6] << 8;
	dist += buf[7];
	double lat = buf[8] + (buf[9] + (buf[10] + buf[11] / 100.0) / 60.0) / 60.0;
	double lon = buf[12] + (buf[13] + (buf[14] + buf[15] / 100.0) / 60.0) / 60.0;
	//save

	MyCoords->Add(gcnew geoPoint(lat, lon, dist, "ID: 1234"));
	listBox1->Items->Add(MyCoords[lCoordsCount]->get_name());
	lCoordsCount++;

	if (lCoordsCount > 8) {
		MyCoords->RemoveAt(0);
		lCoordsCount--;
		listBox1->Items->RemoveAt(0);
	}
}

void Evrika::mainform::WriteToComStat(String ^ str)
{
	whatCOM->Text = str;
}

void Evrika::mainform::CheckComConn()
{
	try {
		isOurCom = false;
		Commands::Class_0x0A::TestConnect();
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
			for (size_t i = 0; i < coms_count; i++) {
				if (serialPort1->IsOpen)
					serialPort1->Close();
				serialPort1->PortName = coms[i];
				try {
					serialPort1->Open();
					if (serialPort1->IsOpen) {
						isOurCom = false;
						Commands::Commands(serialPort1);
						Commands::Class_0x0A::TestConnect();
						sEnumCom->WaitOne(10000);	//TODO: настроить
						if (isOurCom) {
							this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), serialPort1->PortName);
							this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ найден по " + whatCOM->Text);
							LastStateIsOpen = true;
							Commands::Class_0x0A::GetLocalAddr();
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

System::String ^ Evrika::mainform::Quality(int q)
{
	//0x2588 full block
	//0x2591 light shade
	//0x2584 half block
	q = q % 7;
	wchar_t buf[8];
	for (int i = 0; i < 7; i++) {
		if (i == 0 && q > 0) buf[i] = 0x2584;
		else if (i > 0 && i < q) buf[i] = 0x2588;
		else buf[i] = 0x2591;
	}
	buf[7] = 0;
	System::String^ str = gcnew System::String(buf);
	return str;
}

int Evrika::mainform::RangeRandInt(int min, int max)
{
	Random^ autoRand = gcnew Random;
	return autoRand->Next(min, max);
}

double Evrika::mainform::RangeRandDouble(double min, double max)
{
	Random^ autoRand = gcnew Random;
	double mult = autoRand->NextDouble();
	double num = min + (max - min)*mult;
	int temp = int(num * 100);
	return temp / 100.0;
}

void Evrika::mainform::SetTimer(bool en)
{
	sys_task->Enabled = en;
}

void Evrika::mainform::WriteLog(String ^ message)
{
	for (int i = 0; i < logs->Count; i++) {
		try {
			logs[i]->AppendText("\r\n" + message);
		}
		catch (...) {
			logs->RemoveAt(i);
			i--;
		}
	}
}

void Evrika::mainform::AddNewPoint(float m)
{
	if (!my_pos_accepted) return;
	double lat = 0, lng = 0, r_m = m;
	myPos->GetPos(&lat, &lng);
	label10->Text = r_m.ToString();
	MyCoords->Add(gcnew geoPoint(lat, lng, r_m));
	if (MyCoords->Count > 8)
		MyCoords->RemoveAt(0);
	groupBox1->Text = "Точек сохранено: " + MyCoords->Count.ToString(); //обновление при получении точк
	WriteLog("Точка добавлена");
	if (MyCoords->Count > 3) {
		areaOvrl->Clear();
		mrkrOvrl->Clear();
		metod_5();
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

void Evrika::mainform::UpdateMapPos()
{
	//обновление картой при изменении
	label2->Text = "Широта: " + map->Position.Lat.ToString();	//Latitude
	label3->Text = "Долгота: " + map->Position.Lng.ToString();	//Longetude
}

bool Evrika::mainform::CheckSum(cli::array<wchar_t>^ rbuf)
{
	if (!((rbuf[0] == 0x65) && (rbuf[1] == 0x76))) return false;	//базовая проверка

	int len = (rbuf[8] << 8) + rbuf[9];

	uint8_t mCK_A = (uint8_t)rbuf[9 + len + 1], mCK_B = (uint8_t)rbuf[9 + len + 2];
	uint8_t cCK_A = 0, cCK_B = 0;
	for (int i = 2; i < (9 + len + 1); i++) {
		cCK_A += (uint8_t)rbuf[i];
		cCK_B += cCK_A;
	}
	if ((cCK_A == mCK_A) && (cCK_B == mCK_B)) return true;
	return false;
}

void Evrika::mainform::UpdateRadioTagsList()
{
	//RadioTagsGrid->Rows->Clear();
	//for (int i = 0; i < Devices->Count; i++) {
	//	RadioTagsGrid->Rows->Add(1);
	//	if (Devices[i]->missing_counter == 0)
	//		RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex();	//id
	//	else
	//		RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex() + " (!)";	//id
	//	RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[1]->Value = Devices[i]->signal_lvl;	//sgnl lvl
	//	RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[2]->Value = Devices[i]->signal_quality;	//quality
	//	RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[3]->Value = Devices[i]->battery_lvl;	//batt lvl
	//	RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[4]->Value = Devices[i]->work_mode;	//mode
	//}

	//for (int i = 0; i < RadioTagsGrid->RowCount; i++) {
	//	double tempval = 0;
	//	int templvl = 100;
	//	//try {
	//	tempval = double(RadioTagsGrid->Rows[i]->Cells[3]->Value);
	//	//}
	//	//catch (...) {}
	//	if (tempval) {
	//		if (tempval < Evrika::settings::GetMySettingP()->voltLvl[0]) {
	//			RadioTagsGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[0];
	//		}
	//		else if (tempval < Evrika::settings::GetMySettingP()->voltLvl[1]) {
	//			RadioTagsGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[1];
	//		}
	//		else {
	//			RadioTagsGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[2];
	//		}
	//	}

	//	//try {
	//	templvl = (int)(RadioTagsGrid->Rows[i]->Cells[1]->Value);
	//	//}
	//	//catch (...) {}
	//	if (templvl < 100) {
	//		if (templvl < Evrika::settings::GetMySettingP()->signlLvl[0]) {
	//			RadioTagsGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[0];
	//		}
	//		else if (templvl < Evrika::settings::GetMySettingP()->signlLvl[1]) {
	//			RadioTagsGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[1];
	//		}
	//		else {
	//			RadioTagsGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[2];
	//		}
	//	}
	//}
}

void Evrika::mainform::UpdateRepeatersList()
{
	this->DCGrid->SelectionChanged -= gcnew System::EventHandler(this, &mainform::DCGrid_SelectionChanged);
	//Очистка сетки
	DCGrid->Rows->Clear();
	for (int i = 0; i < Devices->Count; i++) {
		//добавляем новую строку
		DCGrid->Rows->Add(1);
		//столбец адреса
		if (Devices[i]->missing_counter == 0)
			DCGrid->Rows[DCGrid->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex();	//id
		else
			DCGrid->Rows[DCGrid->RowCount - 1]->Cells[0]->Value = Devices[i]->IdInHex() + " (!)";	//id
		//столбец уровня сигнала
		int8_t rssi = Devices[i]->GetSignalLvl();
		DCGrid->Rows[DCGrid->RowCount - 1]->Cells[1]->Value = rssi.ToString();
		if (rssi < 100) {
			if (rssi < Evrika::settings::GetMySettingP()->signlLvl[0]) {
				DCGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[0];
			}
			else if (rssi < Evrika::settings::GetMySettingP()->signlLvl[1]) {
				DCGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[1];
			}
			else {
				DCGrid->Rows[i]->Cells[1]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[2];
			}
		}
		//столбец качества приема сигнала
		DCGrid->Rows[DCGrid->RowCount - 1]->Cells[2]->Value = Devices[i]->GetSignalQuality().ToString();
		//уровень заряда батареи, В
		float vbatt = Devices[i]->GetBatteryLvl();
		DCGrid->Rows[DCGrid->RowCount - 1]->Cells[3]->Value = vbatt.ToString();
		if (vbatt) {
			if (vbatt < Evrika::settings::GetMySettingP()->voltLvl[0]) {
				DCGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[0];
			}
			else if (vbatt < Evrika::settings::GetMySettingP()->voltLvl[1]) {
				DCGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[1];
			}
			else {
				DCGrid->Rows[i]->Cells[3]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[2];
			}
		}
		//режим работы
		if (Devices[i]->isLocal)
			DCGrid->Rows[DCGrid->RowCount - 1]->Cells[4]->Value = "Локальный";
		else
			DCGrid->Rows[DCGrid->RowCount - 1]->Cells[4]->Value = "Ретранслятор";
	}
	this->DCGrid->SelectionChanged += gcnew System::EventHandler(this, &mainform::DCGrid_SelectionChanged);
	DCGrid_SelectionChanged(this, gcnew EventArgs());
}

void Evrika::mainform::update_event_list()
{
	//dataGridView2->Rows->Clear();
	//for (int i = 0; i < Events->Count; i++) {
	//	dataGridView2->Rows->Add(1);

	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[0]->Value = Events[i]->device->IdInHex();	//id
	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[1]->Value = Events[i]->device->signal_lvl;	//sgnl lvl
	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[2]->Value = Events[i]->device->battery_lvl;	//batt lvl
	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[3]->Value = Events[i]->device->work_mode;	//mode
	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[4]->Value = Events[i]->sEvent;	//event type
	//	dataGridView2->Rows[dataGridView2->RowCount - 1]->Cells[5]->Value = Events[i]->td->ToSysString();	//dt
	//}
}

void Evrika::mainform::ParseDeviceBuffer(cli::array<wchar_t>^ rbuf)
{
	//проверка синхробайтов и контрольной суммы, в случае ошибки выдаем в лог и не обрабатываем
	if (!CheckSum(rbuf)) {
		//WriteLog("Какая-то дичь... : " + gcnew String(rbuf));
		return;
	}
	//проверка пройдена, обработка
	switch (rbuf[MESSAGE_CLASS]) {	//message class
	case 0x0A:
		switch (rbuf[MESSAGE_ID]) {	//message ID
		case 0x00:	//ответ на проверку соединения
			isOurCom = true;
			sEnumCom->Release();
			break;
		case 0x01:	//ответ на запрос локального адреса
		{
			uint32_t addr = ToInt32FromBuf(rbuf, 10);
			Devices->Add(gcnew Repeater(addr, true));
			Commands::Class_0x0A::GetVoltage(Devices[0]->GetAddr());
			UpdateRepeatersList();
		}
		break;
		case 0x02:	//ответ на запрос напряжений
		{
			uint32_t addr = ToInt32FromBuf(rbuf, 2);
			float vbatt = GetFloatFromBuf(rbuf, 10);
			float charger = GetFloatFromBuf(rbuf, 14);
			float lna1 = GetFloatFromBuf(rbuf, 18);
			float lna2 = GetFloatFromBuf(rbuf, 22);
			float vcore = GetFloatFromBuf(rbuf, 26);
			float vtemp = GetFloatFromBuf(rbuf, 30);

			if (Devices[0]->GetAddr() == addr) {
				Devices[0]->Fill(vbatt, 0, 0);
				UpdateRepeatersList();
			}
			else {
				for (int i = 1; i < Devices->Count; i++) {
					if (addr == Devices[i]->GetAddr()) {
						vbattLbl->Text = "vbatt: " + vbatt.ToString() + " V";
						vchargerLbl->Text = charger.ToString();
						vlna1Lbl->Text=lna1.ToString();
						vlna2Lbl->Text=lna2.ToString();
						vcoreLbl->Text=vcore.ToString();
						vtempLbl->Text=vtemp.ToString();
					}
				}
			}
		}
		break;
		case 0x88:	//ответ на запрос о состоянии реле
		{
			uint32_t addr = ToInt32FromBuf(rbuf, 2);
			uint8_t state = rbuf[10];
			for (int i = 0; i < Devices->Count; i++)
				if (addr == Devices[i]->GetAddr())
					Devices[i]->SaveRelayStat(state);
			RelayStatCheckBox->Checked = state;
		}
		break;
		case 0x89:	//ответ на управление реле

			break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0A");
			break;
		}
		break;
	case 0x0B:
		switch (rbuf[MESSAGE_ID]) {
		case 0x01:	//ответ на управление питанием GPS
			if (eGPS)
				WriteLog("GPS включен");
			else
				WriteLog("GPS выключен");
			break;
		case 0x02:	//ответ на запрос состояния питания GPS
		{
			bool state = rbuf[10];
#pragma region Old Code
			//int len = (rbuf[4] << 8) + rbuf[5];	//28
			//uint8_t hh = (uint8_t)rbuf[6];	//1
			//uint8_t mm = (uint8_t)rbuf[7];	//2
			//uint8_t ss = (uint8_t)rbuf[8];	//3
			//int8_t lat_p = (int8_t)rbuf[9];	//4
			//uint8_t lat_dd = (uint8_t)rbuf[10];	//5
			//uint8_t lat_mm = (uint8_t)rbuf[11];	//6
			//double lat_ss = GetFloatFromBuf(rbuf, 12);	//10
			//int8_t lng_p = (int8_t)rbuf[17];	//11
			//uint8_t lng_dd = (uint8_t)rbuf[18];	//12
			//uint8_t lng_mm = (uint8_t)rbuf[19];	//13
			//double lng_ss = GetFloatFromBuf(rbuf, 20);	//17
			//uint8_t satellites = (uint8_t)rbuf[25];	//18
			//double HDOP = GetFloatFromBuf(rbuf, 26);	//22
			//double height = GetFloatFromBuf(rbuf, 30);	//26

			//double lat = lat_dd + (lat_mm + lat_ss) / 60.0,
			//	lng = lng_dd + (lng_mm + lng_ss) / 60.0;

			//if (myPos->bFirstRead) {
			//	myPos->bFirstRead = false;
			//	myPos->SetState(lat, lng, HDOP, height);
			//}
			//myPos->Correct(lat, lng, HDOP, height);
			////Test-----------------------------
			///*{
			//GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::red_small);
			//mrkrOvrl->Markers->Add(marker);

			//GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			//circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Red));
			//circ->Stroke = gcnew Pen(Color::Red, 1);
			//areaOvrl->Polygons->Add(circ);
			//}*/
			////---------------------------------
			//myPos->GetState(&lat, &lng, &HDOP, &height);
			//toolStripStatusLabel3->Text = "Sat: " + satellites;
			//toolStripStatusLabel3->Visible = true;
			//toolStripStatusLabel4->Text = "HDOP: " + (float)HDOP;
			//toolStripStatusLabel4->Visible = true;
			//toolStripStatusLabel5->Text = "H: " + (float)height + " m";
			//toolStripStatusLabel5->Visible = true;
			////---------------------------------
			///*myPosOvrl->Clear();
			//myPosOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::blue_small));
			//GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			//circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Blue));
			//circ->Stroke = gcnew Pen(Color::Blue, 1);
			//myPosOvrl->Polygons->Add(circ);*/
			////sPointReciver->Release();
			////---------------------------------
			//my_pos_accepted = true;
#pragma endregion
		}
		break;
		case 0x03:	//ответ на запрос статуса GPS
		{
			//0 - nofix, 1 - standart, 2 - Diff., 3 - Estimate
			uint8_t type = rbuf[10];
		}
		break;
		case 0x04:	//ответ на запрос данных GPS
		{
			uint8_t hh = rbuf[10];
			uint8_t mm = rbuf[11];
			uint8_t ss = rbuf[12];
			uint8_t lat_sign = rbuf[13];
			uint8_t lat_deg = rbuf[14];
			uint8_t lat_min = rbuf[15];
			float lat_sec = GetFloatFromBuf(rbuf, 16);
			uint8_t lon_sign = rbuf[20];
			uint8_t lon_deg = rbuf[21];
			uint8_t lon_min = rbuf[22];
			float lon_sec = GetFloatFromBuf(rbuf, 23);
			uint8_t satellites = rbuf[27];
			float hdop = GetFloatFromBuf(rbuf, 28);
			float alt = GetFloatFromBuf(rbuf, 32);

		}
		break;
		case 0x05:	//ответ на переключение антенны
		{

		}
		break;
		case 0x06:	//ответ на запрос исп. антенны
		{
			bool isExternal = rbuf[10];

		}
		break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0B");
			break;
		}
		break;
	case 0x0C:
		switch (rbuf[MESSAGE_ID]) {	//message ID
		case 0x01:	//ответ на запуск цикла пробуждения меток
		{
			uint8_t count = rbuf[10];
#pragma region Old Code
			//int len = (rbuf[4] << 8) + rbuf[5];
			//int devices = (len - 0) / 8;	//количество устройств в буфере
			//List<Device^>^ tempdev = gcnew List<Device^>;
			////парсинг буфера в список у-в
			//for (int i = 0; i < devices; i++) {	//массив у-в в список у-в
			//	int addr = rbuf[6 + 8 * i] + (rbuf[7 + 8 * i] << 8) + (rbuf[8 + 8 * i] << 16) + (rbuf[9 + 8 * i] << 24);
			//	int raw_v = rbuf[12 + 8 * i];
			//	double volt = raw_v >> 4;
			//	volt += ((double)(raw_v & 0xF)) / 10.0;
			//	tempdev->Add(gcnew Device(addr, (char)rbuf[10 + 8 * i], rbuf[11 + 8 * i], volt, rbuf[13 + 8 * i], NULL));
			//}
			////сброс флагов обработки у-в, уже наход в памяти
			//for (int i = 0; i < Devices->Count; i++) Devices[i]->Processed = false;
			////сравнение и обновление у-в, которые уже были в памяти
			//for (int i = 0; i < Devices->Count; i++) {
			//	for (int j = 0; j < tempdev->Count; j++) {
			//		if (Devices[i]->unique_id == tempdev[j]->unique_id) {
			//			Devices[i]->copy(tempdev[j]);
			//			Devices[i]->Processed = true;
			//			Devices[i]->missing_counter = 0;
			//			tempdev->RemoveAt(j);
			//		}
			//	}
			//}
			////обработка "устаревших" у-в
			//for (int i = 0; i < Devices->Count; i++) {
			//	if (Devices[i]->Processed == false) {
			//		if (Devices[i]->missing_counter > 3) {
			//			//generate_event_disconnect
			//			Events->Add(gcnew Event(Devices[i], Event::EventCode::DEV_DISCONNECTED));
			//			update_event_list();
			//			Devices->RemoveAt(i);
			//		}
			//		else
			//			Devices[i]->missing_counter++;
			//	}
			//}
			////обработка "новых" у-в
			//for (int i = 0; i < tempdev->Count; i++) {
			//	//generate_newdev_event
			//	Events->Add(gcnew Event(tempdev[i], Event::EventCode::DEV_CONNECTED));
			//	update_event_list();
			//	Devices->Add(tempdev[i]);
			//	tempdev->RemoveAt(i);
			//}
			//if (Devices->Count > 0)
			//	this->device_get = true;
			//else
			//	device_get = false;
			////обновление списка у-в
			//update_device_list();
			////обновление окон св-в
			//update_prop_windows();
#pragma endregion
		}
		break;
		case 0x02:	//ответ на запрос параметров радиометок
		{
			uint16_t len = rbuf[8] + rbuf[9] << 8;
			uint32_t addr = rbuf[10] + rbuf[11] << 8 + rbuf[12] << 16 + rbuf[13] << 24;
			int8_t rssi = rbuf[14];
			int8_t lqi = rbuf[15];
			uint8_t vbatt = rbuf[16];
			int8_t a_rssi = rbuf[17];
			uint8_t bitrate = rbuf[18];
			//rbuf[19]
#pragma region Old code time meas
			////invoke в device_prop
			//int size = (rbuf[4] << 8) + rbuf[5];
			//int count = size / 5;
			//List<int>^ sign_lvls = gcnew List<int>;
			//List<int64_t>^ cycles = gcnew List<int64_t>;
			//int midRSSI = 0;
			//for (int i = 0; i < count; i++) {
			//	sign_lvls->Add((char)(rbuf[6 + 5 * i]));
			//	cycles->Add(rbuf[7 + 5 * i] + (rbuf[8 + 5 * i] << 8) + (rbuf[9 + 5 * i] << 16) + (rbuf[10 + 5 * i] << 24));
			//	midRSSI += (char)(rbuf[6 + 5 * i]);
			//}
			//midRSSI /= sign_lvls->Count;
			//if (cycles->Count == 0) return;
			//try {
			//	//device_prop::hDevice_prop->Invoke(gcnew Action< List<int64_t>^ >(device_prop::hDevice_prop, &device_prop::SaveCycles), cycles);
			//	device_prop::hDevice_prop->SaveCycles(cycles, midRSSI);
			//}
			//catch (...) {

			//}
#pragma endregion
		}
		break;
		case 0x03:
		{

		}
		break;
		case 0x04:
		{

		}
		break;
		case 0x06:	//базовая информация о метке
		{
			//Device^ tempdev;
			//парсинг буфера в список у-в
			uint32_t addr = rbuf[10] + (rbuf[11] << 8) + (rbuf[12] << 16) + (rbuf[13] << 24);
			int8_t rssi = rbuf[14];
			uint32_t time = rbuf[15] + rbuf[16] << 8 + rbuf[17] << 16 + rbuf[18] << 24;
			int8_t lqi = rbuf[19];
			uint8_t vbatt = rbuf[20];
			int8_t a_rssi = rbuf[21];
			float a_time = GetFloatFromBuf(rbuf, 22);
			uint8_t bitrate = rbuf[26];
			//double volt = raw_v >> 4;
			//volt += ((double)(raw_v & 0xF)) / 10.0;
			//tempdev = gcnew Device(addr, (char)rbuf[10], rbuf[11], volt, rbuf[13], NULL);
			//сравнение и обновление у-в, которые уже были в памяти
			//for (int i = 0; i < Devices->Count; i++)
			//	if (Devices[i]->unique_id == tempdev->unique_id)
			//		Devices[i]->copy(tempdev);
			//обновление окон св-в
			//update_prop_windows();
			//маякнуть окну св-в об изменении статов
			//device_prop::sMeasDist->Release();
			//обновление списка у-в
			//update_device_list();
		}
		break;
		case 0x07: //ответ на сброс СС1101 к перв. уст.
		{

		}
		break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0C");
			break;
		}
		break;
	case 0x0D:
		switch (rbuf[MESSAGE_ID]) {
		case 0x01:	//ответ на запуск поиска ретрансл.
		{
			uint8_t count = rbuf[10];
			if (count > 0) {
				CurrentActionLbl->Text = "Найденно ретрансляторов: " + count.ToString() + ". Запрос параметров...";
				Commands::Class_0x0D::GetRepeatersParam(NULL, count);
			}
			else
				CurrentActionLbl->Text = "Найденно ретрансляторов: " + count.ToString() + ".";
		}
		break;
		case 0x02:	//ответ на запрос параметров ретрансл.
		{
			int len = (rbuf[8] << 8) + rbuf[9];
			int devices = len / 8;	//количество устройств в буфере
			List<Repeater^>^ tempdev = gcnew List<Repeater^>;
			//парсинг буфера в список у-в
			for (int i = 0; i < devices; i++) {	//массив у-в в список у-в
				uint32_t addr = ToInt32FromBuf(rbuf, 10 + 8 * i);
				int8_t rssi = rbuf[14 + 8 * i];
				int8_t lqi = rbuf[15 + 8 * i];
				float vbatt = (rbuf[16 + 8 * i] >> 4) + (rbuf[16 + 8 * i] & 0xF) / 10.0;
				//uint8_t param = rbuf[17+8*i];
				tempdev->Add(gcnew Repeater(addr, false));
				tempdev[i]->Fill(vbatt, rssi, lqi);
			}
			//сброс флагов обработки у-в, уже наход в памяти
			for (int i = 1; i < Devices->Count; i++) Devices[i]->Processed = false;
			//сравнение и обновление у-в, которые уже были в памяти
			for (int i = 1; i < Devices->Count; i++) {
				for (int j = 0; j < tempdev->Count; j++) {
					if (Devices[i]->GetAddr() == tempdev[j]->GetAddr()) {
						Devices[i]->copy(tempdev[j]);
						Devices[i]->Processed = true;
						Devices[i]->missing_counter = 0;
						tempdev->RemoveAt(j);
					}
				}
			}
			//обработка "устаревших" у-в
			for (int i = 1; i < Devices->Count; i++) {
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
			if (Devices->Count > 1)
				this->device_get = true;
			else
				device_get = false;
			//обновление списка у-в
			UpdateRepeatersList();
			CurrentActionLbl->Text += " Готово.";
		}
		break;
		case 0x99:	//ответ на глобальный сброс всех ретрансл.
		{

		}
		break;
		default:
			WriteLog("ParseBuffer error: Unknown message ID in class 0x0D");
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

System::Void Evrika::mainform::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MyCoords[lCoordsCount] = gcnew geoPoint(map->Position.Lat, map->Position.Lng, double::Parse(textBox1->Text), "P" + lCoordsCount.ToString());
	MyCoords->Add(gcnew geoPoint(map->Position.Lat, map->Position.Lng, double::Parse(textBox1->Text), "P" + lCoordsCount.ToString()));
	listBox1->Items->Add(MyCoords[lCoordsCount]->get_name());
	lCoordsCount++;
}

System::Void Evrika::mainform::listBox1_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (listBox1->SelectedIndex<0 || listBox1->SelectedIndex>lCoordsCount - 1) return;
	groupBox2->Text = MyCoords[listBox1->SelectedIndex]->get_name();
	label5->Text = "R: " + MyCoords[listBox1->SelectedIndex]->get_r().ToString();
	label6->Text = "Lat: " + MyCoords[listBox1->SelectedIndex]->get_lat().ToString();
	label7->Text = "Lng: " + MyCoords[listBox1->SelectedIndex]->get_lng().ToString();
}

System::Void Evrika::mainform::button5_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (listBox1->SelectedIndex<0 || listBox1->SelectedIndex>lCoordsCount - 1) return;
	delete MyCoords[listBox1->SelectedIndex];
	for (int i = listBox1->SelectedIndex; i < lCoordsCount - 1; i++) {
		MyCoords[i] = MyCoords[i + 1];
	}
	lCoordsCount--;
	listBox1->Items->Clear();
	for (int i = 0; i < lCoordsCount; i++) {
		listBox1->Items->Add(MyCoords[i]->get_name());
	}
}

System::Void Evrika::mainform::button3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//draw area point
	if (listBox1->SelectedIndex<0 || listBox1->SelectedIndex>lCoordsCount - 1) return;
	GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(MyCoords[listBox1->SelectedIndex]->get_pointLatLng(), Markers::GMarkerGoogleType::blue_small);
	mrkrOvrl->Markers->Add(marker);

	GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::SortPoints_distance(MyCoords[listBox1->SelectedIndex]->CreateCircle()), "circ");
	circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Blue));
	circ->Stroke = gcnew Pen(Color::Blue, 1);
	areaOvrl->Polygons->Add(circ);
}

System::Void Evrika::mainform::button6_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	areaOvrl->Clear();
	mrkrOvrl->Clear();
}

System::Void Evrika::mainform::button4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	GMarkerGoogle^ marker = gcnew GMarkerGoogle(MyCoords[listBox1->SelectedIndex]->get_pointLatLng(), GMarkerGoogleType::blue_pushpin);
	mrkrOvrl->Markers->Add(marker);
}

System::Void Evrika::mainform::button7_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//find points of intersect
	Triangulate(MyCoords[0], MyCoords[1]);
}

System::Void Evrika::mainform::button9_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	metod_5();
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

System::Void Evrika::mainform::button7_Click_1(System::Object ^ sender, System::EventArgs ^ e)
{
	//RadioTagsGrid->Rows[0]->Cells[0]->Value = "abc";
	//RadioTagsGrid->Rows->Add(1);
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[0]->Value = "1";	//id
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[1]->Value = "2";	//temp id
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[2]->Value = RangeRandInt(-127, 10);	//sgnl lvl
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[3]->Value = Quality(RangeRandInt(0, 7));	//quality
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[4]->Value = RangeRandDouble(2.5, 4.5);	//batt lvl
	//RadioTagsGrid->Rows[RadioTagsGrid->RowCount - 1]->Cells[5]->Value = "0";	//mode


	try {
		serialPort1->Open();
		serialPort1->WriteLine("WAKE\r");

	}
	catch (IO::IOException ^ioexception) {
		proglog->AppendText("\r\n" + ioexception->Message);
	}
}

System::Void Evrika::mainform::настройкиToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	settings_window->Show();
}

System::Void Evrika::mainform::tabControl1_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	switch (tabControl1->SelectedIndex)
	{
	case 0:
		this->Width = 512;
		this->Height = 570;
		break;
	case 1:
	case 2:
		this->Width = 902;
		this->Height = 636;
		break;
	default:
		break;
	}
	this->Refresh();
}

System::Void Evrika::mainform::button8_Click_1(System::Object ^ sender, System::EventArgs ^ e)
{
	for (int i = 0; i < RadioTagsGrid->RowCount; i++) {
		double tempval = 0;
		int templvl = 100;
		//try {
		tempval = double(RadioTagsGrid->Rows[i]->Cells[4]->Value);
		//}
		//catch (...) {}
		if (tempval) {
			if (tempval < Evrika::settings::GetMySettingP()->voltLvl[0]) {
				RadioTagsGrid->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[0];
			}
			else if (tempval < Evrika::settings::GetMySettingP()->voltLvl[1]) {
				RadioTagsGrid->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[1];
			}
			else {
				RadioTagsGrid->Rows[i]->Cells[4]->Style->BackColor = Evrika::settings::GetMySettingP()->voltCol[2];
			}
		}

		//try {
		templvl = (int)(RadioTagsGrid->Rows[i]->Cells[2]->Value);
		//}
		//catch (...) {}
		if (templvl < 100) {
			if (templvl < Evrika::settings::GetMySettingP()->signlLvl[0]) {
				RadioTagsGrid->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[0];
			}
			else if (templvl < Evrika::settings::GetMySettingP()->signlLvl[1]) {
				RadioTagsGrid->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[1];
			}
			else {
				RadioTagsGrid->Rows[i]->Cells[2]->Style->BackColor = Evrika::settings::GetMySettingP()->SignlLvlCol[2];
			}
		}
	}
}

System::Void Evrika::mainform::serialPort1_DataReceived(System::Object ^ sender, System::IO::Ports::SerialDataReceivedEventArgs ^ e)
{
	cli::array<wchar_t>^ rbuf = gcnew cli::array<wchar_t>(512);
	try {
		for (int i = 0; i < 512; i++)
			rbuf[i] = serialPort1->ReadByte();

		this->Invoke(gcnew Action<cli::array<wchar_t>^>(this, &mainform::ParseDeviceBuffer), rbuf);
	}
	catch (...) {

	}
	//serialPort1->Close();
}

System::Void Evrika::mainform::checkBox2_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Get_Dev->Checked)
		get_device_progress->Value = 0;
}

System::Void Evrika::mainform::open_device(System::Object ^ sender, System::Windows::Forms::DataGridViewCellEventArgs ^ e)
{
	//int row = e->RowIndex;
	//if ((row < 0) || (Devices->Count == 0) || (row > Devices->Count - 1)) return;

	////ConstructCMD(serialPort1, Devices[row]->unique_id, true);
	//device_prop^ prop = gcnew device_prop(Devices[row], serialPort1);
	//prop->Show();
	//logs->Add(prop->my_log);
	//PropWindows->Add(prop);
}

System::Void Evrika::mainform::save_events(System::Object ^ sender, System::EventArgs ^ e)
{
	//TimeAndDate dt;
	//dt.GetCurrentTimeAndDate();
	//String^ datatime = dt.ToSysString();
	//saveFileDialog2->FileName = "Evrika_session_" + datatime;
	//saveFileDialog2->ShowDialog();

	//EvLog::EventLog eLog;
	//for (int i = 0; i < Events->Count; i++) {
	//	EvLog::Event* tempevent = eLog.add_events();

	//	EvLog::Device* dev = new EvLog::Device();

	//	dev->set_battery_lvl(Events[i]->device->battery_lvl);
	//	dev->set_signal_lvl(Events[i]->device->signal_lvl);
	//	dev->set_signal_quality(Events[i]->device->signal_quality);
	//	dev->set_unique_id(Events[i]->device->unique_id);
	//	dev->set_work_mode(Events[i]->device->work_mode);

	//	dev->set_allocated_pmode1(new EvLog::Device_mode1());
	//	dev->set_allocated_pmode2(new EvLog::Device_mode2());
	//	dev->set_allocated_pmode3(new EvLog::Device_mode3());
	//	dev->set_allocated_pmode4(new EvLog::Device_mode4());

	//	tempevent->set_allocated_dev(dev);

	//	EvLog::TD* td = new EvLog::TD();

	//	td->set_day(Events[i]->td->day);
	//	td->set_month(Events[i]->td->month);
	//	td->set_year(Events[i]->td->year);
	//	td->set_hour(Events[i]->td->hours);
	//	td->set_minute(Events[i]->td->minutes);
	//	td->set_second(Events[i]->td->seconds);

	//	tempevent->set_allocated_td(td);

	//	tempevent->set_ecode((UINT32)Events[i]->eCode);

	//	//delete dev;
	//	//delete td;
	//}
	//ofstream fs((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(saveFileDialog2->FileName), ios::out | ios::trunc | ios::binary);
	//int b = eLog.ByteSize();
	//void *output = malloc(b);
	//if (!eLog.SerializeToArray(output, b)) {
	//	//WriteLog("Error loading settings.");
	//}
	//fs.write((char*)output, b);
	//fs.close();
	//delete output;
	////saveFileDialog2->FileName; путь
}

System::Void Evrika::mainform::load_session(System::Object ^ sender, System::EventArgs ^ e)
{
	//openFileDialog1->ShowDialog();

	//ifstream ifs((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName), ios::in | ios::binary);

	//struct stat fi;
	//stat((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName), &fi);
	//int filesize = fi.st_size;

	//void *input = malloc(filesize);
	//ifs.read((char*)input, filesize);

	//EvLog::EventLog *eLog = new EvLog::EventLog();
	//if (!eLog->ParseFromArray(input, filesize)) {
	//	//cerr << "Failed to parse address book." << endl;
	//	return;
	//}

	//Events->Clear();
	//for (int i = 0; i < eLog->events_size(); i++) {
	//	EvLog::Event tempevent = eLog->events(i);

	//	EvLog::Device dev = tempevent.dev();
	//	Event::EventCode eCode = (Event::EventCode)tempevent.ecode();
	//	EvLog::TD td = tempevent.td();

	//	Events->Add(gcnew Event(gcnew Device(dev.unique_id(), dev.signal_lvl(), dev.signal_quality(), dev.battery_lvl(), dev.work_mode(), NULL),
	//		gcnew TimeAndDate(td.day(), td.month(), td.year(), td.hour(), td.minute(), td.second()), eCode));
	//}
	//update_event_list();
}

System::Void Evrika::mainform::переподключениеКДЦToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::EnumCOMs));
	connthrd->Start();
}

System::Void Evrika::mainform::проверкаСоединенияToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::CheckComConn));
	connthrd->Start();
}

System::Void Evrika::mainform::mainform_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	my_handle = this;
	Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::EnumCOMs));
	connthrd->Start();
}

System::Void Evrika::mainform::ExportMapBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	map->ShowExportDialog();
}

System::Void Evrika::mainform::ImportMapBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	map->ShowImportDialog();
}

System::Void Evrika::mainform::button11_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!eGPS) return;
	try {
		if (!serialPort1->IsOpen)
			serialPort1->Open();
		//ConstructCMD(serialPort1, CMDtype::GETGPS);
		Commands::Class_0x0B::GetGPSPosition(NULL);
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
		//ConstructCMD(serialPort1, eGPS);
		Commands::Class_0x0B::SetGPSPowerState(NULL, eGPS);
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
					//ConstructCMD(serialPort1, CMDtype::GETGPS);
					Commands::Class_0x0B::GetGPSPosition(NULL);
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
					//ConstructCMD(serialPort1, (uint32_t)3000);
					Commands::Class_0x0C::WakeUp(NULL, 3000);
			}
			catch (IO::IOException ^ioexception) {
				proglog->AppendText("\r\n" + ioexception->Message);
			}
			//sPointReciver->WaitOne(4000);
		}
	}
	//T=1c
	else if (sys_task_counter % 10 == 0) {
		if (this->Get_Dev->Checked) get_device_progress->Value++;
		if (GPS_En->Checked) {
			try {
				if (serialPort1->IsOpen) {
					Commands::Class_0x0B::GetGPSStatus(NULL);
				}
			}
			catch (IO::IOException ^ioexception) {
				proglog->AppendText("\r\n" + ioexception->Message + " in sys_task_Tick.");
			}
		}
	}
	sys_task_counter++;
}

System::Void Evrika::mainform::button10_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (!serialPort1->IsOpen)
			serialPort1->Open();
		//ConstructCMD(serialPort1, CMDtype::RESET);
		Commands::Class_0x0C::ResetCC1101(NULL);
	}
	catch (IO::IOException ^ioexception) {
		textBox1->AppendText("\r\n" + ioexception->Message);
	}
}

System::Void Evrika::mainform::DCGrid_SelectionChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (DCGrid->SelectedCells->Count != 1) return;
	int row = DCGrid->SelectedCells[0]->RowIndex;
	if ((row < 0) || (Devices->Count == 0) || (row > Devices->Count - 1)) return;
	if (PrevSelectedRepeaterIndex == row) return;
	PrevSelectedRepeaterIndex = row;
	Commands::Class_0x0A::GetRelayState(Devices[row]->GetAddr());
	Sleep(300);
	Commands::Class_0x0A::GetVoltage(Devices[row]->GetAddr());
}

System::Void Evrika::mainform::RelayStatCheckBox_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if ((PrevSelectedRepeaterIndex<0 || PrevSelectedRepeaterIndex>Devices->Count) || (Devices->Count < 1)) return;
	Commands::Class_0x0A::SetRelayState(Devices[PrevSelectedRepeaterIndex]->GetAddr(), RelayStatCheckBox->Checked);
}

System::Void Evrika::mainform::ResetRepeaterBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if ((PrevSelectedRepeaterIndex<0 || PrevSelectedRepeaterIndex>Devices->Count) || (Devices->Count < 1)) return;
	Commands::Class_0x0A::ProgrammReset(Devices[PrevSelectedRepeaterIndex]->GetAddr());
}

System::Void Evrika::mainform::button12_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Commands::Class_0x0D::StartSearchRepeaters(NULL);
	CurrentActionLbl->Text = "Поиск ретрансляторов...";
}

System::Void Evrika::mainform::ResetRepeatersBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Commands::Class_0x0D::GlobalResetRepeaters(NULL);
}

Evrika::mainform::MyPosition::MyPosition()
{
	lat = gcnew KalmanFilter();
	lng = gcnew KalmanFilter();
	HDOP = gcnew KalmanFilter();
	Height = gcnew KalmanFilter();
	bFirstRead = true;
}

Evrika::mainform::MyPosition::~MyPosition()
{
	delete lat;
	delete lng;
	delete HDOP;
	delete Height;
}

void Evrika::mainform::MyPosition::SetState(double _lat, double _lng, double _HDOP, double _Height)
{
	lat->SetState(_lat, 0.1);
	lng->SetState(_lng, 0.1);
	HDOP->SetState(_HDOP, 0.1);
	Height->SetState(_Height, 0.1);
}

void Evrika::mainform::MyPosition::Correct(double _lat, double _lng, double _HDOP, double _Height)
{
	lat->Correct(_lat);
	lng->Correct(_lng);
	HDOP->Correct(_HDOP);
	Height->Correct(_Height);
}

void Evrika::mainform::MyPosition::GetState(double * _lat, double * _lng, double * _HDOP, double * _Height)
{
	*_lat = lat->State;
	*_lng = lng->State;
	*_HDOP = HDOP->State;
	*_Height = Height->State;
}

void Evrika::mainform::MyPosition::GetPos(double * _lat, double * _lng)
{
	*_lat = lat->State;
	*_lng = lng->State;
}
