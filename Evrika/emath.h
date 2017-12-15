#pragma once

using namespace GMap::NET;
using namespace System;
using namespace System::Collections::Generic;

namespace Evrika {
	namespace EMath {

		extern double ScaleCoef;

		ref class LatLngComparer : System::Collections::Generic::IComparer<PointLatLng> {
		public:
			virtual int Compare(PointLatLng x, PointLatLng y) {
				if (x.Lat == y.Lat && x.Lng == y.Lng) {
					return 0;
				}
				else return 1;
			}
		};

		ref class geoPoint {                 // ласс geoPoint дл€ хранени€ координат точек
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
			geoPoint(const geoPoint %c)   // конструктор копировани€
			{
				_lat = c._lat;
				_lng = c._lng;
				_name = c._name;
				_r = c._r;
			}
			void set_point(double lat, double lng, double r_m) //метод присваивани€
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
				return _r*ScaleCoef;
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
		ref class Line                 // ласс line дл€ хранени€ коэффициентов A, B, C уравнени€ пр€мой на плоскости
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
			void set_line(PointLatLng ^ P0, PointLatLng ^ P1)          //метод составл€ет уравнение пр€мой по двум точкам и сохран€ет коэффициенты
			{
				A = P1->Lng - P0->Lng;
				B = P0->Lat - P1->Lat;
				C = 0 - B * P0->Lng - A * P0->Lat;
			}
			int check_point(PointLatLng ^ P0)                  //метод дл€ проверки положени€ точки относительно пр€мой
			{
				if (A* P0->Lat + B * P0->Lng + C == 0)
				{
					return 0;                        // ¬озвращает 0, если точка лежит на пр€мой
				}
				else
					if (A* P0->Lat + B * P0->Lng + C < 0)
					{
						return -1;                   // ¬озвращает -1, если точка лежит в правой полуплоскости (условно)
					}
					else
						return 1;                    // ¬озвращает 1, если точка лежит в левой полуплоскости (условно)
			}


			double get_A()  //¬озвращает коэффициет A
			{
				return A;
			}
			double get_B()   //¬озвращает коэффициет B
			{
				return B;
			}
			double get_C()  //¬озвращает коэффициет C
			{
				return C;
			}
		};

		ref class WeightPoint {

			PointLatLng point;
			int weight;

		public:
			
			WeightPoint(PointLatLng Point,int Weight) {
				this->point = Point;
				this->weight = Weight;
			}

			PointLatLng Point() { return point; }
			void Point(PointLatLng p) { point = p; }

			int Weight() { return weight; }
			void Weight(int w) { weight = w; }
		};

		//void FindIntersect(geoPoint^ circle1, geoPoint^ circle2);
		//поиск точек пересечени€ двух окружностей
		void FindIntersect(geoPoint^ circle1, geoPoint^ circle2, List<PointLatLng>^ twoPoints);
		//факториал числа
		int Factorial(int n);
		//сортировка точек, использу€ уравнение пр€мой
		List<PointLatLng>^ SortPoint_Line(List<PointLatLng>^ in_p);
		//сортировка точек, кажда€ следующа€ ближайша€ к предыдущей
		List<PointLatLng>^ SortPoints(List<PointLatLng>^ in_p);
		//проверка нахождени€ точки во всем массиве окружностей
		bool InTheArea(PointLatLng point, List<geoPoint^>^ Coords);
		//проверка нахождени€ точки в трех окружност€х из всего массива
		bool InTheArea(PointLatLng point, int i, int j, int k, List<geoPoint^>^ Coords);
		//проверка нахождени€ точки в окружности
		bool InTheArea(PointLatLng point, int index, List<geoPoint^>^ Coords);
		//основной алгоритм триангул€ции
		List<PointLatLng>^ Triangulate(List<geoPoint^>^ Coords);
		//рандомное целое число
		int RangeRandInt(int min, int max);
		//рандомное число с плавающей точкой
		double RangeRandDouble(double min, double max);
		//деление окружности на равноудаленные точки
		List<PointLatLng>^ DivideCircle(PointLatLng center, double radius_km, int segments);
		//алгоритм нахождени€ области пересечени€ на основе общих дуг окружностей
		List<PointLatLng>^ SixthAttempt(List<geoPoint^>^ Coords);
		//находит область пересечени€ двух окружностей
		List<Evrika::EMath::WeightPoint^>^ Area(geoPoint^ point,int index, List<geoPoint^>^ Coords);
	}
}
