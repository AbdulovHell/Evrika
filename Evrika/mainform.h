#pragma once
#include <stdint.h>
#define MESSAGE_CLASS 6
#define MESSAGE_ID 7
namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace GMap::NET;
	using namespace GMap::NET::WindowsForms;
	using namespace GMap::NET::WindowsForms::Markers;
	using namespace std;
	using namespace System::Threading;

	ref class mainform;
	ref class mapform;
	ref class settings;
	ref class loading_page;
	ref class KalmanFilter;
	ref class geoPoint;
	ref class Device;
	ref class Event;
	ref class Repeater;
	ref class RadioTag;
	/// <summary>
	/// Сводка для mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		mainform(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~mainform()
		{
			if (serialPort1->IsOpen)
				serialPort1->Close();
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button9;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::TextBox^  proglog;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  whatCOM;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  savemap;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::DataGridView^  RadioTagsGrid;

	private: System::Windows::Forms::ToolStripMenuItem^  settings_menu;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;

	private: System::Windows::Forms::Timer^  sys_task;

	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripProgressBar^  get_device_progress;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::DataGridView^  EventsGrid;







	private: System::Windows::Forms::ToolStripMenuItem^  SaveSessionBtn;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadSessionBtn;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  подключениеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ConnectDC;
	private: System::Windows::Forms::ToolStripMenuItem^  ConnCheck;
	private: System::Windows::Forms::ToolStripMenuItem^  кэшToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ExportMapBtn;
	private: System::Windows::Forms::ToolStripMenuItem^  ImportMapBtn;

	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel5;
	private: System::Windows::Forms::ToolStripStatusLabel^  ImageIndication;





	private: System::Windows::Forms::Label^  label10;





	private: System::Windows::Forms::DataGridView^  DCGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  WorkMode;
	private: System::Windows::Forms::CheckBox^  RelayStatCheckBox;
	private: System::Windows::Forms::Button^  ResetRepeaterBtn;
	private: System::Windows::Forms::Button^  SearchRepeatersBtn;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel6;
	private: System::Windows::Forms::ToolStripStatusLabel^  CurrentActionLbl;
	private: System::Windows::Forms::Button^  ResetRepeatersBtn;
	private: System::Windows::Forms::Label^  vbattLbl;
	private: System::Windows::Forms::Label^  vchargerLbl;
	private: System::Windows::Forms::Label^  vlna1Lbl;
	private: System::Windows::Forms::Label^  vlna2Lbl;
	private: System::Windows::Forms::Label^  vcoreLbl;
	private: System::Windows::Forms::Label^  vtempLbl;
	private: System::Windows::Forms::GroupBox^  RepeaterParamBox;
	private: System::Windows::Forms::CheckBox^  GPSOnOff;
	private: System::Windows::Forms::ProgressBar^  GetRepParamProgress;
	private: System::Windows::Forms::Label^  GPSStatLbl;
	private: System::Windows::Forms::CheckBox^  GPSAntenna;
	private: System::Windows::Forms::Button^  WakeUpRadioTagBtn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  UniqueID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SignalLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  QualityLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  BatteryLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::Button^  TagAndRepeaterResetBtn;
	private: System::Windows::Forms::GroupBox^  RadioTagParamBox;
	private: System::Windows::Forms::Label^  TimeLbl;
	private: System::Windows::Forms::Label^  ARSSILbl;
	private: System::Windows::Forms::Label^  BitrateLbl;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  UpdateTagBtn;
	private: System::Windows::Forms::CheckBox^  AutoUpdateTagChk;
	private: System::Windows::Forms::Button^  UpdateRepeaterParamBtn;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  PingModeBtn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
	private: System::Windows::Forms::GroupBox^  TagAndRepInfoBox;
	private: System::Windows::Forms::Timer^  TagAndRepInfoUpdate;
	private: System::Windows::Forms::Label^  SelectedTagDistanceLbl;
	private: System::Windows::Forms::Label^  SelectedRepeaterInfoLbl;
	private: System::Windows::Forms::Button^  DrawPointBtn;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog3;


















	private: System::Windows::Forms::ListBox^  listBox1;

	private: ref class geoPoint {                 //Класс geoPoint для хранения координат точек
	private:
		double _lat, _lng, _r;	//градусы, км в градусах					
		System::String ^_name;
	public:
		geoPoint()
		{
		}
		geoPoint(double lat, double lng, double r_m)
		{
			_lat = lat;
			_lng = lng;
			_r = r_m;
		}
		geoPoint(double lat, double lng, double r_m, System::String ^name)
		{
			_lat = lat;
			_lng = lng;
			_r = r_m;
			_name = name;
		}
		geoPoint(System::String ^name)
		{
			_lat = 0;
			_lng = 0;
			_r = 0;
			_name = name;
		}
		geoPoint(const geoPoint %c)   // конструктор копирования
		{
			_lat = c._lat;
			_lng = c._lng;
			_name = c._name;
			_r = c._r;
		}
		void set_point(double lat, double lng, double r_m) //метод присваивания
		{
			_lat = lat;
			_lng = lng;
			_r = r_m;
		}
		double get_lat()                    //возвращает координату х точки
		{
			return _lat;
		}
		double get_lng()                     //возвращает координату у точки
		{
			return _lng;
		}
		double get_r()
		{
			return _r;
		}
		System::String^ get_name() {
			return _name;
		}
		PointLatLng get_pointLatLng() {
			return PointLatLng(_lat, _lng);
		}
		static double RadiansToDegrees(double rads) {
			return rads*(180.0 / Math::PI);
		}
		static double DegreesToRadians(double degr) {
			return degr*(Math::PI / 180.0);
		}
		static List<PointLatLng>^ CreateCircle(PointLatLng geoPoint, double radius_m) {
			int segments = 360;
			List<PointLatLng>^ gpollist = gcnew List<PointLatLng>();

			for (int i = 0; i < segments; i++)
				gpollist->Add(geoPoint::FindPointAtDistanceFrom(geoPoint, 2 * Math::PI*i / segments, radius_m / 1000));

			return gpollist;
		}
		List<PointLatLng>^ CreateCircle() {
			PointLatLng geoPoint = get_pointLatLng();
			double radius_km = get_r() / 1000;
			int segments = 360;
			List<PointLatLng>^ gpollist = gcnew List<PointLatLng>();

			for (int i = 0; i < segments; i++)
				gpollist->Add(FindPointAtDistanceFrom(geoPoint, 2 * Math::PI*i / segments, radius_km));

			return gpollist;
		}
		static PointLatLng FindPointAtDistanceFrom(PointLatLng^ startPoint, double initialBearingRadians, double distanceKilometres) {
			const double radiusEarthKilometres = 6371.01;
			double distRatio = distanceKilometres / radiusEarthKilometres;
			double distRatioSine = Math::Sin(distRatio);
			double distRatioCosine = Math::Cos(distRatio);

			double startLatRad = DegreesToRadians(startPoint->Lat);
			double startLonRad = DegreesToRadians(startPoint->Lng);

			double startLatCos = Math::Cos(startLatRad);
			double startLatSin = Math::Sin(startLatRad);

			double endLatRads = Math::Asin((startLatSin*distRatioCosine) + (startLatCos*distRatioSine*Math::Cos(initialBearingRadians)));

			double endLonRads = startLonRad + Math::Atan2(
				Math::Sin(initialBearingRadians)*distRatioSine*startLatCos,
				distRatioCosine - startLatSin*Math::Sin(endLatRads));

			return PointLatLng(RadiansToDegrees(endLatRads), RadiansToDegrees(endLonRads));
		}
		static double GetDistanceToPointFrom(PointLatLng^ startPoint, PointLatLng^ endPoint) {
			double distanceKilometres = 0;
			const double radiusEarthKilometres = 6371.01;
			double startLatRad = DegreesToRadians(startPoint->Lat);
			double startLonRad = DegreesToRadians(startPoint->Lng);
			double endLatRad = DegreesToRadians(endPoint->Lat);
			double endLonRad = DegreesToRadians(endPoint->Lng);
			double temp = Math::Sin(startLatRad)*Math::Sin(endLatRad) + Math::Cos(startLatRad)*Math::Cos(endLatRad)*Math::Cos(startLonRad - endLonRad);
			double d = Math::Acos(temp);
			distanceKilometres = d*radiusEarthKilometres;
			return distanceKilometres;
		}
		static List<PointLatLng>^ SortPoints_distance(List<PointLatLng>^ sorting_point) {
			return sorting_point;
			double temp_dist = 0, min_dist = 0;
			int min_index = -1, size = sorting_point->Count;
			PointLatLng tempPoint;
			List<PointLatLng>^ sorted_point = gcnew List<PointLatLng>;

			sorted_point->Add(sorting_point[0]);
			sorting_point->RemoveAt(0);
			for (int i = 0; i < size - 1; i++) {
				for (int j = 0; j < size; j++) {
					temp_dist = Math::Sqrt(
						Math::Pow(Math::Abs(sorting_point[i].Lat - sorting_point[j].Lat), 2) +
						Math::Pow(Math::Abs(sorting_point[i].Lng - sorting_point[j].Lng), 2));
					if (min_dist == 0)
					{
						min_dist = temp_dist;
						min_index = j;
					}
					else if (temp_dist < min_dist) {
						min_dist = temp_dist;
						min_index = j;
					}
				}
				sorted_point->Add(sorting_point[min_index]);
				sorting_point->RemoveAt(min_index);
				min_index = -1;
				min_dist = 0;
			}
			sorted_point->Add(sorting_point[0]);
			sorting_point->RemoveAt(0);
			return sorted_point;
		}
	};
			 ref class Line                 //Класс line для хранения коэффициентов A, B, C уравнения прямой на плоскости
			 {
			 private:
				 double A, B, C;
			 public:
				 Line()
				 {
				 }
				 Line(double a, double b, double c)
				 {
					 A = a;
					 B = b;
					 C = c;
				 }
				 Line(PointLatLng P0, PointLatLng P1)
				 {
					 A = P1.Lng - P0.Lng;
					 B = P0.Lat - P1.Lat;
					 C = 0 - B * P0.Lng - A * P0.Lat;
				 }
				 void set_line(PointLatLng ^ P0, PointLatLng ^ P1)          //метод составляет уравнение прямой по двум точкам и сохраняет коэффициенты
				 {
					 A = P1->Lng - P0->Lng;
					 B = P0->Lat - P1->Lat;
					 C = 0 - B * P0->Lng - A * P0->Lat;
				 }
				 int check_point(PointLatLng ^ P0)                  //метод для проверки положения точки относительно прямой
				 {
					 if (A* P0->Lat + B * P0->Lng + C == 0)
					 {
						 return 0;                        // Возвращает 0, если точка лежит на прямой
					 }
					 else
						 if (A* P0->Lat + B * P0->Lng + C < 0)
						 {
							 return -1;                   // Возвращает -1, если точка лежит в правой полуплоскости (условно)
						 }
						 else
							 return 1;                    // Возвращает 1, если точка лежит в левой полуплоскости (условно)
				 }


				 double get_A()  //Возвращает коэффициет A
				 {
					 return A;
				 }
				 double get_B()   //Возвращает коэффициет B
				 {
					 return B;
				 }
				 double get_C()  //Возвращает коэффициет C
				 {
					 return C;
				 }
			 };
	public:	 ref class MyPosition {
		KalmanFilter^ lat;
		KalmanFilter^ lng;
		KalmanFilter^ HDOP;
		KalmanFilter^ Height;
	public:
		bool bFirstRead;

		MyPosition();
		~MyPosition();
		void SetState(double _lat, double _lng, double _HDOP, double _Height);
		void Correct(double _lat, double _lng, double _HDOP, double _Height);
		void GetState(double* _lat, double* _lng, double* _HDOP, double* _Height);
		void GetPos(double* _lat, double* _lng);
	};
	public:
		void SetTimer(bool en);
		void WriteLog(String^ message);
		void AddNewPoint(double lat, double lng, double m);
		void UpdateMapPos();
		bool CheckSum(cli::array<wchar_t>^ rbuf);
		void UpdateRadioTagsList();
		void UpdateRepeatersList();
		void UpdateEventList();
		void ParseDeviceBuffer(cli::array<wchar_t>^ rbuf);

		static mainform^ my_handle;
		MyPosition^ myPos;
	private:
		void Triangulate(geoPoint^ circle1, geoPoint^ circle2);
		void Triangulate(geoPoint^ circle1, geoPoint^ circle2, List<PointLatLng>^ twoPoints);
		int factorial(int n);
		List<PointLatLng>^ SortPoint_Line(List<PointLatLng>^ in_p);
		bool inTheArea(PointLatLng point);
		bool inTheArea(PointLatLng point, int i, int j, int k);
		void metod_5();
		void ParseToPoint(cli::array<wchar_t>^ buf);
		void WriteToComStat(String^ str);
		void CheckComConn();
		void EnumCOMs();
		System::String^ Quality(int q);
		int RangeRandInt(int min, int max);
		double RangeRandDouble(double min, double max);
		void ParamRequest();
		void IncrementProgress();
		void MakeVisible(bool state);
		void GetTagParam();
		void SetCurrentActionLblText(String^ str);

		Evrika::mapform^ mapform;
		static Evrika::settings^ settings_window;
		Evrika::loading_page^ ldng_wnd;
		String^ ourPort;
		bool eGPS;
		KalmanFilter^ mid_cycles;
		KalmanFilter^ ftime;

		cli::array<GMarkerGoogle^> ^markers;
		//long lCoordsCount;
		bool isOurCom;
		//bool notLoaded;
		List<geoPoint^> ^MyCoords;
		List<Repeater^>^ Devices;
		Repeater^ SelectedDevice;
		List<Event^>^ Events;
		//int cDevices;
		GMapControl^ map;
		GMapOverlay ^mrkrOvrl;
		Semaphore ^sEnumCom;
		Semaphore^ sPointReciver;
		Semaphore^ ParamReciver;
		GMapOverlay ^areaOvrl;
		GMapOverlay^ myPosOvrl;
		bool LastStateIsOpen;
		bool GPS_KnownPos = false;
		bool my_pos_accepted = false;
		bool device_get = false;
		bool DoExport = false;
		cli::array<double>^ collection0;
		cli::array<double>^ collection1;
		cli::array<double>^ collection2;
		int LastBandWidth = -1;
		List<TextBox^>^ logs;
		uint64_t sys_task_counter = 0;
		int PrevSelectedTagIndex = -1;
		uint8_t PrevCountFindedRepeaters = 0;
		uint8_t PrevCountFindedRadioTags = 0;
		Thread^ RadioTagAutoUpdateThrd;
		bool RadioTagAutoUpdateEnabled = false;
		Semaphore^ RadioTagUpdateEnabledSemaphore;
		Semaphore^ RadioTagUpdateParam;
		//test
		double temp2 = 0;
		uint64_t mid2 = 0;
		int i2 = 0, i3 = 0;
		double temp3 = 0;
		uint64_t mid3 = 0;

		double min_time, max_time;
		int first = 1;
		double min_atime, max_atime;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->listBox1 = (gcnew System::Windows::Forms::ListBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->button5 = (gcnew System::Windows::Forms::Button());
				 this->button4 = (gcnew System::Windows::Forms::Button());
				 this->button3 = (gcnew System::Windows::Forms::Button());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->button6 = (gcnew System::Windows::Forms::Button());
				 this->button9 = (gcnew System::Windows::Forms::Button());
				 this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
				 this->proglog = (gcnew System::Windows::Forms::TextBox());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->ImageIndication = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->whatCOM = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->get_device_progress = (gcnew System::Windows::Forms::ToolStripProgressBar());
				 this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel5 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel6 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->CurrentActionLbl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->savemap = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->SaveSessionBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->LoadSessionBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->подключениеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ConnectDC = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ConnCheck = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->кэшToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ExportMapBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ImportMapBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->settings_menu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->RadioTagsGrid = (gcnew System::Windows::Forms::DataGridView());
				 this->UniqueID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->SignalLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->QualityLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->BatteryLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->TagAndRepInfoBox = (gcnew System::Windows::Forms::GroupBox());
				 this->DrawPointBtn = (gcnew System::Windows::Forms::Button());
				 this->SelectedRepeaterInfoLbl = (gcnew System::Windows::Forms::Label());
				 this->SelectedTagDistanceLbl = (gcnew System::Windows::Forms::Label());
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->button8 = (gcnew System::Windows::Forms::Button());
				 this->button7 = (gcnew System::Windows::Forms::Button());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->RadioTagParamBox = (gcnew System::Windows::Forms::GroupBox());
				 this->PingModeBtn = (gcnew System::Windows::Forms::Button());
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->AutoUpdateTagChk = (gcnew System::Windows::Forms::CheckBox());
				 this->UpdateTagBtn = (gcnew System::Windows::Forms::Button());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->BitrateLbl = (gcnew System::Windows::Forms::Label());
				 this->ARSSILbl = (gcnew System::Windows::Forms::Label());
				 this->TimeLbl = (gcnew System::Windows::Forms::Label());
				 this->TagAndRepeaterResetBtn = (gcnew System::Windows::Forms::Button());
				 this->WakeUpRadioTagBtn = (gcnew System::Windows::Forms::Button());
				 this->RepeaterParamBox = (gcnew System::Windows::Forms::GroupBox());
				 this->UpdateRepeaterParamBtn = (gcnew System::Windows::Forms::Button());
				 this->GPSAntenna = (gcnew System::Windows::Forms::CheckBox());
				 this->GPSStatLbl = (gcnew System::Windows::Forms::Label());
				 this->GetRepParamProgress = (gcnew System::Windows::Forms::ProgressBar());
				 this->GPSOnOff = (gcnew System::Windows::Forms::CheckBox());
				 this->RelayStatCheckBox = (gcnew System::Windows::Forms::CheckBox());
				 this->vlna1Lbl = (gcnew System::Windows::Forms::Label());
				 this->vtempLbl = (gcnew System::Windows::Forms::Label());
				 this->vchargerLbl = (gcnew System::Windows::Forms::Label());
				 this->ResetRepeaterBtn = (gcnew System::Windows::Forms::Button());
				 this->vcoreLbl = (gcnew System::Windows::Forms::Label());
				 this->vbattLbl = (gcnew System::Windows::Forms::Label());
				 this->vlna2Lbl = (gcnew System::Windows::Forms::Label());
				 this->ResetRepeatersBtn = (gcnew System::Windows::Forms::Button());
				 this->SearchRepeatersBtn = (gcnew System::Windows::Forms::Button());
				 this->DCGrid = (gcnew System::Windows::Forms::DataGridView());
				 this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->WorkMode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				 this->EventsGrid = (gcnew System::Windows::Forms::DataGridView());
				 this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->sys_task = (gcnew System::Windows::Forms::Timer(this->components));
				 this->saveFileDialog2 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->TagAndRepInfoUpdate = (gcnew System::Windows::Forms::Timer(this->components));
				 this->saveFileDialog3 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->groupBox1->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->statusStrip1->SuspendLayout();
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RadioTagsGrid))->BeginInit();
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->TagAndRepInfoBox->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 this->RadioTagParamBox->SuspendLayout();
				 this->RepeaterParamBox->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DCGrid))->BeginInit();
				 this->tabPage3->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EventsGrid))->BeginInit();
				 this->SuspendLayout();
				 this->button1->Location = System::Drawing::Point(6, 6);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(169, 43);
				 this->button1->TabIndex = 0;
				 this->button1->Text = L"Скрыть/Показать карту";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
				 this->listBox1->FormattingEnabled = true;
				 this->listBox1->Location = System::Drawing::Point(180, 6);
				 this->listBox1->Name = L"listBox1";
				 this->listBox1->Size = System::Drawing::Size(114, 303);
				 this->listBox1->TabIndex = 1;
				 this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::listBox1_SelectedIndexChanged);
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(6, 16);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(75, 13);
				 this->label1->TabIndex = 2;
				 this->label1->Text = L"Центр карты:";
				 this->groupBox1->Controls->Add(this->label4);
				 this->groupBox1->Controls->Add(this->textBox1);
				 this->groupBox1->Controls->Add(this->button2);
				 this->groupBox1->Controls->Add(this->label3);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->label1);
				 this->groupBox1->Location = System::Drawing::Point(6, 55);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(169, 130);
				 this->groupBox1->TabIndex = 3;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"groupBox1";
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(6, 78);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(60, 13);
				 this->label4->TabIndex = 7;
				 this->label4->Text = L"Радиус, м:";
				 this->textBox1->Location = System::Drawing::Point(72, 75);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(91, 20);
				 this->textBox1->TabIndex = 6;
				 this->textBox1->Text = L"1";
				 this->button2->Location = System::Drawing::Point(6, 101);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(157, 23);
				 this->button2->TabIndex = 5;
				 this->button2->Text = L"Сохранить";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &mainform::button2_Click);
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(6, 56);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(35, 13);
				 this->label3->TabIndex = 4;
				 this->label3->Text = L"label3";
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(6, 38);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(35, 13);
				 this->label2->TabIndex = 3;
				 this->label2->Text = L"label2";
				 this->groupBox2->Controls->Add(this->button5);
				 this->groupBox2->Controls->Add(this->button4);
				 this->groupBox2->Controls->Add(this->button3);
				 this->groupBox2->Controls->Add(this->label7);
				 this->groupBox2->Controls->Add(this->label6);
				 this->groupBox2->Controls->Add(this->label5);
				 this->groupBox2->Location = System::Drawing::Point(300, 6);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(182, 218);
				 this->groupBox2->TabIndex = 4;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"groupBox2";
				 this->button5->Location = System::Drawing::Point(13, 158);
				 this->button5->Name = L"button5";
				 this->button5->Size = System::Drawing::Size(157, 23);
				 this->button5->TabIndex = 5;
				 this->button5->Text = L"Удалить";
				 this->button5->UseVisualStyleBackColor = true;
				 this->button5->Click += gcnew System::EventHandler(this, &mainform::button5_Click);
				 this->button4->Location = System::Drawing::Point(13, 129);
				 this->button4->Name = L"button4";
				 this->button4->Size = System::Drawing::Size(157, 23);
				 this->button4->TabIndex = 4;
				 this->button4->Text = L"Точка";
				 this->button4->UseVisualStyleBackColor = true;
				 this->button4->Click += gcnew System::EventHandler(this, &mainform::button4_Click);
				 this->button3->Location = System::Drawing::Point(13, 100);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(157, 23);
				 this->button3->TabIndex = 3;
				 this->button3->Text = L"Окружность";
				 this->button3->UseVisualStyleBackColor = true;
				 this->button3->Click += gcnew System::EventHandler(this, &mainform::button3_Click);
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(10, 74);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(35, 13);
				 this->label7->TabIndex = 2;
				 this->label7->Text = L"label7";
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(10, 49);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(35, 13);
				 this->label6->TabIndex = 1;
				 this->label6->Text = L"label6";
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(10, 23);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(35, 13);
				 this->label5->TabIndex = 0;
				 this->label5->Text = L"label5";
				 this->button6->Location = System::Drawing::Point(5, 191);
				 this->button6->Name = L"button6";
				 this->button6->Size = System::Drawing::Size(169, 23);
				 this->button6->TabIndex = 5;
				 this->button6->Text = L"Очистить карту";
				 this->button6->UseVisualStyleBackColor = true;
				 this->button6->Click += gcnew System::EventHandler(this, &mainform::button6_Click);
				 this->button9->Location = System::Drawing::Point(99, 220);
				 this->button9->Name = L"button9";
				 this->button9->Size = System::Drawing::Size(75, 21);
				 this->button9->TabIndex = 9;
				 this->button9->Text = L"Triangulate";
				 this->button9->UseVisualStyleBackColor = true;
				 this->button9->Click += gcnew System::EventHandler(this, &mainform::button9_Click);
				 this->serialPort1->BaudRate = 115200;
				 this->serialPort1->ParityReplace = static_cast<System::Byte>(255);
				 this->serialPort1->PortName = L"COM5";
				 this->serialPort1->ReadBufferSize = 512;
				 this->serialPort1->ReadTimeout = 1000;
				 this->serialPort1->ReceivedBytesThreshold = 5;
				 this->serialPort1->WriteBufferSize = 512;
				 this->serialPort1->WriteTimeout = 1000;
				 this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &mainform::serialPort1_DataReceived);
				 this->proglog->Location = System::Drawing::Point(1, 324);
				 this->proglog->Multiline = true;
				 this->proglog->Name = L"proglog";
				 this->proglog->ReadOnly = true;
				 this->proglog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->proglog->Size = System::Drawing::Size(482, 130);
				 this->proglog->TabIndex = 13;
				 this->proglog->Text = L"Старт...";
				 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
					 this->ImageIndication, this->whatCOM,
						 this->toolStripStatusLabel1, this->get_device_progress, this->toolStripStatusLabel2, this->toolStripStatusLabel3, this->toolStripStatusLabel4,
						 this->toolStripStatusLabel5, this->toolStripStatusLabel6, this->CurrentActionLbl
				 });
				 this->statusStrip1->Location = System::Drawing::Point(0, 735);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(882, 22);
				 this->statusStrip1->TabIndex = 14;
				 this->statusStrip1->Text = L"statusStrip1";
				 this->ImageIndication->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->ImageIndication->Name = L"ImageIndication";
				 this->ImageIndication->Size = System::Drawing::Size(0, 17);
				 this->whatCOM->Name = L"whatCOM";
				 this->whatCOM->Size = System::Drawing::Size(40, 17);
				 this->whatCOM->Text = L"COM\?";
				 this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
				 this->toolStripStatusLabel1->Size = System::Drawing::Size(10, 17);
				 this->toolStripStatusLabel1->Text = L"|";
				 this->get_device_progress->Maximum = 10;
				 this->get_device_progress->Name = L"get_device_progress";
				 this->get_device_progress->Size = System::Drawing::Size(100, 16);
				 this->get_device_progress->Step = 1;
				 this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
				 this->toolStripStatusLabel2->Size = System::Drawing::Size(10, 17);
				 this->toolStripStatusLabel2->Text = L"|";
				 this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
				 this->toolStripStatusLabel3->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel3->Text = L"toolStripStatusLabel3";
				 this->toolStripStatusLabel3->Visible = false;
				 this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
				 this->toolStripStatusLabel4->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel4->Text = L"toolStripStatusLabel4";
				 this->toolStripStatusLabel4->Visible = false;
				 this->toolStripStatusLabel5->Name = L"toolStripStatusLabel5";
				 this->toolStripStatusLabel5->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel5->Text = L"toolStripStatusLabel5";
				 this->toolStripStatusLabel5->Visible = false;
				 this->toolStripStatusLabel6->Name = L"toolStripStatusLabel6";
				 this->toolStripStatusLabel6->Size = System::Drawing::Size(10, 17);
				 this->toolStripStatusLabel6->Text = L"|";
				 this->CurrentActionLbl->Name = L"CurrentActionLbl";
				 this->CurrentActionLbl->Size = System::Drawing::Size(10, 17);
				 this->CurrentActionLbl->Text = L" ";
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->файлToolStripMenuItem,
						 this->подключениеToolStripMenuItem, this->кэшToolStripMenuItem, this->settings_menu
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(882, 24);
				 this->menuStrip1->TabIndex = 16;
				 this->menuStrip1->Text = L"menuStrip1";
				 this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->savemap,
						 this->SaveSessionBtn, this->LoadSessionBtn
				 });
				 this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
				 this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
				 this->файлToolStripMenuItem->Text = L"Файл";
				 this->savemap->Name = L"savemap";
				 this->savemap->Size = System::Drawing::Size(258, 22);
				 this->savemap->Text = L"Сохранить карту в *.bmp ...";
				 this->savemap->Click += gcnew System::EventHandler(this, &mainform::savemap_Click);
				 this->SaveSessionBtn->Name = L"SaveSessionBtn";
				 this->SaveSessionBtn->Size = System::Drawing::Size(258, 22);
				 this->SaveSessionBtn->Text = L"Сохранить текущую сессию...";
				 this->SaveSessionBtn->Click += gcnew System::EventHandler(this, &mainform::save_events);
				 this->LoadSessionBtn->Name = L"LoadSessionBtn";
				 this->LoadSessionBtn->Size = System::Drawing::Size(258, 22);
				 this->LoadSessionBtn->Text = L"Загрузить сохраненную сессию...";
				 this->LoadSessionBtn->Click += gcnew System::EventHandler(this, &mainform::load_session);
				 this->подключениеToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->ConnectDC,
						 this->ConnCheck
				 });
				 this->подключениеToolStripMenuItem->Name = L"подключениеToolStripMenuItem";
				 this->подключениеToolStripMenuItem->Size = System::Drawing::Size(86, 20);
				 this->подключениеToolStripMenuItem->Text = L"Соединение";
				 this->ConnectDC->Name = L"ConnectDC";
				 this->ConnectDC->Size = System::Drawing::Size(207, 22);
				 this->ConnectDC->Text = L"Переподключение к ДЦ";
				 this->ConnectDC->Click += gcnew System::EventHandler(this, &mainform::переподключениеКДЦToolStripMenuItem_Click);
				 this->ConnCheck->Name = L"ConnCheck";
				 this->ConnCheck->Size = System::Drawing::Size(207, 22);
				 this->ConnCheck->Text = L"Проверка соединения";
				 this->ConnCheck->Click += gcnew System::EventHandler(this, &mainform::проверкаСоединенияToolStripMenuItem_Click);
				 this->кэшToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->ExportMapBtn,
						 this->ImportMapBtn
				 });
				 this->кэшToolStripMenuItem->Name = L"кэшToolStripMenuItem";
				 this->кэшToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				 this->кэшToolStripMenuItem->Text = L"Карта";
				 this->ExportMapBtn->Name = L"ExportMapBtn";
				 this->ExportMapBtn->Size = System::Drawing::Size(202, 22);
				 this->ExportMapBtn->Text = L"Экспорт файла карты...";
				 this->ExportMapBtn->Click += gcnew System::EventHandler(this, &mainform::ExportMapBtn_Click);
				 this->ImportMapBtn->Name = L"ImportMapBtn";
				 this->ImportMapBtn->Size = System::Drawing::Size(202, 22);
				 this->ImportMapBtn->Text = L"Импорт файла карты...";
				 this->ImportMapBtn->Click += gcnew System::EventHandler(this, &mainform::ImportMapBtn_Click);
				 this->settings_menu->Name = L"settings_menu";
				 this->settings_menu->Size = System::Drawing::Size(88, 20);
				 this->settings_menu->Text = L"Настройки...";
				 this->settings_menu->Click += gcnew System::EventHandler(this, &mainform::настройкиToolStripMenuItem_Click);
				 this->saveFileDialog1->DefaultExt = L"bmp";
				 this->saveFileDialog1->Filter = L"Bitmap|*.bmp|Все файлы|*.*";
				 this->saveFileDialog1->SupportMultiDottedExtensions = true;
				 this->RadioTagsGrid->AllowUserToAddRows = false;
				 this->RadioTagsGrid->AllowUserToDeleteRows = false;
				 this->RadioTagsGrid->AllowUserToResizeRows = false;
				 this->RadioTagsGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->RadioTagsGrid->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->RadioTagsGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->RadioTagsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->RadioTagsGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
					 this->UniqueID, this->SignalLVL,
						 this->QualityLVL, this->BatteryLVL, this->Column2
				 });
				 this->RadioTagsGrid->Location = System::Drawing::Point(500, 3);
				 this->RadioTagsGrid->MultiSelect = false;
				 this->RadioTagsGrid->Name = L"RadioTagsGrid";
				 this->RadioTagsGrid->ReadOnly = true;
				 this->RadioTagsGrid->RowHeadersVisible = false;
				 this->RadioTagsGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
				 this->RadioTagsGrid->Size = System::Drawing::Size(371, 345);
				 this->RadioTagsGrid->TabIndex = 17;
				 this->RadioTagsGrid->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainform::open_device);
				 this->RadioTagsGrid->SelectionChanged += gcnew System::EventHandler(this, &mainform::RadioTagsGrid_SelectionChanged);
				 this->UniqueID->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
				 this->UniqueID->Frozen = true;
				 this->UniqueID->HeaderText = L"Адрес";
				 this->UniqueID->Name = L"UniqueID";
				 this->UniqueID->ReadOnly = true;
				 this->UniqueID->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->UniqueID->Width = 92;
				 this->SignalLVL->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
				 this->SignalLVL->Frozen = true;
				 this->SignalLVL->HeaderText = L"Уровень сигнала";
				 this->SignalLVL->Name = L"SignalLVL";
				 this->SignalLVL->ReadOnly = true;
				 this->SignalLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->SignalLVL->Width = 65;
				 this->QualityLVL->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
				 this->QualityLVL->Frozen = true;
				 this->QualityLVL->HeaderText = L"Качество приема сигнала";
				 this->QualityLVL->Name = L"QualityLVL";
				 this->QualityLVL->ReadOnly = true;
				 this->QualityLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->QualityLVL->Width = 70;
				 this->BatteryLVL->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
				 this->BatteryLVL->Frozen = true;
				 this->BatteryLVL->HeaderText = L"Уровень заряда батареи";
				 this->BatteryLVL->Name = L"BatteryLVL";
				 this->BatteryLVL->ReadOnly = true;
				 this->BatteryLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->BatteryLVL->Width = 80;
				 this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
				 this->Column2->Frozen = true;
				 this->Column2->HeaderText = L"Режим работы";
				 this->Column2->Name = L"Column2";
				 this->Column2->ReadOnly = true;
				 this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->Column2->Width = 79;
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Controls->Add(this->tabPage3);
				 this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tabControl1->Location = System::Drawing::Point(0, 24);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(882, 711);
				 this->tabControl1->TabIndex = 19;
				 this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::tabControl1_SelectedIndexChanged);
				 this->tabPage1->Controls->Add(this->TagAndRepInfoBox);
				 this->tabPage1->Controls->Add(this->checkBox1);
				 this->tabPage1->Controls->Add(this->label10);
				 this->tabPage1->Controls->Add(this->groupBox2);
				 this->tabPage1->Controls->Add(this->button1);
				 this->tabPage1->Controls->Add(this->listBox1);
				 this->tabPage1->Controls->Add(this->groupBox1);
				 this->tabPage1->Controls->Add(this->button6);
				 this->tabPage1->Controls->Add(this->button9);
				 this->tabPage1->Controls->Add(this->proglog);
				 this->tabPage1->Location = System::Drawing::Point(4, 22);
				 this->tabPage1->Name = L"tabPage1";
				 this->tabPage1->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage1->Size = System::Drawing::Size(874, 685);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Text = L"Управление";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 this->TagAndRepInfoBox->Controls->Add(this->DrawPointBtn);
				 this->TagAndRepInfoBox->Controls->Add(this->SelectedRepeaterInfoLbl);
				 this->TagAndRepInfoBox->Controls->Add(this->SelectedTagDistanceLbl);
				 this->TagAndRepInfoBox->Location = System::Drawing::Point(300, 230);
				 this->TagAndRepInfoBox->Name = L"TagAndRepInfoBox";
				 this->TagAndRepInfoBox->Size = System::Drawing::Size(182, 88);
				 this->TagAndRepInfoBox->TabIndex = 24;
				 this->TagAndRepInfoBox->TabStop = false;
				 this->TagAndRepInfoBox->Text = L"groupBox3";
				 this->DrawPointBtn->Location = System::Drawing::Point(6, 59);
				 this->DrawPointBtn->Name = L"DrawPointBtn";
				 this->DrawPointBtn->Size = System::Drawing::Size(75, 23);
				 this->DrawPointBtn->TabIndex = 2;
				 this->DrawPointBtn->Text = L"На карту";
				 this->DrawPointBtn->UseVisualStyleBackColor = true;
				 this->DrawPointBtn->Click += gcnew System::EventHandler(this, &mainform::DrawPointBtn_Click);
				 this->SelectedRepeaterInfoLbl->AutoSize = true;
				 this->SelectedRepeaterInfoLbl->Location = System::Drawing::Point(7, 35);
				 this->SelectedRepeaterInfoLbl->Name = L"SelectedRepeaterInfoLbl";
				 this->SelectedRepeaterInfoLbl->Size = System::Drawing::Size(35, 13);
				 this->SelectedRepeaterInfoLbl->TabIndex = 1;
				 this->SelectedRepeaterInfoLbl->Text = L"label8";
				 this->SelectedTagDistanceLbl->AutoSize = true;
				 this->SelectedTagDistanceLbl->Location = System::Drawing::Point(7, 20);
				 this->SelectedTagDistanceLbl->Name = L"SelectedTagDistanceLbl";
				 this->SelectedTagDistanceLbl->Size = System::Drawing::Size(35, 13);
				 this->SelectedTagDistanceLbl->TabIndex = 0;
				 this->SelectedTagDistanceLbl->Text = L"label8";
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Location = System::Drawing::Point(611, 128);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(80, 17);
				 this->checkBox1->TabIndex = 23;
				 this->checkBox1->Text = L"checkBox1";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(310, 196);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(41, 13);
				 this->label10->TabIndex = 22;
				 this->label10->Text = L"label10";
				 this->tabPage2->Controls->Add(this->button8);
				 this->tabPage2->Controls->Add(this->button7);
				 this->tabPage2->Controls->Add(this->chart1);
				 this->tabPage2->Controls->Add(this->RadioTagParamBox);
				 this->tabPage2->Controls->Add(this->TagAndRepeaterResetBtn);
				 this->tabPage2->Controls->Add(this->WakeUpRadioTagBtn);
				 this->tabPage2->Controls->Add(this->RepeaterParamBox);
				 this->tabPage2->Controls->Add(this->ResetRepeatersBtn);
				 this->tabPage2->Controls->Add(this->SearchRepeatersBtn);
				 this->tabPage2->Controls->Add(this->DCGrid);
				 this->tabPage2->Controls->Add(this->RadioTagsGrid);
				 this->tabPage2->Location = System::Drawing::Point(4, 22);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(874, 685);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Устройства";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 this->button8->Location = System::Drawing::Point(356, 354);
				 this->button8->Name = L"button8";
				 this->button8->Size = System::Drawing::Size(57, 23);
				 this->button8->TabIndex = 38;
				 this->button8->Text = L"Export";
				 this->button8->UseVisualStyleBackColor = true;
				 this->button8->Click += gcnew System::EventHandler(this, &mainform::button8_Click);
				 this->button7->Location = System::Drawing::Point(419, 354);
				 this->button7->Name = L"button7";
				 this->button7->Size = System::Drawing::Size(75, 23);
				 this->button7->TabIndex = 37;
				 this->button7->Text = L"Chart reset";
				 this->button7->UseVisualStyleBackColor = true;
				 this->button7->Click += gcnew System::EventHandler(this, &mainform::button7_Click_1);
				 chartArea2->Name = L"ChartArea1";
				 this->chart1->ChartAreas->Add(chartArea2);
				 legend2->Name = L"Legend1";
				 this->chart1->Legends->Add(legend2);
				 this->chart1->Location = System::Drawing::Point(3, 524);
				 this->chart1->Name = L"chart1";
				 series4->BorderWidth = 2;
				 series4->ChartArea = L"ChartArea1";
				 series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
				 series4->Legend = L"Legend1";
				 series4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
				 series4->Name = L"time";
				 series5->BorderWidth = 2;
				 series5->ChartArea = L"ChartArea1";
				 series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
				 series5->Legend = L"Legend1";
				 series5->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
				 series5->Name = L"a_time";
				 series6->BorderWidth = 2;
				 series6->ChartArea = L"ChartArea1";
				 series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
				 series6->Legend = L"Legend1";
				 series6->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
				 series6->Name = L"f(time)";
				 this->chart1->Series->Add(series4);
				 this->chart1->Series->Add(series5);
				 this->chart1->Series->Add(series6);
				 this->chart1->Size = System::Drawing::Size(862, 155);
				 this->chart1->TabIndex = 36;
				 this->chart1->Text = L"chart1";
				 this->RadioTagParamBox->Controls->Add(this->PingModeBtn);
				 this->RadioTagParamBox->Controls->Add(this->label12);
				 this->RadioTagParamBox->Controls->Add(this->label11);
				 this->RadioTagParamBox->Controls->Add(this->AutoUpdateTagChk);
				 this->RadioTagParamBox->Controls->Add(this->UpdateTagBtn);
				 this->RadioTagParamBox->Controls->Add(this->textBox3);
				 this->RadioTagParamBox->Controls->Add(this->textBox2);
				 this->RadioTagParamBox->Controls->Add(this->BitrateLbl);
				 this->RadioTagParamBox->Controls->Add(this->ARSSILbl);
				 this->RadioTagParamBox->Controls->Add(this->TimeLbl);
				 this->RadioTagParamBox->Location = System::Drawing::Point(500, 383);
				 this->RadioTagParamBox->Name = L"RadioTagParamBox";
				 this->RadioTagParamBox->Size = System::Drawing::Size(371, 135);
				 this->RadioTagParamBox->TabIndex = 35;
				 this->RadioTagParamBox->TabStop = false;
				 this->RadioTagParamBox->Text = L"groupBox3";
				 this->PingModeBtn->Enabled = false;
				 this->PingModeBtn->Location = System::Drawing::Point(275, 13);
				 this->PingModeBtn->Name = L"PingModeBtn";
				 this->PingModeBtn->Size = System::Drawing::Size(90, 23);
				 this->PingModeBtn->TabIndex = 9;
				 this->PingModeBtn->Text = L"Пеленгация";
				 this->PingModeBtn->UseVisualStyleBackColor = true;
				 this->label12->AutoSize = true;
				 this->label12->Location = System::Drawing::Point(7, 116);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(41, 13);
				 this->label12->TabIndex = 8;
				 this->label12->Text = L"label12";
				 this->label12->Click += gcnew System::EventHandler(this, &mainform::label12_Click);
				 this->label11->AutoSize = true;
				 this->label11->Location = System::Drawing::Point(80, 54);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(41, 13);
				 this->label11->TabIndex = 7;
				 this->label11->Text = L"label11";
				 this->AutoUpdateTagChk->AutoSize = true;
				 this->AutoUpdateTagChk->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->AutoUpdateTagChk->Location = System::Drawing::Point(234, 110);
				 this->AutoUpdateTagChk->Name = L"AutoUpdateTagChk";
				 this->AutoUpdateTagChk->Size = System::Drawing::Size(50, 17);
				 this->AutoUpdateTagChk->TabIndex = 6;
				 this->AutoUpdateTagChk->Text = L"Авто";
				 this->AutoUpdateTagChk->UseVisualStyleBackColor = true;
				 this->AutoUpdateTagChk->CheckedChanged += gcnew System::EventHandler(this, &mainform::AutoUpdateTagChk_CheckedChanged);
				 this->UpdateTagBtn->Location = System::Drawing::Point(290, 106);
				 this->UpdateTagBtn->Name = L"UpdateTagBtn";
				 this->UpdateTagBtn->Size = System::Drawing::Size(75, 23);
				 this->UpdateTagBtn->TabIndex = 5;
				 this->UpdateTagBtn->Text = L"Обновить";
				 this->UpdateTagBtn->UseVisualStyleBackColor = true;
				 this->UpdateTagBtn->Click += gcnew System::EventHandler(this, &mainform::UpdateTagBtn_Click);
				 this->textBox3->Location = System::Drawing::Point(113, 85);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->Size = System::Drawing::Size(100, 20);
				 this->textBox3->TabIndex = 4;
				 this->textBox3->Text = L"26";
				 this->textBox2->Location = System::Drawing::Point(7, 85);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(100, 20);
				 this->textBox2->TabIndex = 3;
				 this->textBox2->Text = L"1,4";
				 this->BitrateLbl->AutoSize = true;
				 this->BitrateLbl->Location = System::Drawing::Point(10, 54);
				 this->BitrateLbl->Name = L"BitrateLbl";
				 this->BitrateLbl->Size = System::Drawing::Size(41, 13);
				 this->BitrateLbl->TabIndex = 2;
				 this->BitrateLbl->Text = L"label12";
				 this->ARSSILbl->AutoSize = true;
				 this->ARSSILbl->Location = System::Drawing::Point(10, 37);
				 this->ARSSILbl->Name = L"ARSSILbl";
				 this->ARSSILbl->Size = System::Drawing::Size(41, 13);
				 this->ARSSILbl->TabIndex = 1;
				 this->ARSSILbl->Text = L"label11";
				 this->TimeLbl->AutoSize = true;
				 this->TimeLbl->Location = System::Drawing::Point(7, 20);
				 this->TimeLbl->Name = L"TimeLbl";
				 this->TimeLbl->Size = System::Drawing::Size(44, 13);
				 this->TimeLbl->TabIndex = 0;
				 this->TimeLbl->Text = L"TimeLbl";
				 this->TagAndRepeaterResetBtn->Location = System::Drawing::Point(636, 354);
				 this->TagAndRepeaterResetBtn->Name = L"TagAndRepeaterResetBtn";
				 this->TagAndRepeaterResetBtn->Size = System::Drawing::Size(235, 23);
				 this->TagAndRepeaterResetBtn->TabIndex = 34;
				 this->TagAndRepeaterResetBtn->Text = L"Сброс к начальным установкам";
				 this->TagAndRepeaterResetBtn->UseVisualStyleBackColor = true;
				 this->TagAndRepeaterResetBtn->Click += gcnew System::EventHandler(this, &mainform::TagAndRepeaterResetBtn_Click);
				 this->WakeUpRadioTagBtn->Location = System::Drawing::Point(500, 354);
				 this->WakeUpRadioTagBtn->Name = L"WakeUpRadioTagBtn";
				 this->WakeUpRadioTagBtn->Size = System::Drawing::Size(130, 23);
				 this->WakeUpRadioTagBtn->TabIndex = 33;
				 this->WakeUpRadioTagBtn->Text = L"Поиск радиометок";
				 this->WakeUpRadioTagBtn->UseVisualStyleBackColor = true;
				 this->WakeUpRadioTagBtn->Click += gcnew System::EventHandler(this, &mainform::WakeUpRadioTagBtn_Click);
				 this->RepeaterParamBox->Controls->Add(this->UpdateRepeaterParamBtn);
				 this->RepeaterParamBox->Controls->Add(this->GPSAntenna);
				 this->RepeaterParamBox->Controls->Add(this->GPSStatLbl);
				 this->RepeaterParamBox->Controls->Add(this->GetRepParamProgress);
				 this->RepeaterParamBox->Controls->Add(this->GPSOnOff);
				 this->RepeaterParamBox->Controls->Add(this->RelayStatCheckBox);
				 this->RepeaterParamBox->Controls->Add(this->vlna1Lbl);
				 this->RepeaterParamBox->Controls->Add(this->vtempLbl);
				 this->RepeaterParamBox->Controls->Add(this->vchargerLbl);
				 this->RepeaterParamBox->Controls->Add(this->ResetRepeaterBtn);
				 this->RepeaterParamBox->Controls->Add(this->vcoreLbl);
				 this->RepeaterParamBox->Controls->Add(this->vbattLbl);
				 this->RepeaterParamBox->Controls->Add(this->vlna2Lbl);
				 this->RepeaterParamBox->Location = System::Drawing::Point(3, 383);
				 this->RepeaterParamBox->Name = L"RepeaterParamBox";
				 this->RepeaterParamBox->Size = System::Drawing::Size(491, 135);
				 this->RepeaterParamBox->TabIndex = 32;
				 this->RepeaterParamBox->TabStop = false;
				 this->RepeaterParamBox->Text = L"RepeaterParamBox";
				 this->UpdateRepeaterParamBtn->Location = System::Drawing::Point(410, 106);
				 this->UpdateRepeaterParamBtn->Name = L"UpdateRepeaterParamBtn";
				 this->UpdateRepeaterParamBtn->Size = System::Drawing::Size(75, 23);
				 this->UpdateRepeaterParamBtn->TabIndex = 36;
				 this->UpdateRepeaterParamBtn->Text = L"Обновить";
				 this->UpdateRepeaterParamBtn->UseVisualStyleBackColor = true;
				 this->UpdateRepeaterParamBtn->Click += gcnew System::EventHandler(this, &mainform::UpdateRepeaterParamBtn_Click);
				 this->GPSAntenna->AutoSize = true;
				 this->GPSAntenna->Location = System::Drawing::Point(191, 71);
				 this->GPSAntenna->Name = L"GPSAntenna";
				 this->GPSAntenna->Size = System::Drawing::Size(140, 17);
				 this->GPSAntenna->TabIndex = 35;
				 this->GPSAntenna->Text = L"Внешняя антенна GPS";
				 this->GPSAntenna->UseVisualStyleBackColor = true;
				 this->GPSAntenna->CheckedChanged += gcnew System::EventHandler(this, &mainform::GPSAntenna_CheckedChanged);
				 this->GPSStatLbl->AutoSize = true;
				 this->GPSStatLbl->Location = System::Drawing::Point(106, 72);
				 this->GPSStatLbl->Name = L"GPSStatLbl";
				 this->GPSStatLbl->Size = System::Drawing::Size(41, 13);
				 this->GPSStatLbl->TabIndex = 34;
				 this->GPSStatLbl->Text = L"label11";
				 this->GetRepParamProgress->Location = System::Drawing::Point(6, 106);
				 this->GetRepParamProgress->Maximum = 6;
				 this->GetRepParamProgress->Name = L"GetRepParamProgress";
				 this->GetRepParamProgress->Size = System::Drawing::Size(100, 23);
				 this->GetRepParamProgress->Step = 1;
				 this->GetRepParamProgress->TabIndex = 33;
				 this->GPSOnOff->AutoSize = true;
				 this->GPSOnOff->Location = System::Drawing::Point(6, 71);
				 this->GPSOnOff->Name = L"GPSOnOff";
				 this->GPSOnOff->Size = System::Drawing::Size(94, 17);
				 this->GPSOnOff->TabIndex = 32;
				 this->GPSOnOff->Text = L"Питание GPS";
				 this->GPSOnOff->UseVisualStyleBackColor = true;
				 this->GPSOnOff->CheckedChanged += gcnew System::EventHandler(this, &mainform::GPSOnOff_CheckedChanged);
				 this->RelayStatCheckBox->AutoSize = true;
				 this->RelayStatCheckBox->Location = System::Drawing::Point(6, 19);
				 this->RelayStatCheckBox->Name = L"RelayStatCheckBox";
				 this->RelayStatCheckBox->Size = System::Drawing::Size(164, 17);
				 this->RelayStatCheckBox->TabIndex = 22;
				 this->RelayStatCheckBox->Text = L"Состояние реле (замкнуто)";
				 this->RelayStatCheckBox->UseVisualStyleBackColor = true;
				 this->RelayStatCheckBox->CheckedChanged += gcnew System::EventHandler(this, &mainform::RelayStatCheckBox_CheckedChanged);
				 this->vlna1Lbl->AutoSize = true;
				 this->vlna1Lbl->Location = System::Drawing::Point(241, 52);
				 this->vlna1Lbl->Name = L"vlna1Lbl";
				 this->vlna1Lbl->Size = System::Drawing::Size(47, 13);
				 this->vlna1Lbl->TabIndex = 28;
				 this->vlna1Lbl->Text = L"vlna1Lbl";
				 this->vtempLbl->AutoSize = true;
				 this->vtempLbl->Location = System::Drawing::Point(357, 52);
				 this->vtempLbl->Name = L"vtempLbl";
				 this->vtempLbl->Size = System::Drawing::Size(50, 13);
				 this->vtempLbl->TabIndex = 31;
				 this->vtempLbl->Text = L"vtempLbl";
				 this->vchargerLbl->AutoSize = true;
				 this->vchargerLbl->Location = System::Drawing::Point(241, 35);
				 this->vchargerLbl->Name = L"vchargerLbl";
				 this->vchargerLbl->Size = System::Drawing::Size(63, 13);
				 this->vchargerLbl->TabIndex = 27;
				 this->vchargerLbl->Text = L"vchargerLbl";
				 this->ResetRepeaterBtn->Location = System::Drawing::Point(6, 42);
				 this->ResetRepeaterBtn->Name = L"ResetRepeaterBtn";
				 this->ResetRepeaterBtn->Size = System::Drawing::Size(75, 23);
				 this->ResetRepeaterBtn->TabIndex = 23;
				 this->ResetRepeaterBtn->Text = L"Сброс";
				 this->ResetRepeaterBtn->UseVisualStyleBackColor = true;
				 this->ResetRepeaterBtn->Click += gcnew System::EventHandler(this, &mainform::ResetRepeaterBtn_Click);
				 this->vcoreLbl->AutoSize = true;
				 this->vcoreLbl->Location = System::Drawing::Point(357, 35);
				 this->vcoreLbl->Name = L"vcoreLbl";
				 this->vcoreLbl->Size = System::Drawing::Size(48, 13);
				 this->vcoreLbl->TabIndex = 30;
				 this->vcoreLbl->Text = L"vcoreLbl";
				 this->vbattLbl->AutoSize = true;
				 this->vbattLbl->Location = System::Drawing::Point(241, 16);
				 this->vbattLbl->Name = L"vbattLbl";
				 this->vbattLbl->Size = System::Drawing::Size(45, 13);
				 this->vbattLbl->TabIndex = 26;
				 this->vbattLbl->Text = L"vbattLbl";
				 this->vlna2Lbl->AutoSize = true;
				 this->vlna2Lbl->Location = System::Drawing::Point(357, 16);
				 this->vlna2Lbl->Name = L"vlna2Lbl";
				 this->vlna2Lbl->Size = System::Drawing::Size(47, 13);
				 this->vlna2Lbl->TabIndex = 29;
				 this->vlna2Lbl->Text = L"vlna2Lbl";
				 this->ResetRepeatersBtn->Location = System::Drawing::Point(156, 354);
				 this->ResetRepeatersBtn->Name = L"ResetRepeatersBtn";
				 this->ResetRepeatersBtn->Size = System::Drawing::Size(175, 23);
				 this->ResetRepeatersBtn->TabIndex = 25;
				 this->ResetRepeatersBtn->Text = L"Сброс всех ретрансляторов";
				 this->ResetRepeatersBtn->UseVisualStyleBackColor = true;
				 this->ResetRepeatersBtn->Click += gcnew System::EventHandler(this, &mainform::ResetRepeatersBtn_Click);
				 this->SearchRepeatersBtn->Location = System::Drawing::Point(3, 354);
				 this->SearchRepeatersBtn->Name = L"SearchRepeatersBtn";
				 this->SearchRepeatersBtn->Size = System::Drawing::Size(147, 23);
				 this->SearchRepeatersBtn->TabIndex = 24;
				 this->SearchRepeatersBtn->Text = L"Поиск ретрансляторов";
				 this->SearchRepeatersBtn->UseVisualStyleBackColor = true;
				 this->SearchRepeatersBtn->Click += gcnew System::EventHandler(this, &mainform::button12_Click);
				 this->DCGrid->AllowUserToAddRows = false;
				 this->DCGrid->AllowUserToDeleteRows = false;
				 this->DCGrid->AllowUserToResizeRows = false;
				 this->DCGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->DCGrid->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->DCGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->DCGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->DCGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
					 this->dataGridViewTextBoxColumn1,
						 this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->dataGridViewTextBoxColumn4, this->WorkMode
				 });
				 this->DCGrid->Location = System::Drawing::Point(3, 3);
				 this->DCGrid->MultiSelect = false;
				 this->DCGrid->Name = L"DCGrid";
				 this->DCGrid->ReadOnly = true;
				 this->DCGrid->RowHeadersVisible = false;
				 this->DCGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
				 this->DCGrid->Size = System::Drawing::Size(491, 345);
				 this->DCGrid->TabIndex = 21;
				 this->DCGrid->SelectionChanged += gcnew System::EventHandler(this, &mainform::DCGrid_SelectionChanged);
				 this->dataGridViewTextBoxColumn1->HeaderText = L"Адрес";
				 this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
				 this->dataGridViewTextBoxColumn1->ReadOnly = true;
				 this->dataGridViewTextBoxColumn1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->dataGridViewTextBoxColumn2->HeaderText = L"Уровень сигнала";
				 this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
				 this->dataGridViewTextBoxColumn2->ReadOnly = true;
				 this->dataGridViewTextBoxColumn2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->dataGridViewTextBoxColumn3->HeaderText = L"Качество приема сигнала";
				 this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
				 this->dataGridViewTextBoxColumn3->ReadOnly = true;
				 this->dataGridViewTextBoxColumn3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->dataGridViewTextBoxColumn4->HeaderText = L"Уровень заряда батареи";
				 this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
				 this->dataGridViewTextBoxColumn4->ReadOnly = true;
				 this->dataGridViewTextBoxColumn4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->WorkMode->HeaderText = L"Режим работы";
				 this->WorkMode->Name = L"WorkMode";
				 this->WorkMode->ReadOnly = true;
				 this->WorkMode->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 this->tabPage3->Controls->Add(this->EventsGrid);
				 this->tabPage3->Location = System::Drawing::Point(4, 22);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage3->Size = System::Drawing::Size(874, 685);
				 this->tabPage3->TabIndex = 2;
				 this->tabPage3->Text = L"События";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 this->EventsGrid->AllowUserToAddRows = false;
				 this->EventsGrid->AllowUserToDeleteRows = false;
				 this->EventsGrid->AllowUserToResizeRows = false;
				 this->EventsGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->EventsGrid->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->EventsGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->EventsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->EventsGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
					 this->Column1, this->Column3,
						 this->Column4, this->Column5, this->Column6, this->Column7
				 });
				 this->EventsGrid->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->EventsGrid->Location = System::Drawing::Point(3, 3);
				 this->EventsGrid->MultiSelect = false;
				 this->EventsGrid->Name = L"EventsGrid";
				 this->EventsGrid->ReadOnly = true;
				 this->EventsGrid->RowHeadersVisible = false;
				 this->EventsGrid->Size = System::Drawing::Size(868, 679);
				 this->EventsGrid->TabIndex = 0;
				 this->Column1->HeaderText = L"Адрес";
				 this->Column1->Name = L"Column1";
				 this->Column1->ReadOnly = true;
				 this->Column3->HeaderText = L"Уровень сигнала";
				 this->Column3->Name = L"Column3";
				 this->Column3->ReadOnly = true;
				 this->Column4->HeaderText = L"Уровень заряда батареи";
				 this->Column4->Name = L"Column4";
				 this->Column4->ReadOnly = true;
				 this->Column5->HeaderText = L"Режим работы";
				 this->Column5->Name = L"Column5";
				 this->Column5->ReadOnly = true;
				 this->Column6->HeaderText = L"Событие";
				 this->Column6->Name = L"Column6";
				 this->Column6->ReadOnly = true;
				 this->Column7->HeaderText = L"Дата/время";
				 this->Column7->Name = L"Column7";
				 this->Column7->ReadOnly = true;
				 this->sys_task->Enabled = true;
				 this->sys_task->Interval = 200;
				 this->sys_task->Tick += gcnew System::EventHandler(this, &mainform::sys_task_Tick);
				 this->saveFileDialog2->DefaultExt = L"esf";
				 this->saveFileDialog2->Filter = L"Evrika session file|*.esf|Все файлы|*.*";
				 this->saveFileDialog2->SupportMultiDottedExtensions = true;
				 this->openFileDialog1->DefaultExt = L"esf";
				 this->openFileDialog1->Filter = L"Evrika session file|*.esf";
				 this->openFileDialog1->SupportMultiDottedExtensions = true;
				 this->TagAndRepInfoUpdate->Enabled = true;
				 this->TagAndRepInfoUpdate->Interval = 1000;
				 this->TagAndRepInfoUpdate->Tick += gcnew System::EventHandler(this, &mainform::TagAndRepInfoUpdate_Tick);
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(882, 757);
				 this->Controls->Add(this->tabControl1);
				 this->Controls->Add(this->statusStrip1);
				 this->Controls->Add(this->menuStrip1);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
				 this->MainMenuStrip = this->menuStrip1;
				 this->MaximizeBox = false;
				 this->Name = L"mainform";
				 this->Text = L"Evrika";
				 this->Load += gcnew System::EventHandler(this, &mainform::mainform_Load);
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->statusStrip1->ResumeLayout(false);
				 this->statusStrip1->PerformLayout();
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RadioTagsGrid))->EndInit();
				 this->tabControl1->ResumeLayout(false);
				 this->tabPage1->ResumeLayout(false);
				 this->tabPage1->PerformLayout();
				 this->TagAndRepInfoBox->ResumeLayout(false);
				 this->TagAndRepInfoBox->PerformLayout();
				 this->tabPage2->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
				 this->RadioTagParamBox->ResumeLayout(false);
				 this->RadioTagParamBox->PerformLayout();
				 this->RepeaterParamBox->ResumeLayout(false);
				 this->RepeaterParamBox->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DCGrid))->EndInit();
				 this->tabPage3->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EventsGrid))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void savemap_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void настройкиToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tabControl1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e);
	private: System::Void open_device(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
	private: System::Void save_events(System::Object^  sender, System::EventArgs^  e);
	private: System::Void load_session(System::Object^  sender, System::EventArgs^  e);
	private: System::Void переподключениеКДЦToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void проверкаСоединенияToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void mainform_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ExportMapBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ImportMapBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void sys_task_Tick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DCGrid_SelectionChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void RelayStatCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ResetRepeaterBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ResetRepeatersBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void GPSOnOff_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void GPSAntenna_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void WakeUpRadioTagBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void RadioTagsGrid_SelectionChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TagAndRepeaterResetBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void UpdateTagBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void AutoUpdateTagChk_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void UpdateRepeaterParamBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void label12_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TagAndRepInfoUpdate_Tick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DrawPointBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button7_Click_1(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
