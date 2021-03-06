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

		ref class geoPoint {                 //����� geoPoint ��� �������� ��������� �����
		private:
			double _lat, _lng, _r;	//�������, �� � ��������					
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
			geoPoint(const geoPoint %c)   // ����������� �����������
			{
				_lat = c._lat;
				_lng = c._lng;
				_name = c._name;
				_r = c._r;
			}
			void set_point(double lat, double lng, double r_m) //����� ������������
			{
				_lat = lat;
				_lng = lng;
				_r = r_m;
			}
			double get_lat()                    //���������� ���������� � �����
			{
				return _lat;
			}
			double get_lng()                     //���������� ���������� � �����
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
		ref class Line                 //����� line ��� �������� ������������� A, B, C ��������� ������ �� ���������
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
			void set_line(PointLatLng ^ P0, PointLatLng ^ P1)          //����� ���������� ��������� ������ �� ���� ������ � ��������� ������������
			{
				A = P1->Lng - P0->Lng;
				B = P0->Lat - P1->Lat;
				C = 0 - B * P0->Lng - A * P0->Lat;
			}
			int check_point(PointLatLng ^ P0)                  //����� ��� �������� ��������� ����� ������������ ������
			{
				if (A* P0->Lat + B * P0->Lng + C == 0)
				{
					return 0;                        // ���������� 0, ���� ����� ����� �� ������
				}
				else
					if (A* P0->Lat + B * P0->Lng + C < 0)
					{
						return -1;                   // ���������� -1, ���� ����� ����� � ������ ������������� (�������)
					}
					else
						return 1;                    // ���������� 1, ���� ����� ����� � ����� ������������� (�������)
			}


			double get_A()  //���������� ���������� A
			{
				return A;
			}
			double get_B()   //���������� ���������� B
			{
				return B;
			}
			double get_C()  //���������� ���������� C
			{
				return C;
			}
		};

		ref class WeightPoint {

			PointLatLng point;
			int weight;

		public:

			WeightPoint(PointLatLng Point, int Weight) {
				this->point = Point;
				this->weight = Weight;
			}

			PointLatLng Point() { return point; }
			void Point(PointLatLng p) { point = p; }

			int Weight() { return weight; }
			void Weight(int w) { weight = w; }
		};

		//void FindIntersect(geoPoint^ circle1, geoPoint^ circle2);
		//����� ����� ����������� ���� �����������
		void FindIntersect(geoPoint^ circle1, geoPoint^ circle2, List<PointLatLng>^ twoPoints);
		//��������� �����
		int Factorial(int n);
		//���������� �����, ��������� ��������� ������
		List<PointLatLng>^ SortPoint_Line(List<PointLatLng>^ in_p);
		//���������� �����, ������ ��������� ��������� � ����������
		List<PointLatLng>^ SortPoints(List<PointLatLng>^ in_p);
		//�������� ���������� ����� �� ���� ������� �����������
		bool InTheArea(PointLatLng point, List<geoPoint^>^ Coords);
		//�������� ���������� ����� � ���� ����������� �� ����� �������
		bool InTheArea(PointLatLng point, int i, int j, int k, List<geoPoint^>^ Coords);
		//�������� ���������� ����� � ����������
		bool InTheArea(PointLatLng point, int index, List<geoPoint^>^ Coords);
		//�������� �������� ������������
		List<PointLatLng>^ Triangulate(List<geoPoint^>^ Coords);
		//��������� ����� �����
		int RangeRandInt(int min, int max);
		//��������� ����� � ��������� ������
		double RangeRandDouble(double min, double max);
		//�� ��������, ��������
		bool isIntersects(List<geoPoint^>^ Coords,int index);
		//
		List<geoPoint^>^ FilterCoords(List<geoPoint^>^ Coords);
		//������� ���������� �� �������������� �����
		List<PointLatLng>^ DivideCircle(PointLatLng center, double radius_km, int segments);
		//�������� ���������� ������� ����������� �� ������ ����� ��� �����������
		List<PointLatLng>^ SixthAttempt(List<geoPoint^>^ Coords);
		//������� ������� ����������� ���� �����������
		List<Evrika::EMath::WeightPoint^>^ Area(geoPoint^ point, int index, List<geoPoint^>^ Coords);
	}

	namespace Filters {

		public ref class KalmanFilter {
			double X0, P0, F, H, R, Q, Covariance, B;

		public:
			double State;
			bool first = true;

			//1, 1, 200, 15
			KalmanFilter() {
				Q = 15;
				R = 200;
				F = 1;
				H = 1;
				B = 0;
			}

			KalmanFilter(double f, double h, double r, double q) {
				Q = q;
				R = r;
				F = f;
				H = h;
				B = 0;
			}

			void SetState(double state, double covariance) {
				State = state;
				Covariance = covariance;
				first = false;
			}

			void Reset() {
				first = true;
			}

			void Correct(double data) {
				X0 = F * State;
				P0 = F * Covariance * F + Q;

				double K = H * P0 / (H * P0 * H + R);
				State = X0 + K * (data - H * X0);
				Covariance = (1 - K * H) * P0;
			}
		};

		template<typename T, int s> class CenterFilter {
			double coefH[3] = { 0.1,0.25,0.5 };
			double coefL[3] = { 1.1,1.25,1.5 };
			T *buf;
			unsigned int limit = s;
			unsigned int it = 0;
			T res;

		public:
			bool Add(T num) {
				if (buf == nullptr) {
					buf = new T(limit);
					it = 0;
				}
				if (it < limit) {
					buf[it++] = num;
					return false;
				}

				T mid = 0;
				unsigned int cnt = limit;
				for (int i = 0; i < limit; i++)
					mid += buf[i];
				mid /= limit;

				T Hl = mid*coefH[2];
				T Ll = mid*coefL[2];

				cnt = 0;
				for (int i = 0; i < limit; i++)
					if (buf[i] >= Ll && buf[i] <= Hl)
						cnt++;

				T *step1 = new T(cnt);
				unsigned int step1it = 0;
				for (int i = 0; i < limit; i++)
					if (buf[i] >= Ll && buf[i] <= Hl) {
						step1[step1it++] = buf[i];
					}

				T step1mid = 0;
				for (int i = 0; i < cnt; i++)
					step1mid += step1[i];
				step1mid /= cnt;

				Hl = mid*coefH[1];
				Ll = mid*coefL[1];

				unsigned int step2cnt = 0;
				for (int i = 0; i < cnt; i++)
					if (step1[i] >= Ll && step1[i] <= Hl)
						step2cnt++;

				T *step2 = new T(step2cnt);
				unsigned int step2it = 0;
				for (int i = 0; i < step2cnt; i++)
					if (step1[i] >= Ll && step1[i] <= Hl) {
						step2[step2it++] = step1[i];
					}

				T step2mid = 0;
				for (int i = 0; i < step2cnt; i++)
					step2mid += step2[i];
				step2mid /= step2cnt;

				if (step2cnt == 1) {
					res = step2mid;
					return true;
				}

				Hl = mid*coefH[0];
				Ll = mid*coefL[0];

				unsigned int step3cnt = 0;
				for (int i = 0; i < step2cnt; i++)
					if (step2[i] >= Ll && step2[i] <= Hl)
						step3cnt++;

				T *step3 = new T(step3cnt);
				unsigned int step3it = 0;
				for (int i = 0; i < step3cnt; i++)
					if (step2[i] >= Ll && step2[i] <= Hl) {
						step3[step3it++] = step2[i];
					}

				T step3mid = 0;
				for (int i = 0; i < step3cnt; i++)
					step3mid += step3[i];
				step3mid /= step3cnt;

				res = step3mid;

				return true;
			}

			T Result() {
				return res;
			}

			void Reset() {
				it = 0;
				max = 0;
				min = 5000000;
				mid = 0;
				delete[] buf;
			}
			void Reset(unsigned int Limit) {
				limit = Limit;
				it = 0;
				max = 0;
				min = 5000000;
				mid = 0;
				delete[] buf;
			}
		};

		template<typename T, int s> class MedianFilter {
			T buf[s];
			unsigned int size = s;
			bool first = true;
			unsigned int it = 0;
		public:
			void Correct(T num) {
				if (first) {
					it = 0;
					first = false;
					for (unsigned int i = 0; i < size; i++)
						buf[i] = num;
				}
				else {
					buf[it] = num;
				}
				it++;
				if (it > size - 1)
					it = 0;
			}
			T State() {
				T res = 0;
				for (unsigned int i = 0; i < size; i++)
					res += buf[i];
				res /= size;
				return res;
			}
			void Reset() {
				first = true;
			}
		};

		extern MedianFilter<double, 10>* mfilt;
		extern CenterFilter<double, 10> cfilt;
	}
}
