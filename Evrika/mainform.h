#pragma once

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

	//ref class Device;
	//ref class Event;
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

	private:
		Evrika::mapform^ mapform;
		static Evrika::settings^ settings_window;
		Evrika::loading_page^ ldng_wnd;
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
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::ToolStripMenuItem^  settings_menu;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Timer^  sys_task;
	private: System::Windows::Forms::CheckBox^  Get_Dev;



	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripProgressBar^  get_device_progress;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  UniqueID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SignalLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  QualityLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  BatteryLVL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  WorkMode;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
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
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel5;
	private: System::Windows::Forms::ToolStripStatusLabel^  ImageIndication;
	private: System::Windows::Forms::CheckBox^  GPS_En;
	private: System::Windows::Forms::TextBox^  A_text;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  n_text;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label10;




	private: System::Windows::Forms::ListBox^  listBox1;
			 /// <summary>
			 /// Свои классы и глобальные переменные
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
			 ref class MyPosition {
				 KalmanFilter^ lat;
				 KalmanFilter^ lng;
				 KalmanFilter^ HDOP;
				 KalmanFilter^ Height;
			 public:
				 bool bFirstRead;

				 MyPosition() {
					 lat = gcnew KalmanFilter();
					 lng = gcnew KalmanFilter();
					 HDOP = gcnew KalmanFilter();
					 Height = gcnew KalmanFilter();
					 bFirstRead = true;
				 }
				 ~MyPosition() {
					 delete lat;
					 delete lng;
					 delete HDOP;
					 delete Height;
				 }
				 void SetState(double _lat, double _lng, double _HDOP, double _Height) {
					 lat->SetState(_lat, 0.1);
					 lng->SetState(_lng, 0.1);
					 HDOP->SetState(_HDOP, 0.1);
					 Height->SetState(_Height, 0.1);
				 }
				 void Correct(double _lat, double _lng, double _HDOP, double _Height) {
					 lat->Correct(_lat);
					 lng->Correct(_lng);
					 HDOP->Correct(_HDOP);
					 Height->Correct(_Height);
				 }
				 void GetState(double* _lat, double* _lng, double* _HDOP, double* _Height) {
					 *_lat = lat->State;
					 *_lng = lng->State;
					 *_HDOP = HDOP->State;
					 *_Height = Height->State;
				 }
				 void GetPos(double* _lat, double* _lng) {
					 *_lat = lat->State;
					 *_lng = lng->State;
				 }
			 };
			 void Triangulate(geoPoint^ circle1, geoPoint^ circle2) {	//return points and array size
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
			 void Triangulate(geoPoint^ circle1, geoPoint^ circle2, List<PointLatLng>^ twoPoints) {	//return points and array size
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
			 int factorial(int n) {
				 int res = 1;
				 for (int i = 1; i < n + 1; i++)
					 res *= i;
				 return res;
			 }
			 List<PointLatLng>^ SortPoint_Line(List<PointLatLng>^ in_p)
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
			 bool inTheArea(PointLatLng point)
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
			 bool inTheArea(PointLatLng point, int i, int j, int k)
			 {
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
			 void metod_4()
			 {
				 List<PointLatLng>^ allPoints = gcnew List<PointLatLng>;
				 List<int>^ allPoints_mass = gcnew List<int>;
				 for (int i = 0; i < lCoordsCount; i++)
					 for (int j = i + 1; j < lCoordsCount; j++) {

						 for (int k = j + 1; k < lCoordsCount; k++)
						 {
							 List<PointLatLng>^ peresech = gcnew List<PointLatLng>;
							 List<PointLatLng>^ center_area = gcnew List<PointLatLng>;
							 List<geoPoint^>^ troyka_okr = gcnew List<geoPoint^>(3);
							 troyka_okr->Add(MyCoords[i]);
							 troyka_okr->Add(MyCoords[j]);
							 troyka_okr->Add(MyCoords[k]);
							 //Находим все пересечения
							 //listBox3->Items->Add(i.ToString() + " " + j.ToString() + " " + k.ToString());
							 for (int a = 0; a < 3; a++)
								 for (int b = a + 1; b < 3; b++)
								 {
									 List<PointLatLng>^ tempPoints = gcnew List<PointLatLng>;
									 Triangulate(troyka_okr[a], troyka_okr[b], tempPoints);
									 peresech->Add(tempPoints[0]);
									 peresech->Add(tempPoints[1]);
								 }
							 PointLatLng center;
							 for (int c = 0; c < peresech->Count; c++)
							 {
								 center.Lat += peresech[c].Lat;
								 center.Lng += peresech[c].Lng;
							 }
							 center.Lat /= peresech->Count;
							 center.Lng /= peresech->Count;

							 double temp_dist, min_dist = 999999999;
							 int min_index = -1;
							 for (int d = 0; d < 3; d++)
							 {
								 for (int e = 0; e < peresech->Count; e++) {
									 temp_dist = Math::Sqrt(
										 Math::Pow(Math::Abs(center.Lat - peresech[e].Lat), 2) +
										 Math::Pow(Math::Abs(center.Lng - peresech[e].Lng), 2));

									 if (temp_dist < min_dist && this->inTheArea(peresech[e], i, j, k)) {
										 min_dist = temp_dist;
										 min_index = e;
									 }
								 }
								 center_area->Add(peresech[min_index]);
								 min_dist = 999999;
								 peresech->RemoveAt(min_index);
								 min_index = -1;
							 }
							 //GMapPolygon ^cent_area = gcnew GMapPolygon(center_area, "center_area");//debug
							 //cent_area->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(63, Color::Green));
							 //cent_area->Stroke = gcnew Pen(Color::Green, 1);
							 //areaOvrl->Polygons->Add(cent_area);
							 for (int p = 0; p < center_area->Count; p++) {
								 bool duplicate = false;
								 int index = -1;
								 for (int f = 0; f < allPoints->Count; f++)
								 {
									 if (center_area[p].Lat == allPoints[f].Lat&&center_area[p].Lng == allPoints[f].Lng)	//0.0000005
									 {
										 duplicate = true;
										 index = f;
										 break;
									 }
								 }
								 if (duplicate)
								 {
									 if (inTheArea(allPoints[index])) {
										 allPoints_mass[index]++;
									 }
								 }
								 else
								 {
									 allPoints->Add(center_area[p]);
									 allPoints_mass->Add(1);
								 }
							 }
						 }

					 }

				 int max_mass = 0;
				 for (int g = 0; g < allPoints_mass->Count; g++) {
					 if (max_mass < allPoints_mass[g])
						 max_mass = allPoints_mass[g];
				 }
				 List<PointLatLng>^ center_area = gcnew List<PointLatLng>;
				 for (int i = 0; i < allPoints->Count; i++) {
					 if (allPoints_mass[i] == max_mass)
						 center_area->Add(allPoints[i]);
				 }
				 /*for (int i = 0; i < allPoints->Count; i++)
				 {
					 GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(allPoints[i], Markers::GMarkerGoogleType::red_small);
					 marker->ToolTipText = allPoints_mass[i].ToString();
					 marker->ToolTipMode = GMap::NET::WindowsForms::MarkerTooltipMode::OnMouseOver;
					 mrkrOvrl->Markers->Add(marker);
				 }*/
				 GMapPolygon ^cent_area = gcnew GMapPolygon(SortPoint_Line(center_area), "center_area");
				 cent_area->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(127, Color::Red));
				 cent_area->Stroke = gcnew Pen(Color::Red, 2);
				 areaOvrl->Polygons->Add(cent_area);
			 }
			 void metod_5() {
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
			 void ParseToPoint(cli::array<wchar_t>^ buf) {
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
			 void WriteToComStat(String^ str) {
				 whatCOM->Text = str;
			 }
			 void CheckComConn();
			 void EnumCOMs();
			 void WriteLog(String^ message) {
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
			 System::String^ Quality(int q) {
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
			 int RangeRandInt(int min, int max) {
				 Random^ autoRand = gcnew Random;
				 return autoRand->Next(min, max);
			 }
			 double RangeRandDouble(double min, double max) {
				 Random^ autoRand = gcnew Random;
				 double mult = autoRand->NextDouble();
				 double num = min + (max - min)*mult;
				 int temp = int(num * 100);
				 return temp / 100.0;
			 }

	public:
		void UpdateMapPos() {
			//обновление картой при изменении
			label2->Text = "Широта: " + map->Position.Lat.ToString();	//Latitude
			label3->Text = "Долгота: " + map->Position.Lng.ToString();	//Longetude
		}
		//static Evrika::settings^ get_settings_windowP() {
		//	return settings_window;
		//}
		bool CheckSum(cli::array<wchar_t>^ rbuf);
		void update_device_list();
		void update_event_list();
		void ParseDeviceBuffer(cli::array<wchar_t>^ rbuf);
		
	private:
		String^ ourPort;
		bool eGPS;

	public:
		static mainform^ my_handle;
		MyPosition^ myPos;
	private:
		KalmanFilter^ mid_cycles;
		cli::array<GMarkerGoogle^> ^markers;
		long lCoordsCount;
		bool isOurCom;
		//bool notLoaded;
		List<geoPoint^> ^MyCoords;
		List<Device^>^ Devices;
		List<Event^>^ Events;
		//int cDevices;
		GMapControl^ map;
		GMapOverlay ^mrkrOvrl;
		Semaphore ^sEnumCom;
		Semaphore^ sPointReciver;
		GMapOverlay ^areaOvrl;
		GMapOverlay^ myPosOvrl;
		bool LastStateIsOpen;
		bool GPS_KnownPos = false;
		bool my_pos_accepted = false;
		bool device_get = false;
		List<TextBox^>^ logs;
		uint64_t sys_task_counter = 0;
	private: System::ComponentModel::IContainer^  components;
			 /// </summary>


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
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
				 this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
				 this->UniqueID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->SignalLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->QualityLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->BatteryLVL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->WorkMode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->button7 = (gcnew System::Windows::Forms::Button());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->A_text = (gcnew System::Windows::Forms::TextBox());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->n_text = (gcnew System::Windows::Forms::TextBox());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->GPS_En = (gcnew System::Windows::Forms::CheckBox());
				 this->button11 = (gcnew System::Windows::Forms::Button());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->Get_Dev = (gcnew System::Windows::Forms::CheckBox());
				 this->button8 = (gcnew System::Windows::Forms::Button());
				 this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				 this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
				 this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->sys_task = (gcnew System::Windows::Forms::Timer(this->components));
				 this->saveFileDialog2 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->groupBox1->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->statusStrip1->SuspendLayout();
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 this->tabPage3->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(6, 6);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(169, 43);
				 this->button1->TabIndex = 0;
				 this->button1->Text = L"Скрыть/Показать карту";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
				 // 
				 // listBox1
				 // 
				 this->listBox1->FormattingEnabled = true;
				 this->listBox1->Location = System::Drawing::Point(180, 6);
				 this->listBox1->Name = L"listBox1";
				 this->listBox1->Size = System::Drawing::Size(114, 303);
				 this->listBox1->TabIndex = 1;
				 this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::listBox1_SelectedIndexChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(6, 16);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(75, 13);
				 this->label1->TabIndex = 2;
				 this->label1->Text = L"Центр карты:";
				 // 
				 // groupBox1
				 // 
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
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(6, 78);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(60, 13);
				 this->label4->TabIndex = 7;
				 this->label4->Text = L"Радиус, м:";
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(72, 75);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(91, 20);
				 this->textBox1->TabIndex = 6;
				 this->textBox1->Text = L"1";
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(6, 101);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(157, 23);
				 this->button2->TabIndex = 5;
				 this->button2->Text = L"Сохранить";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &mainform::button2_Click);
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(6, 56);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(35, 13);
				 this->label3->TabIndex = 4;
				 this->label3->Text = L"label3";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(6, 38);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(35, 13);
				 this->label2->TabIndex = 3;
				 this->label2->Text = L"label2";
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->button5);
				 this->groupBox2->Controls->Add(this->button4);
				 this->groupBox2->Controls->Add(this->button3);
				 this->groupBox2->Controls->Add(this->label7);
				 this->groupBox2->Controls->Add(this->label6);
				 this->groupBox2->Controls->Add(this->label5);
				 this->groupBox2->Location = System::Drawing::Point(300, 6);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(182, 193);
				 this->groupBox2->TabIndex = 4;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"groupBox2";
				 // 
				 // button5
				 // 
				 this->button5->Location = System::Drawing::Point(13, 158);
				 this->button5->Name = L"button5";
				 this->button5->Size = System::Drawing::Size(157, 23);
				 this->button5->TabIndex = 5;
				 this->button5->Text = L"Удалить";
				 this->button5->UseVisualStyleBackColor = true;
				 this->button5->Click += gcnew System::EventHandler(this, &mainform::button5_Click);
				 // 
				 // button4
				 // 
				 this->button4->Location = System::Drawing::Point(13, 129);
				 this->button4->Name = L"button4";
				 this->button4->Size = System::Drawing::Size(157, 23);
				 this->button4->TabIndex = 4;
				 this->button4->Text = L"Точка";
				 this->button4->UseVisualStyleBackColor = true;
				 this->button4->Click += gcnew System::EventHandler(this, &mainform::button4_Click);
				 // 
				 // button3
				 // 
				 this->button3->Location = System::Drawing::Point(13, 100);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(157, 23);
				 this->button3->TabIndex = 3;
				 this->button3->Text = L"Окружность";
				 this->button3->UseVisualStyleBackColor = true;
				 this->button3->Click += gcnew System::EventHandler(this, &mainform::button3_Click);
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(10, 74);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(35, 13);
				 this->label7->TabIndex = 2;
				 this->label7->Text = L"label7";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(10, 49);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(35, 13);
				 this->label6->TabIndex = 1;
				 this->label6->Text = L"label6";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(10, 23);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(35, 13);
				 this->label5->TabIndex = 0;
				 this->label5->Text = L"label5";
				 // 
				 // button6
				 // 
				 this->button6->Location = System::Drawing::Point(5, 191);
				 this->button6->Name = L"button6";
				 this->button6->Size = System::Drawing::Size(169, 23);
				 this->button6->TabIndex = 5;
				 this->button6->Text = L"Очистить карту";
				 this->button6->UseVisualStyleBackColor = true;
				 this->button6->Click += gcnew System::EventHandler(this, &mainform::button6_Click);
				 // 
				 // button9
				 // 
				 this->button9->Location = System::Drawing::Point(300, 288);
				 this->button9->Name = L"button9";
				 this->button9->Size = System::Drawing::Size(75, 21);
				 this->button9->TabIndex = 9;
				 this->button9->Text = L"Triangulate";
				 this->button9->UseVisualStyleBackColor = true;
				 this->button9->Click += gcnew System::EventHandler(this, &mainform::button9_Click);
				 // 
				 // serialPort1
				 // 
				 this->serialPort1->BaudRate = 115200;
				 this->serialPort1->ParityReplace = static_cast<System::Byte>(255);
				 this->serialPort1->PortName = L"COM5";
				 this->serialPort1->ReadBufferSize = 512;
				 this->serialPort1->ReadTimeout = 1000;
				 this->serialPort1->ReceivedBytesThreshold = 5;
				 this->serialPort1->WriteBufferSize = 512;
				 this->serialPort1->WriteTimeout = 1000;
				 this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &mainform::serialPort1_DataReceived);
				 // 
				 // proglog
				 // 
				 this->proglog->Location = System::Drawing::Point(1, 324);
				 this->proglog->Multiline = true;
				 this->proglog->Name = L"proglog";
				 this->proglog->ReadOnly = true;
				 this->proglog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->proglog->Size = System::Drawing::Size(482, 130);
				 this->proglog->TabIndex = 13;
				 this->proglog->Text = L"Старт...";
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
					 this->ImageIndication,
						 this->whatCOM, this->toolStripStatusLabel1, this->get_device_progress, this->toolStripStatusLabel2, this->toolStripStatusLabel3,
						 this->toolStripStatusLabel4, this->toolStripStatusLabel5
				 });
				 this->statusStrip1->Location = System::Drawing::Point(0, 510);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(705, 22);
				 this->statusStrip1->TabIndex = 14;
				 this->statusStrip1->Text = L"statusStrip1";
				 // 
				 // ImageIndication
				 // 
				 this->ImageIndication->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->ImageIndication->Name = L"ImageIndication";
				 this->ImageIndication->Size = System::Drawing::Size(0, 17);
				 // 
				 // whatCOM
				 // 
				 this->whatCOM->Name = L"whatCOM";
				 this->whatCOM->Size = System::Drawing::Size(40, 17);
				 this->whatCOM->Text = L"COM\?";
				 // 
				 // toolStripStatusLabel1
				 // 
				 this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
				 this->toolStripStatusLabel1->Size = System::Drawing::Size(10, 17);
				 this->toolStripStatusLabel1->Text = L"|";
				 // 
				 // get_device_progress
				 // 
				 this->get_device_progress->Maximum = 10;
				 this->get_device_progress->Name = L"get_device_progress";
				 this->get_device_progress->Size = System::Drawing::Size(100, 16);
				 this->get_device_progress->Step = 1;
				 // 
				 // toolStripStatusLabel2
				 // 
				 this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
				 this->toolStripStatusLabel2->Size = System::Drawing::Size(10, 17);
				 this->toolStripStatusLabel2->Text = L"|";
				 // 
				 // toolStripStatusLabel3
				 // 
				 this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
				 this->toolStripStatusLabel3->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel3->Text = L"toolStripStatusLabel3";
				 this->toolStripStatusLabel3->Visible = false;
				 // 
				 // toolStripStatusLabel4
				 // 
				 this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
				 this->toolStripStatusLabel4->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel4->Text = L"toolStripStatusLabel4";
				 this->toolStripStatusLabel4->Visible = false;
				 // 
				 // toolStripStatusLabel5
				 // 
				 this->toolStripStatusLabel5->Name = L"toolStripStatusLabel5";
				 this->toolStripStatusLabel5->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel5->Text = L"toolStripStatusLabel5";
				 this->toolStripStatusLabel5->Visible = false;
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->файлToolStripMenuItem,
						 this->подключениеToolStripMenuItem, this->кэшToolStripMenuItem, this->settings_menu
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(705, 24);
				 this->menuStrip1->TabIndex = 16;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // файлToolStripMenuItem
				 // 
				 this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->savemap,
						 this->SaveSessionBtn, this->LoadSessionBtn
				 });
				 this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
				 this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
				 this->файлToolStripMenuItem->Text = L"Файл";
				 // 
				 // savemap
				 // 
				 this->savemap->Name = L"savemap";
				 this->savemap->Size = System::Drawing::Size(258, 22);
				 this->savemap->Text = L"Сохранить карту в *.bmp ...";
				 this->savemap->Click += gcnew System::EventHandler(this, &mainform::savemap_Click);
				 // 
				 // SaveSessionBtn
				 // 
				 this->SaveSessionBtn->Name = L"SaveSessionBtn";
				 this->SaveSessionBtn->Size = System::Drawing::Size(258, 22);
				 this->SaveSessionBtn->Text = L"Сохранить текущую сессию...";
				 this->SaveSessionBtn->Click += gcnew System::EventHandler(this, &mainform::save_events);
				 // 
				 // LoadSessionBtn
				 // 
				 this->LoadSessionBtn->Name = L"LoadSessionBtn";
				 this->LoadSessionBtn->Size = System::Drawing::Size(258, 22);
				 this->LoadSessionBtn->Text = L"Загрузить сохраненную сессию...";
				 this->LoadSessionBtn->Click += gcnew System::EventHandler(this, &mainform::load_session);
				 // 
				 // подключениеToolStripMenuItem
				 // 
				 this->подключениеToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->ConnectDC,
						 this->ConnCheck
				 });
				 this->подключениеToolStripMenuItem->Name = L"подключениеToolStripMenuItem";
				 this->подключениеToolStripMenuItem->Size = System::Drawing::Size(86, 20);
				 this->подключениеToolStripMenuItem->Text = L"Соединение";
				 // 
				 // ConnectDC
				 // 
				 this->ConnectDC->Name = L"ConnectDC";
				 this->ConnectDC->Size = System::Drawing::Size(207, 22);
				 this->ConnectDC->Text = L"Переподключение к ДЦ";
				 this->ConnectDC->Click += gcnew System::EventHandler(this, &mainform::переподключениеКДЦToolStripMenuItem_Click);
				 // 
				 // ConnCheck
				 // 
				 this->ConnCheck->Name = L"ConnCheck";
				 this->ConnCheck->Size = System::Drawing::Size(207, 22);
				 this->ConnCheck->Text = L"Проверка соединения";
				 this->ConnCheck->Click += gcnew System::EventHandler(this, &mainform::проверкаСоединенияToolStripMenuItem_Click);
				 // 
				 // кэшToolStripMenuItem
				 // 
				 this->кэшToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->ExportMapBtn,
						 this->ImportMapBtn
				 });
				 this->кэшToolStripMenuItem->Name = L"кэшToolStripMenuItem";
				 this->кэшToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				 this->кэшToolStripMenuItem->Text = L"Карта";
				 // 
				 // ExportMapBtn
				 // 
				 this->ExportMapBtn->Name = L"ExportMapBtn";
				 this->ExportMapBtn->Size = System::Drawing::Size(202, 22);
				 this->ExportMapBtn->Text = L"Экспорт файла карты...";
				 this->ExportMapBtn->Click += gcnew System::EventHandler(this, &mainform::ExportMapBtn_Click);
				 // 
				 // ImportMapBtn
				 // 
				 this->ImportMapBtn->Name = L"ImportMapBtn";
				 this->ImportMapBtn->Size = System::Drawing::Size(202, 22);
				 this->ImportMapBtn->Text = L"Импорт файла карты...";
				 this->ImportMapBtn->Click += gcnew System::EventHandler(this, &mainform::ImportMapBtn_Click);
				 // 
				 // settings_menu
				 // 
				 this->settings_menu->Name = L"settings_menu";
				 this->settings_menu->Size = System::Drawing::Size(88, 20);
				 this->settings_menu->Text = L"Настройки...";
				 this->settings_menu->Click += gcnew System::EventHandler(this, &mainform::настройкиToolStripMenuItem_Click);
				 // 
				 // saveFileDialog1
				 // 
				 this->saveFileDialog1->DefaultExt = L"bmp";
				 this->saveFileDialog1->Filter = L"Bitmap|*.bmp|Все файлы|*.*";
				 this->saveFileDialog1->SupportMultiDottedExtensions = true;
				 // 
				 // dataGridView1
				 // 
				 this->dataGridView1->AllowUserToAddRows = false;
				 this->dataGridView1->AllowUserToDeleteRows = false;
				 this->dataGridView1->AllowUserToResizeRows = false;
				 this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->dataGridView1->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
					 this->UniqueID,
						 this->SignalLVL, this->QualityLVL, this->BatteryLVL, this->WorkMode
				 });
				 this->dataGridView1->Location = System::Drawing::Point(0, 0);
				 this->dataGridView1->MultiSelect = false;
				 this->dataGridView1->Name = L"dataGridView1";
				 this->dataGridView1->ReadOnly = true;
				 this->dataGridView1->RowHeadersVisible = false;
				 this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
				 this->dataGridView1->Size = System::Drawing::Size(697, 425);
				 this->dataGridView1->TabIndex = 17;
				 this->dataGridView1->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &mainform::open_device);
				 // 
				 // UniqueID
				 // 
				 dataGridViewCellStyle1->BackColor = System::Drawing::Color::White;
				 this->UniqueID->DefaultCellStyle = dataGridViewCellStyle1;
				 this->UniqueID->HeaderText = L"Уникальный  ID";
				 this->UniqueID->Name = L"UniqueID";
				 this->UniqueID->ReadOnly = true;
				 this->UniqueID->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // SignalLVL
				 // 
				 this->SignalLVL->HeaderText = L"Уровень сигнала";
				 this->SignalLVL->Name = L"SignalLVL";
				 this->SignalLVL->ReadOnly = true;
				 this->SignalLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // QualityLVL
				 // 
				 dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Green;
				 this->QualityLVL->DefaultCellStyle = dataGridViewCellStyle2;
				 this->QualityLVL->HeaderText = L"Качество приема сигнала";
				 this->QualityLVL->Name = L"QualityLVL";
				 this->QualityLVL->ReadOnly = true;
				 this->QualityLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // BatteryLVL
				 // 
				 this->BatteryLVL->HeaderText = L"Уровень заряда батареи";
				 this->BatteryLVL->Name = L"BatteryLVL";
				 this->BatteryLVL->ReadOnly = true;
				 this->BatteryLVL->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // WorkMode
				 // 
				 this->WorkMode->HeaderText = L"Режим работы";
				 this->WorkMode->Name = L"WorkMode";
				 this->WorkMode->ReadOnly = true;
				 this->WorkMode->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // button7
				 // 
				 this->button7->Location = System::Drawing::Point(616, 431);
				 this->button7->Name = L"button7";
				 this->button7->Size = System::Drawing::Size(75, 23);
				 this->button7->TabIndex = 18;
				 this->button7->Text = L"button7";
				 this->button7->UseVisualStyleBackColor = true;
				 this->button7->Click += gcnew System::EventHandler(this, &mainform::button7_Click_1);
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Controls->Add(this->tabPage3);
				 this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tabControl1->Location = System::Drawing::Point(0, 24);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(705, 486);
				 this->tabControl1->TabIndex = 19;
				 this->tabControl1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::tabControl1_SelectedIndexChanged);
				 // 
				 // tabPage1
				 // 
				 this->tabPage1->Controls->Add(this->label10);
				 this->tabPage1->Controls->Add(this->A_text);
				 this->tabPage1->Controls->Add(this->label9);
				 this->tabPage1->Controls->Add(this->n_text);
				 this->tabPage1->Controls->Add(this->label8);
				 this->tabPage1->Controls->Add(this->GPS_En);
				 this->tabPage1->Controls->Add(this->button11);
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
				 this->tabPage1->Size = System::Drawing::Size(697, 460);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Text = L"Управление";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 // 
				 // label10
				 // 
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(310, 196);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(41, 13);
				 this->label10->TabIndex = 22;
				 this->label10->Text = L"label10";
				 // 
				 // A_text
				 // 
				 this->A_text->Location = System::Drawing::Point(329, 245);
				 this->A_text->Name = L"A_text";
				 this->A_text->Size = System::Drawing::Size(46, 20);
				 this->A_text->TabIndex = 21;
				 this->A_text->Text = L"-31";
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(310, 248);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(14, 13);
				 this->label9->TabIndex = 20;
				 this->label9->Text = L"A";
				 // 
				 // n_text
				 // 
				 this->n_text->Location = System::Drawing::Point(329, 218);
				 this->n_text->Name = L"n_text";
				 this->n_text->Size = System::Drawing::Size(46, 20);
				 this->n_text->TabIndex = 19;
				 this->n_text->Text = L"5";
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(310, 220);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(13, 13);
				 this->label8->TabIndex = 18;
				 this->label8->Text = L"n";
				 // 
				 // GPS_En
				 // 
				 this->GPS_En->AutoSize = true;
				 this->GPS_En->Location = System::Drawing::Point(6, 220);
				 this->GPS_En->Name = L"GPS_En";
				 this->GPS_En->Size = System::Drawing::Size(48, 17);
				 this->GPS_En->TabIndex = 17;
				 this->GPS_En->Text = L"GPS";
				 this->GPS_En->UseVisualStyleBackColor = true;
				 this->GPS_En->CheckedChanged += gcnew System::EventHandler(this, &mainform::checkBox3_CheckedChanged);
				 // 
				 // button11
				 // 
				 this->button11->Location = System::Drawing::Point(6, 243);
				 this->button11->Name = L"button11";
				 this->button11->Size = System::Drawing::Size(73, 23);
				 this->button11->TabIndex = 16;
				 this->button11->Text = L"Get position";
				 this->button11->UseVisualStyleBackColor = true;
				 this->button11->Click += gcnew System::EventHandler(this, &mainform::button11_Click);
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->Get_Dev);
				 this->tabPage2->Controls->Add(this->button8);
				 this->tabPage2->Controls->Add(this->dataGridView1);
				 this->tabPage2->Controls->Add(this->button7);
				 this->tabPage2->Location = System::Drawing::Point(4, 22);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(697, 460);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Устройства";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // Get_Dev
				 // 
				 this->Get_Dev->AutoSize = true;
				 this->Get_Dev->Location = System::Drawing::Point(327, 434);
				 this->Get_Dev->Name = L"Get_Dev";
				 this->Get_Dev->Size = System::Drawing::Size(83, 17);
				 this->Get_Dev->TabIndex = 20;
				 this->Get_Dev->Text = L"Get devices";
				 this->Get_Dev->UseVisualStyleBackColor = true;
				 this->Get_Dev->CheckedChanged += gcnew System::EventHandler(this, &mainform::checkBox2_CheckedChanged);
				 // 
				 // button8
				 // 
				 this->button8->Location = System::Drawing::Point(488, 431);
				 this->button8->Name = L"button8";
				 this->button8->Size = System::Drawing::Size(75, 23);
				 this->button8->TabIndex = 19;
				 this->button8->Text = L"button8";
				 this->button8->UseVisualStyleBackColor = true;
				 this->button8->Click += gcnew System::EventHandler(this, &mainform::button8_Click_1);
				 // 
				 // tabPage3
				 // 
				 this->tabPage3->Controls->Add(this->dataGridView2);
				 this->tabPage3->Location = System::Drawing::Point(4, 22);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage3->Size = System::Drawing::Size(697, 460);
				 this->tabPage3->TabIndex = 2;
				 this->tabPage3->Text = L"События";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 // 
				 // dataGridView2
				 // 
				 this->dataGridView2->AllowUserToAddRows = false;
				 this->dataGridView2->AllowUserToDeleteRows = false;
				 this->dataGridView2->AllowUserToResizeRows = false;
				 this->dataGridView2->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
				 this->dataGridView2->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 this->dataGridView2->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
				 this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
					 this->Column1,
						 this->Column3, this->Column4, this->Column5, this->Column6, this->Column7
				 });
				 this->dataGridView2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dataGridView2->Location = System::Drawing::Point(3, 3);
				 this->dataGridView2->MultiSelect = false;
				 this->dataGridView2->Name = L"dataGridView2";
				 this->dataGridView2->ReadOnly = true;
				 this->dataGridView2->RowHeadersVisible = false;
				 this->dataGridView2->Size = System::Drawing::Size(691, 454);
				 this->dataGridView2->TabIndex = 0;
				 // 
				 // Column1
				 // 
				 this->Column1->HeaderText = L"Уникальный ID";
				 this->Column1->Name = L"Column1";
				 this->Column1->ReadOnly = true;
				 // 
				 // Column3
				 // 
				 this->Column3->HeaderText = L"Уровень сигнала";
				 this->Column3->Name = L"Column3";
				 this->Column3->ReadOnly = true;
				 // 
				 // Column4
				 // 
				 this->Column4->HeaderText = L"Уровень заряда батареи";
				 this->Column4->Name = L"Column4";
				 this->Column4->ReadOnly = true;
				 // 
				 // Column5
				 // 
				 this->Column5->HeaderText = L"Режим работы";
				 this->Column5->Name = L"Column5";
				 this->Column5->ReadOnly = true;
				 // 
				 // Column6
				 // 
				 this->Column6->HeaderText = L"Событие";
				 this->Column6->Name = L"Column6";
				 this->Column6->ReadOnly = true;
				 // 
				 // Column7
				 // 
				 this->Column7->HeaderText = L"Дата/время";
				 this->Column7->Name = L"Column7";
				 this->Column7->ReadOnly = true;
				 // 
				 // sys_task
				 // 
				 this->sys_task->Enabled = true;
				 this->sys_task->Interval = 200;
				 this->sys_task->Tick += gcnew System::EventHandler(this, &mainform::sys_task_Tick);
				 // 
				 // saveFileDialog2
				 // 
				 this->saveFileDialog2->DefaultExt = L"esf";
				 this->saveFileDialog2->Filter = L"Evrika session file|*.esf|Все файлы|*.*";
				 this->saveFileDialog2->SupportMultiDottedExtensions = true;
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->DefaultExt = L"esf";
				 this->openFileDialog1->Filter = L"Evrika session file|*.esf";
				 this->openFileDialog1->SupportMultiDottedExtensions = true;
				 // 
				 // mainform
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(705, 532);
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
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
				 this->tabControl1->ResumeLayout(false);
				 this->tabPage1->ResumeLayout(false);
				 this->tabPage1->PerformLayout();
				 this->tabPage2->ResumeLayout(false);
				 this->tabPage2->PerformLayout();
				 this->tabPage3->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//MyCoords[lCoordsCount] = gcnew geoPoint(map->Position.Lat, map->Position.Lng, double::Parse(textBox1->Text), "P" + lCoordsCount.ToString());
		MyCoords->Add(gcnew geoPoint(map->Position.Lat, map->Position.Lng, double::Parse(textBox1->Text), "P" + lCoordsCount.ToString()));
		listBox1->Items->Add(MyCoords[lCoordsCount]->get_name());
		lCoordsCount++;
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (listBox1->SelectedIndex<0 || listBox1->SelectedIndex>lCoordsCount - 1) return;
		groupBox2->Text = MyCoords[listBox1->SelectedIndex]->get_name();
		label5->Text = "R: " + MyCoords[listBox1->SelectedIndex]->get_r().ToString();
		label6->Text = "Lat: " + MyCoords[listBox1->SelectedIndex]->get_lat().ToString();
		label7->Text = "Lng: " + MyCoords[listBox1->SelectedIndex]->get_lng().ToString();
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		//draw area point
		if (listBox1->SelectedIndex<0 || listBox1->SelectedIndex>lCoordsCount - 1) return;
		GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(MyCoords[listBox1->SelectedIndex]->get_pointLatLng(), Markers::GMarkerGoogleType::blue_small);
		mrkrOvrl->Markers->Add(marker);

		GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::SortPoints_distance(MyCoords[listBox1->SelectedIndex]->CreateCircle()), "circ");
		circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Blue));
		circ->Stroke = gcnew Pen(Color::Blue, 1);
		areaOvrl->Polygons->Add(circ);
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		areaOvrl->Clear();
		mrkrOvrl->Clear();
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		GMarkerGoogle^ marker = gcnew GMarkerGoogle(MyCoords[listBox1->SelectedIndex]->get_pointLatLng(), GMarkerGoogleType::blue_pushpin);
		mrkrOvrl->Markers->Add(marker);
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		//find points of intersect
		Triangulate(MyCoords[0], MyCoords[1]);
	}
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
		metod_5();
	}
	private: System::Void savemap_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button7_Click_1(System::Object^  sender, System::EventArgs^  e) {
		//dataGridView1->Rows[0]->Cells[0]->Value = "abc";
		//dataGridView1->Rows->Add(1);
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[0]->Value = "1";	//id
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[1]->Value = "2";	//temp id
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[2]->Value = RangeRandInt(-127, 10);	//sgnl lvl
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[3]->Value = Quality(RangeRandInt(0, 7));	//quality
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[4]->Value = RangeRandDouble(2.5, 4.5);	//batt lvl
		//dataGridView1->Rows[dataGridView1->RowCount - 1]->Cells[5]->Value = "0";	//mode


		try {
			serialPort1->Open();
			serialPort1->WriteLine("WAKE\r");

		}
		catch (IO::IOException ^ioexception) {
			proglog->AppendText("\r\n" + ioexception->Message);
		}
	}
	private: System::Void настройкиToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tabControl1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		switch (tabControl1->SelectedIndex)
		{
		case 0:
			this->Width = 512;
			this->Height = 570;
			break;
		case 1:
		case 2:
			this->Width = 721;
			this->Height = 570;
			break;
		default:
			break;
		}
		this->Refresh();
	}
	private: System::Void button8_Click_1(System::Object^  sender, System::EventArgs^  e);
	private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
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
	private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (Get_Dev->Checked)
			get_device_progress->Value = 0;
	}
	private: System::Void open_device(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
	private: System::Void save_events(System::Object^  sender, System::EventArgs^  e);
	private: System::Void load_session(System::Object^  sender, System::EventArgs^  e);
	private: System::Void переподключениеКДЦToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::EnumCOMs));
		connthrd->Start();
	}
	private: System::Void проверкаСоединенияToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::CheckComConn));
		connthrd->Start();
	}
	private: System::Void mainform_Load(System::Object^  sender, System::EventArgs^  e) {
		my_handle = this;
		Thread^ connthrd = gcnew Thread(gcnew ThreadStart(this, &mainform::EnumCOMs));
		connthrd->Start();
	}
	private: System::Void ExportMapBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		map->ShowExportDialog();
	}
	private: System::Void ImportMapBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		map->ShowImportDialog();
	}
	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void sys_task_Tick(System::Object^  sender, System::EventArgs^  e);
	};
}
