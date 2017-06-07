#include "mainform.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(cli::array<String^>^ args) {
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it
	Application::Run(gcnew CmdTest::mainform());
	return 0;
}

bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t wait_ms) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(14);//+6+len+CKA+CKB+CR+LF
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	rbuf[2] = 0x0C;
	rbuf[3] = 0x01;
	rbuf[4] = 0x00;
	rbuf[5] = 0x04;

	PasteInBuffer(rbuf, 6, wait_ms);//6,7,8,9

	CalcSum(rbuf, 12);	//10,11

	rbuf[12] = '\r';	//CR
	rbuf[13] = '\n';	//LF

	port->Write(rbuf, 0, 14);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint16_t dummy)
{
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(14);//+6+len+CKA+CKB+CR+LF
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	rbuf[2] = 0x0C;
	rbuf[3] = 0x05;
	rbuf[4] = 0x00;
	rbuf[5] = 0x04;

	PasteInBuffer(rbuf, 6, addr);//6,7,8,9

	CalcSum(rbuf, 12);	//10,11

	rbuf[12] = '\r';	//CR
	rbuf[13] = '\n';	//LF

	port->Write(rbuf, 0, 14);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, CMDtype cmd) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(10);
	//ev
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	//message class & ID
	switch (cmd)
	{
	case CMDtype::CHECK_COM:
		rbuf[2] = 0x0A;
		rbuf[3] = 0x01;
		break;
	case CMDtype::RESET:
		rbuf[2] = 0x0A;
		rbuf[3] = 0x02;
		break;
	case CMDtype::GETGPS:
		rbuf[2] = 0x0B;
		rbuf[3] = 0x02;
		break;
	case CMDtype::GPSSTAT:
		rbuf[2] = 0x0B;
		rbuf[3] = 0x03;
		break;
	default:
		break;
	}
	//len
	rbuf[4] = 0x00;
	rbuf[5] = 0x00;

	CalcSum(rbuf, 8);//6,7

	rbuf[8] = '\r';
	rbuf[9] = '\n';

	port->Write(rbuf, 0, 10);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint8_t mode, uint32_t freq, uint8_t power, uint8_t att, uint8_t reserved) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(22);
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	rbuf[2] = 0x0C;
	rbuf[3] = 0x03;
	rbuf[4] = 0x00;
	rbuf[5] = 0x0C;

	PasteInBuffer(rbuf, 6, addr);
	rbuf[10] = mode;
	PasteInBuffer(rbuf, 11, freq);
	rbuf[15] = power;
	rbuf[16] = att;
	rbuf[17] = reserved;

	CalcSum(rbuf, 20);

	rbuf[20] = '\r';
	rbuf[21] = '\n';

	port->Write(rbuf, 0, 22);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint8_t cycles) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(15);
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	rbuf[2] = 0x0C;
	rbuf[3] = 0x02;
	rbuf[4] = 0x00;
	rbuf[5] = 0x05;

	PasteInBuffer(rbuf, 6, addr);
	rbuf[10] = cycles;

	CalcSum(rbuf, 13);

	rbuf[13] = '\r';
	rbuf[14] = '\n';

	port->Write(rbuf, 0, 15);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, bool enable) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(11);
	//ev
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	//message class & ID
	rbuf[2] = 0x0B;
	rbuf[3] = 0x01;
	//len
	rbuf[4] = 0x00;
	rbuf[5] = 0x01;

	rbuf[6] = enable;
	CalcSum(rbuf, 9);

	rbuf[9] = '\r';
	rbuf[10] = '\n';

	port->Write(rbuf, 0, 11);

	return true;
}
bool CmdTest::mainform::ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, bool enable) {
	cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(15);
	//ev
	rbuf[0] = 0x65;
	rbuf[1] = 0x76;
	//message class & ID
	rbuf[2] = 0x0C;
	rbuf[3] = 0x04;
	//len
	rbuf[4] = 0x00;
	rbuf[5] = 0x05;

	PasteInBuffer(rbuf, 6, addr);
	rbuf[10] = enable;
	CalcSum(rbuf, 13);

	rbuf[13] = '\r';
	rbuf[14] = '\n';

	port->Write(rbuf, 0, 15);

	return true;
}

void CmdTest::mainform::CalcSum(cli::array<unsigned char>^ buf, size_t size) {
	uint8_t CK_A = 0, CK_B = 0;
	for (size_t i = 2; i < size - 2; i++) {
		CK_A += buf[i];
		CK_B += CK_A;
	}
	buf[size - 1] = CK_B;
	buf[size - 2] = CK_A;
}

void CmdTest::mainform::PasteInBuffer(cli::array<unsigned char>^ buf, size_t offset, uint32_t num) {
	for (size_t i = offset; i < offset + 4; i++)
		buf[i] = (num & (0xFF << (8 * (i - offset)))) >> (8 * (i - offset));
}

bool CmdTest::mainform::CheckSum(cli::array<wchar_t>^ rbuf)
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

void CmdTest::mainform::EnumCOMs()
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
						ConstructCMD(serialPort1, CMDtype::CHECK_COM);
						sEnumCom->WaitOne(10000);	//TODO: настроить
						if (isOurCom) {
							//this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), serialPort1->PortName);
							this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ найден по " + serialPort1->PortName);
							LastStateIsOpen = true;
							return;
						}
					}
				}
				catch (Exception^ e) {
					this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), e->Message);
				}
				Threading::Thread::Sleep(100);
			}
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ не найден.");
			//this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), "COM?");
			LastStateIsOpen = false;
		}
		else {
			this->Invoke(gcnew Action<String^>(this, &mainform::WriteLog), "ДЦ не найден.");
			//this->Invoke(gcnew Action<String^>(this, &mainform::WriteToComStat), "COM?");
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

System::Void CmdTest::mainform::serialPort1_DataReceived(System::Object ^ sender, System::IO::Ports::SerialDataReceivedEventArgs ^ e)
{
	cli::array<wchar_t>^ rbuf = gcnew cli::array<wchar_t>(512);
	try {
		for (int i = 0; i < 512; i++)
			rbuf[i] = serialPort1->ReadByte();

		this->Invoke(gcnew Action<cli::array<wchar_t>^>(this, &mainform::ParseDeviceBuffer), rbuf);
	}
	catch (...) {

	}
}

System::Void CmdTest::mainform::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Threading::Thread^ connthrd = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &mainform::EnumCOMs));
	connthrd->Start();
}

System::Void CmdTest::mainform::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	switch (comboBox1->SelectedIndex) {
	case 0:
		ConstructCMD(serialPort1, (uint32_t)3000);
		break;
	case 1:
		ConstructCMD(serialPort1, TextToId(textBox2->Text), comboBox3->SelectedIndex, 900000000, comboBox2->SelectedIndex, NULL, NULL);
		break;
	case 2:
		mode = !mode;
		ConstructCMD(serialPort1, TextToId(textBox2->Text), mode);
		break;
	case 3:
		ConstructCMD(serialPort1, TextToId(textBox2->Text), (uint8_t)20);
		break;
	case 4:

		break;
	case 5:
		ConstructCMD(serialPort1,CMDtype::RESET);
		break;
	case 6:
		ConstructCMD(serialPort1, TextToId(textBox2->Text), (uint16_t)NULL);
		break;
	default:
		break;
	}
}

void CmdTest::mainform::ParseDeviceBuffer(cli::array<wchar_t>^ rbuf)
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
		case 0x01:/*
			if (eGPS)
				WriteLog("GPS включен");
			else
				WriteLog("GPS выключен");*/
			break;
		case 0x02:
		{
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
			////test
			///*{
			//GMarkerGoogle^ marker = gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::red_small);
			//mrkrOvrl->Markers->Add(marker);

			//GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			//circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Red));
			//circ->Stroke = gcnew Pen(Color::Red, 1);
			//areaOvrl->Polygons->Add(circ);
			//}*/
			//myPos->GetState(&lat, &lng, &HDOP, &height);
			//toolStripStatusLabel3->Text = "Sat: " + satellites;
			//toolStripStatusLabel3->Visible = true;
			//toolStripStatusLabel4->Text = "HDOP: " + (float)HDOP;
			//toolStripStatusLabel4->Visible = true;
			//toolStripStatusLabel5->Text = "H: " + (float)height + " m";
			//toolStripStatusLabel5->Visible = true;
			///*myPosOvrl->Clear();
			//myPosOvrl->Markers->Add(gcnew Markers::GMarkerGoogle(PointLatLng(lat, lng), Markers::GMarkerGoogleType::blue_small));
			//GMapPolygon ^circ = gcnew GMapPolygon(geoPoint::CreateCircle(PointLatLng(lat, lng), HDOP), "circ");
			//circ->Fill = gcnew SolidBrush(System::Drawing::Color::FromArgb(10, Color::Blue));
			//circ->Stroke = gcnew Pen(Color::Blue, 1);
			//myPosOvrl->Polygons->Add(circ);*/
			//my_pos_accepted = true;
			////sPointReciver->Release();
		}
		break;
		case 0x03:
		{
			//GPS_KnownPos = rbuf[6];
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
			int devices = len / 8;	//количество устройств в буфере
			//парсинг буфера в список у-в
			WriteLog("dev cnt: " + devices.ToString());
			for (int i = 0; i < devices; i++) {	//массив у-в в список у-в
				int addr = rbuf[6 + 8 * i] + (rbuf[7 + 8 * i] << 8) + (rbuf[8 + 8 * i] << 16) + (rbuf[9 + 8 * i] << 24);
				WriteLog("id: " + IdInHex(addr) + " RSSI: " + ((char)rbuf[10 + 8 * i]).ToString());
			}
		}
		break;
		case 0x02:	//резутат измерения времени
		{
			//invoke в device_prop
			int size = (rbuf[4] << 8) + rbuf[5];
			int count = size / 5;
			Generic::List<int>^ sign_lvls = gcnew Generic::List<int>;
			Generic::List<int64_t>^ cycles = gcnew Generic::List<int64_t>;
			int midRSSI = 0;
			for (int i = 0; i < count; i++) {
				sign_lvls->Add((char)(rbuf[6 + 5 * i]));
				cycles->Add(rbuf[7 + 5 * i] + (rbuf[8 + 5 * i] << 8) + (rbuf[9 + 5 * i] << 16) + (rbuf[10 + 5 * i] << 24));
				midRSSI += (char)(rbuf[6 + 5 * i]);
			}
			midRSSI /= sign_lvls->Count;
			if (cycles->Count == 0) return;
			try {
				//device_prop::hDevice_prop->Invoke(gcnew Action< List<int64_t>^ >(device_prop::hDevice_prop, &device_prop::SaveCycles), cycles);
				WriteLog("cycles count: "+cycles->Count.ToString()+" midRSSI: "+ midRSSI.ToString());
			}
			catch (...) {

			}
		}
		break;
		case 0x03:	//изменение параметров метки (полоса, мощность)
		{
			if (rbuf[6]) {
				//device_prop::sMeasDist->Release();
				WriteLog("Параметры изменены");
			}
			else {
				//device_prop::sMeasDist->Release();
				WriteLog("Ошибка при изменении параметров");
			}
		}
		break;
		case 0x04:	//смена режима измерения расстояния на временной метод
		{
			//device_prop::sMeasDist->Release();
			WriteLog("Режим измерения задержки");
		}
		break;
		case 0x05:	//базовая информация о метке
		{
			//Device^ tempdev;
			////парсинг буфера в список у-в
			int addr = rbuf[6] + (rbuf[7] << 8) + (rbuf[8] << 16) + (rbuf[9] << 24);
			//int raw_v = rbuf[12];
			//double volt = raw_v >> 4;
			//volt += ((double)(raw_v & 0xF)) / 10.0;
			//tempdev = gcnew Device(addr, (char)rbuf[10], rbuf[11], volt, rbuf[13], NULL);
			////сравнение и обновление у-в, которые уже были в памяти
			//for (int i = 0; i < Devices->Count; i++)
			//	if (Devices[i]->unique_id == tempdev->unique_id)
			//		Devices[i]->copy(tempdev);
			////обновление окон св-в
			//update_prop_windows();
			////маякнуть окну св-в об изменении статов
			//device_prop::sMeasDist->Release();
			////обновление списка у-в
			//update_device_list();
			WriteLog("id: " + IdInHex(addr) + " RSSI: " + ((char)rbuf[10]).ToString());
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
