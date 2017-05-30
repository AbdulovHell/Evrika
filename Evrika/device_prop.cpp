#include <iostream>
#include "templates.h"
#include "mainform.h"
#include <Windows.h>
#include <Psapi.h>
#include "device_prop.h"

using namespace System::Collections::Generic;

void Evrika::device_prop::MeasDist()
{
	do {
		this->Invoke(gcnew Action<bool>(mainform::my_handle,&mainform::SetTimer),false);
		if (radioButton1->Checked) {	//RSSI
			List<int>^ RSSIs = gcnew List<int>;
			double mid = 0;
			for (int i = 0; i < MeasCycles; i++) {
				try {
					if (comport->IsOpen) {
						//ConstructCMD(comport, curDev->unique_id, (uint8_t)Decimal::ToInt16(numericUpDown1->Value));
						ConstructCMD(comport, curDev->unique_id, (uint16_t)NULL);
					}
					else {
						//закрыт, ошибк
						throw(gcnew IO::IOException("COM-порт закрыт"));
					}
				}
				catch (IO::IOException ^ioexception) {
					textBox1->AppendText("\r\n" + ioexception->Message);
				}
				if (!sMeasDist->WaitOne(1000)) {
					try {
						this->Invoke(gcnew Action<System::String^>(mainform::my_handle, &mainform::WriteLog), "Нету данных об измерении");
						this->Invoke(gcnew Action<bool>(mainform::my_handle, &mainform::SetTimer), true);
						return;
					}
					catch (...) {}
				}
				RSSIs->Add(curDev->signal_lvl);
				mid += curDev->signal_lvl;
			}
			mid /= RSSIs->Count;
			this->Invoke(gcnew Action<double>(this, &device_prop::DrawPoint),mid);
			double powers[] = { 0,3,6,9,12,15,20,27 };
			float dist_m = (float)(SignalLvlToMeters(mid, powers[power_index])*1.4);
			this->Invoke(gcnew Action<float>(this, &device_prop::print_meters), dist_m);
			this->Invoke(gcnew Action<float>(mainform::my_handle, &mainform::AddNewPoint), dist_m);
		}
		else if (radioButton2->Checked) {	//Time
			try {
				if (comport->IsOpen) {
					ConstructCMD(comport, curDev->unique_id, (uint8_t)MeasCycles);
				}
				else {
					//закрыт, ошибк
					throw(gcnew IO::IOException("COM-порт закрыт"));
				}
			}
			catch (IO::IOException ^ioexception) {
				textBox1->AppendText("\r\n" + ioexception->Message);
			}
			sMeasDist->WaitOne(10000);
			float dist_m = (float)ProceedPoints(global_cpu_cycles);
			this->Invoke(gcnew Action<float>(this, &device_prop::print_meters), dist_m);
			this->Invoke(gcnew Action<float>(mainform::my_handle, &mainform::AddNewPoint), dist_m);
		}
		this->Invoke(gcnew Action<System::String^>(mainform::my_handle, &mainform::WriteLog), "Точка добавлена");
		uint32_t sleep = 0;
		try {
			sleep = uint32_t::Parse(textBox6->Text);
		}
		catch (...) {
			//ошибка ввода
		}
		this->Invoke(gcnew Action<bool>(mainform::my_handle, &mainform::SetTimer), true);
		if (checkBox1->Checked) Sleep(sleep * 1000);
	} while (checkBox1->Checked);
}

void Evrika::device_prop::print_meters(float m)
{
	label6->Text = m.ToString();
}

void Evrika::device_prop::DrawPoint(double p)
{
	chart1->Series[0]->Points->Add(p);
}

void Evrika::device_prop::SaveCycles(List<int64_t>^ cpu_cycles)
{
	global_cpu_cycles = cpu_cycles;
}

double Evrika::device_prop::ProceedPoints(List<int64_t>^ cpu_cycles)
{
	int64_t kMid = 0, mid = 0;
	for (int i = 0; i < cpu_cycles->Count; i++) {
		cpu_cycles[i] /= 2;
		mid += cpu_cycles[i];
	}
	mid /= cpu_cycles->Count;
	for (int i = 0; i < cpu_cycles->Count; i++)
	{
		if ((cpu_cycles[i] > (mid + 300)) || (cpu_cycles[i] < (-800 - mid)))
			cpu_cycles[i] = mid;
		if (i == 0 && ststate) {
			cycles_filt->SetState((double)cpu_cycles[i], 0.1);
			ststate = false;
		}
		cycles_filt->Correct((double)cpu_cycles[i]);
		kMid += (int64_t)cycles_filt->State;
	}
	kMid /= cpu_cycles->Count;
	//113405 - 100k
	//1110995 - ?
	//1074215
	last_num = kMid;
	int m_c = kMid - offset;
	return CyclesToMeters(m_c);
}

System::Void Evrika::device_prop::recalc(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (dynamic_cast<TextBox^>(sender) == textBox2) {
			int m = int::Parse(textBox2->Text);
			uint32_t c = 300000000;
			double t = (double)m / (double)c;
			const double cycle = 0.000000010;
			int32_t cycles = (int32_t)(t / cycle);
			textBox3->TextChanged -= gcnew System::EventHandler(this, &device_prop::recalc);
			textBox3->Text = cycles.ToString();
			textBox3->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
		}
		else if (dynamic_cast<TextBox^>(sender) == textBox3) {
			int32_t cycles = int::Parse(textBox3->Text);
			const double cycle = 0.000000010;
			double t = cycles*cycle;
			uint32_t c = 300000000;
			double m = (double)c*t;
			textBox2->TextChanged -= gcnew System::EventHandler(this, &device_prop::recalc);
			textBox2->Text = m.ToString();
			textBox2->TextChanged += gcnew System::EventHandler(this, &device_prop::recalc);
		}
	}
	catch (...) {
		MessageBoxA(0, "pzdc", "Device_prop exception", 0);
	}
}

System::Void Evrika::device_prop::change_dist_meas_method(System::Object ^ sender, System::EventArgs ^ e)
{
	if (radioButton1->Checked) {	//RSSI
		numericUpDown1->Value = 10;
		ConstructCMD(comport, curDev->unique_id, false);
	}
	else if (radioButton2->Checked) {	//Time
		numericUpDown1->Value = 50;
		ConstructCMD(comport, curDev->unique_id, true);
	}
}
