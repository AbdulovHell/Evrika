#include "templates.h"

namespace Evrika {
	using namespace System;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	ref class Device;
	ref class TimeAndDate;

	String^ Device::IdInHex() {
		char* buf = new char[12];
		sprintf_s(buf, 12, "%X", unique_id);
		String^ str = gcnew String(buf);
		delete[] buf;
		return str;
	}
	void Device::copy(Device^ _src) {
		unique_id = _src->unique_id;
		signal_lvl = _src->signal_lvl;
		signal_quality = _src->signal_quality;
		battery_lvl = _src->battery_lvl;
		work_mode = _src->work_mode;
		pWork_mode = _src->pWork_mode;
	}

	int TimeAndDate::GetCurrentTimeAndDate() {
		const time_t timer = time(NULL);

		char* b = new char[28];
		char* startPtr = b;
		errno_t err = ctime_s(b, 28, &timer);

		if (err) {
			MessageBoxA(0, "ctime_s err", "Exception", 0);
			delete[] b;
			return 0;
		}

		char* endPtr;
		endPtr = strstr(b, " ");
		char dow[4] = { 0,0,0,0 };
		memcpy(dow, b, 3);
		b = endPtr + 1;
		endPtr = strstr(b, " ");
		char mnth[4] = { 0,0,0,0 };
		memcpy(mnth, b, 3);
		b = endPtr + 1;
		day = (int)strtod(b, &endPtr);
		b = endPtr + 1;
		hours = (int)strtod(b, &endPtr);
		b = endPtr + 1;
		minutes = (int)strtod(b, &endPtr);
		b = endPtr + 1;
		seconds = (int)strtod(b, &endPtr);
		b = endPtr + 1;
		year = (int)strtod(b, &endPtr);

		if (!strcmp(mnth, "Jan")) month = 1;
		else if (!strcmp(mnth, "Feb")) month = 2;
		else if (!strcmp(mnth, "Mar")) month = 3;
		else if (!strcmp(mnth, "Apr")) month = 4;
		else if (!strcmp(mnth, "May")) month = 5;
		else if (!strcmp(mnth, "Jun")) month = 6;
		else if (!strcmp(mnth, "Jul")) month = 7;
		else if (!strcmp(mnth, "Aug")) month = 8;
		else if (!strcmp(mnth, "Sep")) month = 9;
		else if (!strcmp(mnth, "Oct")) month = 10;
		else if (!strcmp(mnth, "Nov")) month = 11;
		else if (!strcmp(mnth, "Dec")) month = 12;
		else month = 0;

		delete[] startPtr;
		return month;
	}
	String^ TimeAndDate::ToSysString() {
		String^ str = "" + day + "." + month + "." + year + " " + hours + "-" + minutes + "-" + seconds;
		return str;
	}
	void TimeAndDate::copy(TimeAndDate^ _td) {
		day = _td->day;
		month = _td->month;
		year = _td->year;
		hours = _td->hours;
		minutes = _td->minutes;
		seconds = _td->seconds;
	}

	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t wait_ms) {
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint16_t dummy)
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, CMDtype cmd) {
		cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(10);
		//ev
		rbuf[0] = 0x65;
		rbuf[1] = 0x76;
		//message class & ID
		switch (cmd)
		{
		case Evrika::CMDtype::CHECK_COM:
			rbuf[2] = 0x0A;
			rbuf[3] = 0x01;
			break;
		case Evrika::CMDtype::RESET:
			rbuf[2] = 0x0A;
			rbuf[3] = 0x02;
			break;
		case Evrika::CMDtype::GETGPS:
			rbuf[2] = 0x0B;
			rbuf[3] = 0x02;
			break;
		case Evrika::CMDtype::GPSSTAT:
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint8_t mode, uint32_t freq, uint8_t power, uint8_t att, uint8_t reserved) {
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, uint8_t cycles) {
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, bool enable) {
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
	bool ConstructCMD(System::IO::Ports::SerialPort^ port, uint32_t addr, bool enable) {
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

	double CyclesToMeters(int cycles) {
		double m = 0;
		const double cycle = 0.010;
		double t = cycles*cycle;
		uint32_t c = 300;
		m = (double)c*t;
		return m;
	}
	double dBToW(double lvl,double offset) {
		double w = 0;
		w = pow(10.0, (lvl - offset) / 10.0);
		return w;
	}
	double SignalLvlToMeters(double lvl,double tdB) {
		double m = 0,Kptx=1,Kprx=1,htx=0.5,hrx=1.5;
		double Ptx = dBToW(tdB,30);
		double Prx = dBToW(lvl,30);
		m = (Ptx*Kptx*Kprx*htx*hrx) / Prx;
		m = pow(m, 0.25);
		return m;
	}
	double ConvertToMeters(int RSSI, double n, double A) {
		double m = 0;
		m = (-RSSI - A) / (10 * n);
		m = pow(10, m);
		return m;
	}
	//CK_A[size-2],CK_B[size-1]
	void CalcSum(cli::array<unsigned char>^ buf, size_t size) {
		uint8_t CK_A = 0, CK_B = 0;
		for (size_t i = 2; i < size - 2; i++) {
			CK_A += buf[i];
			CK_B += CK_A;
		}
		buf[size - 1] = CK_B;
		buf[size - 2] = CK_A;
	}

	void PasteInBuffer(cli::array<unsigned char>^ buf, size_t offset, uint32_t num) {
		for (size_t i = offset; i < offset + 4; i++)
			buf[i] = (num & (0xFF << (8 * (i - offset)))) >> (8 * (i - offset));
	}

	double GetDoubleFromBuf(cli::array<wchar_t>^ buf, size_t offset)
	{
		uint8_t temp[8];
		for (int i = 0; i < 8; i++)
			temp[i] = buf[i + offset];
		double num = 0;
		memcpy(&num, temp, 8);
		return num;
	}

	float GetFloatFromBuf(cli::array<wchar_t>^ buf, size_t offset)
	{
		uint8_t temp[4];
		for (int i = 0; i < 4; i++)
			temp[i] = buf[i + offset];
		float num = 0;
		memcpy(&num, temp, 4);
		return num;
	}
	
}