#include <iostream>
#include <time.h>
#include <windows.h>
#include "templates.h"

namespace Evrika {
	using namespace System;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	ref class Device;
	ref class TimeAndDate;

	String^ Device::IdInHex() {
		char* buf = new char[12];
		sprintf_s(buf, 12, "%X", Addr);
		String^ str = gcnew String(buf);
		delete[] buf;
		return str;
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

	double CyclesToMeters(uint32_t cycles) {
		double m = 0;
		const double cycle = 0.010;
		double t = cycles*cycle;
		uint32_t c = 300;
		m = (double)c*t;
		return m;
	}
	double TimeToMeters(double time_ns)
	{
		double m = 0;
		double c = 0.3;
		m = (double)c*time_ns;
		return m;
	}
	double dBToW(double lvl, double offset) {
		double w = 0;
		w = pow(10.0, (lvl - offset) / 10.0);
		return w;
	}
	double SignalLvlToMeters(double lvl, double tdB) {
		double m = 0, Kptx = 1, Kprx = 1, htx = 0.1, hrx = 1.5;
		double Ptx = dBToW(tdB, 30);
		double Prx = dBToW(lvl, 30);
		m = (Ptx*Kptx*Kprx*htx*hrx) / Prx;
		m = pow(m, 0.25);
		return m;
	}
	double ConvertToMeters(double RSSI, double n, double RSSI_In_1_m) {
		double m = 0;
		m = (- RSSI - RSSI_In_1_m) / (10 * n);
		m = pow(10, m);
		return m;
	}
	double LinCycleToMeters(uint32_t cycles, uint8_t bitrate)
	{
		switch (bitrate) {
		case 3:
			return 333;
		case 2:
			return (cycles - 268542) / 1.24;
		default:
			return 0;
		}
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
			temp[i] = (uint8_t)buf[i + offset];
		double num = 0;
		memcpy(&num, temp, 8);
		return num;
	}

	float GetFloatFromBuf(cli::array<wchar_t>^ buf, size_t offset)
	{
		uint8_t temp[4];
		for (int i = 0; i < 4; i++)
			temp[i] = (uint8_t)buf[i + offset];
		float num = 0;
		memcpy(&num, temp, 4);
		return num;
	}

	uint32_t ToInt32FromBuf(cli::array<wchar_t>^ rbuf, size_t offset)
	{
		return rbuf[offset] + (rbuf[offset + 1] << 8) + (rbuf[offset + 2] << 16) + (rbuf[offset + 3] << 24);
	}

	void Commands::ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id)
	{
		cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(14);
		//header
		rbuf[0] = 'e';
		rbuf[1] = 'v';
		//Addr
		PasteInBuffer(rbuf, 2, Addr);
		//msg_class
		rbuf[6] = msg_class;
		//msg_id
		rbuf[7] = msg_id;
		//msg_len
		rbuf[8] = 0x0;
		rbuf[9] = 0x0;
		//CK_A, CK_B
		CalcSum(rbuf, 12);	//10,11
		//Bluetooth compatibility
		rbuf[12] = '\r';	//CR
		rbuf[13] = '\n';	//LF
		port->Write(rbuf, 0, rbuf->Length);
	}
	void Commands::ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint8_t msg_data)
	{
		cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(14 + msg_len);
		//header
		rbuf[0] = 'e';
		rbuf[1] = 'v';
		//Addr
		PasteInBuffer(rbuf, 2, Addr);
		//msg_class
		rbuf[6] = msg_class;
		//msg_id
		rbuf[7] = msg_id;
		//msg_len
		rbuf[8] = (uint8_t)(msg_len >> 8);
		rbuf[9] = (uint8_t)msg_len;
		//msg_data
		rbuf[10] = msg_data;
		//CK_A, CK_B
		CalcSum(rbuf, 12 + msg_len);
		//Bluetooth compatibility
		rbuf[12 + msg_len] = '\r';	//CR
		rbuf[13 + msg_len] = '\n';	//LF
		port->Write(rbuf, 0, rbuf->Length);
	}
	void Commands::ConstructCMD(uint32_t Addr, uint8_t msg_class, uint8_t msg_id, uint16_t msg_len, uint32_t msg_data)
	{
		cli::array<unsigned char>^ rbuf = gcnew cli::array<unsigned char>(14 + msg_len);
		//header
		rbuf[0] = 'e';
		rbuf[1] = 'v';
		//Addr
		PasteInBuffer(rbuf, 2, Addr);
		//msg_class
		rbuf[6] = msg_class;
		//msg_id
		rbuf[7] = msg_id;
		//msg_len
		rbuf[8] = (uint8_t)(msg_len >> 8);
		rbuf[9] = (uint8_t)msg_len;
		//msg_data
		PasteInBuffer(rbuf, 10, msg_data);
		//CK_A, CK_B
		CalcSum(rbuf, 12 + msg_len);
		//Bluetooth compatibility
		rbuf[12 + msg_len] = '\r';	//CR
		rbuf[13 + msg_len] = '\n';	//LF
		port->Write(rbuf, 0, rbuf->Length);
	}
	void Commands::Class_0x0A::TestConnect()
	{
		ConstructCMD(NULL, 0x0A, 0);
	}
	void Commands::Class_0x0A::GetLocalAddr()
	{
		ConstructCMD(NULL, 0x0A, 1);
	}
	void Commands::Class_0x0A::GetVoltage(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0A, 2);
	}
	void Commands::Class_0x0A::GetRelayState(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0A, 0x88);
	}
	void Commands::Class_0x0A::SetRelayState(uint32_t Addr, uint8_t state)
	{
		ConstructCMD(Addr, 0x0A, 0x89, 1, state);
	}
	void Commands::Class_0x0A::ProgrammReset(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0A, 0x99);
	}
	void Commands::Class_0x0B::SetGPSPowerState(uint32_t Addr, uint8_t state)
	{
		ConstructCMD(Addr, 0x0B, 1, 1, state);
	}
	void Commands::Class_0x0B::GetGPSPowerState(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0B, 2);
	}
	void Commands::Class_0x0B::GetGPSStatus(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0B, 3);
	}
	void Commands::Class_0x0B::GetGPSPosition(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0B, 4);
	}
	void Commands::Class_0x0B::ToggleGPSAntenna(uint32_t Addr, uint8_t state)
	{
		ConstructCMD(Addr, 0x0B, 5, 1, state);
	}
	void Commands::Class_0x0B::GetGPSUsingAntenna(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0B, 6);
	}
	void Commands::Class_0x0C::WakeUp(uint32_t Addr, uint32_t Timeout)
	{
		ConstructCMD(Addr, 0x0C, 1, 4, Timeout);
	}
	void Commands::Class_0x0C::GetRadioTagsParam(uint32_t Addr, uint8_t Count)
	{
		ConstructCMD(Addr, 0x0C, 2, 1, Count);
	}
	void Commands::Class_0x0C::RequestRadioTagParam(uint32_t Addr, uint32_t TagAddress)
	{
		ConstructCMD(Addr, 0x0C, 5, 4, TagAddress);
	}
	void Commands::Class_0x0C::GetRadioTagParam(uint32_t Addr, uint32_t TagAddress)
	{
		ConstructCMD(Addr, 0x0C, 6, 4, TagAddress);
	}
	void Commands::Class_0x0C::ResetCC1101(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0C, 7);
	}
	void Commands::Class_0x0D::StartSearchRepeaters(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0D, 1);
	}
	void Commands::Class_0x0D::GetRepeatersParam(uint32_t Addr, uint8_t Count)
	{
		ConstructCMD(Addr, 0x0D, 2, 1, Count);
	}
	void Commands::Class_0x0D::GlobalResetRepeaters(uint32_t Addr)
	{
		ConstructCMD(Addr, 0x0D, 0x99);
	}
	void Repeater::GetInfo()
	{

	}
}