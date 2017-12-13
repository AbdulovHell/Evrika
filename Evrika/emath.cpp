#include "emath.h"

using namespace GMap::NET;
using namespace System;
using namespace System::Collections::Generic;

//считает точки пересечения двух окружностей и рисует их
//void Evrika::EMath::FindIntersect(geoPoint ^ circle1, geoPoint ^ circle2)
//{	//return points and array size
//	double d, x31, x32, y31, y32, x0, x1, x2, y0, y1, y2, a, r0 = circle1->get_r() / 1000, r1 = circle2->get_r() / 1000;
//	System::Collections::Generic::List<GMap::NET::PointLatLng> ^Points = gcnew System::Collections::Generic::List<GMap::NET::PointLatLng>;
//	System::Collections::Generic::List<GMap::NET::PointLatLng> ^cPoints = gcnew System::Collections::Generic::List<GMap::NET::PointLatLng>;
//
//	double Z = Math::Cos(circle1->get_lat()*(Math::PI / 180));	//поправка на длинну мередиана
//
//	double A0, B0, C0;
//	//d = circle1->get_dist(circle2);
//	//r0 *= 111.11;
//	//r1 *= 111.11;
//	//listView1->Items->Clear();
//	y0 = circle1->get_lat();
//	y1 = circle2->get_lat();
//	x0 = circle1->get_lng();
//	x1 = circle2->get_lng();
//	//double x = (x1 - x0)*111.11*Z;
//	//double y = (y1 - y0)*111.11;
//	double y = circle2->get_lat() - circle1->get_lat();
//	double x = circle2->get_lng() - circle1->get_lng();
//	x *= 111.11*Z;
//	y *= 111.11;
//	d = Math::Sqrt(y*y + x*x);
//	//d = Math::Sqrt((y1 - y0)*(y1 - y0) + (x1 - x0)*(x1 - x0));
//	if (d > r0 + r1)
//		return;
//	if (d < Math::Abs(r0 - r1))
//		return;
//	a = ((r0 * r0 - r1 * r1) + d * d) / (2 * d);
//
//	y2 = (a / d) * y;
//	x2 = (a / d) * x;
//
//	A0 = x;
//	B0 = y;
//	C0 = -A0*x2 - B0*y2;
//
//	double alfa = Math::Acos(a / r0);  //угол между отрезком, который соединяет центры, и одним из радиусов первой окружности, проведённым в точку пересечения.
//									   //хз как арккосинус считается, поправь если что.
//									   //здесь требуется правильно считать a.
//	double cosOx = x / (Math::Sqrt(x*x + y*y)); // вычисляем синус и косинус угла между отрезком, который соединяет центры, и осью иксов
//	double sinOx = y / (Math::Sqrt(x*x + y*y));  //надо считать корень!)
//
//	double alfa0;             // смотрим на расположение отрезка по знаку sin/cos
//	if (sinOx >= 0)
//		alfa0 = Math::Acos(cosOx);  //первая и вторая четверть, угол положительный 
//	else
//		alfa0 = -Math::Acos(cosOx); // третья и четвёртая четверть, знак косинуса не важен, только знак синуса
//
//	double alfa1 = alfa0 + alfa;
//	double alfa2 = alfa0 - alfa;
//
//	if ((alfa1 == Math::PI / 2) || (alfa2 == Math::PI / 2) || (alfa1 == -Math::PI / 2) || (alfa2 == -Math::PI / 2))
//	{
//		//проверяем не равен какой-либо из углов пи на два или минус пи на 2. если хоть один из них равен
//		//то нельзя считать тангенс (он бесконечен), решение будет немного другим. Как пи пишется я не знаю.
//		if ((alfa1 == Math::PI / 2) || (alfa1 == -Math::PI / 2))
//		{
//			x31 = 0;
//			x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
//			y31 = -C0 / B0;
//			y32 = x32 * Math::Tan(alfa2);
//		}
//		if ((alfa2 == Math::PI / 2) || (alfa2 == -Math::PI / 2))
//		{
//			x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
//			x32 = 0;
//			y31 = x31 * Math::Tan(alfa1);
//			y32 = -C0 / B0;
//		}
//
//	}
//	else                //здесь собственно решение, если углы норм. тогда тг считать можно.
//	{
//		x31 = -C0 / (A0 + B0 * Math::Tan(alfa1));
//		x32 = -C0 / (A0 + B0 * Math::Tan(alfa2));
//		y31 = x31 * Math::Tan(alfa1);
//		y32 = x32 * Math::Tan(alfa2);
//	}
//
//	y2 /= 111.11;
//	x2 /= 111.11*Z;
//
//	x31 /= 111.11*Z;
//	x32 /= 111.11*Z;
//	y31 /= 111.11;
//	y32 /= 111.11;
//
//	Points->Add(PointLatLng(x0 + x31, y0 + y31));
//	Points->Add(PointLatLng(x0 + x32, y0 + y32));
//	cPoints->Add(PointLatLng(y0, x0));
//	cPoints->Add(PointLatLng(y1, x1));
//
//	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y2, x0 + x2), Markers::GMarkerGoogleType::purple));
//	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y31, x0 + x31), Markers::GMarkerGoogleType::red));
//	mrkrOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(y0 + y32, x0 + x32), Markers::GMarkerGoogleType::red));
//	GMapPolygon ^line = gcnew GMapPolygon(Points, "line0");
//	GMapPolygon ^lineC = gcnew GMapPolygon(cPoints, "line0");
//	line->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(50, Color::Red));
//	line->Stroke = gcnew Pen(Color::Red, 1);
//	lineC->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(50, Color::Blue));
//	lineC->Stroke = gcnew Pen(Color::Blue, 1);
//	areaOvrl->Polygons->Add(line);
//	areaOvrl->Polygons->Add(lineC);
//	return;
//}
//считает точки пересечения двух окружностей и сохраняет их
void Evrika::EMath::FindIntersect(geoPoint ^ circle1, geoPoint ^ circle2, List<PointLatLng>^ twoPoints)
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
	if (x == 0 || y == 0) return;	//точки одинаковы
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
//факториал числа
int Evrika::EMath::Factorial(int n)
{
	int res = 1;
	for (int i = 1; i < n + 1; i++)
		res *= i;
	return res;
}
//сортировка массива точек, каждая следующая точка ближайшая к предыдущей
List<PointLatLng>^ Evrika::EMath::SortPoint_Line(List<PointLatLng>^ in_p)
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
//проверка нахождения точки в любой из окружностей
bool Evrika::EMath::InTheArea(PointLatLng point, List<geoPoint^>^ Coords)
{
	bool result = true;
	for (int i = 0; i < Coords->Count; i++)
	{
		double r = geoPoint::GetDistanceToPointFrom(point, Coords[i]->get_pointLatLng()) * 1000;
		double rad = Coords[i]->get_r();
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
//проверка нахождения точки в пересечении трех окружностей с индексами i j k
bool Evrika::EMath::InTheArea(PointLatLng point, int i, int j, int k, List<geoPoint^>^ Coords) {
	bool result = true;
	double r1 = geoPoint::GetDistanceToPointFrom(point, Coords[i]->get_pointLatLng()) * 1000;
	double r2 = geoPoint::GetDistanceToPointFrom(point, Coords[j]->get_pointLatLng()) * 1000;
	double r3 = geoPoint::GetDistanceToPointFrom(point, Coords[k]->get_pointLatLng()) * 1000;
	double radius1 = Coords[i]->get_r();
	double radius2 = Coords[j]->get_r();
	double radius3 = Coords[k]->get_r();
	if ((r1 - 0.002*radius1 > radius1) || (r2 - 0.002*radius2 > radius2) || (r3 - 0.002*radius3 > radius3))
		result = false;
	return result;
}
bool Evrika::EMath::InTheArea(PointLatLng point, int index, List<geoPoint^>^ Coords)
{
	bool result = true;
	double r1 = geoPoint::GetDistanceToPointFrom(point, Coords[index]->get_pointLatLng()) * 1;
	double radius1 = Coords[index]->get_r();
	if (r1 - 0.002*radius1 > radius1)
		result = false;
	return result;
}
//триангуляция
List<PointLatLng>^ Evrika::EMath::Triangulate(List<geoPoint^>^ Coords)
{
	List<PointLatLng>^ area_points = gcnew List<PointLatLng>;
	List<int>^ mass = gcnew List<int>;
	//будем проверять каждую точку со всеми остальными
	for (int i = 0; i < Coords->Count; i++)
		for (int j = i + 1; j < Coords->Count; j++) {
			List<PointLatLng>^ tempPoints = gcnew List<PointLatLng>;
			//находим пересечения двух окружностей
			FindIntersect(Coords[i], Coords[j], tempPoints);
			if (tempPoints->Count == 0) {
				return gcnew List<PointLatLng>;	//пересечений нет
			}
			for (int p = 0; p < tempPoints->Count; p++) {
				bool duplicate = false;
				int index = -1;
				for (int f = 0; f < area_points->Count; f++)
				{
					if (tempPoints[p].Lat == area_points[f].Lat&&tempPoints[p].Lng == area_points[f].Lng)
					{
						duplicate = true;
						index = f;
						break;
					}
				}
				if (duplicate)
				{
					if (InTheArea(tempPoints[p], Coords)) {
						mass[index]++;
					}
				}
				else
				{
					if (InTheArea(tempPoints[p], Coords)) {
						area_points->Add(tempPoints[p]);
						mass->Add(1);
					}
				}
			}
		}
	//если точек составляющий пересечение больше 3, дополнительно сортируем
	if (area_points->Count > 3) area_points = SortPoint_Line(area_points);
	return area_points;
}
//возвращает случайное целое число
int Evrika::EMath::RangeRandInt(int min, int max)
{
	Random^ autoRand = gcnew Random;
	return autoRand->Next(min, max);
}
//возвращает случайное число с плавающей точкой
double Evrika::EMath::RangeRandDouble(double min, double max)
{
	Random^ autoRand = gcnew Random;
	double mult = autoRand->NextDouble();
	double num = min + (max - min)*mult;
	int temp = int(num * 100);
	return temp / 100.0;
}

List<PointLatLng>^ Evrika::EMath::DivideCircle(PointLatLng center, double radius_km, int segments)
{
	//int segments = 360;
	List<PointLatLng>^ gpollist = gcnew List<PointLatLng>();

	for (int i = 0; i < segments; i++)
		gpollist->Add(geoPoint::FindPointAtDistanceFrom(center, 2 * Math::PI*i / segments, radius_km));

	return gpollist;
}

List<PointLatLng>^ Evrika::EMath::SixthAttempt(List<geoPoint^>^ Coords)
{
	LatLngComparer^ cmpr = gcnew LatLngComparer();
	List<PointLatLng>^ points = gcnew List<PointLatLng>;
	for (int i = 0; i < Coords->Count - 1; i++) {
		//Dictionary<PointLatLng, int> mass;

		SortedList<PointLatLng, int>^ mass = gcnew SortedList<PointLatLng, int>(cmpr);
		List<PointLatLng>^ temp = DivideCircle(Coords[i]->get_pointLatLng(), Coords[i]->get_r(), 360);
		for (int n = 0; n < temp->Count; n++) {
			mass->Add(temp[n], 0);
		}
		for (int j = 1 + i; j < Coords->Count; j++) {
			for (int k = 0; k < mass->Count; k++) {
				if (InTheArea(mass->Keys[k], j, Coords)) {
					mass->Values[k] = mass->Values[k] + 1;
				}
			}
		}
		int max_mass = 0, cnt = 0;;
		for (int k = 0; k < mass->Count; k++) {
			if (mass->Values[k] > max_mass) {
				max_mass = mass->Values[k];
				cnt = 1;
			}
			else if (mass->Values[k] == max_mass) {
				cnt++;
			}
		}
		for (int k = 0; k < mass->Count; k++) {
			if (mass->Values[k] == max_mass) {
				points->Add(mass->Keys[k]);
			}
		}
	}
	return points;
}
